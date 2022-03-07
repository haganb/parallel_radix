#include "../helpers.c"
#include <sys/time.h>

#define SIZE 50
#define SIZE_PRINT_LIMIT 100

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

// get_max: Helper method used for CPU-bound Radix sort
int get_max(unsigned int *matrix, int N){
    int max = matrix[0];
    for(int i = 0; i < N; i++){
        if(matrix[i] > max){
            max = matrix[i];
        }
    }
    return max;
}

// counting_sort: Helper method used for CPU-bound Radix Sort
void counting_sort(unsigned int *matrix, int place, int N, int max){
    int i; //used for multiple iterators
    int output[N];
    int count[max];
    // Initialize all values in count to 0
    for(i = 0; i < max; i++){
        count[i] = 0;
    }
    // Build count[] such that count[i] = position of i in output[]
    for(i = 0; i < N; i++){
        count[(matrix[i] / place) % 10]++;
    }
    // Calculating Prefix Sum
    for(i = 1; i < 10; i++){
        count[i] += count[i-1];
    }
    // Build output array by assigning sorted elements, decrement count
    for(i = N - 1; i >= 0; i--){
        output[count[(matrix[i] / place) % 10] - 1] = matrix[i];
        count[(matrix[i] / place) % 10]--;
    }
    // Re-assigning values for in-place sorting
    for(i = 0; i < N; i++){
        matrix[i] = output[i];
    }
}

// Conventional Radix Sort implementation, all done on CPU
void cpu_radix(unsigned int *matrix, int N){
    int max = get_max(matrix, N);
    for(int place = 1; max / place > 0; place *= 10){
        counting_sort(matrix, place, N, max);
    }
}

// get_cpu_benchmark: method to use radix sort on CPU and benchmark
float get_cpu_benchmark(unsigned int *unsorted_matrix){
    // Set up benchmarking tools
    struct timeval begin;
    struct timeval end;
    gettimeofday(&begin, NULL);

    // Actual sorting
    cpu_radix(unsorted_matrix, SIZE);

    // Finish benchmarking
    gettimeofday(&end, NULL);
    float host_time = (float)((end.tv_usec - begin.tv_usec)) / 1000;
    printf("Elapsed time for CPU-bound sorting (ms): %f\n", host_time);

    // Ensure that device is properly sorted
    if(check_if_sorted(unsorted_matrix, SIZE)){
        printf("Host matrix was sorted ");
        printf(ANSI_GREEN "successfully." ANSI_RESET "\n");

        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Good sort: ");
            print_matrix(unsorted_matrix, SIZE);
        }
    }else{
        printf("ERROR: Host matrix sorting ");
        printf(ANSI_RED "failed." ANSI_RESET "\n");
        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Bad sort: ");
            print_matrix(unsorted_matrix, SIZE);
        }
    }
    printf("\n");
    return host_time;
}

int main(){
    printf("Sorting array with %d elements\n", SIZE);

    unsigned int* array = (int*) malloc(sizeof(int) * SIZE);
    init_matrix(array, SIZE);
    float sequential_time = get_cpu_benchmark(array);
    return 0;
}