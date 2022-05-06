#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "strutils.h"
using namespace std;


// Yagiz Kilicarslan 28126



 //  -----------------------------------------------------------------

void Location(int wordCount, string& location){
	location += (itoa(wordCount) + " ");
}

string readpool(ifstream& poolInput){
	string poolLine, poolWord, pool="";
	

	while(getline(poolInput, poolLine)){
		

		istringstream strLine(poolLine); 
		while(strLine >> poolWord){
			

			ToLower(poolWord);
			pool += poolWord + " ";
		}
	}

	return pool;
}

string readtext(ifstream& textInput, string& location){

	string textLine, textWord, text = "";
	
	while(getline (textInput, textLine)){

		int wordCount=0;
		istringstream strLine(textLine);
		while(strLine >> textWord){
			wordCount++;

			ToLower(textWord);
			text += textWord + " ";
		}
		Location(wordCount, location);
	}

	return text;
}

int Spellcheck(string textWord, string poolWord){
	string result;
	int similar_count = 0;

	if (textWord.length() == poolWord.length()){ 
		for(int t=0; t < poolWord.length(); t++){
			if (textWord.substr(t,1) == poolWord.substr(t,1)){
				similar_count +=1;
			}	
		}
		return similar_count;
	}
}

string rawResult(string text, string pool){
	string textWord, poolWord, strLine;
	string rawRes = "";

	istringstream strText(text);
	while(strText >> textWord){
		string result = ""; 
		bool stop = false;
		double l = textWord.length();
		l = l/2;
		double fewest = l;
		istringstream strPool(pool);
		while( (strPool >> poolWord) && (stop == false) ){
			if (textWord.length() == poolWord.length()){ 
	
				if (Spellcheck(textWord, poolWord) == textWord.length()){
					result = poolWord;
					stop = true;
				}
				
				else if (Spellcheck(textWord, poolWord) >= l){
					if (Spellcheck(textWord, poolWord) > fewest){
						result = poolWord + " ";
						fewest = Spellcheck(textWord, poolWord); 
					}
					else if (Spellcheck(textWord, poolWord) == fewest){
						result += poolWord + " ";
					}
				}
				
			

			}
		}

		if (result == ""){
			result = ("{" + textWord + "}");
		}

		else if (result.find(" ") != string::npos){
			if(result.find(" ") != result.rfind(" ")){
				istringstream strResult(result);
				string resWord;
				result = "(";
				while(strResult >> resWord){
					result += resWord + ",";
				}
				result = result.substr(0, result.length()-1);
				result += ")";
			}
			else{
				result = result.substr(0, result.length()-1);
			}
		}

		rawRes += result + "/";
	}

	return rawRes;
}

void Print(string rawRes, string location){
	string adet;
	istringstream strLoc(location);
	int i=0;

	while(strLoc >> adet){
		string output = "";
		int r = atoi(adet);
		int t =0;
		while ((i < rawRes.length()) && (t < r)){
			output += rawRes.substr(i,rawRes.find("/",i)-i) + " ";
			i = rawRes.find("/",i)+1;
			t++;
		}
		cout << output.substr(0, output.length()-1);
		cout << endl;
	}


}



int main(){
				// INPUT CHECK AND FLOW

	ifstream poolInput, textInput;
	string poolName, textName;

// POOL OPEN
	cout << "Please enter a filename for the word pool: ";
	cin >> poolName;

	poolInput.open(poolName.c_str());

	while (poolInput.fail()){
		cout << "Cannot open the word pool file."<< endl;
		cout << "Please enter a filename for the word pool: ";
		cin >> poolName;
		poolInput.open(poolName.c_str());
	}
		

// TEXT OPEN
	cout << "Please enter a filename for the main text: ";
	cin >> textName;

	textInput.open(textName.c_str());

	while (textInput.fail()){
		cout << "Cannot open the main text file."<< endl;
		cout << "Please enter a filename for the main text: ";
		cin >> textName;
		textInput.open(textName.c_str());
	}

	cout << "You may find the results below:" << endl << endl;



// READING AND CONVERTING FILE TO STRING
	string pool;
	pool = readpool(poolInput);

	//cout << "pool: " << pool << endl;
	

	string text;
	string location = "";  // also find location of words
	text = readtext(textInput, location);

	//cout << "text: " << text << endl;
	//cout << "location: " << location << endl;



// Spellcheck and Print
	string rawRes;

	rawRes = rawResult(text, pool); // find correspondand results
	//cout << "rawRes: " << rawRes << endl;
	
	Print(rawRes, location);

	


	poolInput.close();
	textInput.close();
	return 0;
}
