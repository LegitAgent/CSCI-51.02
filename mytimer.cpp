#include <iostream>
#include <unistd.h>
#include <ctime>
#include <string>
#include <bits/stdc++.h>

using namespace std;

// Function to get current time as a formatted string
const string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct; // tm structure
    char buffer[22]; // 1 + 4 + 1 + 2 + 1 + 2 + 1 + 1 + 2 + 1 + 2 + 1 + 2 + 1 (null terminator "/0") = 22
    tstruct = *localtime(&now);
    // Format: [yyyy-mm-dd] hh:mm:ss
    strftime(buffer, sizeof(buffer), "[%Y-%m-%d] %H:%M:%S", &tstruct);
    return buffer;
}

int main() {
    pid_t pid1, pid2;
    pid1 = fork();
    if(pid1 == 0) {
        // first child
        const char* path = "/usr/bin/xclock";
        char* argv[] = { (char*)"myXclock", (char*)"-digital", NULL };
        if(execv(path, argv) == -1) {
            cout << "Error" << endl;
        }
    } else {
        pid2 = fork();
        if(pid2 == 0) {
            // second child
            string str;
            getline(cin, str);
            cout << "”Terminated”" << endl;
        } else {
            // parent process
            int counter = 0;
            while(true) {
                counter++;
                cout << currentDateTime() << endl;

                if(counter % 3 == 0) {
                    cout << "”This program has gone on for far too long. Close the myXclock window or press Enter on this window to exit.”" << endl;
                    counter = 0;
                }
                sleep(3);

            }
        }
    }
    return 0;
}