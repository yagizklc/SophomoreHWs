/* ********************************************

Yagiz Kilicarslan 28126

This program creates a matrix from the letters 
of a given word, which is stored within a file.
Placement of the letters is decided by Starting Point,
Direction and Orientation inputs that are also in the file.

*********************************************** */


#include <iostream>	// for cin, cout
#include <vector>	// for vector operations
#include <string>	// for string data type
#include <fstream>	// for file operations
#include <sstream>  // for istringstream 
using namespace std;


/****************************************
openFile: Takes input file and file name as parameters
then tries to open file with that name until a valid
file name is entered

*****************************************/
void openFile(ifstream & input, string fileName){ 

	input.open(fileName.c_str());
	while (input.fail()){ // try until a correct file name is entered
		cout << "File name is incorrect, please enter again: ";
		cin >> fileName;
		input.open(fileName.c_str());
	}
}


/**********************************
matrixGenerator: Takes row and column number as parameters 
then firstly creates a 2D vector of '-' with size of column number
after that creates a Matrix from these 2D vectors with size of row number

***********************************/
vector <vector <char>> matrixGenerator(int row, int col){

	vector <char> v(col, '-'); // 2D Vector => [-,-,-,..] with column size 
	vector <vector <char>> matrix(row, v); // Matrix => [[-,-,..],[-,-,..],[-,-,..],...] with row size
	return matrix;
}


/************************************
prompt: Takes inputs that are taken from the file as parameters
then prints out an appropriate message according to sign value
that is determined by weather the word is placed in the matrix successfully

*************************************/
void prompt(string word, bool sign, int spR, int spC, string direction, string orientation){
	
	if (sign){	// sign is for positive/negative output difference
		cout << "\""<<  word << "\"" << " was put into the matrix with given starting point: " 
			<< spR << "," << spC << endl <<"direction: " << direction
			<< "	orientation: " << orientation << endl;
	}

	else{
		cout << "\"" << word << "\"" << " could not be put into the matrix with given starting point: " 
			<< spR << "," << spC << endl << "direction: " << direction
			<< "	orientation: " << orientation << endl;
	}
}


/**************************************
PrintMatrix: Takes the created matrix as parameter
then prints it using a basic nested loop

***************************************/
void printMatrix(vector <vector <char>> &matrix){

	for (int i = 0; i < matrix.size(); i++){
		for (int k = 0; k< matrix[0].size(); k++){
			cout << matrix[i][k] << "  " ;
		}
		cout << endl;
	}
}



/*************************************
Right/Left/Up/Down Direction: These functions try to reach the next location 
in their given direction within the matrix. If that location exist and available
then adds the given letter of the word and updates the location. If not, then returns false

**************************************/
bool rightDirection(char c, vector <vector <char>> &matrix, int &spR, int &spC){
	
	if (spC < matrix[0].size()-1 && matrix[spR][spC+1] == '-'){ // checks next column
		matrix[spR][spC+1] = c;
		spC++;	//updates column location
		return true;
	}

	else{
		return false;
	}
}


bool leftDirection(char c, vector <vector <char>> &matrix, int &spR, int &spC){
	
	if (spC > 0 && matrix[spR][spC-1] == '-'){ //checks previous column
		matrix[spR][spC-1] = c;
		spC--;	//updates column location
		return true;
	}

	else{
		return false;
	}
	
}


bool upDirection(char c, vector <vector <char>> &matrix, int &spR, int &spC){

	if (spR > 0 && matrix[spR-1][spC] == '-'){ // checks previous row
		matrix[spR-1][spC] = c;
		spR--;	//updates row location
		return true;
	}

	else{
		return false;
	}
}


bool downDirection(char c, vector <vector <char>> &matrix, int &spR, int &spC){

	if (spR < matrix.size()-1 && matrix[spR+1][spC] == '-'){ //checks next row
		matrix[spR+1][spC] = c;
		spR++;	//updates row location
		return true;
	}

	else{
		return false;
	}
}


/******************************
Operation: Takes the direction values as parameters
then tries placement for each direction. If one of them works,
then the operation stops. Howeever, if none of them work,
this means there is no room to go for that letter,
therefore operation returns false

*******************************/
bool operation(string d1, string d2, string d3, char &c, vector <vector <char>> &matrix, int &spR, int &spC){
	vector <string> v; //creating vector from directions to sequentially try them
	v.push_back(d1);
	v.push_back(d2);
	v.push_back(d3);
	
	bool stop = false;

	for (int i = 0; i < v.size() && !stop; i++){
		if (v[i] == "r"){
			stop = rightDirection(c, matrix, spR, spC);
		}
		else if (v[i] == "u"){
			stop = upDirection(c, matrix, spR, spC);
		}
		else if (v[i] == "l"){
			stop = leftDirection(c, matrix, spR, spC);
		}
		else if (v[i] == "d"){
			stop = downDirection(c, matrix, spR, spC);
		}
	}

	if (stop == false){ // if none of the directions successfully worked, then returns false
		return false;
	}
	else{
		return true;
	}
}


/*****************************************
PlacementMain: main part of placement algorithm.
Tries to place every letter of the word. 
-If the first letter is not placed, stops and signals failure.
-else If any other letter cannot be placed, stops and signals failure.
-else no problem returns not-Fail

***************************************/

bool placementMain(string &word, int &spR, int &spC, string &direction, 
				   string &orientation, vector <vector <char>> &matrix){
	
	bool fail = false;
	char c;
	string orgD = direction;  // Initial direction value, this is used for prioritizing the originial direction
	c = word.at(0);

	// Placement of first letter
	if (matrix[spR][spC] == '-'){
		matrix[spR][spC] = c;
	}
	else{
		return true; // if fails stops immediately
	}

	
	for (int i = 1; i < word.length() && !fail; i++){
		c = word.at(i);

		if (orgD == "r"){
			if (!rightDirection(c, matrix, spR, spC)){
				if (orientation == "CW"){
					fail = !operation("d","l","u",c, matrix, spR, spC);
				}
				else if (orientation == "CCW"){
					fail = !operation("u","l","d",c, matrix, spR, spC);
				}
			}
		}
		

		else if (orgD == "d"){
			if (!downDirection(c, matrix, spR, spC)){			
				if (orientation == "CW"){
					fail = !operation("l","u","r",c, matrix, spR, spC);
				}
				else if (orientation == "CCW"){
					fail = !operation("r","u","l",c, matrix, spR, spC);
				}
			}
		}
		

		else if (orgD == "l"){
			if (!leftDirection(c, matrix, spR, spC)){			
				if (orientation == "CW"){
					fail = !operation("u","r","d",c, matrix, spR, spC);
				}
				else if (orientation == "CCW"){
					fail = !operation("d","r","u",c, matrix, spR, spC);
				}
			}	
		}


		else if (orgD == "u"){
			if (!upDirection(c, matrix, spR, spC)){								
				if (orientation == "CW"){
					fail = !operation("r","d","l",c, matrix, spR, spC);
				}
				else if (orientation == "CCW"){
					fail = !operation("l","d","r",c, matrix, spR, spC);
				}
			}
		}	
	}

	return fail;
}




int main(){


//	File opening 
//	---------------------------------
	ifstream input;			
	string fileName;

	cout << "Please enter the name of the file: ";	
	cin >> fileName;
	openFile(input, fileName);	// Tries to open file until a valid file name is given.
	cout << endl;
//	---------------------------------


//	Initializations
//	----------------------------------
	int row, col;	// row and column of Matrix
	int spR, spC;	// Starting Point Row/Column
	int orgSpr, orgSpc;	// Initial values of spR/spC
	string word, direction, orientation;
	string orgD;	// Initial value of Direction
	vector <vector <char>> matrix;	
	vector <vector <char>> orgmatrix;	// Initial matrix
//	----------------------------------


	string line;	// each line of file
	string w;		// will be used for detecting excessive words
	int wordCounter;	// will be used for detecting missing words
	int lineCount = 0;	// used for separating the first line (row/col values) from the others
	bool error;		// used for stoping after an error message

	while (getline(input, line)){  // storing each line in 'line' variable
		istringstream strStream(line);	// converting line into input stream called strStream

		if (lineCount == 0){  // detecting first line 
			strStream >> row >> col;	

			if ((row <= 0) || (col <= 0)){ // checking row/col values
				cout << "Invalid number for row and/or column!" << endl;
				return 0;
			}

			matrix = matrixGenerator(row, col);  // Generating Matrix
			lineCount++;
		}

		else{
			error = false; 
			wordCounter = 0;

			strStream >> word; // word input
			wordCounter++;

			if (strStream >> spR >> spC){ // Starting Point Row/colum values input
				wordCounter += 2;
				if (!((0<=spR && spR<row) && (0<=spC && spC<col))){  // input check
					cout << "Starting point is out of range! Point:	" << spR << " " << spC << endl << endl;
					error = true;
				}
			}


			if (strStream >> direction){  // Direction input
				wordCounter++;
				if ( (!((direction == "d") || (direction == "r") || (direction == "l") || (direction == "u"))) && !error){ // Input check
					cout << "Invalid input for direction! Direction: " << direction << endl<< endl;
					error = true;
				}
			}
			
			if (strStream >> orientation){  // Orientation input
				wordCounter++;
				if ( (!(orientation == "CW" || orientation == "CCW")) && !error){  // Input check
					cout << "Invalid input for orientation! Orientation: " << orientation << endl << endl;
					error = true;
				}
			}

			if ( ( (wordCounter < 5) || (strStream >> w) ) && (!error)){ // checking Input count on a line 
				cout << "Invalid line! Number of values is different than 5." << endl << endl;
				error = true;
			}
		
			if (error == false){ // if there is no error flag placement algorithm starts
				orgSpr = spR;  // Storing original values of Starting Point, direction and matrix for printing purposes
				orgSpc = spC;
				orgD = direction;
				orgmatrix = matrix;
				if (!placementMain(word, spR, spC, direction, orientation, matrix)){ // if Placement Algorithm successes  
					prompt(word, true, orgSpr, orgSpc, orgD, orientation); // print positive message
					printMatrix(matrix);
					cout << endl;
				} 
				else{  // if placement algorithm did not succeded
					matrix = orgmatrix; // get rid of last edit on matrix
					prompt(word, false, orgSpr, orgSpc, orgD, orientation); // print negative message
					printMatrix(matrix);
					cout << endl;
				}
			}
		}
	}

	input.close();
	return 0;
}