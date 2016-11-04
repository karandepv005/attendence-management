/*****************************************************************************
 * "Attendance Management" 
 *
 * This code performs various operations mainly used while taking attendance.
 *
 * Copyright (C) 2016 Priyanka V. Karande.
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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "alldef.h"
#define STAFF 1
#define STUDENT 2
#define EXIT 3
int main() {
	int ch, *tp, studo;
	char usrname[28], *pass1;
	printf("\n\n*******************************************************************************\n");
	printf("enter option no:\n");
	printf("1. Staff\n");
	printf("2. Student\n");
	printf("3. Exit\n");
	printf("\n\n*******************************************************************************\n");
	scanf("%d", &ch);
	do {
		switch(ch) {
			case STAFF:
				 {
					printf("successfully logged in\n");
					int sch;
					sch = staffoptions();
					tp = malloc(sizeof(int));
					*tp = stafftask(sch);
					free(tp);
					ch = choice();
				}
				break;
			case STUDENT:
				system("clear");
				/* options: 1. check your attendance,   
				2. list of attendance
				3. check defaulter list */ 
				studo = studoptions(); //calls the students options.
				studtask(studo);
				ch = choice();
				break;
			case EXIT:
				system("clear");
				break;
			default:
				system("clear");
				printf("wrong choice try again....\n");
				ch = choice();
				break;
		}
	}
	while(ch != 3);
	return 0;
}
