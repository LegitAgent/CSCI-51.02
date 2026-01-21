#include <iostream>

using namespace std;

int main(){
	int agentCount;										                                // Int variable to store number of agents (first line in txt file)
    cout << "Enter Amount of Agents: ";		                                            // Prints a statement to prompt the user for an input
    cin >> agentCount;                                                                  // Prompt the user for an input
    cin.ignore(); 										                                // To ignore the newline character after reading agentCount

    for (int i = 1; i <= agentCount; i++) {                                             // Loop through by the amount of agents
        int posX; int posY; string line;                                                // declare x,y and line variables
        cin >> posX >> posY;                                                            // gets the first 2 inputs, each input is separated by white space
        getline(cin, line);                                                             // gets the whole line, apart from the 2 inputs, meaning it gets the input of the user after 2 white spaces.
        cout << "Agent #" << i << " is at (" << posX << ", " << posY << ")" << endl;    // prints out the location of the agent

        bool isInt = true;                                                              // determines if the input at the line is an integer
        for(int j = 1; j < line.length(); j++) {                                        // loops through the length of the line, start at 1 because the first character is white space
            if(!isdigit(line[j])) {                                                     // checks whether the character at line[j] isn't a digit
                isInt = false;                                                          // marks false if the character isn't a digit
                break;                                                                  // break out of the loop if so
            }
        }
        if(isInt) {                                                                     // checks if it is an integer
            cout << "Agent #" << i << " has the number " << line.substr(1) << endl;     // if so, print that the agent has a number
        } else {                                                                        // checks if it isn't an integer
            cout << "Agent #" << i << " yells: \"" << line.substr(1) << "\"" << endl;   // if so, print that the agent yells a string
        }
    }
	return 0;                                                                           // return 0 to indicate a succesful execution
}

