#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// init_matrix: Method used to populate matrix with randomized values
void init_matrix(unsigned int* matrix, int N){
    srand(time(NULL));
    //int val = N;
    for(int i = 0; i < N; i++){
        matrix[i] = rand () % N;
        //matrix[i] = val;
        //val--;
    }
}

// check_if_sorted: iterate through values in matrix, ensure that it is in proper order
bool check_if_sorted(unsigned int* matrix, int N){
    for(int i = 0; i < N-1; i++){
        if(matrix[i] > matrix[i+1]){
            return false;
        }
    }
    return true;
}

// compare_matrix: method used to compare all indexes in both matrices to ensure they both got sorted the same way
bool compare_matrix(unsigned int* device_matrix, unsigned int* host_matrix, int N){
    for(int i = 0; i < N; i++){
        if(device_matrix[i] != host_matrix[i]){
            return false;
        }
    }
    return true;
}

// print_matrix: helper method to print all values in matrix
void print_matrix(unsigned int* matrix, int N){
    printf("[");
    for(int i = 0; i < N; i++){
        if(i != (N-1)){
            printf("%d, ", matrix[i]);
        }else{
            printf("%d]\n", matrix[i]);
        }
    }
}

