#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "flats.h"
#include "functions.h"

flat flats;

//Creates memory space for owner field and returns a memory location
Owner* create_owner(){
    Owner* x = (Owner *)malloc(sizeof(Owner));
    if(x == NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    return x;
}

//Reads the file (data.csv) and saves it to the memory (residence array)
void read_file() {
    FILE *file = fopen(dataset, "r");
    if (file == NULL) {
        printf("error: couldn't open the file\n");
        return;
    }
    char header[150];
    fgets(header, sizeof(header), file);  // Ignorin the first line in the CSV file ('Cause it has headings, which is unnecessery)
    char line[500];
    char status[15];

    while (fgets(line, sizeof(line), file)) { 
        int i=0;
        while(line[i]!=','){
            status[i]= line[i];
            i++;
        }
        status[i] = '\0';

        if(strcmp(status, "Booked")==0){
            flats.owner = create_owner(); 

            if (sscanf(line, "%9[^,],%9[^,],%9[^,],%d,%49[^,],%49[^,],%f,%f,%f,%s", flats.status, flats.ID, flats.type, &flats.price, flats.owner->name, flats.owner->o_info, &flats.owner->paid, &flats.owner->bal, &flats.owner->due, flats.owner->date) == 10) {
                if (current >= size) {
                    printf("Error: Exceeded maximum residence capacity\n");
                    break;
                    }
            residence[current++] = flats; // increasing the current value (from 0 (in dsa.c file)) till the loop ends... (It'll store the total number of Lines in the file and, residence array will move to the next structure element to save the data)
            }
        }
        
        else if (strcmp(status, "Available")==0){
            if (sscanf(line, "%9[^,],%9[^,],%9[^,],%d", flats.status, flats.ID, flats.type, &flats.price) == 4) {
                if (current >= size) {
                    printf("Error: Exceeded maximum residence capacity\n");
                    break;
                    }
            flats.owner = NULL;
            residence[current++] = flats;
            }
        }
        
        else {
            printf("Failed to parse line: %s\n", line);
            printf("line: %s\n", line); //upon error reading the file, it'll just print this
        }
    }
    fclose(file);
    printf("\nLoading the main menu...Please Wait\n");
}
//This one will overwrite the whole thing (i mean the file) - ie., we're using it in the end of the program to save the data that we fetched/edited during the runtime... so, we'll be erasing the previous data in .csv file and rewrite everything that we've inside the memory (residence array)
void write_file(){
    FILE *file = fopen(dataset, "w");
        if (file == NULL){
            printf("error: couldn't open the file");
            return;
        }
    fprintf(file, "Status,Flat ID,Type,Price,Owner Name,Contact Info,Amount Paid So Far,Remaining Balance,Next Monthly Installment,Due Date\n");
    char line[500];
    for(int i=0; i<current; i++){
        if(strcmp(residence[i].status, "Booked")==0){
            sprintf(line, "%s,%s,%s,%d,%s,%s,%.2f,%.2f,%.2f,%s\n",residence[i].status, residence[i].ID, residence[i].type, residence[i].price, residence[i].owner->name, residence[i].owner->o_info, residence[i].owner->paid, residence[i].owner->bal, residence[i].owner->due, residence[i].owner->date);

            // printf("%s,%s,%s,%d,%s,%s,%.2f,%.2f,%.2f,%s\n",residence[i].status, residence[i].ID, residence[i].type, residence[i].price, residence[i].owner->name, residence[i].owner->o_info, residence[i].owner->paid, residence[i].owner->bal, residence[i].owner->due, residence[i].owner->date);

            fwrite(line, sizeof(char), strlen(line), file);
            free(flats.owner);
        }
        else if(strcmp(residence[i].status, "Available")==0){
            sprintf(line, "%s,%s,%s,%d,%p\n",residence[i].status, residence[i].ID, residence[i].type, residence[i].price, residence[i].owner);

            // printf("%s,%s,%s,%d,%p\n",residence[i].status, residence[i].ID, residence[i].type, residence[i].price, residence[i].owner);

            fwrite(line, sizeof(char), strlen(line), file);
        }
        else{
            printf("\nwriting error at %d\n", i);
        }
    }
    fclose(file);

}

//calculates the downpayment amount by fetching price of the flat and the % of downpayment
float down(int price, float value){
    price = (price*value)/100;
    return price;
}

//calculate the principal amount of the loan/emi using downpayment and price of the flat
float principal(int price, float down){
    return price-down;
}

//calculates the emi of the flat by using p-principal, i-intrest per annum, y-years left for repayment of the loan
float emi(float p, int i, int y) {
    float m = (float)i / 12 / 100;
    int n = y * 12; 
    float emi = (p * m * pow(1 + m, n)) / (pow(1 + m, n) - 1);
    return emi;
}

//displays the emi option inside booking menu, when u book a flat and choose emi option
int display_emi(int price){
    int ch;
    printf("\nPlease Choose Any of the EMI options from below\n");
        printf("\n1.Standard Plan\n");
        printf("\n%-20s %-10.2f\n%-20s %-10.2f\n%-20s %-20s\n%-20s %-20s\n%-20s %.2f\n", "Down Payment:", down(price, 20), "Loan Amount:", principal(price, down(price, 20)), "EMI Tenure:", "5 Years", "Interest Rate:", "7% annually", "EMI:", emi(principal(price, down(price, 20)), 7, 5) );

        printf("\n2.Flexible Tenure\n");
        printf("\n%-20s %-10.2f\n%-20s %-10.2f\n%-20s %-20s\n%-20s %-20s\n%-20s %.2f\n", "Down Payment:", down(price, 25), "Loan Amount:", principal(price, down(price, 25)), "EMI Tenure:", "6 Years", "Interest Rate:", "7.5% annually", "EMI:", emi(principal(price, down(price, 25)), 7.5, 6) );

        printf("\n3.Affordable EMI\n");
        printf("\n%-20s %-10.2f\n%-20s %-10.2f\n%-20s %-20s\n%-20s %-20s\n%-20s %.2f\n", "Down Payment:", down(price, 30), "Loan Amount:", principal(price, down(price, 30)), "EMI Tenure:", "7 Years", "Interest Rate:", "8% annually", "EMI:", emi(principal(price, down(price, 30)), 8, 7) );

        printf("Please choose a plan: ");
        while((scanf("%d", &ch)!=1)){ //when u just give scanf and use %d as format specifier, or %f or smtng which isnt a char... if u happend to type a char in the input feild when it is prompted,  the code will go infinite loop, or any unwanted errors.. so using a while loop with having a condition that it should run until the input returns 0 (ie., true - a integer has been typed), and returns error message when the condition is met, else it'll just save the input in variable 'ch' and exites the while loop
            while (getchar() != '\n'); //this is to clear the buffer if it has a newline character (also, if unseen, might cause errors)
            errors(1); //calls errors function which has errors with own value...errors(1) shows, that there are no flats with the given id or errors(2) shows, that the value entered is wrong (the choice)
        }
    return ch;
}

//confirms the flat ID if it exists or not, if exist it'll return the index of array which the flat present in, else, -1
int confirmFlatID(char *id){
    for(int i=0; i<current; i++){
        if(strcmp(id, residence[i].ID)==0)
            return i;
    }
    return -1;
}

//books the flat and asks whether the customer wants to do full on payment or pay using emi
int book(char *id, char *name, char *contact){
    int ch;
    for(int i=0; i<current; i++){
        if(strcmp(residence[i].ID, id)==0){
            residence[i].owner = create_owner(); //allocating memory for a new owner
            strcpy(residence[i].owner->name , name);
            strcpy(residence[i].owner->o_info , contact);
            printf("\nPayment method: 1. Full on payment    2. Pay with EMI\nEnter your choice: ");
            do{
                while((scanf("%d", &ch)!=1)){
                while (getchar() != '\n');
                errors(1);
                }
                if (ch == 1){
                    printf("\nSuccessfully created a record, in the name of %s with flat id %s\n", residence[i].owner->name, residence[i].ID);
                    strcpy(residence[i].status , "Booked");
                    residence[i].owner->paid = residence[i].price;
                    residence[i].owner->bal = 00.00;
                    residence[i].owner->due = 00.00;
                    // residence[i].owner->date = NULL;
                    return 1;
                }
                else if (ch == 2){
                    int e = display_emi(residence[i].price);
                    if (e == 1){ //in emi funtion, the 1st emi option returns 1
                        strcpy(residence[i].status , "Booked");
                        strcpy(residence[i].owner->name , name);
                        strcpy(residence[i].owner->o_info , contact);
                        residence[i].owner->paid = down(residence[i].price, 20);
                        residence[i].owner->bal = residence[i].price - residence[i].owner->paid;
                        residence[i].owner->due = emi(principal(residence[i].price, down(residence[i].price, 20)), 7, 5);
                        strcpy(residence[i].owner->date , "1/1/2024");
                        printf("\nSuccessfully created a record, in the name of %s with flat id %s, your next due, %.2f, is on %s\n", residence[i].owner->name, residence[i].ID,residence[i].owner->due,residence[i].owner->date);
                        return 1;
                    }
                    else if (e == 2){ //2nd emi option returns 2
                        strcpy(residence[i].status , "Booked");
                        strcpy(residence[i].owner->name , name);
                        strcpy(residence[i].owner->o_info , contact);
                        residence[i].owner->paid = down(residence[i].price, 25);
                        residence[i].owner->bal = residence[i].price - residence[i].owner->paid;
                        residence[i].owner->due = emi(principal(residence[i].price, down(residence[i].price, 25)), 7.5, 6);
                        strcpy(residence[i].owner->date , "1/1/2024");
                        printf("\nSuccessfully created a record, in the name of %s with flat id %s, your next due, %.2f, is on %s\n", residence[i].owner->name, residence[i].ID,residence[i].owner->due,residence[i].owner->date);
                        return 1;
                    }
                    else if (e == 3){ //3rd emioption returns 3
                        strcpy(residence[i].status , "Booked");
                        strcpy(residence[i].owner->name , name);
                        strcpy(residence[i].owner->o_info , contact);
                        residence[i].owner->paid = down(residence[i].price, 30);
                        residence[i].owner->bal = residence[i].price - residence[i].owner->paid;
                        residence[i].owner->due = emi(principal(residence[i].price, down(residence[i].price, 30)), 8, 7);
                        strcpy(residence[i].owner->date , "1/1/2024");
                        printf("\n Successfully created a record, in the name of %s with flat id %s, your next due, %.2f, is on %s\n", residence[i].owner->name, residence[i].ID,residence[i].owner->due,residence[i].owner->date);
                        return 1;
                    }
                }
                else{
                    errors(1); 
                }
            }while(1);
        }
    }
    return 0;
    
}

//this one is for to display the booked flats and the info
void display_booked(){
    printf("\n%-20s %-20s %-20s %-20s %-20s\n", "Flat ID", "Type", "Price", "Owner Name", "Contact info");
    for(int i =0; i < current; i++){
        if(strcmp(residence[i].status, "Booked")== 0){
            printf("%-20s %-20s %-20d %-20s %-20s\n", residence[i].ID, residence[i].type, residence[i].price, residence[i].owner->name, residence[i].owner->o_info);
        }
    }
}

//shows the available flats (flats which are not booked)
void display_available(){
        printf("\n%-20s %-20s %-20s\n", "Flat ID", "Type", "Price");
    for(int i =0; i < current; i++){
        if(strcmp(residence[i].status, "Available")== 0){
            printf("%-20s %-20s %-20d\n", residence[i].ID, residence[i].type, residence[i].price);
        }
    }
}

//shows the flat info and returns 1 if the flat has 0 bal to be paid, 2 if it has some amount left to be cleared, 3 if it is not yet booked, 0 if the search was failed
int flatinfo(char *id){
    for(int i=0; i<current; i++){
        if(strcmp(id, residence[i].ID)==0){
            printf("\n%-10s %-20s %-20s\n", " ", "Flat no.:", residence[i].ID);
            
            if(strcmp(residence[i].status, "Booked")==0){
                if(residence[i].owner->bal == 0){
                    printf("%-10s %-20s %-20s\n", " ", "Owner:", residence[i].owner->name);
                    printf("%-10s %-20s %-20s\n", " ", "Contact info:", residence[i].owner->o_info);
                    printf("%-10s %-20s %-20s\n", " ", "Type:", residence[i].type);
                    printf("%-10s %-20s %-20d\n", " ", "Price:", residence[i].price);
                    printf("%-10s %-20s %-20s\n", " ", "Balance:", "00.00");
                    return 1;
                }
                else{
                    printf("%-10s %-20s %-20s\n", " ", "Owner:", residence[i].owner->name);
                    printf("%-10s %-20s %-20s\n", " ", "Contact info:", residence[i].owner->o_info);
                    printf("%-10s %-20s %-20s\n", " ", "Type:", residence[i].type);
                    printf("%-10s %-20s %-20d\n", " ", "Price:", residence[i].price);
                    printf("%-10s %-20s %-20.f\n", " ", "Balance:", residence[i].owner->bal);
                    printf("%-10s %-20s %-20.2f\n", " ", "Due Next Month:", residence[i].owner->due);
                    printf("%-10s %-20s %-20s\n", " ", "Due Date:", residence[i].owner->date);
                    return 2;

                }
            } 
            else{
                printf("%-10s %-20s %-20s\n", " ", "Type:", residence[i].type);
                printf("%-10s %-20s %-20d\n", " ", "Price:", residence[i].price);
                return 3;
            }     
        }
    }
    return 0;
}

//this one will pays the next due amount of the flat (if there's)
void pay(char *id){
    for(int i=0; i<current; i++){
        if(strcmp(id, residence[i].ID)==0){
            residence[i].owner->paid += residence[i].owner->due;
            residence[i].owner->bal = residence[i].price - residence[i].owner->paid;
            residence[i].owner->due = 00.00;
            strcpy(residence[i].owner->date , "1/2/2024");
            printf("\nChanges recorded on Flat number %s\n\nUpdated details:\n", residence[i].ID );
            printf("\n%-10s %-20s %-20.2f", " ", "Balance:", residence[i].owner->bal);
            printf("\n%-10s %-20s %-20.2f", " ", "Due Next Month:", residence[i].owner->due);
            printf("\n%-10s %-20s %-20s\n", " ", "Due Date:", residence[i].owner->date);
            
        }
    }
}

//The menu funtion for Flat Info
void flatinfoMenu(){
    int ch;
    char c;
    char id[10];
    printf("\n%-10s %s\n\n", " ","-----Flat Information Menu-----");
    printf("\n%-10s %s", " ", "Please enter the flat ID: ");
    do{  
        scanf("%s",id);
        int x = flatinfo(id);

        if (x == 1){
            backToMenu();
            return;
        }
        else if(x == 2){
            printf("\nOptions:\n");
            printf("1. Update payment of the current flat\n");
            printf("2. return to main menu\n");
            printf("Please choose any options from above: ");
            do{
                while((scanf("%d", &ch)!=1)){
                while (getchar() != '\n');
                errors(1);
                }
                if(ch == 1){
                    printf("\nPlease enter [y/Y] if the owner has paid his current due, else type [n/N]: ");
                    do{
                        while ((c = getchar()) != '\n');
                        c = getchar();
                        if (c == 'y' || c == 'Y') {
                            pay(id);
                            backToMenu();
                            return;
                        }
                        else if(c == 'n'|| c == 'N'){
                            printf("\nNo changes were made\n");
                            backToMenu();
                            return;
                        }
                        else{
                            printf("\nERROR: Please type [y/Y] or [n/N]: ");
                        }
                    }while(1);
                }
                else if(ch == 2){
                    return;
                }
                else{
                    errors(1);
                }
            }while(1);
        }
        else if( x == 3){
            printf("%-10s\n" , "Not Booked yet!");
            backToMenu();
            return;
        }
        else
        {
            printf("\n%-10s %s", " ", "Please enter the correct flat ID: ");
        }


    }while(1);
}

//Menu funtion for Booking the Flat
void bookMenu(){
    int ch;
    char id[10];
    char name[50];
    char contact[50];
    printf("\n%-10s %s\n\n", " ","-----Book A New Flat-----");
    printf("Type the flat ID: ");
    do{
        scanf("%s", id);
        if (confirmFlatID(id)!=-1){
            if (strcmp(residence[confirmFlatID(id)].status, "Booked")== 0){
                printf("\nThis Flat is already Booked in the name of %s\n", residence[confirmFlatID(id)].owner->name);
                printf("1. try again if your flat ID was wrong \n2. check the list of available flats\n3. Go back to main menu \nPlease choose an option: ");
                do{
                    scanf("%d", &ch);
                    if(ch == 1){
                        break;
                    }
                    else if(ch == 2){
                        display_available();
                        backToMenu();
                        return;
                    }
                    else if(ch == 3){
                        return;
                    }
                    else{
                        errors(1);
                    }
                }while(1);
            }
            else{
                printf("\nPlease enter your name: ");
                scanf("%s", name);
                printf("Please enter your contact number: ");
                scanf("%s", contact);
                book(id, name, contact);
                printf("\nsuccessfully Booked The Flat!!\n");
                backToMenu();
                return;
            }
        }
        else{
            errors(0);
        }

    }while(1);
    return; 
}

//Menu funtion that shows the available flats and used backtomenu funtion to prompt the user to go back to the main menu
void availableMenu(){
    display_available();
    backToMenu();
    return;
}

//Menu funtion that shows the Booked flats and used backtomenu funtion to prompt the user to go back to the main menu
void bookedMenu(){
    display_booked();
    backToMenu();
    return;
}

//Menu funtion to manage payment of the flats which has due... uses pay() funtion.
void paymentMenu(){
    char id[10];
    int ch;
    char c;
    printf("\nPlease enter the flat ID: ");
    do{
        scanf("%s", id);
        if(confirmFlatID(id)!=-1){
            int x = flatinfo(id);
            if(x== 1){
                printf("\nThis flat has no due, no payment is required\n");
                backToMenu();
                return;
            }
            else if(x == 2){    
                printf("\nPlease enter [y/Y] if the owner has paid his current due, else type [n/N]: ");
                do{
                    while ((c = getchar()) != '\n');
                    c = getchar();
                    if (c == 'y' || c == 'Y') {
                        pay(id);
                        printf("\nSuccessfully updated the records\n");
                        backToMenu();
                        return;
                    }
                    else if (c == 'n' || c == 'N'){
                        printf("\nNo changes were made\n");
                        backToMenu();
                        return;
                    }
                    else{
                        printf("\nERROR: Please type [y/Y] or [n/N]: ");
                    }
                }while(1);
            }
            else if(x == 3){
                printf("\nThis flat is not yet booked, no payment is required\n");
                backToMenu();
                return;
            }
        }
        else{
            errors(0);
            printf("\n1. Try again\n2. Go back to main menu\nPlease choose an option: ");
            do{
                while((scanf("%d", &ch)!=1)){
                while (getchar() != '\n');
                errors(1);
                }
                if(ch == 1){
                    break;
                }
                else if(ch == 2){
                    return;
                }
                else{
                    errors(1);
                }
            }while(1);
        }
    }while(1);
}

//saves the whole data into the csv file... 
void save(){
    
    printf("\nSaving changes....\n");
    write_file();
    free(flats.owner);
    printf("\nLogging out....\n");
    return;
}

//errors. 0 for Wrong or unsuccessfull search of Flat with the given ID and 1 for wrong choice
void errors(int value){
    if (value == 0){
        printf("\nCouldn't find the flat with that ID, please try again: ");
        return;
    }
    else if (value == 1){
        printf("Wrong choice, Please try again: ");
        return;
    }
    else{
        return;
    }
}

//Function which prompts to the user whether he wants to go back to the main menu..
void backToMenu() {
    int ch;
    printf("\ntype 0 to return to the main menu: ");
    while (1) {
        if (scanf("%d", &ch) == 1 ) { 
            if (ch == 0) {
                return;
            } 
            else {
                errors(1);
            }
        }
        else {
            while (getchar() != '\n');
            errors(1);
        }
    }
}

//  MAIN MENU funtion. 
void menufn(){
    int ch;
    char c;
    char *id[10];
    while(1){
        printf("\n--------Menu--------\n");
        printf("1. View Flat info\n");
        printf("2. Book a new flat\n");
        printf("3. List booked flats\n");
        printf("4. List Available flats\n");
        printf("5. Update payment of a flat\n");
        printf("6. Save and logout\n");
        printf("\nPlease select an option: ");
        while((scanf("%d", &ch)!=1)){
            while (getchar() != '\n');
            errors(1);
        }
        switch(ch){
            case 1: flatinfoMenu(); break;
            case 2: bookMenu(); break;
            case 3: bookedMenu(); break;
            case 4: availableMenu(); break;
            case 5: paymentMenu(); break;
            case 6: save(); exit(0);
            default: errors(1); break;
        }
    }
}
