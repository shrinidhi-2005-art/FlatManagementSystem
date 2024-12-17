#ifndef FLATS_H
#define FLATS_H
#define size 101

const char *dataset = "data.csv";
int current = 100;
//owners' struct
typedef struct {
    char name[50];
    char o_info[50];
    float paid;
    float bal;
    float due;
    char date[50];
}Owner;

//flats' struct
typedef struct {
    char ID[10];
    char type[10];
    int price;
    char status[10];
    Owner *owner;
}flat;

flat residence[size];


#endif