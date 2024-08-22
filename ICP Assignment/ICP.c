#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

int password();
void addtask();
void viewtask();
void edittask();
void deletetask();
void editpassword();
struct task
{
    char time[6];
    char name[20];
    char progress[5];
    char deadline[15];
    char note[200];
} ;

int main()
{
    int ch;
    while(1)
    {
        printf("============================================================\n");
        printf("------------------------------------------------------------\n");
        printf("-------------- WELCOME TO SYCAMORE TASK MANAGER ------------\n");
        printf("-------------------------- MAIN MENU -----------------------\n");
        printf("------------------------------------------------------------\n");
        printf("============================================================\n");
        printf("\n\n\t(1)\tAdd Task");
        printf("\n\t(2)\tView Task");
        printf("\n\t(3)\tEdit Task");
        printf("\n\t(4)\tDelete Task");
        printf("\n\t(5)\tEdit Password");
        printf("\n\t(6)\tExit\t\t");
        printf("\n\n\tEnter Your Choice (1-6) :");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            addtask();
            break;
        case 2:
            viewtask();
            break;
        case 3:
            edittask();
            break;
        case 4:
            deletetask();
            break;
        case 5:
            editpassword();
            break;
        case 6:
            printf("\n\n\t\tThank You For Using Sycamore Task Manager ");
            getch();
            exit(0);
        default:
            printf("\nInvalid Option");
            printf("\nPress Any Key to Continue");
            getch();
            break;
        }
        system("cls");
    }
    return 0;
}

void addtask( )
{
    system("cls");
    FILE *fp ;
    char another = 'Y' ,time[10], filename[15];
    struct task e ;
    int choice;
    printf("============================================================\n");
    printf("------------------------------------------------------------\n");
    printf("-------------------- SYCAMORE TASK MANAGER -----------------\n");
    printf("------------------------- ADD TASK MENU---------------------\n");
    printf("------------------------------------------------------------\n");
    printf("============================================================\n");
    printf("\n\n\tEnter Today's Date:[dd-mm-yyyy]:");
    fflush(stdin);
    gets(filename);
    fp = fopen (filename, "ab+" ) ;
    if ( fp == NULL )
    {
        fp=fopen(filename,"wb+");
        if(fp==NULL)
        {
            printf("\nSystem Error");
            printf("\nPress Any Key to Continue");
            getch();
            return ;
        }
    }
    while ( another == 'Y'|| another=='y' )
    {
        choice=0;
        fflush(stdin);
        printf ( "\n\tEnter Start Time [hh:mm]:");
        scanf("%s",time);
        rewind(fp);
        while(fread(&e,sizeof(e),1,fp)==1)

        {
            if(strcmp(e.time,time)==0)
            {
                printf("\n\tTask Already Exists\n");
                choice=1;
            }
        }
        if(choice==0)
        {
            strcpy(e.time,time);
            printf("\tEnter Task Name:");
            fflush(stdin);
            gets(e.name);
            fflush(stdin);
            printf("\tEnter Task Progression:");
            gets(e.progress);
            fflush(stdin);
            printf("\tEnter Task Deadline:");
            gets(e.deadline);
            fflush(stdin);
            printf("\tEnter Task Note:");
            gets(e.note);
            fwrite ( &e, sizeof ( e ), 1, fp ) ;
            printf("\nTask Successfully Added...\n");
        }
        printf ( "\n\tAdd Another Task(Y/N): " ) ;
        fflush ( stdin ) ;
        another = getchar( ) ;
    }
    fclose ( fp ) ;
    printf("\n\n\tPress Any Key to Continue");
    getch();
}

void viewtask( )
{
    FILE *fpte ;
    system("cls");
    struct task view ;
    char name[8],choice,filename[14];
    int ch;
    printf("============================================================\n");
    printf("------------------------------------------------------------\n");
    printf("-------------------- SYCAMORE TASK MANAGER -----------------\n");
    printf("------------------------ VIEW TASK MENU---------------------\n");
    printf("------------------------------------------------------------\n");
    printf("============================================================\n");
    choice=password();
    if(choice!=0)
    {
        return ;
    }
    do
    {
        printf("\n\tEnter The Date of The Task Created:[dd-mm-yyyy]:");
        fflush(stdin);
        gets(filename);
        fpte = fopen ( filename, "rb" ) ;
        if ( fpte == NULL )
        {
            puts ( "\nData not Found\n" ) ;
            printf("Press Any Key to Continue");
            getch();
            return ;
        }
        system("cls");
        printf("\n\tHow Do You Want To View Your Task:\n");
        printf("\n\t1.All Task by Date");
        printf("\n\t2.By Task Name");
        printf("\n\t\tEnter Your Choice:");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            printf("\nThe Task For The Date %s Is:",filename);
            while ( fread ( &view, sizeof ( view ), 1, fpte ) == 1 )
            {
                printf("\n");
                printf("\nStart Time: %s",view.time);
                printf("\nTask Name: %s",view.name);
                printf("\nTask Progression: %s",view.progress);
                printf("\nTask Deadline: %s",view.deadline);
                printf("\nTask Note: %s",view.note);
                printf("\n");
            }
            break;
        case 2:
            fflush(stdin);
            printf("\nEnter Task Name:");
            gets(name);
            while ( fread ( &view, sizeof ( view ), 1, fpte ) == 1 )
            {
                if(strcmp(view.name,name)==0)
                {
                    printf("\nThe Task is:");
                    printf("\nStart Time: %s",view.time);
                    printf("\nTask Name: %s",view.name);
                    printf("\nTask Progression: %s",view.progress);
                    printf("\nTask Deadline: %s",view.deadline);
                    printf("\nTask Note: %s",view.note);
                }
            }
            break;
        default:
            printf("\nInvalid Option\n");
            break;
        }
        printf("\n\nDo You Want to Continue Viewing? (Y/N):");
        fflush(stdin);
        scanf("%c",&choice);
    }
    while(choice=='Y'||choice=='y');
    fclose ( fpte ) ;
    return ;
}

void edittask()
{
    system("cls");
    FILE *fpte ;
    struct task view ;
    char name[10],choice,filename[14];
    int num,count=0;
    printf("============================================================\n");
    printf("------------------------------------------------------------\n");
    printf("-------------------- SYCAMORE TASK MANAGER -----------------\n");
    printf("------------------------ EDIT TASK MENU---------------------\n");
    printf("------------------------------------------------------------\n");
    printf("============================================================\n");
    choice=password();
    if(choice!=0)
    {
        return ;
    }
    do
    {
        printf("\n\tEnter The Date of The Task That Want to be Edited:[dd-mm-yyyy] : ");
        fflush(stdin);
        gets(filename);
        printf("\n\tEnter Task Name : ");
        gets(name);
        fpte = fopen ( filename, "rb+" ) ;
        if ( fpte == NULL )
        {
            printf( "\nTask Does Not Exists:" ) ;
            printf("\nPress Any Key to Continue");
            getch();
            return;
        }
        while ( fread ( &view, sizeof ( view ), 1, fpte ) == 1 )
        {
            if(strcmp(view.name,name)==0)
            {
                printf("\nStart Time: %s",view.time);
                printf("\nTask Name: %s",view.name);
                printf("\nTask Progression: %s",view.progress);
                printf("\nTask Deadline: %s",view.deadline);
                printf("\nTask Note: %s",view.note);
                printf("\n\n\t\tWhat Details Would You Like to Edit : ");
                printf("\n(1)\tStart Time");
                printf("\n(2)\tTask Name");
                printf("\n(3)\tTask Progression");
                printf("\n(4)\tTask Deadline");
                printf("\n(5)\tTask Note");
                printf("\n(6)\tThe Whole Task");
                printf("\n(7)\tReturn to Main Menu");
                do
                {
                    printf("\n\tEnter Your Choice:");
                    fflush(stdin);
                    scanf("%d",&num);
                    fflush(stdin);
                    switch(num)
                    {
                    case 1:
                        printf("\nEnter New Data:");
                        printf("\nNew Start Time:[hh:mm]:");
                        gets(view.time);
                        break;
                    case 2:
                        printf("\nEnter New Data:");
                        printf("\nNew Task Name:");
                        gets(view.name);
                        break;
                    case 3:
                        printf("\nEnter New Data:");
                        printf("\nNew Task Progression:");
                        gets(view.progress);
                        break;
                    case 4:
                        printf("\nEnter New Data:");
                        printf("\nNew Task Deadline:");
                        gets(view.deadline);
                        break;
                    case 5:
                        printf("\nEnter New Data:");
                        printf("\nNew Task Note:");
                        gets(view.note);
                        break;
                    case 6:
                        printf("\nEnter New Data:");
                        printf("\nNew Start Time:[hh:mm]:");
                        gets(view.time);
                        printf("\nNew Task Name:");
                        gets(view.name);
                        printf("\nNew Task Progression:");
                        gets(view.progress);
                        printf("\nNew Task Deadline:");
                        gets(view.deadline);
                        printf("\nNew Task Note:");
                        gets(view.note);
                        break;
                    case 7:
                        printf("\nPress Any Key to Continue\n");
                        getch();
                        return ;
                        break;
                    default:
                        printf("\nInvalid Input, Try Again\n");
                        break;
                    }
                }
                while(num<1||num>8);
                    fseek(fpte,-sizeof(view),SEEK_CUR);
                    fwrite(&view,sizeof(view),1,fpte);
                    fseek(fpte,-sizeof(view),SEEK_CUR);
                    fread(&view,sizeof(view),1,fpte);
                    choice=5;
                    break;
            }
        }
        if(choice==5)
        {
            system("cls");
            printf("\n\t\tTask Details Updated\n");
            printf("--------------------\n");
            printf("The New Task Details:\n");
            printf("--------------------\n");
            printf("\nStart Time: %s",view.time);
            printf("\nTask Name: %s",view.name);
            printf("\nTask Progress: %s",view.progress);
            printf("\nTask Deadline: %s",view.deadline);
            printf("\nTask Note: %s",view.note);
            fclose(fpte);
            printf("\n\n\tDo You Want to Edit Another Task Details?(Y/N) : ");
            scanf("%c",&choice);
            count++;
        }
        else
        {
            printf("\nThe Task Does Not Exist::\n");
            printf("\nDo You Like to Try Again(Y/N)");
            scanf("%c",&choice);
        }
    }
    while(choice=='Y'||choice=='y');
    fclose ( fpte ) ;
    if(count==1)
        printf("\n%d File is Edited...\n",count);
    else if(count>1)
        printf("\n%d Files are Edited..\n",count);
    else
        printf("\nNo File Edited...\n");
    printf("\tPress Enter to Exit.");
    getch();
}

void deletetask( )
{
    system("cls");
    FILE *fp,*fptr ;
    struct task file ;
    char filename[15],another = 'Y' ,name[10];;
    int choice,check;
    printf("============================================================\n");
    printf("------------------------------------------------------------\n");
    printf("-------------------- SYCAMORE TASK MANAGER -----------------\n");
    printf("----------------------- DELETE TASK MENU--------------------\n");
    printf("------------------------------------------------------------\n");
    printf("============================================================\n");
    check = password();
    if(check==1)
    {
        return ;
    }
    while ( another == 'Y' )
    {
        printf("\n\n\tHow Would You Like To Delete The Task?");
        printf("\n\n\t(1)\tDelete The Whole Task\t\t");
        printf("\n\t(2)\tDelete Task By Name");
        do
        {
            printf("\n\t\tEnter Your Choice:");
            scanf("%d",&choice);
            switch(choice)
            {
            case 1:
                printf("\n\tEnter The Date of The Task Created:[dd-mm-yyyy]:");
                fflush(stdin);
                gets(filename);
                fp = fopen (filename, "wb" ) ;
                if ( fp == NULL )
                {
                    printf("\nThe File Does not Exists");
                    printf("\nPress Any Key to Continue");
                    getch();
                    return ;
                }
                fclose(fp);
                remove(filename);
                printf("\n\Successfully Deleted");
                break;
            case 2:
                printf("\n\tEnter The Date of The Task Created:[dd-mm-yyyy]:");
                fflush(stdin);
                gets(filename);
                fp = fopen (filename, "rb" ) ;
                if ( fp == NULL )
                {
                    printf("\nThe File Does not Exists");
                    printf("\nPress Any Key to Continue");
                    getch();
                    return ;
                }
                fptr=fopen("temp","wb");
                if(fptr==NULL)
                {
                    printf("\nSystem Error");
                    printf("\nPress Any Key to Continue");
                    getch();
                    return ;
                }
                printf("\n\tEnter The Task Name : ");
                fflush(stdin);
                gets(name);
                while(fread(&file,sizeof(file),1,fp)==1)
                {
                    if(strcmp(file.name,name)!=0)
                        fwrite(&file,sizeof(file),1,fptr);
                }
                fclose(fp);
                fclose(fptr);
                remove(filename);
                rename("temp",filename);
                printf("\nTask Deleted Successfully...");
                break;
            default:
                printf("\n\tInvalid Input");
                break;
            }
        }
        while(choice<1||choice>2);
        printf("\n\tDo You Want to Delete Another Task?(Y/N):");
        fflush(stdin);
        scanf("%c",&another);
    }
    printf("\n\n\tPress Any Key to Continue...");
    getch();
}

int password()
{
    char pass[15]= {0},check[15]= {0},ch;
    FILE *fpp;
    int i=0,j;
    printf("\n\t\tFor Security Purpose");
    printf("\n\t\tOnly 5 Tries Are Allowed");
    for(j=0; j<5; j++)
    {
        i=0;
        printf("\n\nEnter The Password:");
        pass[0]=getch();
        while(pass[i]!='\r')
        {
            if(pass[i]=='\b')
            {
                i--;
                printf("\b");
                printf(" ");
                printf("\b");
                pass[i]=getch();
            }
            else
            {
                printf("*");
                i++;
                pass[i]=getch();
            }
        }
        pass[i]='\0';
        fpp=fopen("SE","r");
        if (fpp==NULL)
        {
            printf("\n 404 Error [File not Found]\n");
            getch();
            return 1;
        }
        else
            i=0;
        while(1)
        {
            ch=fgetc(fpp);
            if(ch==EOF)
            {
                check[i]='\0';
                break;
            }
            check[i]=ch-5;
            i++;
        }
        if(strcmp(pass,check)==0)
        {
            printf("\n\n\tSuccessfully Login\n");
            return 0;
        }
        else
        {
            printf("\n\n\tLogin Unsuccessful\n\n\tAccess Denied\n");
        }
    }
    printf("\n\n\tYou Enter The Wrong Password\n\n\tPress Any Key to Continue");
    getch();
    return 1;
}

void editpassword()
{
    system("cls");
    printf("\n");
    char pass[15]= {0},confirm[15]= {0},ch;
    int choice,i,check;
    FILE *fp;
    fp=fopen("SE","rb");
    printf("============================================================\n");
    printf("------------------------------------------------------------\n");
    printf("-------------- WELCOME TO SYCAMORE TASK MANAGER ------------\n");
    printf("--------------------- EDIT PASSWORD MENU -------------------\n");
    printf("------------------------------------------------------------\n");
    printf("============================================================\n");
    if(fp==NULL)
    {
        fp=fopen("SE","wb");
        if(fp==NULL)
        {
            printf("System Error");
            getch();
            return ;
        }
        fclose(fp);

    }
    fclose(fp);
    check=password();
    if(check==1)
    {
        return ;
    }
    do
    {
        if(check==0)
        {
            i=0;
            choice=0;
            printf("\n\n\tEnter New Password:");
            fflush(stdin);
            pass[0]=getch();
            while(pass[i]!='\r')
            {
                if(pass[i]=='\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    pass[i]=getch();
                }
                else
                {
                    printf("*");
                    i++;
                    pass[i]=getch();
                }
            }
            pass[i]='\0';
            i=0;
            printf("\n\tConfirm:");
            confirm[0]=getch();
            while(confirm[i]!='\r')
            {
                if(confirm[i]=='\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    confirm[i]=getch();
                }
                else
                {
                    printf("*");
                    i++;
                    confirm[i]=getch();
                }
            }
            confirm[i]='\0';
            if(strcmp(pass,confirm)==0)
            {
                fp=fopen("SE","wb");
                if(fp==NULL)
                {
                    printf("\n\t\tSystem Error");
                    getch();
                    return ;
                }
                i=0;
                while(pass[i]!='\0')
                {
                    ch=pass[i];
                    putc(ch+5,fp);
                    i++;
                }
                putc(EOF,fp);
                fclose(fp);
            }
            else
            {
                printf("\n\tNew Password Do Not Match.");
                choice=1;
            }
        }
    }
    while(choice==1);
    printf("\n\n\tPassword Updated\n\n\tPress Any Key to Continue");
    getch();
}
