#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <openssl/sha.h>
#include <string.h>
#include <time.h>

int NUM_PASSWORDS = 100000;
int MAX_THREADS  = 20;

struct thread_data {
    int  thread_id;
    int  num_threads;
    char **plaintexts;
    char **encrypted;
    double *execution_times;
};

void *encrypt_passwords(void *threadarg) {
    struct thread_data *data;
    data = (struct thread_data *) threadarg;
    int i, start, end, thread_id, num_threads;
    //double start_time, end_time;

    thread_id = data->thread_id;
    num_threads = data->num_threads;

    // Each thread encrypts a portion of the plaintexts array
    start = thread_id * NUM_PASSWORDS / num_threads;
    end = (thread_id + 1) * NUM_PASSWORDS / num_threads;

    
    //start_time = omp_get_wtime();
    clock_t start_time = clock();
    
    for (i = start; i < end; i++) {
        SHA1(data->plaintexts[i], strlen(data->plaintexts[i]), data->encrypted[i]);
    }

    // for (i = start; i < end; i++) {
    //     for (int j = 0; j < 100; j++) {
    //         SHA1(data->plaintexts[i], strlen(data->plaintexts[i]), data->encrypted[i]);
    //     }
    // }

    //end_time = omp_get_wtime();
    clock_t end_time = clock();
    data->execution_times[thread_id] = end_time - start_time;
    //usleep(1000);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if(argc > 2){
        NUM_PASSWORDS = atoi(argv[2]);
        MAX_THREADS = atoi(argv[1]);
    }

    int i, rc;
    pthread_t threads[MAX_THREADS];
    struct thread_data data[MAX_THREADS];

    char *plaintexts[NUM_PASSWORDS];
    char *encrypted[NUM_PASSWORDS];
    double execution_times[MAX_THREADS];

    for (i = 0; i < NUM_PASSWORDS; i++) {
        plaintexts[i] = "password1234533333";
        encrypted[i] = malloc(SHA_DIGEST_LENGTH);
    }

    for (i = 1; i <= MAX_THREADS; i++) {
        data[i-1].thread_id = i-1;
        data[i-1].num_threads = i;
        data[i-1].plaintexts = plaintexts;
        data[i-1].encrypted = encrypted;
        data[i-1].execution_times = execution_times;
        rc = pthread_create(&threads[i-1], NULL, encrypt_passwords, (void *) &data[i-1]);
        if (rc) {
            printf("Error: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for (i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the execution times for each number of threads
    for (i = 0; i < MAX_THREADS; i++) {
        printf("Execution time with %d threads: %f seconds\n", i+1, execution_times[i]);
    }

    // Save the data to a file for plotting
    FILE *f = fopen("data.txt", "w");
    for (i = 0; i < MAX_THREADS; i++) {
        fprintf(f, "%d %f\n", i+1, execution_times[i]);
    }
    fclose(f);

    // Clean up
    for (i = 0; i < NUM_PASSWORDS; i++) {
        free(encrypted[i]);
    }

    

    FILE* gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set term png\n");
    fprintf(gnuplot, "set output 'plot.png'\n");
    fprintf(gnuplot, "set xlabel 'Number of Threads'\n");
    fprintf(gnuplot, "set ylabel 'Execution Time (s)'\n");
    fprintf(gnuplot, "set title 'Multithreaded SHA-1 Encryption Benchmark'\n");
    fprintf(gnuplot, "plot 'data.txt' using 1:2 with lines");
    fflush(gnuplot);
    pclose(gnuplot);
    printf("Plot created: plot.png\n");
    //return 0;
    pthread_exit(NULL);
    //return 0;
}