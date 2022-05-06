
// Yagiz Kilicarslan 28126 THE3
#include <iostream>
#include <string>
using namespace std;


bool source_check(string Source){
/*
	unsigned long location1 = Word.find("END");
	unsigned long location2 = Word.find("end");
	if (!((location1 != string::npos) || (location2 != string::npos))){
		return false;
	}
*/
	if (Source == ""){
		return false;
	}

	else{
		for (int i=0; i < Source.length() ; i++){
			int x = int(Source.at(i));
		
			if (! ( ((48 <= x) && (x<= 57)) || ((65 <= x) && ( x<= 90)) || ((97<=x) && ( x<= 122)) || (x==32) ) ){
				return false;
			}
		}
	}

	return true;

}

string input_source(){
	string Source = "", Word;
	const string Last_word = "end";
	const string Last_word2 = "END";

/*
	do{
		cout << "Enter source string: ";
		cin >> Word;
		while (!((Word == Last_word) || (Word == Last_word2))){
			Source += Word + " ";
			cin >> Word;
		}

	}
	while (!source_check(Source));

	return Source;
*/
	while ((!source_check(Source))){
		Source = "";
		cout << "Enter source string: ";
		cin >> Word;
		while (!((Word == Last_word) || (Word == Last_word2))){
			Source += Word + " ";
			cin >> Word;
		}
	}
	return Source;
/*
	if ((Source.find("end") == 0) || (Source.find("END") == 0)){
		return Source.substr(4);
	}
	
	else{
		return Source;
	}
*/





}	


bool search_check(string Search){
	if (Search == ""){ 
		return false;
	}

	int l = int(Search.at((Search.length() - 1)));
	if (! ((( l >= 42 ) && ( l <= 43)) || ( l == 46)) ){
		return false;
	}

	else {
		return true;
	}
}

string input_search(){
	string Search;
	cout << "Enter search string: ";
	cin >> Search;

	if ((Search == "quit") || (Search == "QUIT")){
		Search = "quit";
	}

	else{
		while(!search_check(Search)){
			cout << "Enter search string: ";
			cin >> Search;
			if ((Search == "quit") || (Search == "QUIT")){
				Search = "quit";
				break;
			}
		}
	}


	return Search;
}


void search_operation(const string Search, const string Source){

	string operation, parameter;
	if (Search.at(Search.length()-2) == '*'){
		operation = Search.substr(Search.length()-2);	
		parameter = Search.substr(0, Search.length()-2);
	} 
	else{
		operation = Search.substr(Search.length()-1);
		parameter = Search.substr(0, Search.length()-1);
	}
	



	// first word index
	if (Source.find(parameter) != string::npos){
		int word_index = Source.find(parameter);
		// cout << "Word Index: " << word_index << endl; 
		string new_source =  " " + Source + " ";
		// cout << "New Source: " << new_source << endl;
		string space = " ";
		while ((word_index < Source.length()-1) && (word_index != string::npos)){
			// finding word
			int space_index_end = new_source.find(space, word_index+1);
			int space_index_beg = new_source.rfind(space, word_index+1);
			// cout << "beg: " << space_index_beg << endl << "end: " << space_index_end << endl;
			string word = new_source.substr(space_index_beg+1, space_index_end-space_index_beg-1);
			// cout <<	"Word: " << word << endl;	
			// cout << "Operation: " << operation << endl << "Parameter: " << parameter << endl;
			int wl = word.length(); 
			int pl = parameter.length();
			// cout << "wl: " << wl << endl << "pl: " << pl << endl;

			if (operation == "+"){
				// cout << "+ calisiyir" << endl;
				if (word.substr(0,pl) == parameter){
					cout << "index: " << word_index << " word: " << word << endl;
				}
				word_index = Source.find(parameter, word_index+1);
			}


			else if (operation == "."){
				// cout << ". calisiyir" << endl;
				if ((word.substr(wl - pl, pl) == parameter) && (new_source.substr(word_index+1,pl+1) == parameter+" ")){
					cout << "index: " << word_index << " word: " << word << endl;
				}
				word_index = Source.find(parameter, word_index+1);
			}


			else if (operation == "*"){
				// cout << "* calisiyir" << endl;
				if ((!(word.substr(0,pl) == parameter))
				&& (!((word.substr(wl - pl, pl) == parameter)))){	//&& (new_source.substr(word_index+1,pl+1) == parameter+" ")))){
					//unsigned long loc = word.find(parameter);
					//if (loc != string::npos){
					cout << "index: " << word_index << " word: " << word << endl;
					//}
				}
				word_index = Source.find(parameter, word_index+1);
			}

			else if (operation == "**"){
				// cout << "** calisiyir" << endl;
				unsigned long loc = word.find(parameter);
				if (loc != string::npos){
					cout << "index: " << word_index << " word: " << word << endl;
				}
				word_index = Source.find(parameter, word_index+1);
			}
			else{
				word_index = Source.find(parameter, word_index+1);
			}
			
		}
	}
}



int main(){
	string Source, Search;
	Source = input_source();
	Search = input_search();
	// cout << "Source: " << Source << endl << "Search: " << Search << endl;

	while (!((Search == "QUIT") || (Search == "quit"))) {
		search_operation(Search, Source);
		Search = input_search();
	}
	
	return 0;
}
