#include "header.h"
#include "guardia.h"



void* Guardia (void* parameters) {
	Params* p;
	p =(Params*)parameters;
	
	Setup setup = p->_setup;
	GameObject* guardia = p->gameObj;
	int guardiaX, guardiaY, viteG;
	
	// posizioni iniziali
	pthread_mutex_lock(p->mutex);
	guardiaX = guardia->x;
	guardiaY = guardia->y;
	viteG = *(p->vite);
	mvaddch(guardiaY, guardiaX, guardia->c);
	pthread_mutex_unlock(p->mutex);
	int k;
	//timeout(10);
	keypad(stdscr, true);
	while(true){
	
		k=getch();
		switch(k) {
			case KEY_UP:
				if(guardiaY > 1) {
					guardiaY--;
				}
				break;
			
			case KEY_DOWN:
				if(guardiaY < setup.maxY-2) {
					guardiaY++;
				}
				break;
			
			case KEY_LEFT:	
				if(guardiaX > 1) {
					guardiaX--;
				}
				break;
			
			case KEY_RIGHT:	
				if(guardiaX < setup.maxX-2) {
					guardiaX++;
				}
				break;
		}//switch
		
		// ---	sez critica ----
		pthread_mutex_lock(p->mutex);
		mvaddch(guardia->y, guardia->x, ' ');
		//mvprintw(4,2,"viteG%2d",viteG);
		guardia->x = guardiaX;
		guardia->y = guardiaY;
		viteG = *(p->vite);
		mvaddch(guardiaY, guardiaX, guardia->c);
		refresh();
		pthread_mutex_unlock(p->mutex);
		//	---	fine sez	critica	---
		
		//fflush(stdin);
		if(viteG !=1) break;
	}//while	
	
	return 0;
}
