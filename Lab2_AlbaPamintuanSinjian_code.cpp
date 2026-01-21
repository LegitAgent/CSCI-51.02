#include <iostream>
#include <stdlib.h>
using namespace std;

void CreateAgentCoordinateLine(int i, char* x, char* y){
	string xCoordinate = string(x);
	string yCoordinate = string(y);
	
	cout << "Agent #" << i << " is at (" << xCoordinate << ", " << yCoordinate << ")";
	
}


int main(int argc, char* argv[]){
	CreateAgentCoordinateLine(1, argv[1], argv[2]);
	return 0;
}

