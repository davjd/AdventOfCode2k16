/*
 * =====================================================================================
 *
 *       Filename:  Day4.cpp
 *
 *    Description: REQUIRES std=++11  
 *
 *        Version:  1.0
 *        Created:  12/24/2016 06:22:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  youngthvg, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <algorithm>
#include <vector> 
bool isLetter(char c){ return (c >= 'a' && c <= 'z');} // to check if character is a letter, expecting lwercase char.
std::string getName(std::string s){ // retrieves the letters of the name of the room.
	std::string tmp = "";
	int end = s.length() - 10;
	for(int i = 0; i < end; ++i){
		if(isLetter(s[i])) tmp += s[i]; // if it's a letter, add to temporary string.
	}
	return tmp; // return only the letters.
}
std::string reverse(std::string s){ // won't be used.
	std::string tmp = "";
	for(int i = s.length() - 1; i > 0; --i){ tmp += s[i];}
	return tmp;
}
int getId(std::string s){
	// get Sector ID of room.
	int begin = s.length() - 10; // where we will being parsing the string.
	std::string tmp = "";
	tmp += s[begin];
	tmp += s[begin + 1];
	tmp += s[begin + 2];
	return std::stoi(tmp); // require std=++11
}
bool doesExist(std::map<char,int> &d, char l){
	return (d.count(l) == 1); // will check if letter is already in map.
}
std::string getCheckSum(std::string s){
	int end = s.length() - 1;
	std::string tmp = "";
	for(int i = end - 5; i < end; ++i) tmp += s[i];
	return tmp;
}
bool isValid(std::string correct, std::string current){ return correct == current;} // check if the current checksum is correct

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
	return std::pair<B,A>(p.second, p.first);
}
template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
	std::multimap<B,A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), flip_pair<A,B>);
	return dst;
}
std::string getValidCSum(std::string s){ // will return the valid checksum.
	std::map<char,int> dictionary; // will be used to keep track of duplicates.
	for(int i = 0; i < s.length(); ++i){
		if(doesExist(dictionary,s[i])) ++dictionary[s[i]]; // update duplicate counter.
		else dictionary.insert(std::make_pair(s[i], 1)); // add letter and update counter.
	}

	std::multimap<int, char> dst = flip_map(dictionary); // by flipping the map, we will sort it by value.
	std::map<int, char>::reverse_iterator iter;
	std::string checksum = ""; // will contain string of checksum
	std::map<int, char>::reverse_iterator h; // will store the highest repeated letter.
	for(int i = 0; i < 5; ++i){ // we need to extract the top 5 most repetives.
		h = dst.rbegin(); // default highest will be the first item.
		for(iter = dst.rbegin(); iter != dst.rend(); ++iter){
			if((*iter).first >= (*h).first && (*iter).second < (*h).second) h = iter; // update highest number.
		} // after find the highest repeated letter --> add it to the checksum.
		checksum += (*h).second; // add the letter.
		dst.erase(std::next(h).base()); // delete the letter from the sorted map.
	}
	return checksum;
}
char shift(char ch, int shift){
	return ch == 'z' || ch == 'Z' ? ch - 25 : ch + 1;
}
void split(std::string s, std::vector<std::string> &ln){
	std::string tmp = "";
	for(int i = 0;i < s.length(); ++i){
		if(isLetter(s[i])) tmp += s[i];
		else{
			ln.push_back(tmp);
			tmp = "";
		}	
	}
	ln.push_back(tmp);
}


int main(){

	std::vector<std::string> validInputs; // THIS IS FOR PART B --> will hold valid room inputs
	std::vector<std::string> allInputs;
	std::ifstream file("input.txt"); // get file.
	//std::string ln = "aaaaa-bbb-z-y-x-123[abxyz]";
	std::string ln; // will hold line of room input.
	std::string name; // will hold name of room.
	int sum = 0;
	int t = 0;
	while(file >> ln){
		++t;
		name = getName(ln);
		//std::cout << ln << "\n\n\n";
		if(isValid(getValidCSum(name),getCheckSum(ln))){ 
			sum += getId(ln); // check if the checksum is valid. if so add to sum
			// FOR PART B --> we'll save the valid room inputs.
			validInputs.push_back(ln);
		}
		allInputs.push_back(ln);
	}
	std::cout << "sum: " << sum; // PART A SOLUTION.
	std::vector<std::string>::iterator iter = allInputs.begin();
	int s;
	int end;
	std::string decrypt = ""; // will hold the decrypted line.
	int newC;
	std::vector<std::string> names;
	for(; iter != allInputs.end(); ++iter){
		ln = *iter;
		end = ln.length() - 11;
		s = getId(ln) % 26; // find out how many real shifts we'll have to execute.
		//std::cout << ln << "\nshift: " << s <<"\n";
		for(int i = 0; i < end; ++i){

			if(isLetter(ln[i])){
				newC = static_cast<int>(ln[i]) + s;
				if(static_cast<int>('z') < newC){
					// check bounds.
					--newC;
					decrypt += static_cast<int>('a') + (newC - static_cast<int>('z'));
				}
				else decrypt += newC;
			}
			else decrypt += " ";
		}
		names.push_back(decrypt);
		std::vector<std::string> splitted;
		split(decrypt,splitted);
		//std::cout << "\nSPLIT: \n";
		for(int j = 0; j < splitted.size(); ++j){ 
			if(splitted[j] == "northpole" || splitted[j] == "north" || splitted[j] == "pole" || splitted[j] == "objects"){ 
				std::cout << splitted[j] << "\n\n";
				std::cout << decrypt << "\n";
				std::cout << "\n\n\n------------FOUND----------\n\n\n" << *iter << "\n";
			}
		}
		//std::cout << "\n\n";
		//std::cout << "decrypted: " << decrypt << "\n\n";
		decrypt = ""; // reset string.
	}
	for(int i = 0; i < names.size(); ++i) std::cout << names[i] << "\n";
	std::cout << "total: " << t << ": " << allInputs.size() << "\n";
	return 0;
}
