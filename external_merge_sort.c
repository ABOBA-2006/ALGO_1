#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

#include "defines.h"



// Comparison function
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void read100MB(struct FILES *files){
    while(!feof(files->file_A2)){
        int *buffer = calloc(AMOUNT_OF_INTS, sizeof(int));
        int counter = 0;

        while (counter<AMOUNT_OF_INTS && !feof(files->file_A2)){
            fscanf(files->file_A2, "%d", &buffer[counter]);
            counter++;
        }

        if(counter != AMOUNT_OF_INTS){
            realloc(buffer, counter * sizeof(int));
        }

        qsort(buffer, counter, sizeof(int), compare);

        for(int i=0; i<counter; i++){
            fprintf(files->file_A, "%d\n", buffer[i]);
        }

        free(buffer);
    }
}


bool isFileEmpty(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size == 0;
}


void splitData(struct FILES *files, int subArrayLength){
    bool isB_File = true;

    while(!feof(files->file_A)){
        int counter = 0;
        int number = 0;

        while (counter<subArrayLength && !feof(files->file_A)){
            fscanf(files->file_A, "%d", &number);

            if(isB_File){
                fprintf(files->file_B, "%d\n", number);
            }else{
                fprintf(files->file_C, "%d\n", number);
            }
            counter++;
        }

        isB_File = !isB_File;
    }
}


void mergeData(struct FILES *files, int subArrayLength) {
    int x, y;
    int xAmount = 0, yAmount = 0;
    if(fscanf(files->file_B, "%d", &x) == EOF) {
        xAmount = subArrayLength;
    }
    if(fscanf(files->file_C, "%d", &y) == EOF) {
        yAmount = subArrayLength;
    }

    while(!feof(files->file_B) || !feof(files->file_C)) {

        if(!feof(files->file_B) && !feof(files->file_C)) {
            while(xAmount < subArrayLength && yAmount < subArrayLength) {
                if(x < y) {
                    fprintf(files->file_A, "%d\n", x);
                    xAmount++;
                    if(fscanf(files->file_B, "%d", &x) == EOF) {
                        xAmount = subArrayLength;
                    }
                }else {
                    fprintf(files->file_A, "%d\n", y);
                    yAmount++;
                    if(fscanf(files->file_C, "%d", &y) == EOF) {
                        yAmount = subArrayLength;
                    }
                }
            }
        }

        while(xAmount < subArrayLength) {
            fprintf(files->file_A, "%d\n", x);
            xAmount++;
            if(fscanf(files->file_B, "%d", &x) == EOF) {
                xAmount = subArrayLength;
            }
        }

        while (yAmount < subArrayLength) {
            fprintf(files->file_A, "%d\n", y);
            yAmount++;
            if(fscanf(files->file_C, "%d", &y) == EOF) {
                yAmount = subArrayLength;
            }
        }

        xAmount = feof(files->file_B)? xAmount:0;
        yAmount = feof(files->file_C)? yAmount:0;
    }
}


void extendedSort(struct FILES *files, int subArrayLength) {
    do {
        freopen(PATH_A, "r+", files->file_A);
        freopen(PATH_B, "w+", files->file_B);
        freopen(PATH_C, "w+", files->file_C);
        splitData(files, subArrayLength);
        freopen(PATH_A, "w+", files->file_A);
        freopen(PATH_B, "r+", files->file_B);
        freopen(PATH_C, "r+", files->file_C);
        mergeData(files, subArrayLength);

        subArrayLength*=2;
    }while (!isFileEmpty(files->file_C));
}


int main(){
    //long int startSubArrayLength = 1;
    long int startSubArrayLength = AMOUNT_OF_INTS;
    struct FILES *myFiles = (struct FILES *)malloc(sizeof(struct FILES));
    struct timeval start, end;

    gettimeofday(&start, NULL);

    //myFiles->file_A = fopen(PATH_A, "r+");
    myFiles->file_A = fopen(PATH_A, "w+");
    myFiles->file_A2 = fopen(PATH_A2, "r+");
    myFiles->file_B = fopen(PATH_B, "w+");
    myFiles->file_C = fopen(PATH_C, "w+");

    if (myFiles->file_A == NULL || myFiles->file_B == NULL || myFiles->file_C == NULL) {
        perror("Error opening file");
        exit(1);
    }

    read100MB(myFiles);
    extendedSort(myFiles, startSubArrayLength);


    fclose(myFiles->file_A);
    fclose(myFiles->file_B);
    fclose(myFiles->file_C);
    free(myFiles);

    gettimeofday(&end, NULL);

    double time_taken = end.tv_sec + end.tv_usec / 1e6 -
                        start.tv_sec - start.tv_usec / 1e6; // in seconds

    printf("time program took %f seconds to execute\n", time_taken);
}