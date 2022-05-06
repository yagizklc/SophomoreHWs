//#include <iostream>
//#include <vector>
//#include <string>
#include "strutils.h"
#include <fstream>
#include <sstream>
#include "favoriteseries.h"
using namespace std;


void menu(string& option){
	cout << "---" << endl;
	cout << "MENU" << endl;
	cout << "1. Print all TV series" << endl;
	cout << "2. Add TV series" << endl;
	cout << "3. Drop TV series" << endl;
	cout << "4. Print your favorite series with schedule" << endl;
	cout << "5. Print all your favorite actors" << endl;
	cout << "6. Exit" << endl;
	cout << "---" << endl;
	
	cout << "Please enter your choice: ";
	cin >> option;
}

void InsertSort(vector <episode> & allEP, episode & EP){
	int count = allEP.size();
	allEP.push_back(EP);
	// morning afternoon evening night
	int loc = count;
	bool stop = false;
	
	while (loc > 0 && ( allEP[loc-1].date >= EP.date) && !stop){
		if (allEP[loc-1].date > EP.date){
			allEP[loc] = allEP[loc-1];
			loc--;
		}
		
		else if (allEP[loc-1].date == EP.date){
			if ( allEP[loc-1].slot != "MORNING" && EP.slot == "MORNING" ){
				allEP[loc] = allEP[loc-1];
				loc--;
			}
			else if ( (allEP[loc-1].slot == "EVENING" || allEP[loc-1].slot == "NIGHT") && EP.slot == "AFTERNOON"){
				allEP[loc] = allEP[loc-1];
				loc--;
			}
			else if ( allEP[loc-1].slot == "NIGHT" && EP.slot == "EVENING"){
				allEP[loc] = allEP[loc-1];
				loc--;
			}
			else if ( allEP[loc-1].slot == EP.slot){
				if (allEP[loc-1].seriesCode > EP.seriesCode){
					allEP[loc] = allEP[loc-1];
					loc--;
				}
				else {
					stop = true;
				}
			}
			else{	
				stop = true;
			}
			
		}
	}
	allEP[loc] = EP;
	

	/*
	while (loc > 0 && allEP[loc-1].date > EP.date){
		allEP[loc] = allEP[loc-1];
		loc--;
	}
	allEP[loc] = EP;
	*/
	
}

void readSeries(ifstream & seriesF, vector<series> & allV){
	string seriesLine, word;

	while(getline(seriesF, seriesLine)){
		istringstream strLine(seriesLine);
		int i = 0;
		series SE;
		string actorName = "", seriesN = "";
		bool refresh = false;
		while (strLine >> word){
			if (refresh){
				actorName = "";
			}
			refresh = false;

			if(i == 0){
				SE.seriesCode = atoi(word); 
				i++;
			}
			else if (i == 1){
				if (word.find(";") != string::npos){
					seriesN += word.substr(0,word.length()-1);
					SE.seriesName = seriesN;
					i++;
				}
				else{
					seriesN += word + " ";
				}

			}
			else{
				if (word.find(",") != string::npos){
					actorName += word.substr(0, word.length()-1);
					SE.actorNames.push_back(actorName);
					refresh = true;
				}
				else{
					actorName += word + " ";
				}
			}
		}

		SE.actorNames.push_back(actorName);
		allV.push_back(SE);
	}

	for (int i =0; i < allV.size(); i++){
		for (int k = 0; k < allV[i].actorNames.size(); k++){
			if (allV[i].actorNames[k].substr(allV[i].actorNames[k].length()-1) == " "){
				allV[i].actorNames[k] = allV[i].actorNames[k].substr(0,allV[i].actorNames[k].length()-1);
			}
		}
	}
}

void readEpisodes(ifstream & episodesF, vector<series> & allV){
	string seriesLine, word;

	while(getline(episodesF, seriesLine)){
		istringstream strLine(seriesLine);
		episode EP;
		int i = 0;
		string epName = "";
		while(strLine >> word){ 
			if (i == 0){
				EP.seriesCode = atoi(word);
				i++;
			}
			else if (i == 1){
				int m, d, y, b, s;
				for (int k= 0; k < 3; k++){
					b = word.find("/");
					s = word.rfind("/");
					if (k == 0){
						m = atoi(word.substr(0, b));
					}
					else if (k == 1){
						d = atoi(word.substr(b+1, s-b-1));
					}
					else if (k == 2){
						y = atoi(word.substr(s+1));
					}
				}
				Date EPdate(m,d,y);
				EP.date = EPdate;
				i++;
			}
			else if (i == 2){
				EP.slot = UpperString(word); 
				i++;
			}
			else{ 
				epName += UpperString(word) + " ";
			}
		}

		EP.episodeName = epName.substr(0,epName.length()-1);
		ToUpper(EP.episodeName);
		bool stop = false;
		for (int i = 0; i < allV.size() && !stop; i++ ){
			if (allV[i].seriesCode == EP.seriesCode){
				allV[i].episodes.push_back(EP);
				stop = true;
			}
		}
	}
}

void PrintAll(vector <episode> &allEP, vector <series> & allV){
	for (int i = 0; i < allV.size() ; i++){
		for (int k = 0; k < allV[i].episodes.size() ; k++){
			if (allEP.size() == 0){
				allEP.push_back(allV[i].episodes[k]);
			}
			else{
				InsertSort(allEP, allV[i].episodes[k]);
			}
		}
	}

	for (int i = 0; i < allEP.size(); i++){
		for (int k = 0; k < allV.size(); k++){
			if (allEP[i].seriesCode == allV[k].seriesCode){
				cout << allV[k].seriesCode << ","
					<< UpperString(allV[k].seriesName) << "," 
					<< allEP[i].episodeName << ","
					<< allEP[i].date << ","
					<< allEP[i].slot << endl;
			}
		}
	}
}


int main(){
	
	ifstream seriesF, episodesF;
	string fsn = "series.txt", fen = "episodes.txt";
	
	vector <series> allV;

// Read Series file into allV vector
	seriesF.open(fsn.c_str());

	readSeries(seriesF, allV);

// Read Episodes file into series of allV vector
	episodesF.open(fen.c_str());

	readEpisodes(episodesF, allV);



//  welcome -- take name-surname and make it uppercase
	string name, surname;
	cout << "Welcome to my favorite TV series schedule program!" << endl;
	cout << "Please, enter your name and surname: ";
	cin >> name >> surname;
	
	ToUpper(name);
	ToUpper(surname);

	FavoriteSeries FavSeries(name, surname); // Construct Class

	string option = "0";

	bool stop = false;
	while(option != "6" && !stop){
		menu(option);

		if (option == "1"){
			vector <episode> allEP;
			cout << "CODE,SERIES,EPISODE,DATE,SLOT" << endl;
			PrintAll(allEP, allV);
		}

		else if (option == "2"){
			cout << "Enter code for the TV series you want to add: ";
			series SE;
			cin >> SE.seriesCode;
			
			bool exists = false;
			for (int i = 0; i < allV.size() && !exists; i++){
				if (allV[i].seriesCode == SE.seriesCode){
					SE = allV[i];
					exists = true;
				}
			}
			if(!exists){
				cout << FavSeries.getFullName() << ", there is no such TV series in the database!" << endl; 
			}

			else{
				FavSeries.addSeries(SE);
			}
		}

		else if (option == "3"){
			if (FavSeries.isListEmpty()){
				cout << FavSeries.getFullName() << ", you did not add any TV series yet!" << endl;
			}
			else{
				series SE;
				cout << "Enter code for the TV series you want to drop: ";
				cin >> SE.seriesCode;
				FavSeries.dropSeriesSorted(SE.seriesCode);
			}
		}

		else if (option == "4"){
			FavSeries.displayFavoriteList();
		}

		
		else if (option == "5"){
			FavSeries.displayFavoriteActors();
		}
		

		else if (option == "6"){
			cout << "Goodbye, " << FavSeries.getFullName() << "!"<< endl;
			stop = true;
		}

		else{
			cout << "Invalid option!" << endl;
		}
	}
	

	seriesF.close();
	episodesF.close();
	return 0;
}
