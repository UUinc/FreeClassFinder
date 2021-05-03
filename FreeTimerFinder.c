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
void IsItFree();
int HourConverter(char hour[5]);
int FreeClassroom(int classID, int day, int hour, int time);
void FreeClassrooms();

//Global variables
Class class[25];
Class classGroup[50];

int main()
{
    int i=0, j=0, k=0, l=0, N, exit=0;
    char className[25][50] = {"A1","A2","B1","B2","B3","B4","B5","C1","C2","C3","C4","C5","D2","D4","CC1","CC2","CC3","CC4","CC5","LCSE","LAI","LRDM","CMDS","LTOPO","LR"};
    FILE *file;
    char path[200],fileName[20]="/schedule.TXT",ch;

    //Initialize all class by their name
    for(i=0; i<25; i++)
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
            case 2: IsItFree(); break;
            case 3: FreeClassrooms(); break;
            case 0: exit = 1; printf("\nChilli m3a rassk ^.^\n"); break;
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
    printf("2.Is the Class Free\n");
    printf("3.Free Classrooms\n");
    printf("0.Exit\n");

    do
    { 
        printf("\nChoice : ");
        fflush(stdin);
        error = !scanf("%d",&choice);
        error = error || choice > 3 || choice < 0 ? 1 : 0;
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

void IsItFree()
{
    int i,j;
    int day, hour, time, error;
    char _class[10], h[5];

    printf("\nClass ex : (A1, LCSE ...)\n\n");
    error = 1;
    do{
        printf("Class : "); scanf("%s",_class);
        for(i=0; i<25; i++)
            if(strcmp(class[i].name,_class) == 0)
            {
                error = 0; break;
            }
        if(error)
            printf("Class Not found! try again\n");
    }while(error);

    printf("1.Monday\n2.Tuesday\n3.Wednesday\n4.Thursday\n5.Friday\n6.Saturday\n\n");
    do{printf("Day : "); error = scanf("%d",&day);}while(!error || day<1 || day>6); day--;

    printf("\nFrom 8:30 To 18:15 (15 min)\n\n");
    do{printf("Hour : "); scanf("%s",h); hour = error = HourConverter(h);}while(error<0 || error>39);

    printf("\n\ntime frame (1 = 15 min)\nmin : 1 (15 min)\nmax : 24 (6 hours)\n\n");
    do{printf("time : "); error = scanf("%d",&time);}while(!error || time<1 || time>24 || hour+time>39);

    int r = FreeClassroom(i,day,hour,time);
    if(r)
    {
        printf("\n----Classroom isn't Available!-----\n");
        printf("\n-Class : %s\n",class[i].schedule[day][r]);
    }
    else
        printf("\n----Classroom is Available!----\n");
}

int HourConverter(char hour[5])
{
    int h, min, r;

    if(hour[1]==':')
    {
        h = hour[0]-'0';
        min = (hour[2]-'0')*10 + (hour[3]-'0');
    }
    else if(hour[2]==':')
    {
        h = (hour[0]-'0')*10 + (hour[1]-'0');
        min = (hour[3]-'0')*10 + (hour[4]-'0');
    }

    r = ((h*60+min) - 510) / 15;

    return r;
}

int FreeClassroom(int classID, int day, int hour, int time)
{
    for(int j=hour; j<hour+time; j++)
        if(strcmp(class[classID].schedule[day][j],"0") != 0)
            return j;
    return 0;
}

void FreeClassrooms()
{
    int i,j;
    int day, hour, time, error;
    char h[5];

    printf("1.Monday\n2.Tuesday\n3.Wednesday\n4.Thursday\n5.Friday\n6.Saturday\n\n");
    do{printf("Day : "); error = scanf("%d",&day);}while(!error || day<1 || day>6); day--;

    printf("\nFrom 8:30 To 18:15 (15 min)\n\n");
    do{printf("Hour : "); scanf("%s",h); hour = error = HourConverter(h);}while(error<0 || error>39);

    printf("\n\ntime frame (1 = 15 min)\nmin : 1 (15 min)\nmax : 24 (6 hours)\n\n");
    do{printf("time : "); error = scanf("%d",&time);}while(!error || time<1 || time>24 || hour+time>39);

    printf("-----Availables :-----\n");

    for(i=0; i<25; i++)
    {
        if(!FreeClassroom(i,day,hour,time))
            printf("  -%s\n",class[i].name);
    }
}