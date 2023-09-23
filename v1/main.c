//#include "utilities.h"
#include "inizializza.h"
#include "schermo.h"
#include "tronco.h" 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void main()
{
    GameData *gameData = (GameData *)malloc(sizeof(GameData));
    inizializzaNcurses();
    //GameData gameData;
    inizializza(gameData);
    Params tronco_args = {&mutex, gameData, 'T'};


    pthread_mutex_lock(&mutex);
    stampaMatrice( gameData->schermo.staticScreenMatrix);
    pthread_mutex_unlock(&mutex);
   
    /* esempio creazione del thread rana */
    void *rana_exit_value;
    void *tronco_exit_value;
    Params rana_args;
    //Params tronco_args = {&mutex, gameData, 'T'};

    pthread_t pid_tronco;
    pthread_create(&pid_tronco, NULL, &tronco, &tronco_args);

    
    //pthread_create(&gameData->pids.pidTronchi[0], NULL, &tronco, &tronco_args);

    //pthread_create(&gameData->pids.pidRana, NULL, &Rana, &rana_args);

    /* while disegna    */
    //pthread_mutex_lock(&mutex);
    //stampaMatrice( gameData->schermo.staticScreenMatrix);
    //stampaMatrice( gameData->schermo.screenMatrix);
    //pthread_mutex_unlock(&mutex);

    while(1){
        pthread_mutex_lock(&mutex);
        //stampaMatrice( gameData->schermo.staticScreenMatrix);
        stampaMatrice( gameData->schermo.screenMatrix);
        //PipeData tronco = gameData->oldPos.general[1];
        //mvaddch(tronco.y,tronco.x, tronco.type);
        refresh();    
        pthread_mutex_unlock(&mutex);
    }

    //refresh();
    sleep(3);
    
    // gioco terminato
    pthread_join(pid_tronco, &tronco_exit_value);

    //pthread_join(gameData->pids.pidRana, &rana_exit_value);

    endwin();
    printf("\n fine gioco regolare \n\n");
}