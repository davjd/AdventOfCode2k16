/*
 * =====================================================================================
 *
 *       Filename:  Day9.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/28/2016 02:01:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  youngthvg, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <vector>
#include <iostream>
#include <fstream>

int main(){

	std::string input = "";
	std::string ln;
	std::ifstream file("input.txt");
	while(file >> ln) input += ln;
	
	/*  std::string s = "(106x9)";
	int mid = s.find('x');
	int end = s.find(')');
	std::cout << "mid: " << mid << "\nend: " << end << "\n";
	std::cout << s.substr(1,mid - 1) << "\n" << s.substr(mid + 1,end - 1 - mid);
	*/
	int mid, end;
	std::string decomp = ""; // will hold the decompressed string.
	int len, times; // will hold length of to be decompressed and how many times.
	std::string tmp = ""; // will hold temporary strings built.
	int j ; // will be used later for for-loop.
	for(int i = 0; i < input.length(); ++i){ // we'll traverse through the string.
		if(input[i] == '('){ // signals beginning of marker.
			//std::cout << "i: " << i << "\n\n\n";
			mid = input.substr(i + 1).find('x');
			end = input.substr(2 + mid + i).find(')');
			len = std::stoi(input.substr(i + 1,mid));
			times = std::stoi(input.substr(mid + i + 2, end));
			//std::cout << "tobe repeated: \n";
			tmp = ""; // creating new temp to be added later.
			for(j = (i + mid + end + 3); j < (i + mid + end + 3 + len); ++j){
				tmp += input[j]; // add character to tmp.
				//std::cout << input[j];
			}
			//std::cout << "\n\ntemp:" << tmp << "\n\n\n";
			for(int n = 0; n < times; ++n) decomp += tmp; // add tmp len times.

			/*  
			std::cout << "\nnext: " << input[i + mid + end + 3] << "\n";
			*///std::cout << "\n--------MARKER-------\n";
			//std::cout << "i: " << i << "mid: " << mid << "\nend: " << end << "\n";
			//std::cout << input.substr(i, end+mid + 3) << "\n";
			//std::cout << "len: " << len << "\ntimes: " << times << "\n";		
			
			//std::cout << "\n--------decomp: " << decomp << "\n\n";
			i = j - 1; // update i.
		}
		else decomp += input[i];
	}
	std::cout << decomp.length() << "\n";
	return 0;
}

