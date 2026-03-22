#include <iostream>
#include <unistd.h>
#include <ctime>
#include <string>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/prctl.h>
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

// Method to check if one child process terminates or is killed
void check_children_termination(pid_t first, pid_t second){
    int status;
    // waitpid: wait on child process status to be updated
    // info about waitpid retrieved from 'man waitpid'
    pid_t dead_process = waitpid(-1, &status, WNOHANG); //WNOHANG: check status of children without pausing execution
    if(dead_process == first){
        kill(second, SIGTERM);  // kill child process 2
        exit(0);    // exit parent process
    }else if(dead_process == second){
        kill(first, SIGTERM);   // kill child process 1
        exit(0);    // exit parent process
    }
}

int main() {
    pid_t pid1, pid2, parent_pid;
    bool pressed_enter = false;
    pid_t dead_process;

    parent_pid = getpid();

    pid1 = fork();
    if(pid1 == 0) {
        // first child
        prctl(PR_SET_PDEATHSIG, SIGTERM);       // check if parent process terminates or killed, if so terminate
        const char* path = "/usr/bin/xclock";   // get path to xclock
        char* argv[] = { (char*)"myXclock", (char*)"-digital", NULL };  // get arguments for executing myXclock
        if(execv(path, argv) == -1) {           // execute xclock
            cout << "Error" << endl;            // error if execv returns -1
        }
    } else {
        pid2 = fork();
        if(pid2 == 0) {
            // second child
            prctl(PR_SET_PDEATHSIG, SIGTERM);   // check if parent process terminates or killed, if so terminate
            string str;
            getline(cin, str);  // press enter to continue code, then exit
            cout << "”Terminated”" << endl;
        } else {
            // parent process
            int counter = 0;
            while(true) {
                check_children_termination(pid1, pid2); // refer to check_children_termination fucntion
                counter++;
                cout << currentDateTime() << endl;

                if(counter % 3 == 0) {  // prompts every three times
                    cout << "”This program has gone on for far too long. Close the myXclock window or press Enter on this window to exit.”" << endl;
                    counter = 0;
                }
                sleep(3);       // sleep the thread for 3 seconds
            }
        }
    }
    return 0;
}
