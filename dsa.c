#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"
#include "flats.h"

const char dataset[50] = "data.csv";
int current;
flat residence[size];


int main(){

//declare things....
    //for login: 
    char user[10];
    int pass, i=2;


//Login page thing...

    printf("--------Welcome to Flat Management System--------\n\n         Please Login to continue:\n");
    printf("%-10s %s", " ", "Username: ");
    scanf("%9s", user);
    printf("%-10s %s", " ", "Password: ");
    while(1){
        scanf("%d",&pass);
        if(i==0){
            printf("Sorry, Maximum Number Of Attempts Has Reached");
            exit(0);
        }
        if (pass != 1234){
            printf("Incorrect Password, Try again: (%d attempts left)\n", i);
            printf("%-10s %s", " ", "Password: ");
        }
        else{
            printf("\n--------Successfully Logged In--------\n");
            break;
        }
        i--;
    }
    read_file();

    menufn();

    return 0;
}