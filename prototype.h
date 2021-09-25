#include<stdio.h>

typedef struct MOVIE{
    int movieCode;
    char name[20];
    float cost;
    int totalBooked;
}MOVIE;

typedef struct movie{
    MOVIE show;
    struct movie* next;
}movie;

typedef struct TRANSACTION{
    char name[30];
    long long int mobile;
    MOVIE show;
    int nSeats;
    float cost;
    float food;
}TRANSACTION;

typedef struct transaction{
    TRANSACTION ticket;
    struct transaction* next;
}transaction;


void enter();

void importMovieList();
void importTicketList();
void exportMovieList();
void exportTicketList();
void addToMovieList();
void addToTicketList();

void addMovie();
void viewMovies();
void modifyExistingMovie();
void deleteMovie();

void bookTickets();
void findTicket();

void printTransactions();
void viewTransactions();

int printMainMenu();
int userMenu();
void user();
int administratorMenu();
void administrator();

int isUniqueCode(int);
int food();
