#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#include "prototype.h"

#define capacity 100
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

char password[] = "marvel";

movie* m = NULL;
transaction* t = NULL;

void enter(){
    char e;
    printf("\n<Press Enter>");
    fflush(stdin);
    scanf("[^.]%c",&e);
    system("cls");
}

void addToMovieList(MOVIE show){
    movie* temp = (movie*)malloc(sizeof(movie));
    temp->next = NULL;
    temp->show = show;

    if(m==NULL)
    {
        m=temp;
        return;
    }

    movie* cur = m;
    while(cur->next!=NULL){
        cur=cur->next;
    }
    cur->next = temp;
}

void addToTicketList(TRANSACTION ticket){
    transaction* temp = (transaction*)malloc(sizeof(transaction));
    temp->next = NULL;
    temp->ticket = ticket;

    if(t==NULL){
        t=temp;
        return;
    }

    transaction* cur = t;
    while(cur->next!=NULL){
        cur=cur->next;
    }
    cur->next = temp;
}

void importMovieList()
{
    MOVIE block;
    FILE *fp;
    fp=fopen("movieList.dat","rb");
    if(fp!=NULL)
    {
        while((fread(&block,sizeof(MOVIE),1,fp))!=0)
        {
            addToMovieList(block);
        }
    }
    fclose(fp);
}

void importTicketList()
{
    TRANSACTION block;
    FILE *fp;
    fp=fopen("ticketList.dat","rb");
    if(fp!=NULL)
    {
        while((fread(&block,sizeof(TRANSACTION),1,fp))!=0)
        {
            addToTicketList(block);
        }
    }
    fclose(fp);

}

void exportMovieList()
{
    movie *cur=m;
    FILE *fp;
    fp=fopen("movieList.dat","wb");

    if(fp!=NULL)
    {
        while(cur!=NULL)
        {
            fwrite(&cur->show, sizeof(MOVIE),1,fp);
            cur=cur->next;
        }
    }
    fclose(fp);
}

void exportTicketList()
{
    transaction *cur2=t;

    FILE *fp2;
    fp2=fopen("ticketList.dat","wb");
    if(fp2!=NULL)
    {
        while(cur2!=NULL)
        {
            fwrite(&cur2->ticket, sizeof(TRANSACTION),1,fp2);
            cur2=cur2->next;
        }
    }
    fclose(fp2);
}

void printTransactions()
{
    transaction *cur=t;

    FILE *fp3;
    fp3=fopen("allTransactions.txt","w");
    if(fp3!=NULL)
    {
        fprintf(fp3,"================ALL TRANSACTIONS================\n");
        while(cur != NULL){
        fprintf(fp3,"\nName            : %s\n", cur->ticket.name);
        fprintf(fp3,"Mobile          : %lld\n", cur->ticket.mobile);
        fprintf(fp3,"Movie Code      : %d\n", cur->ticket.show.movieCode);
        fprintf(fp3,"Movie Name      : %s\n", cur->ticket.show.name);
        fprintf(fp3,"Number of Seats : %d\n", cur->ticket.nSeats);
        fprintf(fp3,"Cost per ticket : %.2f\n", cur->ticket.show.cost);
        fprintf(fp3,"Basic Cost      : %.2f\n", cur->ticket.cost);
        fprintf(fp3,"Food charges    : %.2f\n",cur->ticket.food);
        fprintf(fp3,"\nTotal (+7%% VAT) : %.2f\n",(cur->ticket.cost + cur->ticket.food)*1.07);
        fprintf(fp3,"=======================================\n");
        cur=cur->next;
        }
    }
    fclose(fp3);
}

int printMainMenu(){
    int choice;
    printf("Test");
    system("cls");
    printf(ANSI_COLOR_LRED"\n============WELCOME TO B315 Cinemas - SNU============\n"ANSI_COLOR_YELLOW);
    printf("1. User\n");
    printf("2. Administrator\n");
    printf("0. Exit\n");
    printf(ANSI_COLOR_LCYAN);
    printf("Choose an option:\n");
    printf(ANSI_COLOR_RESET);
    scanf("%d",&choice);
    return choice;
}

void viewMovies()
{
    printf(ANSI_COLOR_LCYAN);
    if(m==NULL)
    {
        printf("No record of movies\n");
        enter();
        return;
    }

    system("cls");
    printf(ANSI_COLOR_LRED);
    printf("=========================AVAILABLE MOVIES=========================\n\n");
    printf(ANSI_COLOR_LGREEN);
    char disString[]="Movie Name";
    printf("\nMovie Code\t%20s\tTicket Cost\tSeats Left\n",disString);

    movie* cur = m;

    printf(ANSI_COLOR_YELLOW);
    while(cur!=NULL){
        printf("%10d\t%20s\t%8.2f\t%10d\n",cur->show.movieCode,cur->show.name,cur->show.cost,(capacity-cur->show.totalBooked));
        cur=cur->next;
    }
    printf(ANSI_COLOR_RESET);
    enter();
    return;
}

int isUniqueCode(int code)
{
    movie* crt=m;
    while(crt!=NULL)
    {
        if(crt->show.movieCode==code)
            return 0;
        crt=crt->next;
    }
    return 1;
}


void addMovie()
{
    movie* new1 = (movie*)malloc(sizeof(movie));
    new1->next=NULL;
    new1->show.totalBooked=0;
    int code;
    printf(ANSI_COLOR_LCYAN"Enter the movie code:\n"ANSI_COLOR_RESET);
    scanf("%d",&code);
    while(!isUniqueCode(code))
    {
        printf(ANSI_COLOR_LMAGENGTA"Entered movie code already exists.\n"ANSI_COLOR_RESET);
        printf(ANSI_COLOR_LCYAN"Please enter another code:\n"ANSI_COLOR_RESET);
        scanf("%d",&code);
    }
    new1->show.movieCode=code;

    printf(ANSI_COLOR_LCYAN"Enter the movie name:\n"ANSI_COLOR_RESET);
    scanf("%s",new1->show.name);

    printf(ANSI_COLOR_LCYAN"Enter the cost of movie ticket:\n"ANSI_COLOR_RESET);
    scanf("%f",&new1->show.cost);

    movie* cur = m;

    printf(ANSI_COLOR_LCYAN);
    if(cur==NULL){
        m=new1;
        printf("Movie added successfully.\n");
        printf(ANSI_COLOR_RESET);
        enter();
        return;
    }

    while(cur->next!=NULL){
        cur=cur->next;
    }
    cur->next=new1;
    printf(ANSI_COLOR_RESET);
    enter();
    return;
}

void deleteMovie(){
    movie *cur = m,*prev;
    int movieCode;
    printf(ANSI_COLOR_LCYAN"Enter Movie Code for deletion:\n"ANSI_COLOR_RESET);
    scanf("%d",&movieCode);

    if(cur!=NULL && cur->show.movieCode == movieCode)
    {
        m = cur->next;
        free(cur);
        printf(ANSI_COLOR_LCYAN"Movie deletion successful\n"ANSI_COLOR_RESET);
        enter();
        return;
    }

    while(cur!=NULL && cur->show.movieCode != movieCode){
        prev=cur;
        cur=cur->next;
    }

    if(cur == NULL) {
        printf(ANSI_COLOR_LCYAN"Movie record does not exist\n"ANSI_COLOR_RESET);
        enter();
        return;
    };
    prev->next = cur -> next;
    free(cur);
    printf(ANSI_COLOR_LCYAN"Movie deletion successful\n"ANSI_COLOR_RESET);
    enter();
    return;
}

void modifyExistingMovie(){
int code, op, flag=0, i;
    printf(ANSI_COLOR_LCYAN"Enter movie code:\n"ANSI_COLOR_RESET);
    scanf("%d",&code);

    movie* cur = m;
    while(cur!=NULL)
    {
        if(cur->show.movieCode == code)
        {
            if(cur->show.totalBooked != 0){
                printf(ANSI_COLOR_LCYAN"Cannot modify details\nSome seats are already booked for this show\n"ANSI_COLOR_RESET);
                enter();
                return;
            }
            system("cls");
            printf(ANSI_COLOR_LRED);
            printf("\n================PRESENT DETAILS================\n");
            printf(ANSI_COLOR_YELLOW);
            printf("1. Movie Code   : %d\n", cur->show.movieCode);
            printf("2. Movie Name   : %s\n", cur->show.name);
            printf("3. Ticket cost  : %.2f\n", cur->show.cost);
            printf("0. To exit module\n");
            printf(ANSI_COLOR_LCYAN"Select an option to modify:\n"ANSI_COLOR_RESET);
            scanf("%d",&op);

            switch(op){
                case 1:
                printf(ANSI_COLOR_LCYAN"Enter modified movie code:\n"ANSI_COLOR_RESET);
                scanf("%d",&i);
                while(!isUniqueCode(i))
                {
                    printf(ANSI_COLOR_LMAGENGTA"Entered movie code already exists.\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_LCYAN"Please enter another code:\n"ANSI_COLOR_RESET);
                    scanf("%d",&i);
                }
                cur->show.movieCode=i;
                flag=1;
                break;

                case 2:
                printf(ANSI_COLOR_LCYAN"Enter modified movie name:\n"ANSI_COLOR_RESET);
                scanf("%s",cur->show.name);
                flag=1;
                break;

                case 3:
                printf(ANSI_COLOR_LCYAN"Enter modified movie ticket cost:\n"ANSI_COLOR_RESET);
                scanf("%f", &cur->show.cost);
                flag=1;
                break;

                case 0:
                    system("cls");
                    return;

                default:
                    printf(ANSI_COLOR_LCYAN"Invalid choice\n"ANSI_COLOR_RESET);
                    enter();
                    return;

            }
            if(flag == 1)
                break;
        }
        cur=cur->next;
    }
    if(flag==1){

        printf(ANSI_COLOR_LCYAN"\nMovie details modified successfully\n"ANSI_COLOR_RESET);
        enter();
        return;
    }
    printf(ANSI_COLOR_LCYAN"Movie Record not found.\n"ANSI_COLOR_RESET);
    enter();
    return;
}

void viewTransactions(){
    printf(ANSI_COLOR_LCYAN);
    if(t == NULL){
        printf("No record of Transactions found\n");
        enter();
        return;
    }

    transaction* cur = t;
    printf(ANSI_COLOR_LRED);
    printf("\n================ALL TRANSACTIONS================\n");

    while(cur != NULL){
        printf(ANSI_COLOR_YELLOW);
        printf("\nName            : %s\n", cur->ticket.name);
        printf("Mobile          : %lld\n", cur->ticket.mobile);
        printf("Movie Code      : %d\n", cur->ticket.show.movieCode);
        printf("Movie Name      : %s\n", cur->ticket.show.name);
        printf("Number of Seats : %d\n", cur->ticket.nSeats);
        printf("Cost per ticket : %.2f\n", cur->ticket.show.cost);
        printf("Basic Cost      : %.2f\n", cur->ticket.cost);
        printf("Food charges    : %.2f\n",cur->ticket.food);
        printf("\nTotal (+7%% VAT) : %.2f\n",(cur->ticket.cost + cur->ticket.food)*1.07);
        printf(ANSI_COLOR_LGREEN);
        printf("=======================================\n");
        cur=cur->next;
    }
    printf(ANSI_COLOR_RESET);
    enter();
}

int food(){
    int op;
    int number;
    system("cls");
    printf(ANSI_COLOR_LRED);
    printf("\nSpecial bigMac Combo for only Rs. 100/- per combo\n");
    printf("Would you like to add the combos to your ticket?\n");
    printf(ANSI_COLOR_YELLOW);
    printf("1. Yes\n2. No\n");
    printf(ANSI_COLOR_LCYAN);
    printf("Enter your choice(1/2):\n"ANSI_COLOR_RESET);
    scanf("%d",&op);
        switch(op){
            case 1:

                    printf(ANSI_COLOR_LGREEN"How many combos would you like to add?\n"ANSI_COLOR_RESET);
                    scanf("%d",&number);
                    printf(ANSI_COLOR_LGREEN"Thanks for availing the service\n"ANSI_COLOR_RESET);
                    break;
            case 2:
                    printf(ANSI_COLOR_LCYAN"That's okay! :)\n"ANSI_COLOR_RESET);
                    number = 0;
                    break;
            default:
                    printf(ANSI_COLOR_LCYAN"Invalid choice\n"ANSI_COLOR_RESET);
                    enter();
                    number = food();
        }
        printf(ANSI_COLOR_RESET);
        enter();
    return number;
}

void bookTickets(){
    transaction* new1 = (transaction*)malloc(sizeof(transaction));
    new1->next = NULL;

    printf(ANSI_COLOR_LCYAN"Enter movie code:\n"ANSI_COLOR_RESET);
    scanf("%d", &new1->ticket.show.movieCode);

    movie* curm = m;
    while(curm!=NULL){
        if(curm->show.movieCode == new1->ticket.show.movieCode)
            break;
        curm=curm->next;
    }

    if(curm == NULL)
    {
        printf(ANSI_COLOR_LCYAN"Invalid movie code\n"ANSI_COLOR_RESET);
        enter();
        return;
    }

    printf(ANSI_COLOR_LCYAN"Enter number of seats to be booked:\n"ANSI_COLOR_RESET);
    scanf("%d",&new1->ticket.nSeats);
    if(new1->ticket.nSeats > (capacity - curm ->show.totalBooked)){
        printf(ANSI_COLOR_LCYAN"Cannot book tickets\nSeat capacity exceeded\n"ANSI_COLOR_RESET);
        enter();
        return;
    }
    curm->show.totalBooked += new1->ticket.nSeats;

    printf(ANSI_COLOR_LCYAN"Enter your name:\n"ANSI_COLOR_RESET);
    scanf("%s", new1->ticket.name);
    printf(ANSI_COLOR_LCYAN"Enter mobile number:\n"ANSI_COLOR_RESET);
    scanf("%lld", &new1->ticket.mobile);

    new1->ticket.show = curm->show;
    new1->ticket.cost = curm->show.cost * new1->ticket.nSeats;

    transaction* cur = t;

    if(cur == NULL){
        t = new1;
        cur=t;
    }
    else{
            while(cur->next!=NULL){
            cur = cur->next;
        }
    cur->next = new1;
    cur=cur->next;
    }

    cur->ticket.food = food()*100.00;

    system("cls");
    printf(ANSI_COLOR_LRED);
    printf("Here's your ticket\n");
    printf(ANSI_COLOR_YELLOW);
    printf("\nName            : %s\n", cur->ticket.name);
    printf("Mobile          : %lld\n", cur->ticket.mobile);
    printf("Movie Code      : %d\n", cur->ticket.show.movieCode);
    printf("Movie Name      : %s\n", cur->ticket.show.name);
    printf("Number of Seats : %d\n", cur->ticket.nSeats);
    printf("Cost per ticket : %.2f\n", cur->ticket.show.cost);
    printf("Basic Cost      : %.2f\n", cur->ticket.cost);
    printf("Food charges    : %.2f\n",cur->ticket.food);
    printf("\nTotal (+7%% VAT) : %.2f\n",(cur->ticket.cost + cur->ticket.food)*1.07);
    printf(ANSI_COLOR_LRED);
    printf("Thanks for choosing B315 cinemas\nEnjoy your movie\n");
    printf(ANSI_COLOR_RESET);
    enter();
    return;
}

void findTicket(){
    long long int mobile;
    printf(ANSI_COLOR_LCYAN"\nEnter mobile number:\n"ANSI_COLOR_RESET);
    fflush(stdin);
    scanf("%lld", &mobile);

    if(t == NULL){
        printf(ANSI_COLOR_LCYAN"Ticket not found\n"ANSI_COLOR_RESET);
        enter();
        return;
    }

    transaction* cur = t;

    while(cur != NULL){
        if(cur->ticket.mobile == mobile)
        {
            printf(ANSI_COLOR_LRED);
            printf("Here's your ticket\n");
            printf(ANSI_COLOR_YELLOW);
            printf("\nName            : %s\n", cur->ticket.name);
            printf("Mobile          : %lld\n", cur->ticket.mobile);
            printf("Movie Code      : %d\n", cur->ticket.show.movieCode);
            printf("Movie Name      : %s\n", cur->ticket.show.name);
            printf("Number of Seats : %d\n", cur->ticket.nSeats);
            printf("Cost per ticket : %.2f\n", cur->ticket.show.cost);
            printf("Basic Cost      : %.2f\n", cur->ticket.cost);
            printf("Food charges    : %.2f\n",cur->ticket.food);
            printf("\nTotal (+7%% VAT) : %.2f\n",(cur->ticket.cost + cur->ticket.food)*1.07);
            printf(ANSI_COLOR_RESET);
            enter();
            return;
        }
        cur=cur->next;
    }

    printf(ANSI_COLOR_LCYAN"Ticket not found\n"ANSI_COLOR_RESET);
    enter();
    return;
}

int userMenu(){
    int choice;
    system("cls");
    printf(ANSI_COLOR_LRED"\n================USER MENU================\n"ANSI_COLOR_YELLOW);
    printf("\n1. View movies\n");
    printf("2. Book Tickets\n");
    printf("3. Find your tickets\n");
    printf("0. Quit user session\n");
    printf(ANSI_COLOR_LCYAN);
    printf("\nEnter your choice: ");
    printf(ANSI_COLOR_RESET);
    scanf("%d", &choice);
    return choice;
}

void user(){
    int op;
    do{
        op = userMenu();
        switch(op){
            case 1:
                system("cls");
                viewMovies();
                break;
            case 2:
                system("cls");
                bookTickets();
                break;
            case 3:
                system("cls");
                findTicket();
                break;
            case 0:
                system("cls");
                return;
            default:
                printf("Invalid Choice\n");
                enter();
        }
    }while(1);
}

int administratorMenu(){
    int choice;
    printf(ANSI_COLOR_LRED);
    printf("================ADMINISTRATOR MENU================\n");
    printf(ANSI_COLOR_YELLOW);
    printf("\n1. View movies\n");
    printf("2. Add movie\n");
    printf("3. Delete movie\n");
    printf("4. Modify Existing movie\n");
    printf("5. View all transactions\n");
    printf("6. Create a printable file of all transactions\n");
    printf("0. Logout of session\n");
    printf(ANSI_COLOR_LCYAN);
    printf("\nEnter your choice: ");
    printf(ANSI_COLOR_RESET);
    scanf("%d",&choice);
    return choice;
}

void administrator(){
    int n = strlen(password);
    char pass[n],ch;
    int op=0;

    printf(ANSI_COLOR_LCYAN"\nEnter the password:\n"ANSI_COLOR_RESET);
    while(1)
    {
        if(op<0)
            op=0;
        ch=getch();
        if(ch==13)
            break;
        if(ch==8)
        {
            putch('\b');
            putch('\0');
            putch('\b');
            op--;
            continue;
        }
        pass[op++]=ch;
        putch('*');
    }
    pass[op]='\0';
    if(strcmp(pass,password)!=0)
    {
        printf(ANSI_COLOR_LCYAN"\nWrong Password. Try Again."ANSI_COLOR_RESET);
        enter();
        administrator();
    }
    else{
        system("cls");
        printf(ANSI_COLOR_LCYAN"Password Accepted\n"ANSI_COLOR_RESET);

        do{
            op=administratorMenu();
            switch(op){
                case 1:
                    system("cls");
                    viewMovies();
                    break;
                case 2:
                    system("cls");
                    addMovie();
                    break;
                case 3:
                    system("cls");
                    deleteMovie();
                    break;
                case 4:
                    system("cls");
                    modifyExistingMovie();
                    break;
                case 5:
                    system("cls");
                    viewTransactions();
                    break;
                case 6:
                    system("cls");
                    printTransactions();
                    printf(ANSI_COLOR_YELLOW"Printable transactions file created\n"ANSI_COLOR_RESET);
                    enter();
                    break;
                case 0:
                    system("cls");
                    return;
                default:
                    printf("Invalid Choice\n");
                    enter();
            }
        }while(1);
    }
}

