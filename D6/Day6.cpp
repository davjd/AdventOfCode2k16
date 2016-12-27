/*
 * =====================================================================================
 *
 *       Filename:  Day6.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/26/2016 09:06:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  youngthvg
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
int main(){

	std::ifstream file("input.txt");
	std::map<char,int>  row[8];
	char r[8];
	while(file >> r[0] >> r[1] >> r[2] >> r[3] >> r[4] >> r[5] >> r[6] >> r[7]){ 
		for(int i = 0; i < 8; ++i){ 
			if(row[i].count(r[i] == 0)) row[i].insert(std::make_pair(r[i],1));
			else ++row[i][r[i]];	
		}
	}
	std::map<char,int>::iterator iter;
	std::map<char,int>::iterator h; // PART A
	std::map<char,int>::iterator s; // PART B
	std::string strA = ""; // for part A
	std::string strB = ""; // for part B
	for(int i = 0; i < 8; ++i){
		std::cout << "-------new column-----\n\n";
		iter = row[i].begin();
		for(h = row[i].begin(), s = row[i].begin(); iter != row[i].end(); ++iter){
			std::cout << (*iter).first << ": " << (*iter).second << "\n";
			if((*h).second < (*iter).second) h = iter;
			if((*s).second > (*iter).second) s = iter;
		}
		strA += (*h).first;
		strB += (*s).first;
	}
	std::cout << "Part A: " << strA << "\n";	
	std::cout << "Part B: " << strB <<"\n";
	
	return 0;
}

