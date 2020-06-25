#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <vector>
#include <random>
#include <algorithm>
#include <Windows.h>
#include <fstream>
/* 
KORIMBOCUS Muhammad Ikhlas
1910627

----MATHEMATICS TOOL FOR GRADE 3------

This program contains 6 topics in the form of arithmetic questions and quizes for mathematics grade 3.
A calculator utility and user stats option is also included.
Userinfo.uom stores data such as last topic attempted, total score, total questions etc and will be automatically generated if the user is new.
Objects.uom contains names of random object, it is used in two quizes. Userinfo.uom contains information about the user, both are loaded when the program executes.
Most topic requires the user to input number of questions to attempt.
the score is computed and user progress is saved at the end every quiz.

The topics are:
1. Geometry 
2. Numbers
3. Weight [Accessed through measures]
4. Money [Accessed through measures]
5. Capacity [Accessed through measures]
6. Ascending/Descending orders

Additional:
1. User stats.
2. Calculator utility.

*/
using namespace std;

ifstream readuserdata; //to read userinfo
ofstream writeuserdata; //to write to userinfo
HANDLE hConsole; //handle for colours

string answer;
double numbercorrect = 0; //used to calculate score

double finalscore = 0; //used to calculate score
int globalnumberques = 0; //used to specify how many question user wants to attempt
double correctans; //the correct answer in numeral question, gets incremented everytime ans is correct

//--------------------
//this class contains data and methods of the user profile
class User { 
public:
	string username;
	string LastTopic;
	double totalcorrect;//part of loaded user loaded data
	int wronganswer;
	double totalattempts;
	
	

	void defaultuser();
	void displayinfo();
	void userinitialize(); //load user data in program
	void SaveProgress(); //user progress in userinfo.txt 
}; 


void User::defaultuser() {
	username = "x";
	totalcorrect = 0;
	wronganswer = 0;
	totalattempts = 0; //default values when new user created
	LastTopic = "NaN";
	
}
//method to display user information

void User::displayinfo() {
	double finalscore = (totalcorrect / totalattempts) * 100;
	system("CLS");

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	cout << "\t\t" << username << endl;

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "Number of questions attempted: " << totalattempts << endl;
	cout << "Number of correct answers: " << totalcorrect << endl;
	cout << "Number of wrong answers: " << wronganswer << endl;
	cout << "Your average score performance: " << finalscore << endl;
	cout << "Last activity/topic: " << LastTopic << endl << endl;

	if (finalscore >= 50) {
		cout << "You are doing well, keep it up! \n";
	}
	else {
		SetConsoleTextAttribute
		(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY );
		cout << "Your score doesn't look so good, you need to practice more\n";
	}
	

}
//method to load the userfile, if not found ask for username.
void User::userinitialize() {
	


	readuserdata.open("userinfo.uom");
	if (!readuserdata) { //if no savedata found, create new user.
		cout << "-no save data found\n\n\n Please enter your name: ";
		cin >> username;
		writeuserdata.open("userinfo.uom");
		writeuserdata << username;

	}

	readuserdata >> username;
	readuserdata >> totalcorrect;
	readuserdata >> wronganswer;
	readuserdata >> totalattempts;
	readuserdata >> LastTopic;
	cout << " Welcome back, " << username << "! \n";
	readuserdata.close();
	Sleep(300);
	system("CLS");

}

//method to update the user file
void User::SaveProgress() {

	cout << "saving progress\n";
	writeuserdata.open("userinfo.uom");
	writeuserdata << username << endl << totalcorrect << endl << wronganswer << endl << totalattempts << endl << LastTopic;
	writeuserdata.close();

}

User user1;
//--------------------

class Shape { //class used in verticesidequiz() function
public:
	string vertex, sides, type;
	Shape(string, string, string);
	~Shape();
	Shape();
};

Shape::Shape() {
	vertex = "x";
	sides = "x";
	type = "x";
}
Shape::~Shape() {};
Shape::Shape(string x, string y, string t) {

	vertex = x;
	sides = y;
	type = t;
}

//-------------
//this class is for storing the objects and their weights
class RandomObjects {
public:

	string object; //don't need default constructors for this class
	int weight;

};

//vector of the above class for multiple objects
vector <RandomObjects> ListObject(0); //initializes lists of objects with its weight
//--------------------------------

//this function loads and initializes the contents of the object.uom
void LoadObjects() {


	ifstream objectfile("objects.uom"); //object list is in ascending order wrt weight


	string objectname;



	if (!objectfile) {
		cout << "objects file not found\n"; //if the list of objects not found
		system("pause");
		return;
	}


	for (int i = 0; !objectfile.eof(); i++) {

		objectfile >> objectname;
		ListObject.push_back({ objectname, i });

	}


}

//this function calculates score for a quiz as well as updates the user profile. It is called at the end of every quiz
void ProcessScore(double numbcorrect, double numberques) {

	float finalscore = (numbcorrect / numberques) * 100;
	SetConsoleTextAttribute
	(hConsole, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
	//aeshetic purpose



	cout << "Your score is: " << finalscore << endl;
	cout << "You answered " << numbcorrect << " questions correctly!\n";
	user1.totalcorrect += numbcorrect;

	
	if (finalscore >= 50) {
		cout << "Very good! Keep it up!\n";
	}
	else
	{
		SetConsoleTextAttribute
		(hConsole, BACKGROUND_RED );
		cout << "Keep trying, you will do better next time!\n";
	}


	user1.wronganswer += (numberques - numbcorrect); //update the user's wrong answers;
	user1.totalattempts = user1.wronganswer + user1.totalcorrect;
	globalnumberques = 0;
	numbercorrect = 0;
	system("pause");
	
	

}


//generate random numbers 0 - g
int RandomNum(int g) {

	
	int generated = (rand() % g) + 1;
	return generated;
	
}



//the function below generates questions on a shape, it is called in void geometry(). This function can generate 3 different style of question on a shape.
void VerticeSideQuiz(string s, string v, string stype) { //the parameters are the CORRECT answers!
	Shape SCreate;

	//2 types of question, vertice and edge.

	SCreate.vertex = v;
	SCreate.sides = s;
	SCreate.type = stype;

	string geoans;
	int whichquestion = 0;


	string question1 = "A " + SCreate.type + " has how many vertices?"; //vertice
	string question2 = "A " + SCreate.type + " has how many sides?"; //edge
	string question3 = "Which shape has " + SCreate.vertex + " vertices and " + SCreate.sides + " sides and is uniform?"; //shape
	string arrques[] = { question1,question2,question3 };


	

	SetConsoleTextAttribute
	(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);




	
	whichquestion = RandomNum(3); //generate random type of question for same shape
	switch (whichquestion) {

	case 1:
		cout << arrques[0] << endl;
		whichquestion = 1; //just making sure and forcing it for checking purpose
		break;

	case 2:
		cout << arrques[1] << endl;
		whichquestion = 2;
		break;

	case 3:
		cout << arrques[2] << endl;
		whichquestion = 3;
		break;

	default: cout << arrques[0] << endl;
		whichquestion = 1;
		break;
	}


	cin >> answer; // input answer
	

	if (whichquestion == 1) {
		if (answer == SCreate.vertex) {
			cout << "CORRECT\n";
			user1.totalcorrect++;
			numbercorrect++; //# of correct answers for geometry
		}
		else {
			cout << "A " << SCreate.type << " has " << SCreate.vertex << " vertices.\n";
		}
	}
	else

		if (whichquestion == 2) {
			if (answer == SCreate.sides) {
				cout << "CORRECT\n";
				user1.totalcorrect++;
				numbercorrect++;
			}
			else
				cout << "A " << SCreate.type << " has " << SCreate.sides << " sides.\n";
		}
		else

			
			if (whichquestion == 3) {
				if (answer == SCreate.type) 
				{
					cout << "CORRECT\n";
					user1.totalcorrect++;
					numbercorrect++;
				}
				else
				{
					cout << " That's a " << SCreate.type << " !\n";
				}

			}

	

};

//geometry topic, user is assesed on vertices and sides of shapes, the correct answers are inside the shapevec vector. More shapes can be easily added in the vector itself.

void Geometry() {

	struct shapeanswers {
		string side;
		string vert;
		string sname;
	};

	int accessvector = 0; //index of vector

	vector <shapeanswers> shapevec = { {"0","0","Circle"},{"4","4","Square"},{"3","3","Triangle"},{"8","5","Pyramid"} };




	
	SetConsoleTextAttribute
	(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "Topic: G E O M E T R Y \n";
	cout << "\n\nInput is case sensitive!, x to exit anytime.\n\nHow many questions you want to attempt?\n "; //need to do questions

	do {
		cin.clear();
		cin.ignore();
		cin >> globalnumberques;
	} while (cin.fail()); //in case input is non int


	for (int i = 0; (i < globalnumberques)&&(answer!="x"); i++) {
		accessvector = RandomNum(3);
		VerticeSideQuiz(shapevec[accessvector].side, shapevec[accessvector].vert, shapevec[accessvector].sname);
		
	}//question is answered in the verticesidequiz function

	ProcessScore(numbercorrect, globalnumberques);
	user1.LastTopic = "Geometry";

	answer = "0"; //so that it doesn't keep exiting the loop above
	
}



//number topic (multiple choice style) , two random numbers with a random operator are shown the user is required to choose the correct answer based on the arithmetic operator.
void Numbers() {


	int randopidx;
	
	char choice;
	double frstnum, scndnum;
	
	
	string randop[4] = { "+","-","*","/" };


	cout << "Test yourself on numbers! \n Choose answer by typing A, B, C or D (x to exit anytime during questions)\n How many questions you want to attempt?\n\n";


	do { //numberques is how many questions want to attempt.
		cin.clear();
		cin.ignore();
		cin >> globalnumberques;
	} while (!cin >> globalnumberques); //do not crash program if wrong input, clear the input stream ignore it and carry on!



	system("CLS"); //clean the screen!
	for (int j = 0; j < globalnumberques; ++j) {

		
		frstnum = RandomNum(50);
		scndnum = RandomNum(50); //Generate random number
		randopidx = RandomNum(3); // used to access vector of operators
		 
		cout << j + 1 << ") " << frstnum << " " << randop[randopidx] << " " << scndnum << "\n\n";
		
		switch (randopidx) {
		case 0: correctans = frstnum + scndnum;
			break;
		case 1: correctans = frstnum - scndnum;
			break;
		case 2: correctans = frstnum * scndnum;
			break;
		case 3: correctans = frstnum / scndnum;
			break;
		}


		vector <double> OptionABCD(0);
		vector <char> ABCD = { 'A','B','C','D' }; // used to show users the options.

		for (int i = 0; i < 3; i++) {			//inserting wrong answers in vector
			double wrongans = (rand() % 50) + 1;
			OptionABCD.push_back(wrongans);
		}
		OptionABCD.push_back(correctans); //the options needs to include correct answer!


		std::shuffle(OptionABCD.begin(), OptionABCD.end(), std::random_device()); //make sure answers are shuffled!

		for (int i = 0; i < ABCD.size(); ++i) {
			cout << ABCD[i] << ". " << OptionABCD[i] << endl; //display the options with correct one, in random order
		}




		bool found = 1;
		do {


			cin >> choice;	//user INPUT answer here
			if (choice == 'x') { //exit to main menu if x is input! otherwise, it is a non valid input.
				system("CLS");
				return;
			}

			for (int i = 0; i < ABCD.size(); ++i) { //finding the position of 'choice', if not found then input NOT VALID
				if (choice == ABCD[i]) {
					randopidx = i;	//we are using exising variable randoipx since it won't be used again [to get index]
					found = 1;
					break;
				}
				else
				{
					found = 0;
				}
			}
			if (found == 0) cout << "Please enter a valid input! (Remember that it is case sensitive)" << endl;
		} while (found == 0);



		cout << "Your answer: " << OptionABCD[randopidx] << "\n\n";
		if (OptionABCD[randopidx] == correctans) {
			numbercorrect++;
			system("color 0a");
		}
		else
		{
			system("color 04");
		}
		system("color 07");
	}

	//when all questions completed.
	
	
	ProcessScore(numbercorrect, globalnumberques);
	user1.LastTopic = "Numbers";
	system("color 07");

}



//simple calculator tool
void Calculator() {

	int exit = 0;

	while (exit < 1) {
		system("color 0E");
		char op;
		float num1, num2;

		do {

			system("CLS");
			cin.clear();
			cin.ignore();
			cout << "\t\t CALCULATOR\n Enter two numbers: \n";
			cin >> num1 >> num2;

			cout << "Enter operator either + or - or * or /: ";
			cin >> op;
			
		} while (cin.fail()); //don't break program if wrong datatype input
		

		switch (op)
		{
		case '+':
			cout << num1 + num2;
			break;

		case '-':
			cout << num1 - num2;
			break;

		case '*':
			cout << num1 * num2;
			break;

		case '/':
			cout << num1 / num2;
			break;

		default:
			// If the operator is other than +, -, * or /, error message is shown
			cout << "Error! operator is not correct";
			break;
		}
		system("color 0a");
		cout << "\n Exit to menu? (Yes = 1, No = 0)\n";
		cin >> exit;
		
	}
	user1.LastTopic = "Calculator";
}

//This function uses the object class and the questions asked are of the genre: "is object heaver/lighter than object2?", answer is of type true or false.
void WeightQuiz() {
	

	system("CLS");
	//below is question part

	cout << "Test your intuition and answer the following! (T or F, x to exit anytime)\n How many questions you want to attempt? \n";




	do { //numberques is how many questions want to attempt.
		if (globalnumberques == 120)return; //if 'x' is input, exit to menu
		cin.clear();
		cin.ignore();
		cin >> globalnumberques;
	} while (!cin >> globalnumberques); //do not crash program if wrong input, clear the input stream ignore it and carry on!



	for (int i = 0; (i < globalnumberques); i++) {

//generate random number from 0 - (vectorsize) to choose random object

		int firstobj = RandomNum(ListObject.size() - 1); 
		int secondobj = RandomNum(ListObject.size() - 1);
		int QuesType = RandomNum(50);

		if (QuesType < 25) {
			cout << "A " << ListObject[firstobj].object << " is heavier than a " << ListObject[secondobj].object << endl;
		} else 
			if (QuesType >= 25) {
				cout << "A " << ListObject[firstobj].object << " is lighter  than a " << ListObject[secondobj].object << endl;
			}


		while (cin >> answer) {
			if (answer == "T" or answer == "F")break;
			else if (answer == "x")return;
		}
		//loop this if the input not valid

		if ((ListObject[firstobj].weight > ListObject[secondobj].weight) && (answer == "T") && (QuesType <25)) {
			cout << "Correct! \n";
			numbercorrect++;

		}
		else
			if ((ListObject[firstobj].weight <= ListObject[secondobj].weight) && (answer == "F") && (QuesType<25)) {
				cout << "Correct! \n";

				numbercorrect++;
			}
			else
				//----------lighter questions
				if ((ListObject[firstobj].weight > ListObject[secondobj].weight) && (answer == "F") && (QuesType >= 25)) {
					cout << "Correct! \n";
					numbercorrect++;

				}
				else 
					if ((ListObject[firstobj].weight <= ListObject[secondobj].weight) && (answer == "T") && (QuesType >= 25)) {
						cout << "Correct! \n";
						numbercorrect++;

					}
					else {
						cout << "Wrong \n";
					}

	}
	ProcessScore(numbercorrect, globalnumberques);
	user1.LastTopic = "Weight Quiz";

}

//problems involving money in sentence style.
void MoneyQuiz() {
	int i = 0; //iterator, do while loop is used because must be able to continue without incremeting in some case
	system("CLS");
	cout << "\t\t MONEY\n How much questions you want to attempt?";
	
		
		cin >> globalnumberques;

		if (cin.fail()) {
			cin.clear();
				return;
		}


		do{


		double costmoney1 = RandomNum(30); //price of 1st object
		double costmoney2 = RandomNum(50); //price of 2nd object

		double havemoney = RandomNum(500); //how much money john have
		double quantity = RandomNum(10); //qty of object he buys

	
		
		if ((havemoney < (quantity*costmoney1)) || (havemoney < (costmoney1 + costmoney2)))continue;
		//the above condition makes makes sure that JOHN will NEVER be in DEBT (just continue the loop until john's balance > expense)
		i++; //the iterator

		double userans = 0;
		int QueStyle = RandomNum(50);
		int ObjIndx = RandomNum(ListObject.size() - 1); //choose a random object
		int ObjIndx2 = RandomNum(ListObject.size() - 1);

		if (QueStyle >= 25) {
			cout << "\nJohn has Rs" << havemoney << " and buys " << quantity << " " << ListObject[ObjIndx].object << " which costs Rs" << costmoney1 << " each\n";
			cout << "How much money John is left with?\n";
			correctans = havemoney - (quantity*costmoney1);
			
		} 
		else if(QueStyle<25){
		
			cout << "\nJohn has Rs" << havemoney << " and buys a " << ListObject[ObjIndx].object << ", which costs Rs" << costmoney1 << " and a " << ListObject[ObjIndx2].object << ", which costs Rs" << costmoney2 << ". How much money will John be left with?\n";
			correctans = havemoney - (costmoney1 + costmoney2);
			
		}

		do {
			cin.clear();
			cin.ignore();
			cin >> userans;
		} while (cin.fail());
	
		if (userans < 0)return;

		if (userans == correctans) {
			cout << "good\n";
			system("color 0a");
			numbercorrect++;
		} 
		else {
			system("color 04");
			
		}

		system("color 0E");
	
	} while (i < globalnumberques);

	ProcessScore(numbercorrect, globalnumberques);

	user1.LastTopic = "Money";
}



//this function is about arithmetic questions on centilitres and litres which requires the user to convert to appropriate unit
void Capacity() {

	system("CLS");
	double cL = 0;
	double L = 0;
	double userans;
	char Operator[2] = { '+','-' };
	int whichoperator = 0;

	cout << "e.g 1. To convert 1L to cL, we multiply by 100. 1L = 100cL\n e.g 2. 1L+2CL = 100cL + 2cL = 102cL\n";
	cout << " How many questions?\n";
	cin >> globalnumberques;

	for (int i = 0;i<globalnumberques ; i++) {
		whichoperator = RandomNum(60); //a higher sample size is better

		if (whichoperator >= 30) { //one half represent 1, other half represent 0
			whichoperator = 1;
		}
		else {
			whichoperator = 0;
		}



		do {
			cL = RandomNum(100);
			L = RandomNum(1000);
		} while (cL > L); //to avoid negative correct answers

			L = L / 100;

			if (whichoperator == 1) {
				correctans = (L * 100) - cL;
				cout << L << "L" << Operator[whichoperator] << cL << "cL" << " is how many cL?\n";
			}
			else if (whichoperator == 0) {
				correctans = (L * 100) + cL;
				cout << L << "L" << Operator[whichoperator] << cL << "cL" << " is how many cL?\n";
			}

		cin >> userans;
		if (userans == correctans) {
			numbercorrect++;
		}
		else {
			cout << " That's " << correctans << " !\n";
		}
	}

	ProcessScore(numbercorrect, globalnumberques);
	user1.LastTopic = "Capacity";
}

//menu for capacity, money and weight
void Measures() { 
	system("CLS");
	cout << "1. Weight  Quiz \n\n2. Capacity\n\n3. Money\n\n";
	cin >> answer;

	if (answer == "1")
		WeightQuiz();
	if (answer == "2")
		Capacity();
	if (answer == "3")
		MoneyQuiz();

	else return;
}

//This question generates 10 numbers from 1-100 and the user is required to arranged in ascending/ descending
void Orders() {
	//a random list of numbers is give, user needs to arrange in ascending order 
	// everytime, it displays the random list with the corect answer removed along with the sorted-so-far list

	cout << "\t\tAscending/Descending orders!\n";
	vector <int> NumSet(0); //this is the arranged list
	vector <int> NotArranged(0); //unordered list
	vector <int> ThisFillsUp(0); //correct answer fills this up
	int ans;
	int LifeLine = 3; //chances to try again before its over
	int i = 0;

	for (int i = 0; i < 10; i++) { //Generate 10 random numbers and store in vector
		int ThatNumber = RandomNum(100);
		NumSet.push_back(ThatNumber);
		NotArranged.push_back(ThatNumber); //used as reference
		cout << ThatNumber << ", ";
	}

	//----------------------
	int TwoQues = RandomNum(100); //this makes it so the user can be asked to arrange in either ascending or descending!
	if (TwoQues < 50) {
		cout << "\nArrange in Descending order! (x to exit)\n";
		sort(NumSet.begin(), NumSet.end(), greater <>()); //sort the vector by ascending order
	}
	else
	{
		cout << "\nArrange in Ascending order! \n";
		sort(NumSet.begin(), NumSet.end()); //else sort by descending
	}

	//answering part bbelow

	cout << "\n";
	while(i<10) { //continue to accept input while the iterator is less than 10
		cin >> ans;

		if (cin.fail()) { //if anything except integer, return to main menu
			cin.clear();
			return;
		}

		if (ans != NumSet[i]) {

			system("CLS");

			for (int z = 0; z < NotArranged.size(); z++) {//display the unordered list
				cout << NotArranged[z] << ", ";
			}

			cout << "\nTry again!\n";
			LifeLine--; //for every wrong answer, the lifeline is decremented
			
			system("color 04"); //aesthetic, flashes to green/red if answer is correct/wrong
			Sleep(10);
			system("color 0E");

			if (LifeLine == 0)break;
			continue;
			
		}
		else
		{
			i++;
			correctans++;
			ThisFillsUp.push_back(ans); //store the correct answers input by the user

			system("color 0a");
			Sleep(10);
			system("color 0E");

			for (int j = 0; j < NotArranged.size(); j++) {
				if (ans == NotArranged[j]) {
					NotArranged.erase(NotArranged.begin() + j);
					NotArranged.shrink_to_fit(); //remove the value the user entered if its correct (i.e smallest first e.g)
					break;
				}

			}

		}

		system("CLS");



		for (int z = 0; z < NotArranged.size(); z++) {//display the unordered list
			cout << NotArranged[z] << ", ";
		}

		cout << "\n Your answers: ";
		for (int r = 0; r < ThisFillsUp.size(); r++) {
			cout << ThisFillsUp[r] << ",";
		}
		cout << "\n\n";


	}
	ProcessScore(correctans, 10);
	user1.LastTopic = "Asc/Desc Order";
}

//this function is looped in int main() to display the main menu, it displays the topic choices.
void MainMenu() {
	
		system("CLS");
		finalscore = 0;
		numbercorrect = 0; //reset those, as it is used by every quiz.

		int topicchoice;
		//this is what appear first when executed


		cout << "\t\t\t T O O L \n \t\t\t F O R \n \t\t\t M A T H\n \t\t\t G R A D E 3\n"; //aesthetic purpose 
		for (int i = 0; i < 5; i++) {
			system("color 0a");
			Sleep(10);
			system("color 0b");

		}



		SetConsoleTextAttribute
		(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_GREEN);

		cout << "Please choose : \n";
		cout << "1. Geometry Quiz\n\n\n";
		cout << "2. Numbers\n\n\n";
		cout << "3. Measures\n\n\n";
		cout << "4. Asc/Desc Order\n\n\n";
		cout << "5. Calculator\n\n\n";
		cout << "6. My stats\n\n\n";
		


		cout << "Enter input (1-6)\n";		//choosing topic
		cin >> topicchoice;

		switch (topicchoice) {
		case 1:
			system("CLS");
			Geometry();
			break;

		case 2:
			system("CLS");
			Numbers();
			break;

		case 3:
			system("CLS");
			Measures();
			break;

		case 4:
			system("CLS");
			Orders();
			break;

		case 5:
			system("CLS");
			Calculator();
			break;

		case 6:
			user1.displayinfo();
			system("pause");
			system("CLS");
			break;


		default:
			cout << "not a valid input. ";
			cin.clear();
			cin.ignore(); //error handling
			system("CLS");
			break;

		}



};






int main()
{

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //used to produce coloured texts
	LoadObjects();
	user1.userinitialize();
	
	srand((unsigned)time(0)); //this make sure number is random on each execution
	while (true)
	{
		MainMenu();
		user1.SaveProgress(); //save progress everytime after a question, that is, accessing the main menu.
	}
	
	return 0;
}



