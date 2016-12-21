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
 *         Author:  youngthvg, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <utility>
#include <vector>
#include <iostream>
#include <map>
typedef std::map< std::pair<int, int>, int> CodeMap;
struct node{ // will be used to keep track of where in the grid the commands place you.
	int x; // current x coordinate.
	int y; // current y coordinate.
} current;
enum Command{ L, U, R, D}; // avaliable commands --> left, up, right, down
Command getCommand(char c){
	// individual commands will initially be characters,
	// so we must convert them to Command type.
	switch(c){
		case 'L': return L;
		case 'U': return U;
		case 'R': return R;
		case 'D': return D;
	}
}
int doesExist(CodeMap &grid, std::pair<int, int> &coordinates){
	// check if coordinate key  exists in code map.
	return (grid.count(coordinates) == 1); // see if coordinate is in grid.
}
void addCode(std::vector<int> &codeSaved, int newCode){
	codeSaved.push_back(newCode); // add new code.
}


// will need to research if predicates can be passed as arguments.
int getXAdder(CodeMap &grid, node &current, Command command){
	// will return a number to add to current.x
	// x will only change if commands are L or R. (left,right).
	if(command == L && doesExist(grid, std::make_pair(current.x - 1, current.y))) return -1; // go one left.
	else if(command == R && doesExist(grid, std::make_pair(current.x + 1, current.y))) return 1; // go one right
	return 0; // if x coordinate doesn't need to change.
}
int getYAdder(CodeMap &grid, node &current, Command command){
	if(command == D && doesExist(grid, std::make_pair(current.x, current.y - 1))) return -1;
	else if(command == U && doesExist(grid, std::make_pair(current.x, current.y - 1))) return 1;
	return 0; // if no change is needed.
}

void updateNode(CodeMap &grid, Command command, node &current, std::vector<int> codeSaved){
	// this will be the main method where all the magic happens.
	std::pair<int, int> newCoordinates = std::make_pair(-1, -1); // defualt coordinates.
	int xAdder = getXAdder(grid, current, command); // get adder for x coordinate.
	int yAdder = getYAdder(grid, current, command); // get adder for y coordinate.

	// check if there is change needed.
	if(xAdder != 0 || yAdder != 0){
		// we could check what needs to change, but lets not.
		current.x += xAdder;
		current.y += yAdder;
		addCode(codeSaved, grid[current]); // add the new code of those coordinates.
	}
}
int main(){
	const int MAX = 13; // there's 13 possible inputs(1-D).
	int coordinates[MAX][2] = {{2,2},{1,1},{2,1},{3,1},{0,0},{1,0},{2,0},{3,0},{4,0},{1,-1},{2,-1},{3,-1},{2,-2}};
	CodeMap grid;
 	for(int i = 0; i < MAX; ++i){
		grid.insert(std::make_pair(std::make_pair(coordinates[i][0], coordinates[i][1]),i+1)); // insert coordinates as key, digit as code.
	}
	for(int i = 0; i < MAX; ++i){
		std::cout << coordinates[i][0] << "," << coordinates[i][1] << ": " << grid[std::make_pair(coordinates[i][0], coordinates[i][1])] << std::endl;
	}

	// initialize the current node.
	current.x = 0;
	current.y = 0;	
	// create vector to save codes to be entered.
	std::vector<int> codes; // constructor.
	return 0;
}
