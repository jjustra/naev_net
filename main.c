// gcc -o main net.c main.c -lSDL2 -lSDL2_net ; ./main

#include <stdio.h>
#include <SDL2/SDL.h>
#include "net.h"

int main(int ac,char **av){
   SDL_Init(0);
   printf("net_init : %d\n",net_init());

   printf("net_get : %d\n",net_get("'halo there\nhowdy' prt"));
   printf("net_get : %d\n",net_get("1 1 add prt"));

   net_quit();
   SDL_Quit();
   return 0;
}