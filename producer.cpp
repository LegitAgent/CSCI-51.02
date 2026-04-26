/*****************************
 * The producer shall:
● (1 pt) Accept two arguments from the command line:
○ The file name of the ASCII video file.
○ The user-specified FPS of the video file (must be a positive integer)
● (3 pts) Read the ASCII video file on a per-frame basis, and write each frame into a
shared memory region (and only when it has exclusive access to the memory!). The
shared memory region should only contain one frame at a time!
● (1 pt) The next frame should only be read after the frame rate time has passed. For
example, if the user specifies 25 fps, each frame should be written into the shared
memory region every 40 milliseconds.
● (1 pt) When the end of the video file is reached, the program should simply go back to
the start of the video and replay it from the beginning, in an infinite loop.
● (1 pt) When the user presses the Enter key, the producer process should exit.
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <iostream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <fstream>

int main(int argc, char* argv[]) {

    // checks if producer does have the ascii file and the framerate.
    if (argc != 3) {
        std::cerr << "Missing video ASCII file, framerate or both.\nSyntax: " << argv[0] << " <filename> <framerate>" << std::endl;
        return 1;
    }

    // stores the filename and the framerate.
    std::string videofile = argv[1];
    int framerate = std::__cxx11::stoi(argv[2]);

    // opens the video file.
    std::ifstream file(videofile);

    // checks if the file does exist.
    if (!file.is_open()) {
        std::cerr << "Could not open file \"" << videofile << "\".\nVerify if the file is there, and try again." << std::endl;
        return 1;
    } else {
        // debug code if file does exist.
        std::cout << "File " << videofile << " acquired." << std::endl;
    }

    // the following code is the printing of each frame. however, this only is a simple loop.
    // this means that it ends if the loop reads the end of the file.
    // also, it does not honour framerates yet, so it will be done very quickly.
    // this has the side effect of freezing the terminal for a few seconds.
    // if the terminal stays frozen for quite some time (~2 mins), restart the terminal.

    // this will store each line in the frame
    std::string clearline;

    while (std::getline(file, clearline)) {
        // if the line has the ascii ESC c, which in case is x1b and c
        if (!clearline.empty() && clearline[0] == '\x1b' && clearline[1] == 'c') {
            // this line will clear the screen
            std::cout << '\x1b' << 'c';
            // then this line will print out the rest of the line
            std::cout << clearline.substr(2) << std::endl;
        } else {
            // if there is no ascii ESC c, just print out the line as is
            std::cout << clearline << std::endl;
        }
    }

    return 0;

}