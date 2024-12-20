#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"
#include "flats.h"

const char dataset[50] = "data.csv";
int current = 0; 
flat residence[size];

int main(){
    char user[10];
    int pass, i=2;

    //Login page
    printf("--------Welcome to Flat Management System--------\n\n         Please Login to continue:\n");
    printf("%-10s %s", " ", "Username: "); //type wtvr u want but below 10 chars
    scanf("%9s", user);
    printf("%-10s %s", " ", "Password: "); //type the password : 1234 ('cause its what i checked in if condition below...)
    while(1){
        while((scanf("%d", &pass)!=1)){
            while (getchar() != '\n');
            printf("\nPassword should be in Digits!!\n");
            printf("Try again: ");
        }
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
        i--;//decreases the amount of attempts after each tries
    }

    read_file(); //reads the file data.csv and saves all the info to the RAM (residence array)
    menufn(); //calls the main menu funtion

    return 0;
}