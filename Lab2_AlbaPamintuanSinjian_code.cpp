#include <iostream>

using namespace std;

int main(){
	int agentCount;
    cout << "Enter Amount of Agents: " << endl;
    cin >> agentCount;
    cin.ignore(); // To ignore the newline character after reading agentCount

    for (int i = 1; i <= agentCount; i++) {
        int posX; int posY; string line;
        cin >> posX >> posY;
        getline(cin, line);
        cout << "Agent #" << i << " is at (" << posX << ", " << posY << ")" << endl;

        bool isInt = true;
        for(int j = 1; j < line.length(); j++) {
            if(!isdigit(line[j])) {
                isInt = false;
                break;
            }
        }
        if(isInt) {
            cout << "Agent #" << i << " has the number " << line.substr(1) << endl;
        } else {
            cout << "Agent #" << i << " yells: \"" << line.substr(1) << "\"" << endl;
        }
    }

	return 0;
}
