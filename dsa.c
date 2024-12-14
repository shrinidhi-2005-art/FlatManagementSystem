#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"
#include "flats.h"

int main(){

//declare things....
    //for login: 
    char user[5];
    int pass, i=1;


//Login page thing...

printf("--------Welcome to Flat Management System--------\n       Please Login to continue:\n");
printf("\n          Username: ");
scanf("%4s", user);
printf("\n          password: ");
while(1){
    scanf("%d",&pass);
    if(i==4){
        printf("Maximum Number Of Attempts");
        exit(0);
    }
    if (pass != 12345){
        printf("\nIncorrect Password, Try again (attempt %d)", i);
    }
    else
        printf("\n--------Successfully Logged In--------");
        break;
    i++;
}

return 0;
}

