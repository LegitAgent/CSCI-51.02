/********************************************
 * The consumer shall:
● (1 pt) Accept one argument from the command line:
○ An alternative FPS value for playback. This may be lower or higher than the
frame rate of the producer.
● (3 pts) Read the shared memory region only at the user-specified FPS rate. Output each
frame to standard output, starting with the escape sequence to clear the screen.
○ Note that your computer’s terminal may need to process frames at a slower rate
than what the user specified. Printing out text in the terminal is slow, so don’t go
overboard with the FPS values that you test your program with!
● (1 pt) When the user presses the Enter key, the consumer process should exit.
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
    // get arguments
    if (argc != 2) {
        std::cerr << "Incorrect arguments. \nSyntax: " << argv[0] << "<positive integer framerate>" << std::endl;
    }

    // thread for exiting when pressing enter
    pthread_t prod_id;
    if (pthread_create(&prod_id, nullptr, handle_exit, nullptr) != 0) {
        std::cerr << "Something wrong happened with the threading. Try again.";
        return 1;
    }

    int c_framerate = std::stoi(argv[1]);
    int c_framespeed = 1000/c_framerate;

    int semId;
    key_t semKey = 1234;
    int semFlag = IPC_CREAT | 0666;
    int nSems = 1;

    semId = semget( semKey, nSems, semFlag );
    if( semId == -1 )
    {
        perror( "semget" );
        exit( 1 );
    }

    // shared memory stuff
    // Id for the shared memory
    int shmId;
    key_t shmKey = 1234;
    int shmSize = 1 << 13;
    int shmFlags = IPC_CREAT | 0666;
    // Pointer for the starting address of the shared memory segment.
    char* sharedMem;
    shmId = shmget( shmKey, shmSize, shmFlags );
    // shmat() returns the starting address of the shared memory
    // segment, so we assign it to sharedMem.
    sharedMem = (char*)shmat( shmId, NULL, 0 );
    int* shared_fps = (int*)sharedMem;
    int* shared_current_frame = (int*)(sharedMem + sizeof(int));
    int* shared_total_frames = (int*)(sharedMem + sizeof(int) * 2);
    char* shared_frame = sharedMem + (sizeof(int) * 3);
    int producer_fps = *shared_fps;
    int total_frames = *shared_total_frames;

    // -- Semaphore Accessing --
    int nOperations = 2;
    struct sembuf sema[nOperations];

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

    std::string frame;
    int current_frame = 0;
    int last_frame = 0;
    int frames_skipped = 0;

    while(running){
        int opResult = semop( semId, sema, nOperations );
        // If we successfully incremented the semaphore,
        // we can now do stuff.
        if( opResult != -1 )
        {
            // CRITICAL SECTION
            current_frame = *shared_current_frame;
            if (last_frame > current_frame) {
                frames_skipped = 0;
                last_frame = 0;
            } 
            if (current_frame > last_frame) {
                frames_skipped += (current_frame - last_frame - 1);
                last_frame = current_frame;
            }
            frame = shared_frame;
            std::cout << frame;
            std::cout << "Current frame: " << current_frame << " / " << total_frames << " (" << frames_skipped << " frames skipped)"  << std::endl;
            //std::cout << sharedMem;


            // -- Semaphore Releasing --
            // Set number of operations to 1
            // Modify the first operation such that it
            // now decrements the semaphore.
            opResult = semop(semId, &release, 1);
            if( opResult == -1 )
            {
                perror( "semop (decrement)" );
            }
        }
        else
        {
            perror( "semop (increment)" );
        }
        usleep(c_framespeed * 1000); // controls framespeed display
    }
    
    return 0;
}
