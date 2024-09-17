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


int main(){
    struct FILES *myFiles = (struct FILES *)malloc(sizeof(struct FILES));

    myFiles->file_A = fopen("../main_file_small_A.txt", "r+");
    myFiles->file_B = fopen("../temporary_file_small_B.txt", "r+");
    myFiles->file_C = fopen("../temporary_file_small_C.txt", "r+");

    if (myFiles->file_A == NULL || myFiles->file_B == NULL || myFiles->file_C == NULL) {
        perror("Error opening file");
        exit(1);
    }

    splitData(myFiles, 2, true);

    fclose(myFiles->file_A);
    fclose(myFiles->file_B);
    fclose(myFiles->file_C);
    free(myFiles);
}