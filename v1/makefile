DIRECTORY_NAME = GeLA 
PWD = ~/EserciziSO/Threads/GeLA 					# this directory
BACKUP_DIRECTORY = /media/sf_SOLabVM/
HEADER_FILE = header.h
OBJECT_FILE = mutex1.o ladro.o guardia.o avvocato.o

#backup_directory


Mutex1: $(OBJECT_FILE)
	gcc $(OBJECT_FILE) -lpthread -lncurses -o Mutex1
	
mutex1.o: mutex1.c 
	gcc -c mutex1.c
	
ladro.o: ladro.c ladro.h header.h
	gcc -c ladro.c 		
	
guardia.o: guardia.c guardia.h header.h
	gcc -c guardia.c 

avvocato.o: avvocato.c avvocato.h header.h
	gcc -c avvocato.c 

openAll:
	gedit *.c *.h &	

clear:
	rm -fv *.o

backup:
	make clear 
	cd ..
	cp -r $(PWD) $(BACKUP_DIRECTORY)
	ls -l $(BACKUP_DIRECTORY)$(DIRECTORY_NAME)
	


