#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Struct Declaration
typedef struct Class Class;
//Struct Define
struct Class 
{
    char name[10];
    char schedule[6][40][10];

};

//Function Declaration
int Menu();
void DisplayNames(int n,int Group);
void DisplaySchedule(int n,int Group);
void InitializeClassesSchedule();
void SetTimeToClass(int n);

//Global variables
Class class[25];
Class classGroup[50];

int main()
{
    int i=0, j=0, k=0, l=0, N, exit=0;
    char className[25][50] = {"A1","A2","A5","B2","B3","B4","B5","C2","C3","C4","C5","D2","D4","D5","CC1","CC2","CC3","CC4","CC5","LCSE","LAI","ST","LEPE","LTSE","LR"};
    FILE *file;
    char path[200],fileName[20]="/schedule.TXT",ch;

    //Initialize all class by their name
    for(i=0; i<30; i++)
        strcpy(class[i].name,className[i]);

    //Open File (schedule.TXT)
    printf("Path : "); gets(path);
    strcat(path,fileName);
    
    file = fopen(path,"r");

    //Check if the file found
    if (file == NULL)
        printf("Error : file not found!\n");
    else
    {
        //Initialize all class Groups by their name (first line)
        i=j=0;
        while ((ch = fgetc(file)) != '\n')
        {
            if(ch == ' ')
            {
                classGroup[i].name[j] = '\0';
                i++; j=0;
            }
            else
            {
                classGroup[i].name[j] = ch;
                j++;
            }
        }
        N = i+1;
        //Set time schedule
        i=j=k=l=0;
        while ((ch = fgetc(file)) != EOF)
        {
            if(ch == '\n' && j==6)
            {
                i++; j=k=l=0;
            }
            else if(ch == '\n')
            {
                j++; k=l=0;
            }
            else if(ch == ' ')
            {
                classGroup[i].schedule[j][k][l] = '\0';
                l=0; k++;
            }
            else
            {
                classGroup[i].schedule[j][k][l] = ch;
                l++;
            }
        }
    }
    fclose(file);

    InitializeClassesSchedule();

    SetTimeToClass(N);

    while (!exit)
    {
        switch(Menu())
        {
            case 1: DisplaySchedule(N,0); break;
            case 2: break;
            case 0: exit = 1; printf("Chilli m3a rassk ^.^\n"); break;
        }
        getch();
        system("cls");//windows
        //system("clear");//linux
    }
    
    return 0;
}
//Display a Menu
int Menu()
{
    int choice, error;

    printf("Menu :\n\n");
    printf("1.Display Classes Schedule\n");
    printf("2.second option\n");
    printf("0.Exit\n");

    do
    { 
        printf("\nChoice : ");
        fflush(stdin);
        error = !scanf("%d",&choice);
        error = error || choice > 2 || choice < 0 ? 1 : 0;
        if(error)
            printf("choice incorrect!\ntry again\n");
    } while (error);
    
    return choice;
}

//display name (group = 0) show classes only (group != 0) show classes group
void DisplayNames(int n,int Group)
{
    int i,j,k;

    if(!Group)
        for(i=0; i<25; i++)
            printf("%s\n",class[i].name);
    else
        for(i=0; i<n; i++)
            printf("%s\n",classGroup[i].name);
}
void DisplaySchedule(int n,int Group)
{
    int i,j,k;

    if(!Group)
        for(i=0; i<25; i++)
        {
            printf("\n----------Schedule : %s---------------\n",class[i].name);
            for(j=0; j<6; j++)
            {
                for(k=0; k<40; k++)
                    printf("%s ",class[i].schedule[j][k]);
                printf("\n");
            }
        }
    else
        for(i=0; i<n; i++)
        {
            printf("\n----------Schedule : %s---------------\n",classGroup[i].name);
            for(j=0; j<6; j++)
            {
                for(k=0; k<40; k++)
                    printf("%s ",classGroup[i].schedule[j][k]);
                printf("\n");
            }
        }
}
void InitializeClassesSchedule()
{
    int i,j,k;

    for(i=0; i<25; i++)
        for(j=0; j<6; j++)
            for(k=0; k<40; k++)
                strcpy(class[i].schedule[j][k],"0");
}

void SetTimeToClass(int n)
{
    int i,j,k,l;

    for(i=0; i<n; i++)
        for(j=0; j<6; j++)
            for(k=0; k<40; k++)
                for(l=0; l<25; l++)
                    if(strcmp(classGroup[i].schedule[j][k],class[l].name) == 0)
                    {
                        strcpy(class[l].schedule[j][k],classGroup[i].name); break;
                    }
}