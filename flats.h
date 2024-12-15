#ifndef FLATS_H
#define FLATS_H
#define size 100;

const char *dataset = "data.csv";
int current = 100;
flat residence[];


//owners' struct
typedef struct {
    char owner[50];
    char o_info[50];
    float paid;
    float bal;
    float due;
    char date[50];
}owner;

//flats' struct
typedef struct {
    char ID[10];
    char type[10];
    int price;
    char status[10];
    owner *owner;
}flat;


#endif