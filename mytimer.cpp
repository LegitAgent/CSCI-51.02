#include <iostream>
#include <unistd.h>
#include <ctime>
#include <string>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
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
    bool pressed_enter = false;
    pid_t dead_process;
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
            pressed_enter = true;
            cout << "”Terminated”" << endl;
        } else {
            // parent process
            int counter = 0;
            while(!pressed_enter) {
                int status;
                pid_t dead_process = waitpid(-1, &status, WNOHANG);
                if(dead_process > 0){
                    break;
                }
                counter++;
                cout << currentDateTime() << endl;
                cout << pid1 << endl;

                if(counter % 3 == 0) {
                    cout << "”This program has gone on for far too long. Close the myXclock window or press Enter on this window to exit.”" << endl;
                    counter = 0;
                }
                sleep(3);
            }
        }
        if(dead_process == pid1){
            kill(pid2, SIGTERM);
        }else if(dead_process == pid2){
            kill(pid1, SIGTERM);
        }
    }
    return 0;
}
