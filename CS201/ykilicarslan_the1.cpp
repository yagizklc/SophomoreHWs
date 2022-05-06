#include <iostream>
#include <string>
using namespace std;

// Yagiz Kilicarslan 28126 

int main(){
	
	string prevGrade, curGrade, name, course, YN, change, chosenGrade;

	//asking the basics
	cout << "Welcome to the Fall 2020-2021 Semester grading system. What is your name? ";
	cin >> name;

	cout << "Hello " << name << "! Please enter the name of the course to be processed: ";
	cin >> course;

	cout << "Hello " << name << "! If you take the " << course << " for the first time, enter YES otherwise NO: ";
	cin >> YN;

	// checking YN question 
	if ((YN != "YES") && (YN != "NO")){
		return 0;
	}



	// if first time 
	else if (YN == "YES"){
		cout << "What is your grade from (A,B,C,D,F)? ";
		cin >> curGrade;

		// invalid grade check
		if ((curGrade != "A") && (curGrade != "B") && (curGrade !=  "C") && (curGrade != "D") && (curGrade != "F")) {
			cout << "Invalid grade selection. Goodbye..." << endl;
		}

		// if F --> U
		else if (curGrade  == "F") {
			cout << "Do you want to switch your grade from F to U (YES or NO)? ";
			cin >> change;
			
			//invalid answ check
			if ((change!="YES") && (change!="NO")){
				cout << "Invalid grade selection. Goodbye..." << endl;
			}

			else if (change == "YES" ) {
				cout << name <<", your final grade for "<< course << " is U. Goodbye..." << endl;
			}

			else if (change == "NO") {
				cout << name <<", your final grade for "<< course << " is F. Goodbye..." << endl;
			}		
		}
		
		// other than F 
		else if ((curGrade == "A") || (curGrade == "B") || (curGrade == "C") || (curGrade == "D")){
			cout << "Do you want to switch your grade from "<< curGrade << " to S (YES or NO)? ";
			cin >> change;
			
			//invalid answ check
			if ((change!="YES") && (change!="NO")){
				cout << "Invalid grade selection. Goodbye..." << endl;
			}

			else if (change == "YES") {
				cout << name << ", your final grade for "<< course << " is S. Goodbye..." << endl;
			}

			else if (change == "NO") {
				cout << name << ", your final grade for "<< course << " is " << curGrade <<". Goodbye..." << endl;
			}
		}
	}





	// if second time 
	else if (YN == "NO") {
		cout << "Please enter your previous grade from (A,B,C,D,F,S,U): ";
		cin >> prevGrade;
	
		// invalid grade check
		if ((prevGrade != "A") && (prevGrade != "B") && (prevGrade !=  "C") && (prevGrade != "D") && (prevGrade != "F") && (prevGrade  != "S") && (prevGrade  != "U")) {
			cout << "Invalid grade selection. Goodbye..." << endl ;
		}


		else {
			cout << "Please enter your current grade from (A,B,C,D,F): ";
			cin >> curGrade;
			
			// invalid grade check
			if ((curGrade != "A") && (curGrade != "B") && (curGrade !=  "C") && (curGrade != "D") && (curGrade != "F")) {
				cout << "Invalid grade selection. Goodbye..." << endl ;
			}

			else{
				cout << "Please enter the grade you want to choose from (A,B,C,D,F,S,U): ";
				cin >> chosenGrade;



				if (curGrade == "F"){
					
					if (prevGrade == "S") {
						cout << "Invalid grade selection. If you received S before and fail this semester, you get F." << endl;
					}
				
					else if ( (chosenGrade != "F") && (chosenGrade != "U") ){
						cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve. " << endl;
					}

					else if ( chosenGrade == "U") {
						if (prevGrade == "F") {
							cout << "Invalid grade selection. If you received F before, and fail this semester, you get F." << endl;
						}

						else if (prevGrade == "S"){
							cout << "Invalid grade selection. If you received S before and fail this semester, you get F." << endl;
						}

						else{
							cout << name << ", your final grade for " << course << " is " << chosenGrade << ". Goodbye..." << endl;
						}
					}

					else if (chosenGrade == "F") {
						cout <<  name << ", your final grade for " << course << " is " << chosenGrade << ". Goodbye..." << endl;
					}
				} 



				else if (curGrade != "F"){

					if ( (prevGrade == "U" ) && ((chosenGrade != curGrade) && (chosenGrade != "S"))) {
						cout << "Invalid grade selection. If you received U before, you may choose S or current letter grade." << endl ;
					}

					else if ( (chosenGrade != "S") && (chosenGrade != curGrade) ) {
						cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
					}

					else{
						cout << name << ", your final grade for " << course << " is " << chosenGrade << ". Goodbye..." << endl;
					}
				}
			}


		}			
	}

	return 0;
}
