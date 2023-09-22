#include <pthread.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define SEC 1000000
#define FRAME 2
#define FPS SEC/FRAME


// Strutture

// GAMEOBJECT
typedef struct{
	int x;
	int y;
	char c;
}GameObject;


// SETUP
typedef struct{
	int maxX;
	int maxY;
}Setup;


// PARAMS
typedef struct {
	pthread_mutex_t* mutex;
	Setup _setup;
	GameObject* gameObj;
	int* vite;
}Params;
