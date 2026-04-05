#include <iomanip>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <random>

using namespace std;

// structure for data to be sent over the threads
struct Data {
    long long trials;
    long long reportFrequency;
    long long insideCircle;
    int id;
};

// used later for locking cout statements which prevent printing multiple statements at once
pthread_mutex_t printMutex;

// declare functions to be used
long double randomInRange(long double min, long double max);
void *threadfunc(void *ptr);

int main(int argc, char* argv[]) {
    // checks for argc's
    if (argc != 4 ) {
        cout << "Usage: " << argv[0] << " <threadAmount> <trials> <reportFrequency>" << std::endl;
        return 1;
    }

    // variables from the terminal
    int threadAmount = 0;
    long long trials = 0;
    long long reportFrequency = 0;

    // convert all to integers
    threadAmount = stoi(argv[1]);
    trials = stoll(argv[2]);
    reportFrequency = stoll(argv[3]);

    // make a vector of threads and their corresponding data
    vector<pthread_t> threads(threadAmount);
    vector<Data> threadData(threadAmount);

    for(int i = 0; i < threadAmount; i++) {
        threadData[i].trials = trials;
        threadData[i].reportFrequency = reportFrequency;
        threadData[i].insideCircle = 0;
        threadData[i].id = i;
        
        // create threads with a call to execute the function "threadfunc"
        int iret =  pthread_create(&threads[i], nullptr, threadfunc, &threadData[i]);
        if(iret) {
            fprintf(stderr, "Error - pthread_create() return code: %d\n", iret);
            exit(EXIT_FAILURE);
        }
    }

    // variable for storing how many total points are inside the circle area
    long long hits = 0;

    // wait for all processes to end before ending the program
    for(int i = 0; i < threadAmount; i++) {
        int iret = pthread_join(threads[i], nullptr);
        if(iret) {
            fprintf(stderr, "Error - pthread_create() return code: %d\n", iret);
            exit(EXIT_FAILURE);
        }

        hits += threadData[i].insideCircle;
    }

    long long totalTrials = threadAmount * trials;
    long double finalEstimate = 4.0L * hits / totalTrials; // circlearea / squarearea * 4 = pi

    cout << setprecision(18) << "Final result: " << finalEstimate << endl;
    return 0;
}

// returns a random number that is thread safe: https://stackoverflow.com/questions/60450514/safe-random-number-generation-using-rand-or-stdrandom-device-in-c
long double randomInRange(long double min, long double max) {
    // thread local = each thread gets their own separate thing
    thread_local random_device rd; // for seed source
    thread_local mt19937_64 rng(rd()); // use mt19937_64 engine rng generator
    thread_local uniform_real_distribution<long double> uid; // use uniform (equal probability over the interval) dist over an interval
    return uid(rng, decltype(uid)::param_type{min, max}); // generate with all the requested params
}

void *threadfunc(void *ptr) {
    Data *data = (Data*) ptr; // parse void ptr to Data ptr

    for (long long trial = 1; trial <= data->trials; trial++) {
        // generate thread safe random numbers
        long double x = randomInRange(-1.0, 1.0);
        long double y = randomInRange(-1.0, 1.0);

        if ((x * x) + (y * y) <= 1.0L) { // in circle
            data->insideCircle++;
        }

        // reports every reportFrequency trials
        if (trial % data->reportFrequency == 0) {
            long double estimate = 4.0L * data->insideCircle / trial; // estimate area so far

            pthread_mutex_lock(&printMutex);
            cout << setprecision(18) << "Thread " << data->id << ": " << data->insideCircle << " / " << trial << " (estimate: " << estimate << ")" << endl; // print output
            pthread_mutex_unlock(&printMutex);
        }
    }

    pthread_exit((void *) data); // Exit the thread with a return value (the point itself)
    return nullptr;
}
