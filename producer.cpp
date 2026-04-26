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
    } else {
        // debug code if file does exist.
        std::cout << "File " << videofile << " acquired." << std::endl;
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

    char* shmMem = (char*)shmat(shmID, NULL, 0);

    // establishing semaphore

    int nSems = 1;

    int semID = semget(shmKey, nSems, shmFlag);

    if (semID == -1) {
        perror("semget");
        exit(1);
    }

    int nOps = 2;

    struct sembuf sema[nOps];

    sema[0].sem_num = 0; // Use the first semaphore in the semaphore set
    sema[0].sem_op = 0; // Wait if semaphore != 0
    sema[0].sem_flg = SEM_UNDO; // See slides

    sema[1].sem_num = 0; // Use the first semaphore in the semaphore set
    sema[1].sem_op = 1; // Increment semaphore by 1
    sema[1].sem_flg = SEM_UNDO | IPC_NOWAIT; // See slides

    int opResult = semop(semID, sema, nOps);
    if(opResult != -1) {
        printf( "Successfully incremented semaphore!\n" ); // debug line

        std::string clearline, frame;

        while (running) {
            frame.clear();

            // TEST THIS OUT WITH AN IMPLEMENTATION OF CONSUMER.
            // This code might only display one LINE at a time, not one frame.
            while (std::getline(file, clearline)) {
                frame += clearline + "\n";
                if (!clearline.empty() && clearline[0] == '\x1b' && clearline[1] == 'c') break;
            }

            if (file.eof()) {
                file.clear();
                file.seekg(0); // loops back to the beginning
                continue;
            }

            strncpy(shmMem, frame.c_str(), shmSize);

            usleep(framespeed * 1000); // controls framespeed display
        }

        sema[0].sem_num = 0; // Use the first semaphore in the semaphore set
        sema[0].sem_op = -1; // Decrement semaphore by 1
        sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

        opResult = semop(semID, sema, nOps);
        if(opResult == -1)
        {
            perror("semop (decrement)");
        }
        else
        {
            printf("Successfully decremented semaphore!\n"); // debug line
        }
    } else {
        perror("semop (increment)");
    }
    
    return 0;

}