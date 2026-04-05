#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
struct Point3D{ //Sample Struct
    int x;
    int y;
    int z;
};
void *print_message_function( void *ptr );
int main()
{
    pthread_t thread1, thread2;
    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";
    int iret1, iret2;
    void *retval1;
    void *retval2;
    Point3D* p = new Point3D {6,7,67}; //Define struct pointer
    Point3D* q = new Point3D {4,20,420}; //Define struct pointer
    /* Print original values */
    printf("Point p in main function before creation: %d, %d, %d \n", p->x, p->y, p->z);
    printf("Point q in main function before creation: %d, %d, %d \n", q->x, q->y, q->z);
    /* Create independent threads each of which will execute function */
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) p);
    if (iret1)
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        exit(EXIT_FAILURE);
    }
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) q);
    if (iret2)
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
        exit(EXIT_FAILURE);
    }
    printf("pthread_create() for thread 1 returns: %d\n", iret1);
    printf("pthread_create() for thread 2 returns: %d\n", iret2);
    /* Wait till threads are complete before main continues. Unless we */
    /* wait we run the risk of executing an exit which will terminate */
    /* the process and all threads before the threads have completed. */
    pthread_join(thread1, &retval1);
    pthread_join(thread2, &retval2);
    /* Print new values after threads exit */
    printf("Point p in main function after join(): %d, %d, %d \n", p->x, p->y, p->z);
    printf("Point q in main function after join(): %d, %d, %d \n", q->x, q->y, q->z);
    return 0;
}
void *print_message_function( void *ptr )
{
    Point3D *p;
    p = (Point3D *) ptr;
    p->x = 40;
    p->y = 100;
    p->z = 76;
    printf("Local point p inside thread: %d, %d, %d \n", p->x, p->y, p->z);
    pthread_exit((void *) p); //Exit the thread with a return value (the point itself)
    return nullptr;
}
