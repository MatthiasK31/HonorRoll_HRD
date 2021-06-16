/*
Matthias Kim and Ragav Balusamy
Honor Roll Deluxe
Mrs. Digiovanna
6/16/21

Extra: asked students for his/her favorite teacher

Known Bugs:
	- sort will not work after another student is added
	- alphabetical sorts are not used
	- names are not sorted by last name
	- requirement #38: the two students will not be printed in alphabetical order if their gpa is the same
	- requirement #37: the program doesn't strip out spaces
*/

#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

class HonorRoll
{

private:
	int numberOfCourses = 0, sum = 0, count = 0;
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
	vector<bool> allDisciplineIssues;
	vector<double> allAverages;


	//constructors
	HonorRoll();  //default constructor
	HonorRoll(string, int, int, int, vector<string>, vector<int>);

	//validation
	bool getValidInt(int &);

	string askForName();

	vector<string> askForCourse();
	vector<int> askForGrades();

	int numCourses();


	bool disiplineIssue();
	bool checkValidNumInput(string);
	bool checkValidGradeInput(string);

	string lowercaser(string);


	//menu modes
	void clearVectors();
	char inputMenu();
	void enterStudent();
	void adminMode();
		void askWhichStudent();


	//report menu
	char reportMenu();
	void fullHonorRollReport();
	void specificStudentHR();
		void HRReport(int);
	void fullGPAReport();
	void specificStudentGPA();
		void GPAReport(int);
	void disciplinaryReport();

	void clearVariables();
	void BubbleSort(vector<double>&, vector<string>&);


	//file output
	void fileOutput();
};