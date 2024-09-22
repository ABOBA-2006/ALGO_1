#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "defines.h"


void splitData(struct FILES *files, int subArrayLength, bool isBFile){

    for(int i = 0; i < subArrayLength; i++){
        int number = 0;

        if (fscanf(files->file_A, "%d", &number) != EOF) {
            if (isBFile) {
                fprintf(files->file_B, "%d\n", number);
                fflush(files->file_B);
            } else {
                fprintf(files->file_C, "%d\n", number);
                fflush(files->file_C);
            }
        } else {
            return;
        }
    }

    splitData(files, subArrayLength, !isBFile);
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

    while(!feof(files->file_B) && !feof(files->file_C)) {

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

        xAmount = 0;
        yAmount = 0;
    }
}


int main(){
    int currenSubArrayLength = 4;
    struct FILES *myFiles = (struct FILES *)malloc(sizeof(struct FILES));

    myFiles->file_A = fopen(PATH_A, "r+");
    myFiles->file_B = fopen(PATH_B, "w+");
    myFiles->file_C = fopen(PATH_C, "w+");

    if (myFiles->file_A == NULL || myFiles->file_B == NULL || myFiles->file_C == NULL) {
        perror("Error opening file");
        exit(1);
    }

    freopen(PATH_A, "r+", myFiles->file_A);
    freopen(PATH_B, "w+", myFiles->file_B);
    freopen(PATH_C, "w+", myFiles->file_C);
    splitData(myFiles, currenSubArrayLength, true);
    freopen(PATH_A, "w+", myFiles->file_A);
    freopen(PATH_B, "r+", myFiles->file_B);
    freopen(PATH_C, "r+", myFiles->file_C);
    mergeData(myFiles, currenSubArrayLength);



    fclose(myFiles->file_A);
    fclose(myFiles->file_B);
    fclose(myFiles->file_C);
    free(myFiles);
}