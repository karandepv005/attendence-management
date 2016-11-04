project: alldef.h proj.o functions.o
	gcc proj.o functions.o -o project
proj.o: proj.c alldef.h functions.c
	gcc -c proj.c
functions.o: functions.c 
	gcc -c functions.c 
