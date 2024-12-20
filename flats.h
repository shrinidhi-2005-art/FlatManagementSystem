#ifndef FLATS_H 
#define FLATS_H
#define size 100

extern const char dataset[50];
extern int current;

// Struct for owner information
typedef struct {
    char name[50];
    char o_info[50];
    float paid;
    float bal;
    float due;
    char date[50];
}Owner;

//Struct for flat information
typedef struct {
    char ID[10];
    char type[10];
    int price;
    char status[15];
    Owner *owner;
}flat;

//extern is used to interlink the global variables from file to file, in this case, this is declared in our dsa.c file
extern flat residence[size]; //saving all the flat struct inside residence array... 

//ifndef, define and endif are called as Guards... they're used to make sure the header files are not defined multiple times
//ifndef = if not defined
//define = (continuing the last line, if not defined, then define it now...)
//endif = ending of the guard 
#endif

