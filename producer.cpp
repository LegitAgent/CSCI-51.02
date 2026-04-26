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

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <iostream>
#include <fstream>

bool running = true;

void* handle_exit(void* arg) {
    std::cin.get();
    running = false;
    return nullptr;
}

int main(int argc, char* argv[]) {
    pthread_t prod_id;

    // checks if producer does have the ascii file and the framerate.
    if (argc != 3) {
        std::cerr << "Missing video ASCII file, framerate or both.\nSyntax: " << argv[0] << " <filename> <framerate that is positive>" << std::endl;
        return 1;
    }

    // stores the filename and the framerate.
    std::string videofile = argv[1];
    int framerate;
    if (std::__cxx11::stoi(argv[2]) > 0) framerate = std::__cxx11::stoi(argv[2]);
    else {
        std::cerr << "A negative or zero framerate cannot be entered.\n"
        << "Syntax: " << argv[0] << " <filename> <framerate that is positive>" << std::endl;
        
        return 1;
    }
    int framespeed = 1000 / framerate;

    // opens the video file.
    std::ifstream file(videofile);

    // checks if the file does exist.
    if (!file.is_open()) {
        std::cerr << "Could not open file \"" << videofile << "\".\nVerify if the file is there, and try again." << std::endl;
        return 1;
    }

    if (pthread_create(&prod_id, nullptr, handle_exit, nullptr) != 0) {
        std::cerr << "Something wrong happened with the threading. Try again.";
        return 1;
    }

    // establishing shared memory

    key_t shmKey = 1234; // will also be used as semKey
    int shmSize = 1 << 13; // let's see if 8192 bytes is enough
    int shmFlag = IPC_CREAT | 0666; // will also be used as semFlag
    int shmID = shmget(shmKey, shmSize, shmFlag);
    char* shmMem = (char*)shmat(shmID, NULL, 0); // declare shared mem

    // share fps
    int* shared_fps = (int*)shmMem;
    int* shared_current_frame = (int*)(shmMem + sizeof(int));
    int* shared_total_frames = (int*)(shmMem + sizeof(int) * 2);
    char* shared_frame = shmMem + (sizeof(int) * 3);
    int frameSize = shmSize - (sizeof(int) * 3);
    *shared_fps = framerate;
    *shared_current_frame = 0;

    // establishing semaphore

    int nSems = 1;

    int semID = semget(shmKey, nSems, shmFlag);

    if (semID == -1) {
        perror("semget");
        exit(1);
    }

    int thing = semctl(semID, 0, GETVAL);

    int nOps = 2;

    struct sembuf sema[nOps];

    sema[0].sem_num = 0; // Use the first semaphore in the semaphore set
    sema[0].sem_op = 0; // Wait if semaphore != 0
    sema[0].sem_flg = SEM_UNDO; // See slides

    sema[1].sem_num = 0; // Use the first semaphore in the semaphore set
    sema[1].sem_op = 1; // Increment semaphore by 1
    sema[1].sem_flg = SEM_UNDO; // See slides

    struct sembuf release;
    release.sem_num = 0; // Use the first semaphore in the semaphore set
    release.sem_op = -1; // Decrement semaphore by 1
    release.sem_flg = SEM_UNDO; // See slides
    
    std::string clearline, frame;
    int current_frame = 0;
    int total_frames = 0;

    std::string countline;
    while (std::getline(file, countline)) {
        if (!countline.empty() && countline[0] == '\x1b' && countline[1] == 'c')
            total_frames++;
    }
    *shared_total_frames = total_frames;

    file.clear();
    file.seekg(0);

    while (running) {
        frame.clear();

        // TEST THIS OUT WITH AN IMPLEMENTATION OF CONSUMER.
        // This code might only display one LINE at a time, not one frame.

        // First line of the frame will get printed
        while (std::getline(file, clearline)) {
            frame += clearline + "\n";
            if (!clearline.empty() && clearline[0] == '\x1b' && clearline[1] == 'c') break;
        }

        // Then the rest of the frame will get printed
        while (std::getline(file, clearline)) {
            if (!clearline.empty() && clearline[0] == '\x1b' && clearline[1] == 'c') {
                // https://www.geeksforgeeks.org/cpp/set-position-with-seekg-in-cpp-language-file-handling/
                // What this does is it is seeking the lines after the line with the
                // ASCII ESC c. All the lines without it will then be added to the frame.
                // When it encounters a line with the ASCII ESC c, it breaks.
                file.seekg(-(clearline.size() + 1), std::ios_base::cur);
                break;
            }
            frame += clearline + "\n";
        }

        if (file.eof()) {
            file.clear();
            file.seekg(0); // loops back to the beginning
            current_frame = 0;
            continue;
        }

        int opResult = semop(semID, sema, nOps);
        if(opResult != -1) {
            current_frame++;
            *shared_current_frame = current_frame;
            strncpy(shared_frame, frame.c_str(), frameSize);
            shared_frame[frameSize - 1] = '\0';
            opResult = semop(semID, &release, 1);
            if(opResult == -1) {
                    perror("semop (decrement)");
            }
        } else {
            perror("semop (increment)");
        }

        usleep(framespeed * 1000); // controls framespeed display
    }
    
    return 0;

}
