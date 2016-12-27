/*
 * =====================================================================================
 *
 *       Filename:  Day7.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/26/2016 10:15:03 PM
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
std::string getABBA(std::string s){
	for(int i = 3; i < s.length(); ++i){ // we'll start from the first four letters up to end.
		if(s[i] != s[i - 1]){ // first check if the the letters arent repeated.
			if((s.substr(i - 3, 1) + s[i - 2]) == (s.substr(i,1) + s[i - 1])){
				return (s.substr(i - 3,1) + s[i - 2] + s[i - 1] + s[i]);
			}
		}
	}
	return "";
}
void setSSl(std::string s, std::vector<std::string> &lst){
	for(int i = 2; i < s.length(); ++i){
		if(s[i - 2] == s[i] && s[i] != s[i - 1]) lst.push_back(s.substr(i - 2, 3));
	}
}
int main(){

	std::string ln; // line input
	std::string str; // parts of sentence.
	std::ifstream file("input.txt");
	std::string f = "";
	bool inside;
	int countA = 0, countB = 0;
	while(file >> ln){ // get line.
		std::vector<std::string> types[2]; // there will be two types of strings -- inside and outside bracket strings.
		// type 0 -- outside brack .....  type 1 -- inside bracket.
		str = ""; // reset string.
		for(int i = 0; i < ln.length(); ++i){
			if(ln[i] == '[') types[0].push_back(str); // end of outside string.
			else if(ln[i] == ']') types[1].push_back(str); // end of inside string.
			else{ 
				str += ln[i]; 
				continue; // just concat string and continue loop.
			}
			str = ""; // reset string if we HAVE to.
		}
		types[0].push_back(str); // asumming the last string is of type outside.
		inside = false;

		// we'll need two vectors to store the ABAs and BABs.
		std::vector<std::string> ssl[2]; // ssl[0] --> ABAs, ss[1] --> BABs
		for(int i = 0; i < types[1].size(); ++i){
			f = getABBA(types[1][i]);
			if(f.length() != 0){
				inside = true;
				break;
			}
		}
		if(!inside){
			for(int i = 0; i < types[0].size(); ++i){
				f = getABBA(types[0][i]);
				if(f.length() != 0){
					++countA;
					break;
				}
			}
		}

		// PART B
		for(int i = 0; i < types[0].size(); ++i){
			setSSl(types[0][i], ssl[0]); // add ABAs to vector.
		}
		for(int i = 0; i < types[1].size(); ++i){
			setSSl(types[1][i], ssl[1]); // add BABs to vector.
		}
		// now check if theres matching BABs with ABAs
		std::string tmp = "";
		for(int i = 0; i < ssl[0].size(); ++i){
			for(int j = 0; j < ssl[1].size(); ++j){
				tmp = ssl[1][j];
				if(ssl[0][i] == (tmp.substr(1,1) + tmp[0] + tmp[1])){
					++countB;
					i = ssl[0].size();
					break;
				}
			}
		}
	}
	std::cout << "TOTAL A: " << countA << "\n";
	std::cout << "TOTAL B: " << countB << "\n";
	return 0;
}
