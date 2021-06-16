/*
Matthias Kim and Ragav Balusamy
Honor Roll Deluxe
Mrs. Digiovanna
6/16/21

Known Bugs/Defects:
	- sort will not work after another student is added
	- alphabetical sorts are not used
	- names are not sorted by last name
	- requirement #38: the two students will not be printed in alphabetical order if their gpa is the same
	- requirement #37: the program doesn't strip out spaces
	- Disciplinary issues don't work either, they are assigned by default but the assigning part doesnt work as expected
	- average rounds down instead of up.
	- did not re-serach if the name does not exist
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <climits>
#include "student.h"
#include <regex>



HonorRoll::HonorRoll() {}

HonorRoll::HonorRoll(string uName, int num, int allTotal, int mean, vector<string> theCourseNames, vector<int> theCourseGrades) {
	studentName = uName;
	numberOfCourses = num;
	sum = allTotal;
	avg = mean;
	allCourseNames = theCourseNames;
	allTheGrades = theCourseGrades;

}

//input validation
bool HonorRoll::getValidInt(int& t_int)
{
	std::string intScratch = "";
	bool isValid = true;


	getline(cin, intScratch);
	//remove all whitespace
	std::regex r("\\s+");
	intScratch = std::regex_replace(intScratch, r, "");
	//rev 2 make sure only valid characters for an integer number are in the string
	isValid = intScratch.find_first_not_of("-0123456789") == std::string::npos;
	//Only 1 '-' allowed
	if (std::count(intScratch.begin(), intScratch.end(), '-') > 1) {
		isValid = false;
		return isValid;
	}
	//make sure '-' is first char only
	else if (std::count(intScratch.begin(), intScratch.end(), '-') > 0) {
		if (intScratch.at(0) != '-') {
			isValid = false;
			return isValid;
		}
	}
	//convert ONLY if string is contains valid integer characters
	//all errors caught 
	if (isValid) {
		try {
			t_int = stoi(intScratch);
		}
		catch (...) { //<---catches ALL errors - may want to give the user a more specific message.  Shown in next function
			//bad user entry - don't care what it is, return invalid
			isValid = false;
		}
	}
	if (t_int < 0)
		isValid = false;
	else
		isValid = true;

	return isValid;
}


string HonorRoll::askForName()
{
	string first, last;
	//prompt user, clear cin, take input and return n
	cout << "What is your first name?  " << endl;
	cin.clear();
	//cin.ignore(INT_MAX, '\n');
	getline(cin, first);

	//ask for last name, then push back to all name vector
	cout << "What is your last name?  " << endl;
	cin.clear();
	//cin.ignore(INT_MAX, '\n');
	getline(cin, last);
	while (last.length() == 0 || last.at(0) == ' ') {
		cout << "Please enter a valid name:\t";
		getline(cin, last);
	}

	studentName = first + " " + last;
	allNames.push_back(studentName);
	count++;
	return studentName;
}



vector<string> HonorRoll::askForCourse()
{
	//prompt user for input for as many times as the number of courses they entered
	cout << "\nPlease note that the maximum course name is 20 characters. \nAnything above that will be truncated to exactly 20." << endl;
	cout << "Please enter your course name twice if it prompts you to. " << endl;
	for (int i = 0; i < numberOfCourses; i++) {
		//ask for course num and take the entire line
		cout << "Course " << i + 1 << " name:  ";
		string courseName;
		//clear cin
		cin.clear();
		getline(cin, courseName);

		//if the course name is greater than 20 characters then continuously loop until it is less than 20
		if (courseName.length() > 20) {
			courseName = courseName.substr(0, 20);
		}
		else if (courseName.length() == 0) {
			while (true) {
				cout << "Please enter a course name greater than 0!  ";
				getline(cin, courseName);
				if (courseName.length() == 0) {
					continue;
				}
				else {
					break;
				}
			}
		}


		//append the checked and/or input to the vector
		allCourseNames.push_back(courseName);
	}
	allStudentCourseNames.push_back(allCourseNames);
	//return vector
	return allCourseNames;

}

vector<int> HonorRoll::askForGrades()
{
	//define vector
	bool yesOrNo;

	cout << "\nFor each course, enter a grade from 0 to 120." << endl;

	//for loop to iterate through the courses and ask for the grade in each course
	for (int i = 0; i < numberOfCourses; i++) {
		//prompt user
		cout << "Enter your final " << allCourseNames.at(i) << " grade: ";
		cin.clear();
		string grade = ""; getline(cin, grade);
		//while loop to ask user for a new grade while they are invalid
		yesOrNo = checkValidGradeInput(grade);

		//while the input is invalid keep iterating through the loop
		while (yesOrNo) {
			cout << "\tEnter a valid grade:\t";
			cin.clear();
			getline(cin, grade);
			yesOrNo = checkValidGradeInput(grade);
		}

		//append values to the vector
		double convert = stod(grade);
		allTheGrades.push_back(convert);
	}
	allStudentGrades.push_back(allTheGrades);

	for (int i = 0; i < numberOfCourses; i++) {
		sum += allTheGrades.at(i);
	}
	avg = sum / numberOfCourses;
	allAverages.push_back(avg);

	return allTheGrades;
}

bool HonorRoll::checkValidGradeInput(string tester)
{
	//try-catch to validate input
	try {
		double temp = stod(tester);
		int num = stoi(tester); // error trap this with a try/catch block

		if (temp != num) {
			return true;
		}
		if (num > 120 || num < 0) {
			return true;
		}
	}
	catch (invalid_argument& e) {
		//prompt user for valid input/continue loop
		return true;
	}
	return false;
}



int HonorRoll::numCourses()
{
	cout << "\nNext, enter the number of courses you plan to take.\nThis must be between 1 and 8 inclusively." << endl;

	//declare variables
	string courses = "";
	bool yesOrNo;

	//prompt user and ask for input
	cout << "How many courses do you plan to take?\t";
	getline(cin, courses);
	yesOrNo = checkValidNumInput(courses);

	//while the input is invalid keep iterating through the loop
	while (yesOrNo) {
		cout << "\tEnter a valid course number:\t";
		getline(cin, courses);
		yesOrNo = checkValidNumInput(courses);
	}

	//convert the string into an int, then return it
	numberOfCourses = stoi(courses);
	allTheNumOfCourses.push_back(numberOfCourses);
	return numberOfCourses;
}

bool HonorRoll::checkValidNumInput(string tester)
{
	//try-cathc to validate input
	try {
		double temp = stod(tester);
		int num = stoi(tester); // error trap this with a try/catch block

		if (temp != num) {
			return true;
		}
		if (num > 8 || num < 1) {
			return true;
		}
	}
	catch (invalid_argument& e) {
		//prompt user for valid input/continue loop
		return true;
	}
	return false;
}

//cycle through all names and courses
void HonorRoll::fullHonorRollReport()
{
	//formatting the output chart
	string blank = "";
	for (int i = 0; i < allNames.size(); i++) {
		printf("Student Name: %-25s\n", allNames.at(i).c_str());
		printf("# of Courses: %-25d\n", allTheNumOfCourses.at(i));

		printf("%-30s%-30s\n", "Course", "Grade");
		for (int j = 0; j < allStudentCourseNames.at(i).size(); j++)
		{

			printf("%-30s %-30d\n", allStudentCourseNames.at(i).at(j).c_str(), allStudentGrades.at(i).at(j));
		}
		cout << "\nYour final average across all " << allTheNumOfCourses.at(i) << " of your courses is " << allAverages.at(i) << "." << endl;

		//displaying the disciplinary infraction
		cout << "\nDisciplinary Infraction: ";
		if (allDisciplineIssues.at(i) == true) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}

		//determining honor roll
		if (allAverages.at(i) >= 90 && allTheNumOfCourses.at(i) >= 5 && allDisciplineIssues.at(i) == false) {
			cout << "\nCongratulations " << allNames.at(i) << "! You are eligible for honor roll!" << endl;
		}
		else {
			cout << "\nI'm sorry " << allNames.at(i) << ", but you didn't qualify for honor roll." << endl;
		}
	}
}

bool HonorRoll::disiplineIssue()
{
	//out of 100 numbers generated, if the random selected number is from 1 to 5, then return a true value
	srand(time(NULL));
	int percentage = rand() % 100 + 1;

	if (percentage >= 1 && percentage <= 5) {
		hasDisciplineIssue = true;
	}
	else {
		hasDisciplineIssue = false;
	}

	//return bool value
	return hasDisciplineIssue;
}

string HonorRoll::lowercaser(string s)
{
	string newS = "";
	char temp;
	for (int i = 0; i < s.length(); i++) {
		temp = tolower(s.at(i));
		newS += temp;
	}

	return newS;
}

//new functions

//clear vectors
void HonorRoll::clearVectors()
{
	allTheGrades.clear();
	allCourseNames.clear();
}

char HonorRoll::inputMenu()
{
	//display menu, will return character based on what user enters
	string menuChoice;
	cout << "Welcome to Honor Roll! What would you like to do today?\n\tA: Enter Student Data\n\tB: Enter Admin Mode\n\tC: Run Reports\n\tD: Exit Program\n";
	getline(cin, menuChoice);
	//validate that inputted char is a letter
	if (menuChoice.length() == 0 || menuChoice == " " || menuChoice.length() > 1 || !isalpha(menuChoice.at(0))) {
		while (true) {
			cout << "Enter a valid letter choice: ";
			getline(cin, menuChoice);
			if (menuChoice.length() == 1 && menuChoice != " " && isalpha(menuChoice.at(0)))
				break;
		}
	}
	return menuChoice.at(0);
}

void HonorRoll::enterStudent()
{
	askForName();
	//call method to ask for # of courses
	numCourses();
	//call method for a for loop that asks for all of the courses the user takes
	askForCourse();
	//call method for a for loop that asks for all the course grades
	askForGrades();

	allDisciplineIssues.push_back(false);
}

void HonorRoll::adminMode()
{
	//initialize variables
	int adminPassword = 1111, guess = 0;
	string response;

	//while the guess is incorrect, ask if they want to exit, otherwise keep asking for password
	while (guess != adminPassword) {
		cout << "Enter the password to enter administrator mode: ";
		cin >> guess;
		if (guess == adminPassword)
			break;
		cout << "Would you like to exit? (y/n) ";
		getline(cin, response);
		if (response == "y")
			break;
		else {
			cin.ignore(INT_MAX, '\n');
			continue;
		}
	}
	//what to do if password is right
	if (guess == adminPassword) {
		if (count == 0) {
			char enter;
			//ask for a new student entry if the # of students is equal to 0
			cout << "There are no students to assign disciplinary infractions to. Enter a new student? (y/n) ";
			cin >> enter;
			if (enter == 'y') {
				cin.ignore(INT_MAX, '\n');
				enterStudent();
				//ask to enter a disciplinary infraction
				cout << "Would you like to assign a disciplinary infraction to this student? (y/n) ";
				cin >> enter;

				if (enter == 'y')
					hasDisciplineIssue = true;

				//push back discipline issue to respective student's position
				allDisciplineIssues.push_back(hasDisciplineIssue);
				cin.ignore(INT_MAX, '\n');
			}
			else if (enter == 'n')
				cin.ignore(INT_MAX, '\n');
			else
				cin.ignore(INT_MAX, '\n');

		}
		else {
			askWhichStudent();
			cin.ignore(INT_MAX, '\n');
		}

	}
}

//ask for which student they want to assign an infraction to
void HonorRoll::askWhichStudent()
{
	string enter;
	string letters = "abcdefghijklmnopqrstuvwxyz";
	int l = 0, counter = 0;
	//loop through all the students and display a menu of his/her's full name
	cout << "Which student would you like to add a disciplinary infraction for?" << endl;
	for (int i = 0; i < allNames.size(); i++) {
		printf("%-1c . %-25s\n", letters.at(i), allNames.at(i).c_str());
	}
	//get input and then compare to the actual string in the vector
	getline(cin, enter);
	enter = lowercaser(enter);

	string eee = "";
	//if the two match, locate position of the name in the name vector
	while (counter < allNames.size()) {
		if (lowercaser(allNames.at(counter)) == enter) {
			eee += to_string(counter);
			l = stoi(eee);
			break;
		}
		else
			counter++;
	}

	//change the infraction status in the vector at that position to true
	allDisciplineIssues.at(l) = true;
	//cin.ignore(INT_MAX, '\n');
}

////////////////////////////////////////////////////

//display a report menu for the user
char HonorRoll::reportMenu()
{
	string menuChoice;
	//identical to the input menu, it will display options and return the character that the user enters to main
	cout << "What type of report would you like to see?\n\tA: Full Honor Roll Report (all students)\n\tB: Report for 1 Student\n\tC: Full GPA Report (all students)\n\tD: GPA Report for 1 Student\n\tE: Disciplinary Infractions Report\n";
	getline(cin, menuChoice);
	if (menuChoice.length() == 0 || menuChoice == " " || menuChoice.length() > 1 || !isalpha(menuChoice.at(0))) {
		while (true) {
			cout << "Enter a valid letter choice: ";
			getline(cin, menuChoice);
			if (menuChoice.length() == 1 && menuChoice != " " && isalpha(menuChoice.at(0)))
				break;
		}
	}
	return menuChoice.at(0);
}

//asks which student to display a report for 
void HonorRoll::specificStudentHR()
{
	string enter;
	string letters = "abcdefghijklmnopqrstuvwxyz";
	int j = 0, counter = 0;
	//displays a menu of all the students
	cout << "Which student would you like to display a report for?" << endl;
	for (int i = 0; i < allNames.size(); i++) {
		printf("%-1c . %-25s\n", letters.at(i), allNames.at(i).c_str());
	}
	getline(cin, enter);
	enter = lowercaser(enter);

	//will call the report function with the position of the name as the position parameter
	string eee = "";
	while (counter < allNames.size()) {
		if (lowercaser(allNames.at(counter)) == enter) {
			eee += to_string(counter);
			j = stoi(eee);
			break;
		}
		else
			counter++;
	}
	HRReport(j);
}

void HonorRoll::HRReport(int i)
{
	//printf to display all of the output in a neat manner
	double sum, average;
	//formatting the output chart
	printf("Student Name: %-25s\n", allNames.at(i).c_str());
	printf("# of Courses: %-25d\n", allTheNumOfCourses.at(i));

	printf("%-30s%-30s\n", "Course", "Grade");
	for (int j = 0; j < allStudentCourseNames.at(i).size(); j++)
	{

		printf("%-30s %-30d\n", allStudentCourseNames.at(i).at(j).c_str(), allStudentGrades.at(i).at(j));
	}

	cout << "\nYour final average across all " << allTheNumOfCourses.at(i) << " of your courses is " << allAverages.at(i) << "." << endl;

	//displaying the disciplinary infraction
	cout << "\nDisciplinary Infraction: ";
	if (allDisciplineIssues.at(i) == true) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}

	//determining honor roll
	if (allAverages.at(i) >= 90 && allTheNumOfCourses.at(i) >= 5 && allDisciplineIssues.at(i) == false) {
		cout << "\nCongratulations " << allNames.at(i) << "! You are eligible for honor roll!\n" << endl;
	}
	else {
		cout << "\nI'm sorry " << allNames.at(i) << ", but you didn't qualify for honor roll.\n" << endl;
	}
}

//full gpa report
void HonorRoll::fullGPAReport()
{
	//header
	printf("%-20s%-20s\n", "Name:", "GPA:");
	//loop through all names
	for (int i = 0; i < allNames.size(); i++) {
		printf("%-20s%-20.0f\n", allNames.at(i).c_str(), allAverages.at(i));
	}
}

//prints specific student's gpa
void HonorRoll::specificStudentGPA()
{
	string enter;
	string letters = "abcdefghijklmnopqrstuvwxyz";
	int j = 0, counter = 0;
	cout << "Which student would you like to display a GPA report for?" << endl;
	for (int i = 0; i < allNames.size(); i++) {
		printf("%-1c . %-25s\n", letters.at(i), allNames.at(i).c_str());
	}
	getline(cin, enter);
	enter = lowercaser(enter);

	//will call the gpa function with the position of the name as the position parameter
	string eee = "";
	while (counter < allNames.size()) {
		if (lowercaser(allNames.at(counter)) == enter) {
			eee += to_string(counter);
			j = stoi(eee);
			break;
		}
		else
			counter++;
	}
	GPAReport(j);
}

//gpa report print
void HonorRoll::GPAReport(int i)
{
	printf("%-20s%-20s\n", "Name:", "GPA:");
	BubbleSort(allAverages, allNames);
	printf("%-20s%-20.0f\n", allNames.at(i).c_str(), allAverages.at(i));
}

//disciplinary report function
void HonorRoll::disciplinaryReport()
{
	//counts number of false infractions
	int falseCount = 0;
	//header
	printf("%-25s%-20s\n", "Student #:", "Name:");
	//will only print the student's name if the student HAS an infraction
	for (int i = 0; i < allNames.size(); i++) {
		if (allDisciplineIssues.at(i) == true)
			printf("%-25d%-20s\n", i + 1, allNames.at(i).c_str());
		else {
			falseCount++;
			continue;
		}
	}
	//will display  a message if nobody has an infraction
	if (falseCount == allDisciplineIssues.size())
		cout << "There are no students with discipline issues." << endl;
}

//clear variables after each run to prevent unwanted values
void HonorRoll::clearVariables()
{
	numberOfCourses = 0, sum = 0;
	avg = 0;
	studentName = "";
}

//bubble sort (i tried to sort this)
void HonorRoll::BubbleSort(vector<double>& num, vector<string>& name)
{
	int i, j, flag = 1;
	int temp;
	string t;

	for (i = 1; i < allAverages.size(); i++)
	{
		flag = 0;
		for (j = 0; j < allAverages.size() - 1; j++)
		{
			if (num[j + 1] < num[j])
			{
				temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
				t = name.at(j);
				name.at(j) = name.at(j + 1);
				name.at(j + 1) = t;

				flag = 1;
			}
		}
	}
	return;
}

//file output function
void HonorRoll::fileOutput()
{
	//ofstream fout("studentdata.txt", ios::app);
	FILE* fout;
	fout = fopen("studentdata.txt", "a");
	for (int i = 0; i < allNames.size(); i++) {
		fprintf(fout, "Student Name: %-25s\n", allNames.at(i).c_str());
		fprintf(fout, "# of Courses: %-25d\n", allTheNumOfCourses.at(i));
		//displaying the disciplinary infraction
		fprintf(fout, "Disciplinary Infraction: ");
		if (allDisciplineIssues.at(i) == true) {
			fprintf(fout, "YES\n");
		}
		else {
			fprintf(fout, "NO\n");
		}
		//printing out courses and grades in a neat manner
		fprintf(fout, "%-20s %-15s\n", "Course:", "Grade:");
		for (int j = 0; j < allStudentCourseNames.at(i).size(); j++)
		{

			fprintf(fout, "%-20s %-15d\n", allStudentCourseNames.at(i).at(j).c_str(), allStudentGrades.at(i).at(j));
		}
		fprintf(fout, "\n");
	}
}