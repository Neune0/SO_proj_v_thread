DIRECTORY_NAME = GeLA 
PWD = ~/EserciziSO/Threads/GeLA 					# this directory
BACKUP_DIRECTORY = /media/sf_SOLabVM/
HEADER_FILE = #header.h
OBJECT_FILE = main.o schermo.o inizializza.o utilities.o tronco.o 

#backup_directory


Frog: $(OBJECT_FILE)
	gcc $(OBJECT_FILE) -lpthread -lncurses -o Frog
	
main.o: main.c 
	gcc -c main.c
	
schermo.o: schermo.c schermo.h #header.h
	gcc -c schermo.c 		
	
inizializza.o: inizializza.c inizializza.h #header.h
	gcc -c inizializza.c 

utilities.o: utilities.c utilities.h #header.h
	gcc -c utilities.c 

tronco.o: tronco.c tronco.h #header.h
	gcc -c tronco.c 

openAll:
	gedit *.c *.h &	

clear:
	rm -fv *.o

backup:
	make clear 
	cd ..
	cp -r $(PWD) $(BACKUP_DIRECTORY)
	ls -l $(BACKUP_DIRECTORY)$(DIRECTORY_NAME)
	


