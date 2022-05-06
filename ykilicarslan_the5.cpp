#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "strutils.h"
#include <cctype>
using namespace std;

struct seriesData{
	string name, actor;
	double rating;
	int count;
};

seriesData SD;
vector<seriesData> seriesVec;
vector<seriesData> favList;

void readRating(ifstream& rating, seriesData& SD, vector<seriesData>& seriesVec){
	string line, word;
	while(getline(rating, line)){
		string seriesName;
		double rat;
		istringstream strLine(line);
		int num = 0;
		while (strLine >> word){
			if (num == 0){
				rat = atof(word);
				num++;
			}

			else{
				ToLower(word);
				seriesName += word + " ";
			}
		}

		seriesName = seriesName.substr(0,seriesName.length()-1);
		bool var = false;
		int repeatIndex;
		for (int i=0; i < seriesVec.size() && (!var); i++){
			if(seriesVec[i].name == seriesName)
				var = true;
				repeatIndex = i;
		}

		if (!var){
			seriesData veri; 
			veri.name = seriesName;
			veri.rating = rat;
			veri.count = 1;
			seriesVec.push_back(veri);
		}

		else if (var){
			seriesVec[repeatIndex].count += 1;
			seriesVec[repeatIndex].rating += rat; 
		}
	}

	for(int x=0; x < seriesVec.size(); x++)
		if (seriesVec[x].count > 1){
			double r = seriesVec[x].rating / seriesVec[x].count;
			seriesVec[x].rating = r;
		}
}

void readActor(ifstream& actor, seriesData& SD, vector<seriesData>& seriesVec){
	string line, word;
	while(getline(actor, line)){
		string actorName="", seriesName="";
		int stop;
		stop = line.find(";");
		actorName = line.substr(0,stop);
		seriesName = line.substr(stop+1);

		istringstream actorWord(actorName);
		actorName="";
		while(actorWord >> word){
			actorName+=word + " ";
		}
		actorName = actorName.substr(0,actorName.length()-1);

		istringstream seriesWord(seriesName);
		seriesName = "";
		while(seriesWord >> word){
			ToLower(word);
			seriesName += word + " ";
		}
		seriesName = seriesName.substr(0,seriesName.length()-1);

		for(int i=0; i<seriesVec.size(); i++){
			if (seriesVec[i].name == seriesName)
				seriesVec[i].actor = actorName;
		}
	}
}

void menu(string& operation){

	cout << "---" << endl;
	cout << "MENU" << endl;
	cout << "1. Print the series" << endl;
	cout << "2. Search the series according to the rating" << endl;
	cout << "3. Add the series to the favorite list" << endl;
	cout << "4. Print the favorite list" << endl;
	cout << "5. Exit" << endl;
	cout << "---" << endl;
	cout << "Enter your choice: ";
	cin >> operation;
	cout << "---" << endl;
}


void sorting(vector<seriesData>& seriesVec){
	
	
	int j, k, minIndex, numElts = seriesVec.size();
	seriesData temp;
	
	for(k=0; k< numElts-1; k++){
		minIndex = k;
		

		for(j=k+1; j < numElts; j++){
			if(seriesVec[j].rating < seriesVec[minIndex].rating){
				minIndex = j;
			}	
			else if (seriesVec[j].rating == seriesVec[minIndex].rating){
				if(seriesVec[j].name > seriesVec[minIndex].name){
					minIndex = j;
				}
			}
		}
		temp = seriesVec[k];
		seriesVec[k] = seriesVec[minIndex];
		seriesVec[minIndex] = temp;
	}
/*
	for(k=0; k< numElts-1; k++){
		minIndex = k;
		

		for(j=k+1; j < numElts; j++){
			if(seriesVec[j].rating == seriesVec[minIndex].rating){
				bool stop = false;
				for(int i=0; i < seriesVec[j].name.length() && i < seriesVec[k].name.length() && stop == false; i++){
					if(int(UpperString(seriesVec[j].name).at(i)) > int(UpperString(seriesVec[k].name).at(i))){
						minIndex = j;
						stop = true;
					}	
				}	
			}	
		}
		temp = seriesVec[k];
		seriesVec[k] = seriesVec[minIndex];
		seriesVec[minIndex] = temp;
	}
	*/
}



void Print(vector<seriesData>& seriesVec){ //option1
	
	sorting(seriesVec);

	cout << "RANK,NAME,ACTOR,POINTS" << endl;
	for (int i =seriesVec.size()-1; i >= 0; i--){
		cout << seriesVec.size()-i <<",";
		cout << UpperString(seriesVec[i].name) << ",";
		cout << UpperString(seriesVec[i].actor) << ",";
		cout << seriesVec[i].rating << endl;
	}

}

void Search(vector<seriesData>& seriesVec){

	double minRating;
	cout << "Please enter the minimum rating: ";
	cin >> minRating;

	if(minRating > 10 || minRating < 0){
		cout << "This is not a valid rating!" << endl;
	}

	else{
		sorting(seriesVec);

		cout << "RANK,NAME,ACTOR,POINTS" << endl;
		for (int i = seriesVec.size()-1; i >= 0 && seriesVec[i].rating >= minRating; i--){
			cout << seriesVec.size()-i << ",";
			cout << UpperString(seriesVec[i].name) << ",";
			cout << UpperString(seriesVec[i].actor) << ",";
			cout << seriesVec[i].rating << endl;
		}
	}
}

void addFav(vector<seriesData>& seriesVec, vector<seriesData>& favList){
	string s;

	cout << "Please enter the name of series: ";
	int x=0;
	while(getline(cin,s) && x==0){
		x++;
	}

	
	bool var = false;
	int index;
	for(int i=0; i < seriesVec.size() && (!var); i++){
		if(LowerString(seriesVec[i].name) == LowerString(s)){
			var = true;
			index = i;
		}
	}

	if(!var){
		cout << "There is no such TV series!" << endl;
	}

	else if (var){
		bool varAlready = false;
		for (int k=0; k< favList.size() && (!varAlready) ; k++){
			if(LowerString(favList[k].name) == LowerString(s)) {
				varAlready = true;
				
			}
		}

		if(varAlready == false){
			favList.push_back(seriesVec[index]);
		}
		
		else if (varAlready == true){
			cout << "Your favorite list already have " << UpperString(s) << endl;
		}
	}

}

void printFav(vector<seriesData>& favList){

	if (favList.size()==0){
		cout << "Your favorite list is currently empty!" << endl;
	}

	else{
		sorting(favList);

		cout << "RANK,NAME,ACTOR,POINTS" << endl;
		for (int i =favList.size()-1; i >= 0; i--){
			cout << favList.size()-i << ",";
			cout << UpperString(favList[i].name) << ",";
			cout << UpperString(favList[i].actor) << ",";
			cout << favList[i].rating << endl;
		}
	}
}


int main(){

	string ratingName, actorName;
	ifstream rating, actor;

//WELCOME
	cout << "Welcome to Netflix TV Series Ratings Calculator!" << endl;

//INPUT FILE
	cout << "Please enter a filename for Series-Actor file: " ;
	cin >> actorName;

	actor.open(actorName.c_str());

	while(actor.fail()){
		cout << "Can not find the specified file." << endl;
		cout << "Please enter a filename for Series-Actor file: ";
		cin >> actorName;
		actor.open(actorName.c_str());
	}

//Rating FILE
	cout << "Please enter a filename for Rating file: ";
	cin >> ratingName;

	rating.open(ratingName.c_str());

	while(rating.fail()){
		cout << "Can not find the specified file." << endl;
		cout << "Please enter a filename for Rating file: ";
		cin >> ratingName;
		rating.open(ratingName.c_str());
	}

	readRating(rating, SD, seriesVec);
	
	seriesData SD;
	readActor(actor, SD, seriesVec);


//MENU	
	string operation;
	bool exit = false;

	while(exit == false){
		menu(operation);
		if (!((operation == "1") || (operation == "2") || (operation == "3") ||  (operation == "4") ||  (operation == "5"))){
				cout << "This is not a valid option!" << endl;
		}
		else{
			if(operation == "1"){
				Print(seriesVec);
			}

			else if(operation == "2"){
				Search(seriesVec);
			}

			else if(operation == "3"){
				addFav(seriesVec, favList);
			}
			else if(operation == "4"){
				printFav(favList);
			}
			else if (operation == "5"){
				exit = true;
			}
		}	
	}


	actor.close();
	rating.close();
	return 0;
}
