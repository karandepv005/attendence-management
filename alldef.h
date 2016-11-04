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
int check(char *, char *);
int search(long);
int staffoptions();
int choice();
int stafftask(int);
int studoptions();
void pos(int, int);
void studtask(int );
typedef struct stud {
	long  mis;
	char fname[20], mname[20], lname[20];
	int att;
}stud;
void sort(stud*);
void pdate();
void store_att_date();
typedef struct date {
	int month, mday, yr;
}date;
char wday[5];
void checkday(int , char*);
void check_lect_dates();
void changepass();
