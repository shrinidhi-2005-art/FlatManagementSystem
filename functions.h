#ifndef FUNCTIONS_H
#define FUNCTION_H

//just declaring all the functions inside a single file instead of that main file

void read_file(void);
void write_file(void);
float down(int, float);
float principal(int, float);
float emi(float, int, int);
int display_emi(int);
int book(char*, char*, char*);
void display_booked(void);
void display_available(void);
int flatinfo(char*);
void pay(char*);
void flatinfoMenu(void);
void bookMenu(void);
void availableMenu(void);
void bookedMenu(void);
void paymentMenu(void);
void save(void);
void errors(int);
void backToMenu(void);
void menufn(void);
void login(void);

#endif

//ver 2.1.0 stable