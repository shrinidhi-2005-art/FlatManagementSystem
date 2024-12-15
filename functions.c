#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "flats.h"
#include "functions.h"
//i'll do the functions parttttt

flat flats;


//this will read the file and store the data inside array named residence (check flats.h)
void read_file(){

    //allocatin memory for owners
    flats.owner = (owner *)malloc(sizeof(owner));
    if(flats.owner == NULL){
        printf("Memory allocation failed");
        return;
    }

    FILE *file = fopen(dataset, "r");
    if (file == NULL){
        printf("error: couldn't open the file");
        return;
    }

    char header[50];
    fgets(header, sizeof(header), file); //this will make the function to ignore the 1st line in the csv.. idk how tho

    while(fscanf(file, "%9[^,],%9[^,],%d,%49[^,],%49[^,],%f,%f,%f,%49[^,],%9[\n]\n", &flats.ID, &flats.type, &flats.price, &flats.owner->owner, &flats.owner->o_info, &flats.owner->paid, &flats.owner->bal, &flats.owner->due, &flats.owner->date, &flats.status)== 10){
        residence[current++] = flats;
    }
    fclose(file);
}

//This one will overwrite the whole thing (i mean file)
void write_file(){
    FILE *file = fopen(dataset, "w");
        if (file == NULL){
            printf("error: couldn't open the file");
            return;
        }
    
    fprintf(file, "Flat ID,Type,Price,Owner Name,Contact Info,Amount Paid So Far (₹),Remaining Balance (₹),Next Monthly Installment (₹),Due Date,Status");

    for(int i=0; i<current; i++){
        fprintf(file, "%s,%s,%d,%s,%s,%f,%f,%f,%s,%s",residence[i].ID, residence[i].type, residence[i].owner->owner, residence[i].owner->o_info, residence[i].owner->paid, residence[i].owner->bal, residence[i].owner->due, residence[i].owner->date, residence[i].status  );
    }
    fclose(file);

}

//this one's for to display the booked flats and the info 
void display_booked(){
    
}
