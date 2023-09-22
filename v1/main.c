#include "utilities.h"
#include "inizializza.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void main()
{
    inizializzaNcurses();
    GameData gameData;
    inizializza(&gameData);
    
    /* esempio creazione del thread rana */
    void *rana_exit_value;
    Param rana_args;

    pthread_create(&gameData->pids.pidRana, NULL, &Rana, &rana_args);

    /* while disegna    
    
    */
    // gioco terminato
    pthread_join(gameData->pids.pidRana, &rana_exit_value;);

    endwin();

}