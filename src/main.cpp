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

	while (continueOrNo) {
		HonorRoll student(name, courses, total, average, allTheCourses, everyGrade);

		student.clearVectors();


		name = student.askForName();
		courses = student.numCourses();

		//call method for a for loop that asks for all of the courses the user takes
		allTheCourses = student.askForCourse();

		//call method for a for loop that asks for all the course grades
		everyGrade = student.askForGrades();

		//print output
		student.printOutput();
		student.fileOutput();
		/*ofstream fout("studentdata.txt");
		fout << student.allNames.at(0);
		fout.close();*/

		string abc;
		cout << "Would you like to re-run with a new student? Enter Y if so and anything else to quit. ";
		cin >> abc;
		if (tolower(abc.at(0)) == 'y') {
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		else {
			//student.fileOutput();
			continueOrNo = false;
		}
	}
}