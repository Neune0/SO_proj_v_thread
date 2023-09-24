#include "rana.h"
/*
pid_t avviaRana(int* pipe_fd, int* pipe_rana){
	pid_t move_pid = fork(); // pid che contiente il pid della rana
    
  if (move_pid < 0) {
  	perror("Fork failed");
    exit(1);
  } else if (move_pid == 0) {
  		// Processo "muovi"
      close(pipe_fd[0]); // Chiudi l'estremità di lettura della pipe
      moveProcess(pipe_fd, pipe_rana);
      exit(0);
  }
	return move_pid;
}
/**/


void *rana(void* parameters) {

    
    Params *p;
    p = (Params*)parameters;
    int id = p->id;
    //pthread_mutex_t *mutex = p->mutex;

    // recupero puntatori
    // SEZ.CRITICA
    pthread_mutex_lock(p->mutex);
			
		GameData *gameData = p->gameData;
		Schermo *schermo = (Schermo*) &(gameData->schermo);
		ScreenCell *matrice = (ScreenCell *)schermo->screenMatrix;
		
		PipeData* datiVecchi = (PipeData*)(&gameData->oldPos.general[id]);
		
		Sprite *sprite = (Sprite* ) &gameData->sprites[RANA_SPRITE]; 
		char rana_type = p->ch;

	pthread_mutex_unlock(p->mutex);
    
    //Schermo *matrice =&(param->gameData->schermo);

    // limiti dell' area di gioco per la rana
    int minAreaGiocoX = 0;
    int minAreaGiocoY = 4;
    int maxAreaGiocoX = WIDTH -3;
    int maxAreaGiocoY = HEIGHT-6;
    
    PipeData pipeData;
    pipeData.x=WIDTH/2; // coordinate iniziali
    pipeData.y=HEIGHT-6;
    pipeData.type='X';
    pipeData.id=0;
    
    
    // Invia le coordinate iniziali attraverso la pipe
    
    noecho();
    int ch='D';
    while (1) {
        pipeData.type='X'; // resetta il normale carattere della rana
       	
        ch = getch(); // Leggi il carattere dall'input
        
        // Muovi il personaggio in base all'input dell'utente
        switch (ch) {
        	case KEY_UP:
          	if(pipeData.y>minAreaGiocoY){
            	pipeData.y--;
            }
            break;
          case KEY_DOWN:
          	if(pipeData.y<maxAreaGiocoY){
            	pipeData.y++;
            }
            break;
          case KEY_LEFT:
          	if(pipeData.x>0){
            	pipeData.x--;
            	
            }  
            break;
          case KEY_RIGHT:
          	if(pipeData.x<maxAreaGiocoX){
            	pipeData.x++;
            }
            break;
          case 32: // KEY_SPACE 
          	pipeData.type='S'; //cambia carattere per dire a processoDisegna che  rana sta sparando
            break;
          case 'p': // tasto p  PAUSA
          case 'P':
          	pipeData.type = 'Z'; 
            break;
          default:
          	break;
        }
				
        // Invia le coordinate attraverso la pipe
        
        pthread_mutex_lock(p->mutex);
            gameData->pipeData = pipeData;	// aggiorna i dati dentro gameData
            PipeData* vettore_datiVecchi = (PipeData*)(&gameData->oldPos.general); //recupera array old_pos
            PipeData *old_rana = &gameData->oldPos.general[0];
            aggiornaOggetto(gameData, vettore_datiVecchi, RANA_SPRITE);	// aggiorna oggetto in matrice e in gameData
            
		pthread_mutex_unlock(p->mutex);

        // Aspetta un po' prima di generare nuove coordinate forse andrebbe diminuito
        usleep(FPS/10);
        
    }//end while
    
}//end rana 

/*
pid_t resetRana(int* pipe_fd, int* pipe_rana, pid_t pid_processo_rana){
		pid_t newPid;
		kill(pid_processo_rana, SIGKILL);
		waitpid(pid_processo_rana, NULL,0);
		newPid = avviaRana(pipe_fd, pipe_rana);
		return newPid;
}
/**/




