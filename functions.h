#ifndef FUNCTIONS_H
#define FUNCTION_H

void read_file(void);
void write_file(void);
int down(int, int);
int principal(int, int);
int emi(int, int, int);
int display_emi(int);
void book(char*, char*, char*, int);
void display_booked(void);
void display_available(void);
void flatinfo(char*);
void pay(char*);

#endif