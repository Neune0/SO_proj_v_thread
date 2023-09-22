#include "header.h"
#include "ladro.h"
#include "guardia.h"
#include "avvocato.h"

#define CICLI 100


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
	
	int maxx;
	int maxy;
	
	int ladroX, ladroY;
	int guardiaX, guardiaY;
	int avvocatoX, avvocatoY;
	int vite = 1;
	
	char* msgWin = "YOU WIN!!!!";
	char* msgLose = "GAME OVER";
	
	srand(time(NULL));
	initscr();
	curs_set(0);
	noecho();
	getmaxyx(stdscr, maxy,maxx);
	Setup setup = {maxx, maxy};
	ladroX = maxx/2;
	ladroY = maxy/2;
	guardiaX = maxx/4;
	guardiaY = maxx/4;
	avvocatoX = maxx/8;
	avvocatoY = maxx/8;
	GameObject ladro = {ladroX, ladroY, '$'};
	GameObject guardia = {guardiaX, guardiaY, '#'};
	GameObject avvocato = {avvocatoX, avvocatoY, 'A'};
	
	//noecho();
	
	pthread_t thread1_id;
	pthread_t thread2_id;
	pthread_t thread3_id;
	
	void* thread1_exit_value; // non per return NULL
	void* thread2_exit_value;
	void* thread3_exit_value;
	
	/*Params threads1_args = { &mutex, maxx,maxy, &ladroX, &ladroY, &vite};
	pthread_create(&thread1_id, NULL, &Ladro, &threads1_args);*/
	
	Params threads1_args = { &mutex, setup, &ladro, &vite };
	Params threads2_args = { &mutex, setup, &guardia, &vite };
	Params threads3_args = { &mutex, setup, &avvocato, &vite };
	
	pthread_create(&thread1_id, NULL, &Ladro, &threads1_args);
	pthread_create(&thread2_id, NULL, &Guardia, &threads2_args);
	pthread_create(&thread3_id, NULL, &Avvocato, &threads3_args);
	
	//fflush(stdin);
	int edgeHit = 0;
	while(vite == 1){
		
		pthread_mutex_lock(&mutex);
		if((ladro.x == guardia.x) && (ladro.y == guardia.y)){ 
			vite = 2;	
		} else if((ladro.x == avvocato.x) && (ladro.y == avvocato.y)){ 
			vite = 0; 
		}
		
		//mvprintw(2,2,"vite%2d",vite);
		box(stdscr, ACS_VLINE, ACS_HLINE);
		
		//mvprintw(maxy-1, maxx-1,"@");
		
		if(vite!=1){
			if(vite == 0) {
				mvprintw(maxy/2, maxx/2 - (strlen(msgLose)/2), msgLose);
			} else if(vite == 2) {
				mvprintw(maxy/2, maxx/2 - (strlen(msgWin)/2), msgWin);
			}
			refresh();
			sleep(2);
			mvprintw(maxy/2+1, maxx/2 - (strlen(msgWin)/2), "Premi un tasto per uscire!");
		}
		refresh();
		pthread_mutex_unlock(&mutex);	
	}
	
	pthread_join(thread1_id, &thread1_exit_value);
	pthread_join(thread3_id, &thread2_exit_value);
	pthread_join(thread2_id, &thread3_exit_value); 
	
	//clear();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	
	refresh();
	sleep(2);
	
	pthread_mutex_destroy(&mutex); //elimina il semaforo quando non serve più
	endwin();
	return 0;
}


