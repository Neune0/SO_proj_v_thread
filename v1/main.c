
#include "inizializza.h"
#include "tronco.h"
#include "rana.h"



pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
GameData *gameData ; //= (GameData *)malloc(sizeof(GameData));

void main()
{
    gameData = (GameData *)malloc(sizeof(GameData));
    //GameData *gameData;
    inizializzaNcurses();
    inizializza(gameData);
    //Params tronco_args = {&mutex, gameData, 'T', 0};
    Params rana_args = {&mutex, gameData, 'X', 0};
    Params tronco1_args = {&mutex, gameData, 'T', 1};
    Params tronco2_args = {&mutex, gameData, 'T', 2};
    Params tronco3_args = {&mutex, gameData, 'T', 3};

    pthread_mutex_lock(&mutex);
        stampaMatrice( gameData->schermo.staticScreenMatrix);
        pthread_create(&gameData->pids.pidRana, NULL, &rana, &rana_args);
        //gestoreTronchi(gameData, &tronco_args);
        pthread_create(&gameData->pids.pidTronchi[0], NULL, &tronco, &tronco1_args);
        pthread_create(&gameData->pids.pidTronchi[1], NULL, &tronco, &tronco2_args);
        pthread_create(&gameData->pids.pidTronchi[2], NULL, &tronco, &tronco3_args);
    pthread_mutex_unlock(&mutex);
   
    /* esempio creazione del thread rana */
    void *rana_exit_value;
    void *tronco_exit_value;

    pthread_t pid_tronco;
    //pthread_create(&pid_tronco, NULL, &tronco, &tronco_args);
    while(1){
        pthread_mutex_lock(&mutex);
        //stampaMatrice( gameData->schermo.staticScreenMatrix);
        
        stampaMatrice( gameData->schermo.screenMatrix);
        refresh();    
        pthread_mutex_unlock(&mutex);
        //usleep(FPS);
    }

    //refresh();
    sleep(3);
    
    // gioco terminato

    // chiude tutti i tronchi
    for(int i=0; i<NTRONCHI;i++){
        pthread_join(gameData->pids.pidTronchi[i], &tronco_exit_value);
    }
    

    pthread_join(gameData->pids.pidRana, &rana_exit_value);

    pthread_mutex_destroy(&mutex);
    endwin();
    printf("\n fine gioco regolare \n\n");
}