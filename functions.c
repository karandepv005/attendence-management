/*****************************************************************************
 * "Attendance Management" 
 *
 * This code performs various operations mainly used while taking attendance.
 *
 * Copyright (C) 2017 Priyanka V. Karande.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "alldef.h"
#define ENROLL 1
#define TAKEATT 2
#define MODIFY 3
#define DELETE 4
#define MODATT 5
#define CLEAR 6
#define GOBACK 7

int search(long mis) {
	/*read from file where all mis no. names and attendance stored and after each string there is space
	*/
	stud s;
	int lec;
	FILE *fp = fopen("studdata.dat", "r");
	FILE *fp1 = fopen("totallec.dat", "r");
	if(fp == NULL) {
		perror("fopen failed");
		return errno;
	}
	while(1) {
		fscanf(fp, "%ld%s%s%s%d", &s.mis, s.fname, s.mname, s.lname, &s.att);
		if(feof(fp)) {
			printf("Not found\n");
			break;
		}	
		else if(s.mis == mis) {
			printf("your attendance:%d\n", s.att);
			fscanf(fp1, "%d", &lec);
			printf("out of %d lectures\n", lec);
			break;
		}
	}
	fclose(fp);
	fclose(fp1);
	return 0;
}
int staffoptions() {
	/* Display and perform staff operations
	 1. enroll student
	 2. take attendance
	 3. etc
	*/
	//system("clear");
	printf("\n\n*******************************************************************************\n");
	printf("enter option no:\n");
	printf("1. Enroll student\n");
	printf("2. Take attendance\n");
	printf("3. Modify record\n");
	printf("4. Delete record\n");
	printf("5. Modify Attendance (for late comers)\n");
	printf("6. Clear all attendance and start new semester\n");
	printf("7. Go back\n");
	printf("\n\n*******************************************************************************\n");
	int so;
	scanf("%d", &so);
	return so;
}
int choice() {
	//system("clear");
	int ch;
	printf("\n\n*******************************************************************************\n");
	printf("enter option no:\n");
	printf("1. Staff\n");
	printf("2. Student\n");
	printf("3. Exit\n");
	printf("\n\n*******************************************************************************\n");
	scanf("%d", &ch);
	return ch;
}
int stafftask(int sch1) {
	char check;
	int lec, pt;
	long mis;
	int sch = sch1;
	stud s, s1;
	FILE *fp, *fp1, *fp2;
	do {
START:	
		switch(sch) {
			case ENROLL:
				system("clear");
				fp = fopen("studdata.dat", "r");
				//fp2 = fopen("totallec.dat", "r");
				if(fp == NULL) {
					perror("fopen failed");
					return errno;
				}
				printf("enter mis no:\n");
				scanf("%ld", &s.mis);
				while(1) {
					fscanf(fp, "%ld%s%s%s%d", &s1.mis, s1.fname, s1.mname, s1.lname, &s1.att);
					if(feof(fp)) 
						break;
					if(s1.mis == s.mis) {
						printf("this MIS number is already exist\n");
						sch = staffoptions();
						goto START;
					}
				}
				printf("enter first name:\n");
				scanf("%s", s.fname);
				printf("enter middle name:\n");
				scanf("%s", s.mname);
				printf("enter last name:\n");
				scanf("%s", s.lname);
				s.att=0;
				fclose(fp);
				mis = s.mis;
				printf("%ld is enrolled\n", s.mis);
				sort(&s);
			/*	if(mis != s.mis) {
					fp = fopen("studdata.dat", "a+");
					fprintf(fp,"%ld %s %s %s %d \n",s.mis, s.fname, s.mname, s.lname, s.att);
					fclose(fp);
				}
			*/	sch = staffoptions();
				break;
			case  TAKEATT:
				system("clear");
				pdate();
				store_att_date();
				fp = fopen("studdata.dat", "a+");
				fp1 = fopen("tempdata.dat", "w");
				fp2 = fopen("totallec.dat", "r");
				if(fp == NULL || fp1 == NULL || fp2 == NULL) {
					perror("fopen failed");
					return errno;
				}
				printf("press p/a for present/absent respectively\n");
				/* if p then increase attendance from file, else dont do anything....first upon display mis one by one*/
				while(1) {
					fscanf(fp, "%ld%s%s%s%d", &s.mis, s.fname, s.mname, s.lname, &s.att);
					if(feof(fp)) 
						break;	
					printf("%ld:",s.mis);
					scanf(" %c", &check);
					if(check == 'p' || check == 'P') {
						s.att++;
						fprintf(fp1,"%ld %s %s %s %d \n",s.mis, s.fname, s.mname, s.lname, s.att);
					}					
					else
						fprintf(fp1,"%ld %s %s %s %d \n",s.mis, s.fname, s.mname, s.lname, s.att);	
				}
				fscanf(fp2, "%d", &lec);
				lec = lec + 1;
				//printf("%d\n", lec);
				fclose(fp2);
				fp2 = fopen("totallec.dat", "w");
				//remove("totallec.dat");
				fprintf(fp2, "%d ", lec);
				fclose(fp1);
				fclose(fp2);
				//fclose(fp);
				remove("studdata.dat");
				rename("tempdata.dat","studdata.dat");	
				fclose(fp);
				sch = staffoptions();
				break;
			case CLEAR:
				system("clear");
				fclose(fopen("studdata.dat", "w"));
				fp2 = fopen("totallec.dat", "w");
				fprintf(fp2, "%d", 0);
				fclose(fp2);
				sch = staffoptions();
				break;
				/*modify already existed records*/
			case MODIFY:
				system("clear");
				pt = 0;
				printf("enter MIS number to modify record:");
				scanf("%ld", &mis);
				fp = fopen("studdata.dat", "a+");
				fp1 = fopen("tempdata.dat", "w");
				if(fp == NULL || fp1 == NULL) {
					perror("fopen failed");
					return errno;
				}
				while(1) {
					fscanf(fp, "%ld%s%s%s%d", &s.mis, s.fname, s.mname, s.lname, &s.att);
					if(feof(fp)) {
						if(pt != 1)
							printf("Not found\n");
						break;	
					}
					if(mis == s.mis) {
						pt = 1;
						printf("enter first name:\n");
						scanf("%s", s.fname);
						printf("enter middle name:\n");
						scanf("%s", s.mname);
						printf("enter last name:\n");
						scanf("%s", s.lname);
						fprintf(fp1,"%ld %s %s %s %d \n", s.mis, s.fname, s.mname, s.lname, s.att);
					}					
					else
						fprintf(fp1,"%ld %s %s %s %d \n", s.mis, s.fname, s.mname, s.lname, s.att);	
				}
				fclose(fp);
				fclose(fp1);
				remove("studdata.dat");
				rename("tempdata.dat","studdata.dat");	
				sch = staffoptions();
				break;
			case DELETE:
				system("clear");
				pt = 0;
				printf("enter MIS number to delete record:");
				scanf("%ld", &mis);
				fp = fopen("studdata.dat", "a+");
				fp1 = fopen("tempdata.dat", "w");
				if(fp == NULL || fp1 == NULL) {
					perror("fopen failed");
					return errno;
				}
				while(1) {
					fscanf(fp, "%ld%s%s%s%d", &s.mis, s.fname, s.mname, s.lname, &s.att);
					if(feof(fp)) {
						if(pt != 1)
						printf("Not found\n"); 
						break;	
					}
					if(mis == s.mis) {
						//fprintf(fp1,"%ld %s %s %s %d \n", s.mis, s.fname, s.mname, s.lname, s.att);
						printf("Record deleted\n");
						pt = 1;
					}					
					else
						fprintf(fp1,"%ld %s %s %s %d \n", s.mis, s.fname, s.mname, s.lname, s.att);	
				}
				fclose(fp);
				fclose(fp1);
				remove("studdata.dat");
				rename("tempdata.dat","studdata.dat");
				sch = staffoptions();
				break;
			case MODATT:
				system("clear");
				pt = 0;
				printf("enter MIS number to modify attendance:");
				scanf("%ld", &mis);
				fp = fopen("studdata.dat", "a+");
				fp1 = fopen("tempdata.dat", "w");
				if(fp == NULL || fp1 == NULL) {
					perror("fopen failed");
					return errno;
				}
				while(1) {
					fscanf(fp, "%ld%s%s%s%d", &s.mis, s.fname, s.mname, s.lname, &s.att);
					if(feof(fp)) {
						if(pt != 1)
						printf("Not found\n"); 
						break; 	
					}
					if(mis == s.mis) {
						//fprintf(fp1,"%ld %s %s %s %d \n", s.mis, s.fname, s.mname, s.lname, s.att);
						printf("%ld:",s.mis);
						scanf(" %c", &check);
						if(check == 'p' || check == 'P') {
							s.att++;
							fprintf(fp1,"%ld %s %s %s %d \n",s.mis, s.fname, s.mname, s.lname, s.att);
						}
						else
							fprintf(fp1,"%ld %s %s %s %d \n",s.mis, s.fname, s.mname, s.lname, s.att);
						pt = 1;
					}					
					else
						fprintf(fp1,"%ld %s %s %s %d \n", s.mis, s.fname, s.mname, s.lname, s.att);	
				}
				fclose(fp);
				fclose(fp1);
				remove("studdata.dat");
				rename("tempdata.dat","studdata.dat");
				sch = staffoptions();
				break; 
			case GOBACK:
				system("clear");
				break;			
			default:
				system("clear");
				printf("wrong option:\n try again...\n");
				sch = staffoptions();
				break;
		}		
	}
	while(sch != 7);
	return 0;
}
int studoptions() {
	int studo;
	//system("clear");
	printf("\n\n*******************************************************************************\n");
	printf("1. check your attendance\n2. list of attendance\n3. check defaulter list\n4. Check Dates there were lectures taken\n5. Go back\n");
	printf("\n\n*******************************************************************************\n");
	scanf("%d", &studo);
	return studo;
}
void studtask(int studch) {
	int *tp, lec;
	float def;
	int studchs = studch;
	long mis;
	stud s;
	FILE *fp, *fp1;
	do {
		fp = fopen("studdata.dat", "r");	
		fp1 = fopen("totallec.dat", "r");
/* void  function does not return so.....no error check while opening the file a;though we know that file is there and that will open...
		if(fp == NULL) {
			perror("fopen failed");
			return errno;
		}*/
		switch(studchs) {
			case 1:
				system("clear");
				printf("enter your MIS no:");
				scanf("%ld", &mis);
				tp = malloc(sizeof(int));
				*tp = search(mis);
				free(tp);
				studchs = studoptions();
				break;
			case 2:
				system("clear");
				fp = fopen("studdata.dat", "r");	
				fp1 = fopen("totallec.dat", "r");
				fscanf(fp1, "%d", &lec);
				printf("\n\n********************************Attendance Sheet********************************\n");
				printf("MIS\t First name\t Middle name\t last name\t attendance(%d)\n", lec);
				while(1) {
					fscanf(fp, "%ld%s%s%s%d", &s.mis, s.fname, s.mname, s.lname, &s.att);
					if(feof(fp)) 
						break;
					printf("%-8ld %-15s %-15s %-15s %-3d \n", s.mis, s.fname, s.mname, s.lname, s.att);
					/*pos(x,y);
					printf("%ld ", s.mis);
					pos(x,y);
					printf("%s ", s.fname);
					pos(x,y);
					printf("%s ", s.mname);
					pos(x,y);
					printf("%s ", s.lname);
					pos(x,y);
					printf("%d \n", s.att);
					x += 3;
					y += 5;*/
				}
				printf("\n********************************************************************************\n");
				fclose(fp);
				fclose(fp1);
				studchs = studoptions();
				break;
			case 3:
				system("clear");
				fp = fopen("studdata.dat", "r");	
				fp1 = fopen("totallec.dat", "r");
				fscanf(fp1, "%d", &lec);
				printf("\n\n********************************Defaulter List*********************************\n");
				printf("MIS\t First name\t Middle name\t last name \n");
				while(1) {	
					fscanf(fp, "%ld%s%s%s%d", &s.mis, s.fname, s.mname, s.lname, &s.att);
					if(feof(fp)) 
						break;
					def = s.att * 100 / lec;
					if(def < 75)
						printf("%-8ld %-15s %-15s %-15s \n", s.mis, s.fname, s.mname, s.lname);
				}
				printf("\n*************************************Note*****************************************\n");
				printf("Try to attend All remaining lectures\n");
				printf("*********************************************************************************\n");
				fclose(fp);
				fclose(fp1);
				studchs = studoptions();
				break;
			case 4:	
				check_lect_dates();
				studchs = studoptions();
				break;
			case 5:
				system("clear");
				break;
			default:
				system("clear");
				printf("wrong option:\n try again...\n");
				studchs = studoptions();
				break;
		}
	} while(studchs != 5);
	
}
void pos(int x,int y) {  //print on the basis of co-ordinate system
    printf("%c[%d;%df",0x1B,y,x);
}
void sort(stud *s1) {
	stud s;
	int check = 1, ch = 0;
	/* write sort function which will sort new record with comparing all records in studdata.....whenever data is inserted in enroll case of stafftask*/
	FILE *fp = fopen("studdata.dat", "r");
	FILE *fp1 = fopen("tempdata.dat", "w");
	/*if(fp == NULL || fp1 == NULL) {
		perror("fopen failed");
		return errno;
	}*/
	while(1) {
		fscanf(fp, "%ld%s%s%s%d", &s.mis, s.fname, s.mname, s.lname, &s.att);
		if(feof(fp)) {
			if(ch == 0) 
				fprintf(fp1,"%ld %s %s %s %d \n", s1->mis, s1->fname, s1->mname, s1->lname, s1->att);
			/*s1->mis = s.mis;
			strcpy(s1->fname, s.fname);
			strcpy(s1->mname, s.mname);
			strcpy(s1->lname, s.lname);
			s1->att = s.att;*/
			break;
		}
		if(s.mis < s1->mis && check == 1) { 
		
			fprintf(fp1,"%ld %s %s %s %d \n", s.mis, s.fname, s.mname, s.lname, s.att);
			if(feof(fp)) {
				fprintf(fp1,"%ld %s %s %s %d \n", s1->mis, s1->fname, s1->mname, s1->lname, s1->att);
				ch = 1;
				break;
			}
		}
		else if(check == 1) {
			fprintf(fp1,"%ld %s %s %s %d \n", s1->mis, s1->fname, s1->mname, s1->lname, s1->att);
			fprintf(fp1,"%ld %s %s %s %d \n", s.mis, s.fname, s.mname, s.lname, s.att);
			ch = 2;
			check = 2;
		}
		else {
			fprintf(fp1,"%ld %s %s %s %d \n", s.mis, s.fname, s.mname, s.lname, s.att);
		}
		
	}
	fclose(fp1);
	fclose(fp);
	remove("studdata.dat");
	rename("tempdata.dat","studdata.dat");	
}
/* modify enroll case in staff function to modify records*/
/* write date function and add date at every lecture as how possible.*/
void pdate() {
	time_t date;
	struct tm *t;
	time(&date);
	t=localtime(&date);
	checkday(t->tm_wday, wday);
	printf("DATE: %s %d/%d/%d\n", wday, t->tm_mday,(1 + t->tm_mon),(1900 + t->tm_year));
}
void store_att_date() {
	time_t date;
	struct tm *t;
	time(&date);
	t=localtime(&date);
	checkday(t->tm_wday, wday);
	//printf("DATE: %d/%d/%d \n", t->tm_mday,(1 + t->tm_mon),(1900 + t->tm_year));
	FILE *fp = fopen("attdate.dat", "a+");
	fprintf(fp, "%s %d %d %d\n", wday, t->tm_mday,(1 + t->tm_mon),(1900 + t->tm_year));	
	fclose(fp);
}
void check_lect_dates() {
	date d;
	system("clear");
	printf("\n**********************************Dates there were lectures taken*************************************\n");
	printf("Day \tDate(dd/mm/yyyy)\n");
	FILE *fp =fopen("attdate.dat", "r");
	while(!(feof(fp))) {
		fscanf(fp, "%s%d%d%d", wday, &d.mday, &d.month, &d.yr);
		if(feof(fp))
			break;
		printf("%-8s%d/%d/%d\n", wday, d.mday, d.month, d.yr);
	}
	fclose(fp);
}
void checkday(int d, char *day) {
	switch(d) {
		case 0:
			strcpy(day, "Sun");
			break;
		case 1:
			strcpy(day, "Mon");
			break;
		case 2:
			strcpy(day, "Tues");
			break;
		case 3:
			strcpy(day, "Wed");
			break;
		case 4:
			strcpy(day, "Thur");
			break;
		case 5:
			strcpy(day, "Fri");
			break;
		case 6:
			strcpy(day, "Sat");
			break;
	}
}
