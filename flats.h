#ifndef FLATS_H
#define FLATS_H
#define size 101

extern const char dataset[50];
extern int current;
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
    char status[15];
    Owner *owner;
}flat;

extern flat residence[size];


#endif