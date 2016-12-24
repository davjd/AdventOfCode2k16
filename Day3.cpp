/*
 * =====================================================================================
 *
 *       Filename:  Day3.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/24/2016 04:53:39 PM
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
int main(){

	std::ifstream file("input.txt");
	int n1, n2, n3;
	int ctr = 0;
	int number = 0;
	while(file >> n1 >> n2 >> n3){
		std::cout << n1 << " " << n2 << " " << n3 << std::endl;
		++number;
		if((n1 + n2 <= n3) || (n1 + n3 <= n2) || (n2 + n3 <= n1)) continue;
		++ctr; // if break doesnt occur, triangle is valid
	}
	std::cout << "counter: " << ctr << std::endl;
	std::cout << "total: " << number << "\n";

	return 0;
}
