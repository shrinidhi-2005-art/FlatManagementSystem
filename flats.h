#ifndef FLATS_H
#define FLATS_H

//owners' struct
typedef struct {
    char owner[50];
    char o_info[50];
    int paid;
    int bal;
    int due;
    char date[50];
}owner;

//flats' struct
typedef struct {
    char ID[10];
    char type[10];
    int price;
    owner *owner;
}flat;

#endif