#include "header.h"
#include "avvocato.h"



void* Avvocato(void*parameters){
	Params* p;
	p =(Params*)parameters;
	
	Setup setup = p->_setup;
	GameObject* avvocato = p->gameObj;
	
	int dirX, dirY;
	int newX, newY;
	int maxX, maxY;
	int viteAvvocato;
	srand(time(NULL));
	
	// valori iniziali 
	pthread_mutex_lock(p->mutex);

	newX = avvocato->x;
	newY = avvocato->y;

	maxX = setup.maxX;
	maxY = setup.maxY;
	
	viteAvvocato = *(p->vite);
	pthread_mutex_unlock(p->mutex);
	
	while(true) {
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
		viteAvvocato = *(p->vite);
		mvaddch(avvocato->y, avvocato->x, ' ');
		//mvprintw(5,2,"viteAVV%2d",viteAvvocato);
		avvocato->x = newX;
		avvocato->y = newY;
		mvaddch(avvocato->y, avvocato->x, 'A');
		
		refresh();
		pthread_mutex_unlock(p->mutex);	//	fine sez.critica
		usleep(FPS);
		if(viteAvvocato != 1) break;
		
	}
	return 0;
}//end Avvocato
