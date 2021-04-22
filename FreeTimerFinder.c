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

//Global variables
Class class[30];
Class classGroup[17];

int main()
{
    int i=0, j=0, k=0, l=0;
    char className[30][50] = {"A1","A2","A3","A4","A5","B1","B2","B3","B4","B5","C1","C2","C3","C4","C5","D1","D2","D3","D4","D5","CC1","CC2","CC3","CC4","CC5","LSCE","LTOPO","LRDM","LR","CMDS"};
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

    //Display All Names
    for(i=0; i<30; i++)
        printf("%s\n",class[i].name);
    for(i=0; i<17; i++)
        printf("%s\n",classGroup[i].name);
    //Display All class group schedules
    for(i=0; i<17; i++)
    {
        printf("\n----------Schedule : %s---------------\n",classGroup[i].name);
        for(j=0; j<6; j++)
        {
            for(k=0; k<40; k++)
                printf("%s ",classGroup[i].schedule[j][k]);
            printf("\n");
        }
    }
    getch();
    return 0;
}