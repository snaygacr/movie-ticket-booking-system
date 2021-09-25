#include<stdio.h>
#include<stdlib.h>
#include "prototype.h"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_BROWN "\033[22;33m"
#define ANSI_COLOR_GRAY "\033[22;37m"
#define ANSI_COLOR_LRED "\033[01;31m"
#define ANSI_COLOR_LGREEN "\033[01;32m"
#define ANSI_COLOR_LBLUE "\033[01;34m"
#define ANSI_COLOR_LMAGENGTA "\033[01;35m"
#define ANSI_COLOR_LCYAN "\033[01;36m"

int main(){
    importMovieList();
    importTicketList();
    int op;
    do{
        op = printMainMenu();
        switch(op)
        {
            case 1:
                system("cls");
                user();
                break;
            case 2:
                system("cls");
                administrator();
                break;
            case 0:
                system("cls");
                exportMovieList();
                exportTicketList();
                printf(ANSI_COLOR_LCYAN"Thank you for choosing B315 cinemas!"ANSI_COLOR_RESET);
                enter();
                exit(0);
            default:
                printf(ANSI_COLOR_LCYAN"Invalid Choice\n"ANSI_COLOR_RESET);
                enter();
        }
    }while(1);
}

