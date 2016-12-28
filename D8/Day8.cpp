/*
 * =====================================================================================
 *
 *       Filename:  Day8.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/27/2016 01:24:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  youngthvg, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#define TALL 6
#define WIDE 50
enum Command{ Rect, xRotate, yRotate};
void printBox(bool box[][WIDE]){
	for(int y = 0; y < TALL; ++y){
		for(int x = 0; x < WIDE; ++x) std::cout << box[y][x];
		std::cout << "\n";
	}

}
// will emulate turning on the top-right w*h
void rect(int w, int h, bool box[][WIDE]){
	for(int y = 0; y < h; ++y){
		for(int x = 0; x < w; ++x) box[y][x] = true;
	}
}
void rotateR(int rY, int shifts, bool box[][WIDE]){
	// will rotate row Y by amount shifts.
	bool original[TALL][WIDE]; // will contain the original values, to be referenced.
	std::copy(&box[0][0], &box[0][0]+TALL*WIDE,&original[0][0]); // copy old stuff.
	
	for(int c = 0; c < WIDE; ++c){ // we will be shifting WIDE columns.
		if((c + shifts) < WIDE) box[rY][c + shifts] = original[rY][c];// check if there is enough space for the shift.
		else box[rY][(c + shifts) - WIDE] = original[rY][c]; // if there isnt enough space.
	}
}
void rRow(bool box[][WIDE], bool original[][WIDE], int pos, int shifts){
	for(int c = 0; c < WIDE; ++c){
		if((c + shifts) < WIDE) box[pos][c + shifts] = original[pos][c];
		else box[pos][(c + shifts) - WIDE] = original[pos][c];
	}
}
void rCol(bool box[][WIDE], bool original[][WIDE], int pos, int shifts){
	for(int r = 0; r < TALL; ++r){
		if((r + shifts) < TALL) box[r + shifts][pos] = original[r][pos];
		else box[(r + shifts) - TALL][pos] = original[r][pos];
	}
}
void rotate(bool box[][WIDE], int pos, int shifts, std::function<void (bool[][WIDE],bool[][WIDE],int,int)> func){
	// copy items first.
	bool original[TALL][WIDE];
	std::copy(&box[0][0], &box[0][0] + TALL * WIDE, &original[0][0]);
	// call responding function.
	func(box, original, pos, shifts); // for loop will occur here.
}
std::vector<std::string> split(std::string s){
	std::string tmp = "";
	std::vector<std::string> v;
	for(int i = 0; i < s.length(); ++i){
		if(s[i] == ' '){ 
			v.push_back(tmp);
			tmp = "";
		}
		else tmp += s[i];
	}
	v.push_back(tmp);
	return v;
}
int getPos(std::vector<std::string> &v, char l){
	for(int i = 0; i < v.size(); ++i){
		for(int j = 0; j < v[i].length(); ++j){
			if(v[i][j] == l){ // parse from letter. letter --> either 'y' or 'x'.
				int c = 0;
				for(int n = j + 2; n < v[i].length(); ++n){
					++c;
				}
				return std::stoi(v[i].substr(j + 2, c));
			}
		}
	}
}
int getShifts(std::vector<std::string> &v){
	return std::stoi(v[v.size() - 1].substr(0));
}
int getWidth(std::string ln){
	std::string s = "";
	for(int i = 0; ln[i] != 'x'; ++i) s += ln.substr(i,1);
	return std::stoi(s);
}
int getHeight(std::string ln){
	std::string s = "";
	for(int i = ln.length() - 1; ln[i] != 'x'; --i) s += ln.substr(i,1);
	return std::stoi(s);
}
Command interpretln(std::vector<std::string> v){
	if(v[0] == "rect") return Rect;
	else return (v[1] == "row") ? yRotate : xRotate;
}
int main(){
	bool box[TALL][WIDE]; // 6 tall, 50 wide.
	for(int y = 0; y < TALL; ++y){ // init box.
		for(int x = 0; x < WIDE; ++x) box[y][x] = false; // all off at first
	} 
	  
	std::ifstream file("input.txt");
	std::string ln;
	while(std::getline(file,ln)){ // get line of command
		std::cout << "\n\nNEW LN: " << ln << "\n\n";
		std::vector<std::string> v = split(ln);
		Command command = interpretln(v);
		if(command == Rect) rect(getWidth(v[v.size() - 1]), getHeight(v[v.size() - 1]), box);
		else if(command == yRotate) rotate(box,getPos(v,'y'), getShifts(v), rRow);
		else rotate(box, getPos(v,'x'), getShifts(v), rCol);
		printBox(box);
	}
	// PART A:
	int ctr = 0;
	for(int y = 0; y < TALL; ++y){
		for(int x = 0; x < WIDE; ++x){
			if(box[y][x]) ++ctr;
		}
	}
	std::cout << "cntr: " << ctr << "\n"; // part A
	// PART B:
	// You'll need to manually figure out the letters, but spacing it helps.
	for(int i = 1; i <= WIDE/5; ++i){
		for(int y = 0; y < TALL; ++y){
			for(int x = 5 * (i - 1); x <= (5 * i); ++x){
				std::cout << box[y][x];
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	return 0;
}
