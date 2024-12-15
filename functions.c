#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "flats.h"
#include "functions.h"
//i'll do the functions parttttt


void read_file(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("error: couldn't open the file");
        return;
    }

    char header[100];
    fgets(header, sizeof(header), file); //this will make the function to ignore the 1st line in the csv.. idk how tho

    while(fscanf(file, ""))
}   