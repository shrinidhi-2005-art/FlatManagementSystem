#ifndef FLATS_H
#define FLATS_H
#define size 101

const char *dataset = "data.csv";
int current = 100;
//owners' struct
typedef struct {
    char *name;
    char *o_info;
    float paid;
    float bal;
    float due;
    char *date;
}Owner;

//flats' struct
typedef struct {
    char *ID;
    char *type;
    int price;
    char *status;
    Owner *owner;
}flat;

flat residence[size];


#endif