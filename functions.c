#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
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
        fprintf(file, "%s,%s,%d,%s,%s,%.2f,%.2f,%.2f,%s,%s",residence[i].ID, residence[i].type, residence[i].price, residence[i].owner->owner, residence[i].owner->o_info, residence[i].owner->paid, residence[i].owner->bal, residence[i].owner->due, residence[i].owner->date, residence[i].status  );
    }
    fclose(file);

}

int down(int price, int value){
    price = (price*value)/100;
    return price;
}
int principal(int price, int down){
    return price-down;
}
int emi(int p, int i, int y){
    i /= 12;
    y *= 12;
    int emi = (p*i*(pow((1+i), y)))/(pow((1+i), y)-1);
    return emi;
}

int display_emi(int price){
    int ch;
    printf("\nPlease Choose Any of the EMI options from below\n");
        printf("\n1.Standard Plan\n");
        printf("\n%-20s %-10d\n%-20s %-10d\n%-20s %-20s\n%-20s %-20s\n%-20s %.2f\n", "Down Payment:", down(price, 20), "Loan Amount:", principal(price, down(price, 20)), "EMI Tenure:", "5 Years", "Interest Rate:", "7%% annually", "EMI:", emi(principal(price, down(price, 20)), 7, 5) );

        printf("\n2.Flexible Tenure\n");
        printf("\n%-20s %-10d\n%-20s %-10d\n%-20s %-20s\n%-20s %-20s\n%-20s %.2f\n", "Down Payment:", down(price, 25), "Loan Amount:", principal(price, down(price, 25)), "EMI Tenure:", "6 Years", "Interest Rate:", "7.5%% annually", "EMI:", emi(principal(price, down(price, 25)), 7.5, 6) );

        printf("\n3.Affordable EMI\n");
        printf("\n%-20s %-10d\n%-20s %-10d\n%-20s %-20s\n%-20s %-20s\n%-20s %.2f\n", "Down Payment:", down(price, 30), "Loan Amount:", principal(price, down(price, 30)), "EMI Tenure:", "7 Years", "Interest Rate:", "8%% annually", "EMI:", emi(principal(price, down(price, 30)), 8, 7) );

        printf("Please choose a plan: ");
        scanf("%d", &ch);
        return ch;
}


void book(char *id, char *name, char *contact, int choice){
    int ch;
    for(int i=0; i<current; i++){
        if(strcmp(residence[i].ID, id)==0){
            residence[i].owner->owner = name;
            residence[i].owner->contact = contact;
            printf("\nPayment method: 1. Full on payment    2. Pay with EMI\nEnter your choice: ");
            scanf("%d", &ch);
            if (ch == 1){
                printf("Successfully created a record, in the name of %s with flat id %s", residence[i].owner->owner, residence[i].ID);
                residence[i].status = "Booked";
                return;
            }
            else if (ch == 2){
                int e = display_emi(residence[i].price);
                if (e == 1){
                    residence[i].status = "Booked";
                    residence[i].owner->owner = name;
                    residence[i].owner->o_info = contact;
                    residence[i].owner->paid = down(residence[i].price, 20);
                    residence[i].owner->bal = residence[i].price - residence[i].owner->paid;
                    residence[i].owner->due = emi(principal(residence[i].price, down(residence[i].price, 20)), 7, 5);
                    residence[i].owner->date = "1/1/2024";
                    printf("Successfully created a record, in the name of %s with flat id %s, your next due, %d, is on %s", residence[i].owner->owner, residence[i].ID,residence[i].owner->due,residence[i].owner->date);
                    return;
                }
                else if (e == 2){
                    residence[i].status = "Booked";
                    residence[i].owner->owner = name;
                    residence[i].owner->o_info = contact;
                    residence[i].owner->paid = down(residence[i].price, 25);
                    residence[i].owner->bal = residence[i].price - residence[i].owner->paid;
                    residence[i].owner->due = emi(principal(residence[i].price, down(residence[i].price, 25)), 7.5, 6);
                    residence[i].owner->date = "1/1/2024";
                    printf("Successfully created a record, in the name of %s with flat id %s, your next due, %d, is on %s", residence[i].owner->owner, residence[i].ID,residence[i].owner->due,residence[i].owner->date);
                    return;
                }
                else if (e == 3){
                    residence[i].status = "Booked";
                    residence[i].owner->owner = name;
                    residence[i].owner->o_info = contact;
                    residence[i].owner->paid = down(residence[i].price, 30);
                    residence[i].owner->bal = residence[i].price - residence[i].owner->paid;
                    residence[i].owner->due = emi(principal(residence[i].price, down(residence[i].price, 30)), 8, 7);
                    residence[i].owner->date = "1/1/2024";
                    printf("Successfully created a record, in the name of %s with flat id %s, your next due, %d, is on %s", residence[i].owner->owner, residence[i].ID,residence[i].owner->due,residence[i].owner->date);
                    return;
                }
            }
        }
    }
}

//this one's for to display the booked flats and the info 
void display_booked(){
    printf("\n%-20s %-20s %-20s %-20s %-20s\n", "Flat ID", "Type", "Price", "Owner Name", "Contact info");
    for(int i =0; i < current; i++){
        if(strcmp(residence[i].status, "Booked")== 0){
            printf("%-20s %-20s %-20d %-20s %-20s\n", residence[i].ID, residence[i].type, residence[i].price, residence[i].owner->owner, residence[i].owner->o_info);
        }
    }
}

void display_available(){
        printf("\n%-20s %-20s %-20s\n", "Flat ID", "Type", "Price");
    for(int i =0; i < current; i++){
        if(strcmp(residence[i].status, "Available")== 0){
            printf("%-20s %-20s %-20d %-20s %-20s\n", residence[i].ID, residence[i].type, residence[i].price);
        }
    }
}

void flatinfo(char *id){
    for(int i=0; i<current; i++){
        if(strcmp(id, residence[i].ID)==0){
            printf("\n%-10s %-20s %-20s\n", " ", "Flat no.:", residence[i].ID);
            
            if(strcmp(residence[i].status, "Booked")==0){
                if(residence[i].owner->bal == NULL){
                    printf("%-20s %-20s\n", " ", "Owner:", residence[i].owner->owner);
                    printf("\n%-10s %-20s %-20s\n", " ", "Contact info:", residence[i].owner->o_info);
                    printf("%-10s %-20s %-20s\n", " ", "Type:", residence[i].type);
                    printf("\n%-10s %-20s %-20d\n", " ", "Price:", residence[i].price);
                    printf("\n%-10s %-20s %-20s\n", " ", "Balance:", "00.00");
                }
                else{
                    printf("%-20s %-20s\n", " ", "Owner:", residence[i].owner->owner);
                    printf("\n%-10s %-20s %-20s\n", " ", "Contact info:", residence[i].owner->o_info);
                    printf("%-10s %-20s %-20s\n", " ", "Type:", residence[i].type);
                    printf("\n%-10s %-20s %-20d\n", " ", "Price:", residence[i].price);
                    printf("\n%-10s %-20s %-20d\n", " ", "Balance:", residence[i].owner->bal);
                    printf("\n%-10s %-20s %-20d\n", " ", "Due Next Month:", residence[i].owner->due);
                    printf("\n%-10s %-20s %-20s\n", " ", "Due Date:", residence[i].owner->date);

                }
            }      
        }
    }
}

void pay(char *id){
    for(int i=0; i<current; i++){
        if(strcmp(id, residence[i].ID)==0){
            residence[i].owner->paid += residence[i].owner->due;
            residence[i].owner->bal = residence[i].price - residence[i].owner->paid;
            residence[i].owner->due = 00.00;
            residence[i].owner->date = "1/2/2024";
            printf("\nChanges recorded on Flat number %s\n updated details:\n", residence[i].ID );
            printf("\n%-10s %-20s %-20d\n", " ", "Balance:", residence[i].owner->bal);
            printf("\n%-10s %-20s %-20d\n", " ", "Due Next Month:", residence[i].owner->due);
            printf("\n%-10s %-20s %-20s\n", " ", "Due Date:", residence[i].owner->date);
            
        }
    }
}

