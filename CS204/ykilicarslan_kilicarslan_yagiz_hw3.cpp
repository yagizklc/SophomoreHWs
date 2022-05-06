/**************************
Yagiz Kilicarslan 28126

***************************/

#include <sstream>
#include <string>
#include "ykilicarslan_kilicarslan_yagiz_hw3_header.h"
using namespace std;


int main(){

	int number;
	string numbers;
//					gets line as input then checks if empty 
	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers);
	if (numbers.empty()){
		cout << endl <<"FINAL CONTENT" << endl << "List is empty!";
		return 0;
	}
//					create LİST class object
	SubSeqsList list;
	istringstream strStream(numbers);
	while(strStream >> number){   //takes each number
		if (number >= 0){ 
			if (!list.checknumber(number)){  //checks if already exist in List
				list.addNumber(number); // if not -> adds the number to list
			}
		}
		else{
			list.delNumber(number); // if - sign -> deletes from list
		}
	}
	
	list.printList();

	return 0;
}