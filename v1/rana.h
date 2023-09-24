#ifndef RANA_H
#define RANA_H

#include "utilities.h"
#include "schermo.h"
//pid_t avviaRana(int* pipe_fd, int* pipe_rana);
//void moveProcess(int* pipe_fd, int* pipe_rana);
void *rana(void* parameters);
//pid_t resetRana( int* pipe_fd, int* pipe_rana, pid_t pid_processo_rana);
#endif

