#include "header.h"
#include "ladro.h"



void* Ladro(void*parameters){
	Params* p;
	p =(Params*)parameters;
	
	Setup setup = p->_setup;
	GameObject* ladro = p->gameObj;
	
	int dirX, dirY;
	int newX, newY;
	int maxX, maxY;
	int viteLadro;
	srand(time(NULL));
	
	// valori iniziali 
	pthread_mutex_lock(p->mutex);
	
	newX = ladro->x;
	newY = ladro->y;

	maxX = setup.maxX;
	maxY = setup.maxY;
	
	viteLadro = *(p->vite);
	pthread_mutex_unlock(p->mutex);
	
	while(true){
		// determina nuova posizione
		dirX = rand()%3 - 1;
		dirY = rand()%3 - 1;

		// controllo nuova posizione
		if((newX+dirX>1) && (newX+dirX < maxX-2)){
			newX+=dirX;
		}
		if((newY+dirY>1) && (newY+dirY < maxY-2)){
			newY+=dirY;
		}
		
		pthread_mutex_lock(p->mutex);		//	inizio sez.critica
		viteLadro = *(p->vite);
		mvaddch(ladro->y, ladro->x, ' ');
		//mvprintw(3,2,"viteL%2d",viteLadro);
		ladro->x = newX;
		ladro->y = newY;
		mvaddch(ladro->y, ladro->x, '$');
		
		refresh();
		pthread_mutex_unlock(p->mutex);	//	fine sez.critica
		usleep(FPS);
		if(viteLadro != 1) break;
	}
	
	return 0;
}//end Ladro_B



