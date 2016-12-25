/*
 * =====================================================================================
 *
 *       Filename:  Day1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/10/2016 09:52:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  youngthvg, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
/* *
 * COMPASS DIRECTIONS:     N 
 *                        W E
 *                         S
 * */

// W - 0, N - 1, E - 2, S - 3
enum Direction {W, N, E, S};

struct currentDirection{ // will contain info about current facing direction.
	Direction current; // current direction.
	Direction right; // will save direction to the right of current direction.
	Direction left; // will save direction to the left of current direction.
} west, north, east, south;

struct currentNode{ // this will be the actual 'thing' traveling.
	int distance; // total distance traveled.
	currentDirection position; // keep track of where on compass it is.
	int directionDistance[4]; // distances for each direction(W,N,E,S).
} currentPosition;

void parseStr(string str, vector<string> &directions){ // will parse the string of directions.
	// this will parse the route string to get individual directions and length.
	string direct = "";
	for(int i = 0; i < str.length(); ++i){
		if(str[i] == ','){
			// delimiter --> add direction/length to vector and reset direct.
			directions.push_back(direct);
			direct = "";
		}
		else if(str[i] != ' ') direct += str[i]; // concat rest of direct.
	}
	// add last one.
	directions.push_back(direct);
}
Direction parseDirection(string givenDirection, currentNode &currentPosition){
	// will return where to turn(either left or right) of given direction from directions.
	char turn = givenDirection[0]; // parse the where to turn from direction.
	if(turn == 'L') return currentPosition.position.left;
	return currentPosition.position.right; // if not left then right.
}
currentDirection getDirection(Direction newDirection){
	switch(newDirection){ // return the direction, on compass, of the new direction.
		case W:
			return west;
		case N:
			return north;
		case E:
			return east;
		case S:
			return south;
	} // these directions will help when turning left and right.
}
int parseDistance(string givenDirection){ // will return distance from individual direction , ex. 'R5' -> 5
	int numb;
	istringstream (givenDirection.substr(1)) >> numb;
	return numb;
}
int absolute(int value){ // returns absolute value of int.
	if(value < 0){
		return (-1 * value);
	}
	return value;
}
int calculatePath(currentNode &currentPosition, vector<string> &directions){
	for(int i = 0; i < directions.size(); ++i){
		Direction facingDirection = parseDirection(directions[i], currentPosition); // get direction facing.
		currentPosition.position = getDirection(facingDirection); // update direction on compass.
		currentPosition.directionDistance[facingDirection]+= parseDistance(directions[i]); // update distance of that direction.
	}
	return absolute(currentPosition.directionDistance[W] - currentPosition.directionDistance[E]) + absolute(currentPosition.directionDistance[N] - currentPosition.directionDistance[S]);
}
int main(){
	// initialize the directions.
	west.current = W;
	west.left = S;
	west.right = N;
	
	north.current = N;
	north.left = W;
	north.right = E;
	
	east.current = E;
	east.left = N;
	east.right = S;
	
	south.current = S;
	south.left = E;
	south.right = W;
	
	// initialize current position.
	currentPosition.distance = 0;
	currentPosition.position = north;
	string r = "R4, R1, L2, R1, L1, L1, R1, L5, R1, R5, L2, R3, L3, L4, R4, R4, R3, L5, L1, R5, R3, L4, R1, R5, L1, R3, L2, R3,     R1, L4, L1, R1, L1, L5, R1, L2, R2, L3, L5, R1, R5, L1, R188, L3, R2, R52, R5, L3, R79, L1, R5, R186, R2, R1, L3, L5, L2,     R2, R4, R5, R5, L5, L4, R5, R3, L4, R4, L4, L4, R5, L4, L3, L1, L4, R1, R2, L5, R3, L4, R3, L3, L5, R1, R1, L3, R2, R1, R2,     R2, L4, R5, R1, R3, R2, L2, L2, L1, R2, L1, L3, R5, R1, R4, R5, R2, R2, R4, R4, R1, L3, R4, L2, R2, R1, R3, L5, R5, R2, R5    , L1, R2, R4, L1, R5, L3, L3, R1, L4, R2, L2, R1, L1, R4, R3, L2, L3, R3, L2, R1, L4, R5, L1, R5, L2, L1, L5, L2, L5, L2, L    4, L2, R3";

	vector<string> route; // vector of directions.
	parseStr(r,route);
	currentPosition.distance = calculatePath(currentPosition, route);

	cout << "total: " << currentPosition.distance << endl;

}
