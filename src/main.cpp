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

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <climits>
#include <fstream>
#include "student.h"

using namespace std;

int main() {
	string name = " ";
	int courses = 0, total = 0, average = 0;
	vector<string> allTheCourses;
	vector<int> everyGrade;

	//loop controller
	bool continueOrNo = true;

	//vectors to hold data for multiple students
	vector<string> names;

	//clear file to ensure that it is empty
	ofstream begin("studentdata.txt");
	begin.close();
	HonorRoll student(name, courses, total, average, allTheCourses, everyGrade);

	while (continueOrNo) {

		student.clearVectors();

		//set char value to what the input menu returns; will execute a certain function based on value
		char menuResult = student.inputMenu();
		if (tolower(menuResult) == 'a')
			student.enterStudent();

		else if (tolower(menuResult) == 'b')
			student.adminMode();

		else if (tolower(menuResult) == 'c') {
			//same goes for the report menu
			menuResult = student.reportMenu();
			if (tolower(menuResult) == 'a')
				student.fullHonorRollReport();
			else if (tolower(menuResult) == 'b')
				student.specificStudentHR();
			else if (tolower(menuResult) == 'c')
				student.fullGPAReport();
			else if (tolower(menuResult) == 'd')
				student.specificStudentGPA();
			else if (tolower(menuResult) == 'e')
				student.disciplinaryReport();
			else {
				cout << "Invalid input. Reprompting..." << endl;
				menuResult = student.reportMenu();
			}

		}
		else if (tolower(menuResult) == 'd')
			;
		//call input menu again if invalid input is entered
		else {
			cout << "Invalid input. Reprompting..." << endl;
			continue;
		}
		//ask for rerun
		string abc;
		cout << "Would you like to re-run? Enter Y if so and anything else to quit. ";
		getline(cin, abc);
		if (tolower(abc.at(0)) == 'y') {
			student.clearVariables();
			continue;
		}
		else {
			continueOrNo = false;
		}
	} 
	//file output at the end
	student.fileOutput();

}