#ifndef FLATS_H
#define FLATS_H
#define size 101

extern const char *dataset;
extern int current;
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

extern flat residence[size];


#endif