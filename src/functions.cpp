#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
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
	while (first.length() == 0 || first.at(0) == ' ') {
		cout << "Please enter a valid name:\t";
		getline(cin, first);
	}

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
		cout << "Enter your final " << allCourseNames.at(i) << " grade:\t";
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

void HonorRoll::printOutput()
{
	//formatting the output chart
	string blank = "";
	cout << "\n\nName: " << studentName << "\n" << endl;;
	printf("%-30s%-30s\n", "Course", "Grade");
	for (int i = 0; i < allTheGrades.size(); i++) {
		printf("%-30s%-30d\n", allCourseNames.at(i).c_str(), allTheGrades.at(i));
	}
	cout << "\nYour final average across all " << numberOfCourses << " of your courses is " << avg << "." << endl;

	//displaying the disciplinary infraction
	cout << "\nDisciplinary Infraction: ";
	if (hasDisciplineIssue == true) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}

	hasDisciplineIssue = disiplineIssue();
	//determining honor roll
	if (avg >= 90 && numberOfCourses >= 5 && hasDisciplineIssue == false) {
		cout << "\nCongratulations " << studentName << "! You are eligible for honor roll!" << endl;
	}
	else {
		cout << "\nI'm sorry " << studentName << ", but you didn't qualify for honor roll." << endl;
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

//new functions

//clear vectors
void HonorRoll::clearVectors()
{
	allTheGrades.clear();
	allCourseNames.clear();
}

char HonorRoll::inputMenu()
{
	string menuChoice;
	cout << "Welcome to Honor Roll! What would you like to do today?\n\tA: Enter Student Data\n\tB: Enter Admin Mode\n\tC: Run Reportsn\n\tD: Exit Program\n";
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

void HonorRoll::adminMode()
{
	int adminPassword = 1111, guess;
	string letters = "abcdefghijklmnopqrstuvwxyz";
	cout << "Enter the password to enter administrator mode: ";
	while (!getValidInt(guess)) {
		cout << "\tEnter a valid number:\t";
	}

	if (guess == adminPassword) {
		if (allNames.size() == 0) {
			cout << "Invalid password. ";
		}
		else {
			cout << "Which student would you like to display a disciplinary infraction for?" << endl;
			for (int i = 0; i < allNames.size(); i++) {
				printf("%-1c . %-25s", letters.at(i), allNames.at(i).c_str());
			}
		}

	}
}


void HonorRoll::fileOutput()
{
	//ofstream fout("studentdata.txt", ios::app);
	FILE* fout;
	fout = fopen("studentdata.txt", "a");
	for (int i = 0; i < allNames.size(); i++) {
		fprintf(fout, "Student Name: %-25s\n", allNames.at(i).c_str());
		fprintf(fout, "# of Courses: %-25d\n", allTheNumOfCourses.at(i));
		fprintf(fout, "%-20s %-15s\n", "Course:", "Grade:");
		for (int j = 0; j < allStudentCourseNames.at(i).size(); j++)
		{
			//fout << fixed;
			//fout << allStudentCourseNames.at(i).at(j) << setw(20) << setprecision(0) << allStudentGrades.at(i).at(j) << endl;
			fprintf(fout, "%-20s %-15d\n", allStudentCourseNames.at(i).at(j).c_str(), allStudentGrades.at(i).at(j));
		}
		fprintf(fout, "\n");
	} 
}