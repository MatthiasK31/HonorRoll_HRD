#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class HonorRoll
{

private:
	int numberOfCourses = 0, sum = 0;
	double avg = 0;
	vector<string> allCourseNames;
	vector<int> allTheGrades;
	string studentName;


	bool hasDisciplineIssue = false;

public:
	//vectors holding all info
	vector<string> allNames;
	vector<int> allTheNumOfCourses;
	vector<vector<string>> allStudentCourseNames;
	vector<vector<int>> allStudentGrades;

	//constructors
	HonorRoll();  //default constructor
	HonorRoll(string, int, int, int, vector<string>, vector<int>);

	string askForName();

	vector<string> askForCourse();
	vector<int> askForGrades();

	int calculateTotal();


	int numCourses();

	void printOutput();

	bool disiplineIssue();
	bool checkValidNumInput(string);
	bool checkValidGradeInput(string);


	void clearVectors();

	void inputMenu();

	void fileOutput();
};