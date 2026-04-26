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
        std::cout << "File acquired." << std::endl;
    }

    // semaphore initialization
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
    key_t shmKey = 2345;
    int shmSize = 1 << 10;  //1024 bytes
    int shmFlags = IPC_CREAT | 0666;
    // Pointer for the starting address of the shared memory segment.
    char* sharedMem;
    shmId = shmget( shmKey, shmSize, shmFlags );
    // shmat() returns the starting address of the shared memory
    // segment, so we assign it to sharedMem.
    sharedMem = (char*)shmat( shmId, NULL, 0 );


    // -- Semaphore Accessing --
    int nOperations = 2;
    struct sembuf sema[nOperations];
    sema[0].sem_num = 0; // Use the first semaphore in the semaphore set
    sema[0].sem_op = 0; // Wait if semaphore != 0
    sema[0].sem_flg = SEM_UNDO; // See slides
    sema[1].sem_num = 0; // Use the first semaphore in the semaphore set
    sema[1].sem_op = 1; // Increment semaphore by 1
    sema[1].sem_flg = SEM_UNDO | IPC_NOWAIT; // See slides
    int opResult = semop( semId, sema, nOperations );
    // If we successfully incremented the semaphore,
    // we can now do stuff.
    if( opResult != -1 )
    {
        printf( "Successfully incremented semaphore!\n" );
        
        // CRITICAL SECTION
        // TODO: for producer...
        // put frame into shared memory
        if( ((int*)sharedMem) == (int*)-1 )
        {
            perror( "shmop: shmat failed" );
        }
        else
        {
            // TODO: Put frame into shared memory
        }


        // -- Semaphore Releasing --
        // Set number of operations to 1
        nOperations = 1;
        // Modify the first operation such that it
        // now decrements the semaphore.
        sema[0].sem_num = 0; // Use the first semaphore in the semaphore set
        sema[0].sem_op = -1; // Decrement semaphore by 1
        sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;
        opResult = semop( semId, sema, nOperations );
        if( opResult == -1 )
        {
            perror( "semop (decrement)" );
        }
        else
        {
            printf( "Successfully decremented semaphore!\n" );
        }
    }
    else
    {
        perror( "semop (increment)" );
    }
    return 0;

}