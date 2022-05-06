#include <string>
#include "ykilicarslan_kilicarslan_yagiz_class_hw4.h"
#include <fstream>
#include <sstream>
using namespace std;

// These 2 functions are modifications of Lab5 - Main.cpp
//***************************** 
void ClearStack(dynStack& myStack){
	int row, col;
	while(!myStack.isEmpty()){
		myStack.pop(row,col);
	}
}

void Print(dynStack& myStack, string str){
	dynStack reverseStack;
	int row, col;

	if(myStack.isEmpty()){
		cout << "The bit string "<< str << " could not be found." << endl;
	}
	else{
		//Reverse of the stack
		cout << "The bit string " << str << " is found following these cells: " << endl;
		while(!myStack.isEmpty())
		{
			myStack.pop(row,col);
			cout << "("<<row << "," << col << ")" << " ";
			reverseStack.push(row, col);
		}
	}
	//Again my real stack
	while(!reverseStack.isEmpty())
	{
		reverseStack.pop(row,col);
		myStack.push(row,col);
	}

	cout << endl << "----------------------------------------" << endl;
}
//***************************

struct cellStruct{
	char ch;
	bool flag;
};


int main(){
	// Generate Matrix | Modified from matrixnoclass.cpp
	int rows, cols;
	cout << "Please enter the number of rows: "; cin >> rows;
	cout << "Please enter the number of columns: "; cin >> cols;
	cellStruct ** matrix;
	matrix = new cellStruct* [rows]; 
	for (int i = 0; i<rows; i++){ // An built problem occured here but I dont know why
		matrix[i] = new cellStruct [cols];   
	}
	// Read File
	ifstream file;
	string fileName, str, line;
	char c1, c2;
	cout << "Please enter the name of the input file that contains the matrix: ";
	cin >> fileName;
	file.open(fileName.c_str());
	while (file.fail()){
		cout << "File cannot be opened." << endl; 
		cout << "Please enter the name of the input file again: ";
		cin >> fileName;
		file.open(fileName.c_str());
	}	

	// Assign values of Matrix from File
	istringstream strStream;
	int i, j;
	for (i = 0;getline(file, line);i++){
		strStream.clear(); strStream.str(line);
		for (j = 0; strStream >> c1; j++){
			matrix[i][j].flag = false; 
			matrix[i][j].ch = c1;
		}
	}

	// Search Algorithm
	dynStack path;
	while (!cin.eof()){
		cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
		cin >> str;

		ClearStack(path);
		i = 0, j = 0;
		int s = str.length(), t = 0; // t = how much we read

		c2 = str.at(t);
		// check (0,0) index
		if (c2 != matrix[0][0].ch)
			matrix[0][0].flag = true;
		
		for (t = 0; matrix[0][0].flag == false && t!= s;){
			c2 = str.at(t);
			if (matrix[i][j].flag == false && matrix[i][j].ch == c2){
				path.push(i,j);
				t++;
				if (t != s){
					if (i < rows && matrix[i+1][j].flag == false){
						i++; 
						t++;
					}
					else if (j < cols && matrix[i][j+1].flag == false){
						j++; 
						t++;
					}
					else{
						matrix[i][j].flag = true;
						path.pop(i,j);
						t--; 
					}
				}
			}
			else{
				matrix[i][j].flag = true;
				path.pop(i,j);
				t--;
			}	
		}
	
		// Print Path
		Print(path, str);
	}


	file.close();
	return 0;
}
