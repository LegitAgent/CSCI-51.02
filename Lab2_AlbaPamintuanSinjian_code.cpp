#include <iostream>
using namespace std;

int main(){
	int agentCount;
    cin >> agentCount;
    cin.ignore(); // To ignore the newline character after reading agentCount

    for (int i = 1; i <= agentCount; i++) {
        int posX; int posY; string line;
        cin >> posX >> posY;
        getline(cin, line);
        cout << "Agent #" << i << " is at (" << posX << ", " << posY << ")" << endl;

        if (!isdigit(line[1]) || line[2] == ' ') { // <-- TODO: Need to correct this so that it checks if the first chararacter is not a number OR if there are more characters after a whitespace. Currently, it checks if the second character is not a number, so it fails if eg the input is "2 6 548916461954165" or 2 9 51518 48451 848484
        
			cout << "Agent #" << i << " yells: \"" << line.substr(1) << "\"" << endl;
            continue;
        } else {
            cout << "Agent #" << i << " has the number " << line.substr(1) << endl;
            continue;
        }
    }

	return 0;
}
