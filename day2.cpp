/*
 * =====================================================================================
 *
 *       Filename:  day2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/18/2016 04:11:32 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <utility>
#include <vector>
#include <iostream>
#include <map>


int main(){
	const int MAX = 13; // there's 13 possible inputs(1-D).
	int coordinates[MAX][2] = {{2,2},{1,1},{2,1},{3,1},{0,0},{1,0},{2,0},{3,0},{4,0},{1,-1},{2,-1},{3,-1},{2,-2}};
	std::map< std::pair<int,int>, int> grid;
 	for(int i = 0; i < MAX; ++i){
		grid.insert(std::make_pair(std::make_pair(coordinates[i][0], coordinates[i][1]),i+1)); // insert coordinates as key, digit as code.
	}
	for(int i = 0; i < MAX; ++i){
		std::cout << coordinates[i][0] << "," << coordinates[i][1] << ": " << grid[std::make_pair(coordinates[i][0], coordinates[i][1])] << std::endl;
	}	
	return 0;
}
