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
#include <stdlib.h>

int main(int argc, char* argv[]) {
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
        // TODO: for consumer...
        // render the frame that is in the shared memory
        if( ((int*)sharedMem) == (int*)-1 )
        {
            perror( "shmop: shmat failed" );
        }
        else
        {
            // TODO: Render the frame
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