/*
 * =====================================================================================
 *
 *       Filename:  day3.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/24/2016 05:15:19 PM
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
	std::vector<int> r1, r2, r3;
	std::ifstream file("input.txt");
	std::vector<int> *rows[3];
	
	rows[0] = &r1;
	rows[1] = &r2;
	rows[2] = &r3;
	int n1, n2, n3;
	int total = 0;
	int ctr = 0;
	while(file >> n1 >> n2 >> n3){
		r1.push_back(n1);
		r2.push_back(n2);
		r3.push_back(n3);

		++total; // update row count.
		if(!(total % 3)){ // check every 3 elements.
			std::cout << "divided by 3 -> true : " << total << "\n\n";
			for(int i = 0; i < 3; ++i){ // iterate through the vectors.
				n1 = rows[i]->at(total - 1);
				n2 = rows[i]->at(total - 2);
				n3 = rows[i]->at(total - 3);
				if((n1 + n2 <= n3) || (n1 + n3 <= n2) || (n2 + n3 <= n1)) continue;
				++ctr; // if triangle is possible, update counter.
				std::cout << "Triangle was made!\n" << n1 << " " << n2 << " " << n3 << "\n\n";
			}
		}
	}
	std::cout << "total: " << total << "\ncounter: " << ctr << "\n";


	return 0;
}
