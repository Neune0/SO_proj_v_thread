#include "tronco.h"

void gestoreTronchi(GameData *gameData, Params *tronco_args){
	//pthread_mutex_t *mutex = tronco_args->mutex;
	int num_tronchi = NTRONCHI;
  	int dir_tronco[NTRONCHI];
  	dir_tronco[0] = (rand() % 2 == 1) ? 1 : -1;
    		
  	for (int i = 1; i < num_tronchi; i++) {
  		dir_tronco[i] = -1 * dir_tronco[i - 1];
	}

	pthread_mutex_lock(tronco_args->mutex);
		for(int j=0; j<num_tronchi; j++){
			gameData->arrayDirTronchi[j] = dir_tronco[j];
			;
			//Params tronco_args = {&mutex, gameData, 'T', 1};
			tronco_args->id = j+1;
			;
			pthread_create(&gameData->pids.pidTronchi[j], NULL, &tronco, tronco_args);
			;
		}
	pthread_mutex_unlock(tronco_args->mutex);

}
/*
pid_t avviaTronco(int* pipe_fd,int x_spawn,int *dir_tronco,int id){
	pid_t tronco_pid = fork();
	if (tronco_pid < 0) {
		perror("Fork failed");
		exit(1);
	}
	else{
		if (tronco_pid == 0) {
			close(pipe_fd[0]); // Chiudi l'estremità di lettura della pipe
			tronco(pipe_fd,x_spawn, dir_tronco[id-1] ,id);
			exit(0);
		}
	}
	return tronco_pid;
}
/**/
//void tronco(GameData *gameData, int y, int direzione_x, int id)
void *tronco(void *parameters) 
{
	int direzione = 1; // solo di prova

	Params *p = (Params*) parameters;
	int id = p->id;
	//pthread_mutex_t *mutex = p->mutex;
	// recupero puntatori 
	// SEZ.CRITICA 
	pthread_mutex_lock(p->mutex);
			
		GameData *gameData = p->gameData;
		Schermo *schermo = (Schermo*) &(gameData->schermo);
		ScreenCell *matrice = (ScreenCell *)schermo->screenMatrix; // ?
		
		PipeData* datiVecchi = (PipeData*)(&gameData->oldPos.general[id]);
		
		Sprite *sprite = (Sprite* ) &gameData->sprites[TRONCO_SPRITE]; // ?
		char tronco_type = p->ch;

		//int direzione = p->gameData->arrayDirTronchi[id-1]; // recupera direzione dall'array

		//Schermo* schermo, 
		//PipeData* pipeData
	
	pthread_mutex_unlock(p->mutex);

	//ScreenCell *matrice = p->gameData->schermo.screenMatrix;

   	// determina random la coordinata_X  di spawn del tronco 
   	int i=0;
   	int spawn_rand;
   	do{
		spawn_rand = rand() % 100;
		i++;
   	}while(i!=id);
	
	PipeData pipeData;
	pipeData.x=spawn_rand;
	pipeData.type= tronco_type ; //'T';
	pipeData.id=id;


	switch(id){
		case 1:
			pipeData.y=YTRONCOUNO;
			break;
		case 2:
			pipeData.y=YTRONCODUE;
			break;
		case 3:
			pipeData.y=YTRONCOTRE;
			break;
	}
	int lunghezza_tronco= 9;
	int numero_spostamenti=0;
    while (1) {
		pipeData.type='T';

    	//mvprintw(37+pipeData.id,2,"t%d numero spostamenti: %d",pipeData.id,numero_spostamenti);
    	if(numero_spostamenti==108 && pipeData.type=='T'){
    		// il tronco si trasforma in tronco nemico
    		pipeData.type='n';

    	}else{
    		if(direzione==1){
				if(pipeData.x + lunghezza_tronco + 1 < WIDTH){
					pipeData.x++;
				}else{
					direzione*=-1;
				}
			}else{
				if(pipeData.x - 1 > 0){
					pipeData.x--;
				}
				else{
					direzione*=-1;
				}
			}
    	}
		// Scrivi coordinate su gameData
		//	SEZ.CRITICA
      	pthread_mutex_lock(p->mutex);
		gameData->pipeData = pipeData;	// aggiorna i dati dentro gameData
		PipeData* vettore_datiVecchi = (PipeData*)(&gameData->oldPos.general);//recupera array old_pos
		aggiornaOggetto(gameData, vettore_datiVecchi, TRONCO_SPRITE);	// aggiorna oggetto in matrice e in gameData
		
		pthread_mutex_unlock(p->mutex);
		usleep(FPS);

		numero_spostamenti= (numero_spostamenti+1)%1000;
      // Aspetta un po' prima di generare nuove coordinate forse andrebbe diminuito
      
    }
}
