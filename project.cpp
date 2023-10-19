//4/9/2023
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 100
#define filename "STUDENT.txt"

struct STUDENT
{
    char name[50];
    int age;
    float mark;
    char student_id[10];
};

void menu();
void readFile(FILE *f,STUDENT a[],int &count);
void drawBoard(STUDENT a[],int count);
void listStudent(STUDENT a[],int count);
void addStudent(STUDENT &a,int count,STUDENT list[]);
void removeStudent(STUDENT a[],int &count);
void remove(STUDENT a[],int vitri,int count);
void changeInfomationStudent(STUDENT a[],int count);
void find(STUDENT a[],int count);
int findSubString(STUDENT a,char b[]);
void sortAscending(STUDENT a[],int l, int r);
void sortDescending(STUDENT a[],int l, int r);
void markStatistical(STUDENT a[],int count);
void saveFile(STUDENT a[],FILE *f,int count);
float markMax(STUDENT a[],int count);
int main()
{
    int choose;
    FILE *f;
    struct STUDENT list[max];
    int count=0;        //Number of students in the list
    readFile(f,list,count);
    do{
        menu();
        printf("\nEnter your choice:"); scanf("%d",&choose);
        switch(choose){
            case 1:{
                listStudent(list,count); // Print all student in list
                break;
            }
            case 2:{
            	addStudent(list[count],count,list); // add new student
            	count++;
				break;
			}
            case 3:{
                removeStudent(list,count); //remove 1 Student
                break;
            }
            case 4:{
                changeInfomationStudent(list,count); //Change infomation of Student
                break;
            }
            case 5:{
                find(list,count); //Search Student in List
                break;
            }
            case 6:{
                int chose;
                do{
                    printf("\n\t(?)1.Mark Ascending:");
                    printf("\n\t(?)2.Mark Descending:");
                    printf("\n\t(?)3.Complete!!");
                    printf("\n\t(?)Enter selection: ");
                    scanf("%d",&chose);
                    switch(chose){
                        case 1:{
                            sortAscending(list,0,count-1);
                            break;
                        }
                        case 2:{
                            sortDescending(list,0,count-1);
                            break;
                        }
                    }
                }while(chose!=3);
                break;
            }
            case 7:{
                markStatistical(list,count);
                break;
            }
            case 8:{
                saveFile(list,f,count);
                break;
            }
        }
    }while(choose!=9);
}

//Menu list of functions
void menu(){
        printf("\n1.Print List Student");
        printf("\n2.Add Student");
        printf("\n3.Remove Student");
        printf("\n4.Change Infomation of Student");
        printf("\n5.Search Student in List");
        printf("\n6.Sort");
        printf("\n7.Statistical");
        printf("\n8.Back up File");
        printf("\n9.Exit");
}

//Read data in file 
void readFile(FILE *f,STUDENT a[],int &count){
    f=fopen(filename,"r");
    char *token;
    int i=0;
    char line[100];
    while(fgets(line,100,f)!=NULL)
    {
        token=strtok(line,";");
        strcpy(a[i].student_id,token);
        
        token=strtok(NULL,";");
        strcpy(a[i].name,token);
        
        token=strtok(NULL,";");
        a[i].age=atoi(token);

        token=strtok(NULL,";");
        a[i].mark=atof(token);

        i++;
    }
    count=i;
    fclose(f);
}

void drawBoard(STUDENT a[],int count){
    for(int i=0;i<65;i++)
	{
		if(i<11) printf(" ");
		else{
			if(i==11 || i==20 || i==48 || i==56 || i== 64) printf("+");
			else printf("-");
		}
		
	}
    printf("\n%12s%-3s%6s %-15s%12s %-6s%s%5s%3s\n","|","ID","|","Name","|","Age","|","Mark","|");
    for(int i=0;i<65;i++)
	{
		if(i<11) printf(" ");
		else{
			if(i==11 || i==20 || i==48 || i==56 || i== 64) printf("+");
			else printf("-");
		}
		
	}

    for(int i=0;i<count;i++)
	{
		printf("\n%12s%8s%1s %-20s%7s %-6d%s%5.2f%3s","|",a[i].student_id,"|",a[i].name,"|",a[i].age,"|",a[i].mark,"|");
	}
	printf("\n");
    for(int i=0;i<65;i++)
	{
		if(i<11) printf(" ");
		else{
			if(i==11 || i==20 || i==48 || i==56 || i== 64) printf("+");
			else printf("-");
		}
		
	}
    printf("\n");
}

//Print all Student
void listStudent(STUDENT a[],int count){
    printf("\nList Student:\n");
	drawBoard(a,count);
}

//Add 1 Student to the list
void addStudent(STUDENT &a,int count,STUDENT list[]){

    printf("\nAdd new student:");

    //Add Student ID
    printf("\n\t(!)Enter Student ID:");
    fflush(stdin);
    gets(a.student_id);
    fflush(stdin);
    //Check Student ID correct in List
    for(int i=0;i<count;i++){
        while((findSubString(list[i],a.student_id) == 1 || strlen(a.student_id) != 8) ){
            printf("\n\t(!)Student ID already exists, Please re-enter:");
            fflush(stdin);
            gets(a.student_id);
        }
    }

    //Add Student Name
    printf("\n\t(!)Enter name of Student:");
    fflush(stdin);
    gets(a.name);

    //Check Student Name correct
    char str[strlen(a.name)];
    strcpy(str,a.name);
    for(int i=0;i<strlen(a.name);i++){
        while(!((str[i] >= 65 && str[i] <=90) || (str[i]>=97 && str[i]<=122) ||(str[i] ==' '))){
            printf("\n\t(!)Name is not valid, Please re-enter:");
            fflush(stdin);
            gets(a.name);
            strcpy(str,a.name);
        }
    }

    //Add Student Age and Mark
    printf("\n\t(!)Enter age of Studet:");
    scanf("%d",&a.age);
    printf("\n\t(!)Enter mark of Student:");
    scanf("%f",&a.mark);
    printf("\n\t(-)Add successful\n");
}

//Remove 1 Student to the list
void removeStudent(STUDENT a[],int &count){
    char b[max];
    int i = 1;
    	do{
    		printf("\n\t(!)Enter Student ID to be deleted:"); 
    		fflush(stdin);
    		gets(b);
    		for(int j = 0; j<count; j++){
    			if(strcmp(a[j].student_id,b)==0){
            	remove(a,j,count);
            	count--;
            	i = 0;
            	printf("\n\t(-)Deleted!!\n");
            	break;
        		}
				if(j==count) printf("\n\t(!)Student ID false, Please Enter Again");		
        		
			}
		}while(i!=0);
    
    
}

void remove(STUDENT a[],int vitri,int count){
    for(int i=vitri;i<count;i++){
        a[i]=a[i+1];
    }
}

/**
 * Change Infomation Student
 * Have 3 function
 * 1.Change name
 * 2.Change age
 * 3.Change mark
*/
void changeInfomationStudent(STUDENT a[],int count){
	int tmp;
    int chose;
    char b[10];
    int o = 1;
    //Check Student ID correct in List
    do{
    	printf("\n\t(!) Enter Student ID to change infomation of student: ");
    	fflush(stdin);
    	gets(b);
    	for(int i=0;i<count;i++){
    		if(strcmp(a[i].student_id,b)==0){
    			o = 0;
    			tmp = i;
    			break;
		}
	}
	}while(o!=0);
	
    do{
        printf("\n\t(!)Enter selection change infomation of student:");
        printf("\n\t(?)1.Change name of Student");
        printf("\n\t(?)2.Change age of Student");
        printf("\n\t(?)3.Change mark of Studet");
        printf("\n\t(?)4.Exit!!!");
        printf("\n\t(?)Enter selection:");
        scanf("%d",&chose);
        switch(chose){
            case 1:{
            		
            		printf("\n\tName:");
                    fflush(stdin);
                    gets(a[tmp].name);
                    char str[strlen(a[tmp].name)];
    				strcpy(str,a[tmp].name);
    				for(int i=0;i<strlen(a[tmp].name);i++){
        				while(!((str[i] >= 65 && str[i] <=90) || (str[i]>=97 && str[i]<=122) ||(str[i] ==' '))){
            				printf("\n\t(!)Name is not valid, Please re-enter:");
            				fflush(stdin);
            				gets(a[tmp].name);
            				strcpy(str,a[tmp].name);
        				}	
    				}
                	break;
            	}
            case 2:{
            		do{
            			printf("\n\tAge:");
                    	scanf("%d",&a[tmp].age);
						if(a[tmp].age<=0){
							printf("Please Enter age again");
						}	
					}while(a[tmp].age<=0);
                    break;
                }
                
            case 3:{
                	do{
            			printf("\n\tMark:");
                    	scanf("%f",&a[tmp].mark);
						if(a[tmp].mark<0 || a[tmp].mark>10){
							printf("\n\tPlease Enter mark again");
						}	
					}while(a[tmp].mark<0 || a[tmp].mark>10);
                    break;
            	}
        }
    }while(chose!=4);
}

//Find Student with Student ID
void find(STUDENT a[],int count){
    char b[max];
    printf("\n\t(!)Enter Student ID to searching: ");
    fflush(stdin);
    gets(b);
    STUDENT temp[max];
    int sizeTemp=0;
    for(int i=0;i<count;i++)
    {
       if(findSubString(a[i],b)==1) {
            temp[sizeTemp]=a[i];
            sizeTemp++;
        }
    }
    drawBoard(temp,sizeTemp); 
}

//Find subString in String
int findSubString(STUDENT a,char b[]){
    char *str;
    str=strstr(a.student_id,b);
    if(str) return 1;
    else return -1;
}



void sortAscending(STUDENT a[],int l, int r){
	float p = a[(l+r)/2].mark;
	int i = l, j = r;
	while (i < j){
		while (a[i].mark < p){
			i++;
		}
		while (a[j].mark > p){
			j--;
		}
		if (i <= j){
			float temp = a[i].mark;
			a[i].mark = a[j].mark;
			a[j].mark = temp;
			i++;
			j--;
		}
	}
	if (i < r){
		sortAscending(a, i, r);
	}
	if (l < j){
		sortAscending(a, l, j);
	}
}

void sortDescending(STUDENT a[],int l, int r){
	float p = a[(l+r)/2].mark;
	int i = l, j = r;
	while (i < j){
		while (a[i].mark > p){
			i++;
		}
		while (a[j].mark < p){
			j--;
		}
		if (i <= j){
			float temp = a[i].mark;
			a[i].mark = a[j].mark;
			a[j].mark = temp;
			i++;
			j--;
		}
	}
	if (i < r){
		sortDescending(a, i, r);
	}
	if (l < j){
		sortDescending(a, l, j);
	}
}


//Statistics on the number of students by each type
void markStatistical(STUDENT a[],int count){
    int countgioi=0;
    int countkha=0;
    int counttb=0;
    int tmp=0;
    for(int i=0;i<count;i++){
        if(a[i].mark>=8) countgioi++;
        else{
            if(a[i].mark>=6.5 && a[i].mark<8) countkha++;
            else{
                if(a[i].mark>=5 && a[i].mark<6.5) counttb++;
                else tmp++;
            }
        }
    }
    printf("\n\t(-)Ratio of Excellent Students:%.2f%c",(countgioi*100)*1.0/count,'%');
    printf("\n\t(-)Ratio of Good Students:%.2f%c",(countkha*100)*1.0/count,'%');
    printf("\n\t(-)Ratio of Average Students:%.2f%c",(counttb*100)*1.0/count,'%');
    printf("\n\t(-)Ratio of Weak Students:%.2f%c",(tmp*100)*1.0/count,'%');
    printf("\n\t(-)The highest score on the list:%.2f\n",markMax(a,count));
}

//Save File
void saveFile(STUDENT a[],FILE *f,int count){
    f=fopen(filename,"w");
    for(int i=0;i<count;i++){
        fprintf(f,"%s;%s;%d;%.2f\n",a[i].student_id,a[i].name,a[i].age,a[i].mark);
    }
    printf("\n\t(!)Back up successful!!! %s\n ",filename);
    fclose(f);
}


//Searching mark MAX
float markMax(STUDENT a[],int count){
    float maxpoint=a[0].mark;
    for(int i=0;i<count;i++)
    {
        if(a[i].mark>maxpoint) maxpoint=a[i].mark;
    }
    return maxpoint;
}
