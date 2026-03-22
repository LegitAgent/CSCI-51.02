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


void check_children_termination(pid_t first, pid_t second){
    int status;
    pid_t dead_process = waitpid(-1, &status, WNOHANG);
    if(dead_process == first){
        kill(second, SIGTERM);
    }else if(dead_process == second){
        kill(first, SIGTERM);
    }
}

bool is_parent_terminated(pid_t parent_pid){
    pid_t current_parent = getppid();
    return !(current_parent == parent_pid);
}

int main() {
    pid_t pid1, pid2, parent_pid;
    bool pressed_enter = false;
    pid_t dead_process;

    parent_pid = getpid();

    pid1 = fork();
    if(pid1 == 0) {
        // first child
        const char* path = "/usr/bin/xclock";
        char* argv[] = { (char*)"myXclock", (char*)"-digital", NULL };
        if(execv(path, argv) == -1) {
            cout << "Error" << endl;
        }
        if(is_parent_terminated(parent_pid)){
            exit(0);
        }
    } else {
        pid2 = fork();
        if(pid2 == 0) {
            // second child
            string str;
            if(is_parent_terminated(parent_pid)){
                exit(0);
            }
            getline(cin, str);
            cout << "”Terminated”" << endl;
        } else {
            // parent process
            int counter = 0;
            while(true) {
                check_children_termination(pid1, pid2);
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
