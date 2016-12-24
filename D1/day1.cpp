/*
 * =====================================================================================
 *
 *       Filename:  day1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/11/2016 04:37:18 PM
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
#include <vector>
#include <utility>
#include <sstream>
using namespace std;
// W - 0, N - 1, E - 2, S - 3.
enum Direction {W, N, E, S}; 
typedef pair<int,int> Coordinate; // pair of the x and y coordinate.
typedef map<Coordinate, bool> Route; // map of the coordinates traveled to.

struct facingDirection{ // will contain info about current facing direction.
   Direction current; // current direction.
   Direction right; // will save direction to the right of current direction.
   Direction left; // will save direction to the left of current direction.
} west, north, east, south;

struct currentNode{ // this will be the actual 'thing' traveling.
   int distance; // total distance traveled.
   facingDirection position; // keep track of where on compass it is.
   int directionDistance[4]; // distances for each direction(W,N,E,S).
	Coordinate currentCoordinate;
	//currentCoordinate = make_pair(0,0); // coordinate of where the node is.
} currentPosition;


void updateCurrentCoordinate(currentNode& currentPosition, Coordinate newCoord){
	currentPosition.currentCoordinate =  newCoord; // update coordinate of node.
}
bool haveVisited(Coordinate &point, Route &route){
	return (route.count(point) == 1); // check if the map has that coordinate.
}
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
facingDirection getDirection(Direction newDirection){
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
Coordinate getNewCoordinate(string givenDirection, currentNode& currentPosition){

	Direction newFacing = parseDirection(givenDirection,currentPosition);
	Coordinate currentCoord = currentPosition.currentCoordinate; // get current coordinates
	switch(newFacing){
		case W:
			return make_pair(currentCoord.first - 1, currentCoord.second);
		case N:
			return make_pair(currentCoord.first, currentCoord.second + 1);
		case E:
			return make_pair(currentCoord.first + 1, currentCoord.second);
		case S:
			return make_pair(currentCoord.first, currentCoord.second - 1);
	}
}
int parseDistance(string givenDirection){ // will return distance from individual direction , ex. 'R5' -> 5
   int numb;
   istringstream (givenDirection.substr(1)) >> numb;
   return numb;
}
void calculatePath(){

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


	// initialize data structures.
	vector<string> path;
	string r = "R4, R1, L2, R1, L1, L1, R1, L5, R1, R5, L2, R3, L3, L4, R4, R4, R3, L5, L1, R5, R3, L4, R1, R5, L1, R3, L2, R3, R1, L4, L1, R1, L1, L5, R1, L2, R2, L3, L5, R1, R5, L1, R188, L3, R2, R52, R5, L3, R79, L1, R5, R186, R2, R1, L3, L5, L2, R2, R4, R5, R5, L5, L4, R5, R3, L4, R4, L4, L4, R5, L4, L3, L1, L4, R1, R2, L5, R3, L4, R3, L3, L5, R1, R1, L3, R2, R1, R2, R2, L4, R5, R1, R3, R2, L2, L2, L1, R2, L1, L3, R5, R1, R4, R5, R2, R2, R4, R4, R1, L3, R4, L2, R2, R1, R3, L5, R5, R2, R5, L1, R2, R4, L1, R5, L3, L3, R1, L4, R2, L2, R1, L1, R4, R3, L2, L3, R3, L2, R1, L4, R5, L1, R5, L2, L1, L5, L2, L5, L2, L4, L2, R3";
	// convert string to individual directions.
	parseStr(r, path);
	// initialize the map.
	Route route;
	currentPosition.currentCoordinate = make_pair(0,0); // starting point will be 0,0.
	route.insert(make_pair(currentPosition.currentCoordinate, true)); // add the coordinate to traveld map.

	bool visited = false;
	
	for(int i = 0; i < path.size(); ++i){
		if(visited) break; // if we have found the visited coordinate, break off loop.
		Coordinate updatedCoordinate;
		int len = parseDistance(path[i]); // get how long we have to go.
		cout << "dist: " << len << endl;
		for(int j = 1; j <= len; ++j){
			updatedCoordinate = getNewCoordinate(path[i], currentPosition); // get next coordinate.
			visited = haveVisited(updatedCoordinate, route); // check if we've already visited this coordinate.
			updateCurrentCoordinate(currentPosition, updatedCoordinate); // change current coordinate.
			route.insert(make_pair(updatedCoordinate, true)); // add coordinate as visited.
			if(visited) break; // if we already visited it, break loop.
		}
		

		// after updating the coordinates, we must change the facing direction.
		currentPosition.position =  getDirection(parseDirection(path[i], currentPosition));
	}
	cout << currentPosition.currentCoordinate.first << "," << currentPosition.currentCoordinate.second << endl;
}

