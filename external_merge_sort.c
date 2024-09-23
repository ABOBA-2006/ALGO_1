#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

#include "defines.h"




bool isFileEmpty(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size == 0;
}


void splitData(struct FILES *files, int subArrayLength){
    bool isB_File = true;

    while (1) {
        int i;
        for(i = 0; i < subArrayLength; i++){
            int number = 0;

            if (fscanf(files->file_A, "%d", &number) != 1) {
                break; // Break if fscanf fails (reaches end of file)
            }

            if (isB_File) {
                fprintf(files->file_B, "%d\n", number);
                fflush(files->file_B);
            } else {
                fprintf(files->file_C, "%d\n", number);
                fflush(files->file_C);
            }
        }

        if (i < subArrayLength) {
            break;
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
                    fflush(files->file_A);
                    xAmount++;
                    if(fscanf(files->file_B, "%d", &x) == EOF) {
                        xAmount = subArrayLength;
                    }
                }else {
                    fprintf(files->file_A, "%d\n", y);
                    fflush(files->file_A);
                    yAmount++;
                    if(fscanf(files->file_C, "%d", &y) == EOF) {
                        yAmount = subArrayLength;
                    }
                }
            }
        }

        while(xAmount < subArrayLength) {
            fprintf(files->file_A, "%d\n", x);
            fflush(files->file_A);
            xAmount++;
            if(fscanf(files->file_B, "%d", &x) == EOF) {
                xAmount = subArrayLength;
            }
        }

        while (yAmount < subArrayLength) {
            fprintf(files->file_A, "%d\n", y);
            fflush(files->file_A);
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
    long int startSubArrayLength = 1;
    struct FILES *myFiles = (struct FILES *)malloc(sizeof(struct FILES));
    struct timeval start, end;

    gettimeofday(&start, NULL);

    myFiles->file_A = fopen(PATH_A, "r+");
    myFiles->file_B = fopen(PATH_B, "w+");
    myFiles->file_C = fopen(PATH_C, "w+");

    if (myFiles->file_A == NULL || myFiles->file_B == NULL || myFiles->file_C == NULL) {
        perror("Error opening file");
        exit(1);
    }

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