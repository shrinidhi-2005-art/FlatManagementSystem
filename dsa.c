#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"
#include "flats.h"

const char dataset[50] = "data.csv";
int current = 100;
flat residence[size];


int main(){

//declare things....
    //for login: 
    char user[5];
    int pass, i=2;


//Login page thing...

    printf("--------Welcome to Flat Management System--------\n       Please Login to continue:\n");
    printf("\n          Username: ");
    scanf("%4s", user);
    printf("\n          password: ");
    while(1){
        scanf("%d",&pass);
        if(i==0){
            printf("Sorry, Maximum Number Of Attempts Has Reached");
            exit(0);
        }
        if (pass != 1234){
            printf("\nIncorrect Password, Try again (%d attempts left)\n", i);
            printf("\n          password: ");
        }
        else{
            printf("\n--------Successfully Logged In--------");
            break;
        }
        i--;
    }
    read_file();
    printf("\nfinshed\n");

    menufn();
    // printf("\ndisplay_emi()\n");
    // display_emi(50000);
    // printf("\ndisplay_boooked()\n");
    // display_booked();
    // printf("\ndisplay_available()\n");
    // display_available();
    // printf("\nflatinfomenu()\n");
    // flatinfoMenu();
    // printf("\npaymentmenu()\n");
    // paymentMenu();
    // printf("\nBookmenu()\n");
    // bookMenu();
    // printf("\nsave()\n");
    // save();

    return 0;
}