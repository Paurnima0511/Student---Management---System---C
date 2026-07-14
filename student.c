#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Student
{
    int roll;
    char name[50];
    float marks;
};
void addStudent();
void displayStudent();
void searchStudent();
void updateStudent();
void deleteStudent();
int main()
{
    int choice;
    while(1)
    {
        printf("\n STUDENT MANAGEMENT SYSTEM");
        printf("\n1. Add Student");
        printf("\n2. Display Student");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");
        printf("\n Enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                   addStudent();
                
            
                break;
            case 2:
                   displayStudent();
                break;
            case 3:
                   searchStudent();
                break;
            case 4:
                   updateStudent();
                break;
            case 5:
                   deleteStudent();
                break;
            case 6:
                   exit(0);
            default:
                  printf("Invalid Choice");

        }
    }

    return 0;
}
void addStudent()
{
    FILE *fp;
    struct Student s;

    fp=fopen("students.txt","a+b");

    printf("\n Enter Roll Number:");
    scanf("%d",&s.roll);

    printf("Enter Name:");
    scanf("  %[^\n]",s.name);

    printf("Enter Marks:");
    scanf("%f",&s.marks);

    fwrite(&s,sizeof(s),1,fp);
    fclose(fp);

    printf("\n Student Added Successfully!\n");
}
void displayStudent()
{
    FILE *fp;
    struct Student s;
    fp=fopen("students.txt","rb");
    if(fp==NULL)
    {
         printf("\n No record Found!\n");
         return;

    }
    printf("\n Student Records\n");
    
    while(fread(&s,sizeof(s),1,fp))
    {
        printf("\n Roll number : %d",s.roll);
        
        printf("\n Name : %s",s.name);

        printf("\n marks : %.2f",s.marks);

        printf("\n- ------------------------ ");
    }
    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct Student s;
    int roll,found=0;

    fp=fopen("students.txt","rb");

    if(fp==NULL)
    {
        printf("\n No Record Found!\n");
        return;
    }
    printf("\n Enter Roll Number to search:");
          scanf("%d",&roll);

          while(fread(&s,sizeof(s),1,fp))
          {
            if(s.roll==roll)
            {
                printf("\n Student Found\n");
                printf("Roll Number : %d",s.roll);
                printf("Name : %s\n",s.name);
                printf("Marks : %.2f\n",s.marks);

                found=1;
                break;
            
            }
          }
          if(found==0)
          {
            printf("\n Student Not Found!\n");

          }
          fclose(fp);

}
void updateStudent()
{
    FILE *fp;
    struct Student s;
    int roll, found=0;

    fp=fopen("students.txt","rb+");

    if(fp==NULL)
    {
        printf("File not found!");
        return;
    }
    printf("Enter Roll No to Update:");
    scanf("%d",&roll);

    while(fread(&s,sizeof(s),1,fp))
    {
        if(s.roll==roll)
        {
            printf("Enter New Name");
            scanf("%s",s.name);
            printf("Enter New Marks");
            scanf("%f",&s.marks);
            fseek(fp,-sizeof(s),SEEK_CUR);
            fwrite(&s,sizeof(s),1,fp);

              printf("Record Updated Successfully!\n");
              found=1;
              break;
            
        }
    }
    if(found==0)
    {
        printf("Record Not Found!\n");
    }
    fclose(fp);
}
void deleteStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int roll ,found=0;

    fp=fopen("students.txt","rb");
    temp=fopen("temp.txt","wb");

    if(fp==NULL)
    {
        printf("File not found!\n");
        return;
    }
    printf("Enter Roll No to Delete:");
    scanf("%d",&roll);

    while(fread(&s,sizeof(s),1,fp))
    {
        if(s.roll==roll)
        {
            found=1;
        }
        else
        {
            fwrite(&s,sizeof(s),1,temp);
        }
    }
    
    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt","students.text");

    if(found)
       printf("Record Deleted Successfully!\n");
    else
       printf("Record Not Found!\n");
}