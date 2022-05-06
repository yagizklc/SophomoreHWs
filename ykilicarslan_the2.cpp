#include "strutils.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;


// Yagiz Kilicarslan 28126


//function 1
bool check_input(string color, double Height, double Length, double Width){

 	if (bool (!atof(tostring(Length))) || bool (!atof(tostring(Height))) || bool (!atof(tostring(Width)))){
		cout << "Invalid entry for " << color << " cuboid. Dimensions should be positive real numbers!" << endl;
		return false;
	} 

	else if ((Height<0) ||(Length<0) || (Width<0)){
		cout << "Invalid entry for " << color << " cuboid. Dimensions should be positive real numbers!" << endl;
		return false;
	}

	else{
		return true;
	}
}


//function 2 
void checkCubeandDisplay(string color, double Height, double Length, double Width){
	if ((Height == Length) && (Width == Height) && (Width == Length)){
		cout << color << " cuboid is a cube."<< endl;
	}
	else{
		cout << color << " cuboid is not a cube." << endl;
	}
}


//function 3
void display(string color, double area, double volume){
	cout << "Results for the " << color << " cuboid:" << endl; 
	cout << "Area: " << area << endl;
	cout << "Volume: " << volume << endl;
}


//function 4
void calculate(string color, double Height, double Length, double Width, double & Area, double & Volume){
	Area = 2*(Height*Length + Height*Width + Width*Length);
	Volume = (Height*Length*Width);
	display(color, Area, Volume);
	checkCubeandDisplay(color, Height, Length, Width);
}


//function 5  
string compare(string color1, string color2, string chosen_metric, double metric1, double metric2){
	if (chosen_metric == "Area"){
		if (metric1 > metric2){
			return (color1+" has the largest area.");
		}

		else if (metric1 < metric2){
			return  (color2+" has the largest area.");
		}

		else if (metric1 == metric2){
			return ("Two cuboids have the same area.");
		}
	}

	else if (chosen_metric == "Volume"){
		if (metric1 > metric2){
			return color1+" has the largest volume.";
		}

		else if (metric1 < metric2){
			return color2+" has the largest volume.";
		}

		else if (metric1 == metric2){
			return "Two cuboids have the same volume.";
		}
	}
}




int main(){
	cout.setf(ios::fixed);
	cout.precision(2);
	
	string color1, color2;
	double Height1, Length1, Width1;
	double Height2, Length2, Width2;
	double area1, volume1;
	double area2, volume2;
//------------------------------------------------------------------

	// welcome
	cout << "Hello! This program compares two cuboids..." << endl;
	cout << "Please enter colors for the two cuboids: ";
	cin >> color1 >> color2;


	// check color
	if (LowerString(color1) == LowerString(color2)){
		cout << "Color names cannot be the same, good bye..."<< endl;
		return 0;
	}
//-------------------------------------------------------------------

	// input 1 - check
	cout << "Please enter length, width and height of the " << color1 << " cuboid: ";
	cin >> Length1 >> Width1 >> Height1;

	if (!check_input(color1, Height1, Length1, Width1)){
		return 0;
	}

	// input 2 - check
	cout << "Please enter length, width and height of the " << color2 << " cuboid: ";
	cin >> Length2 >> Width2 >> Height2;

	if (!check_input(color2, Height2, Length2, Width2)){
		return 0;
	}
//--------------------------------------------------------------------	

	// calculate
	calculate(color1, Height1, Length1, Width1, area1, volume1);
	cout << endl;
	calculate(color2, Height2, Length2, Width2, area2, volume2);
	cout << endl;
//--------------------------------------------------------------------

	// compare
	cout << "Comparison of the two cuboids:" << endl;
	cout << compare(color1, color2, "Volume", volume1, volume2)<< endl;
	cout << compare(color1, color2, "Area", area1, area2)<< endl;


	return 0;
}
