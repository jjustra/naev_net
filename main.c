// gcc -o main net.c main.c -lSDL2 -lSDL2_net ; ./main

#include <stdio.h>
#include <SDL2/SDL.h>
#include "net.h"

int main(int ac,char **av){
   char buf[1024];

   SDL_Init(0);
   printf("net_init : %d\n\n",net_init());

   printf("net_get : %d\n\n",net_get("'halo there\thowdy' prt"));
   printf("net_get : %d\n\n",net_get("1 2 add prt"));
   printf("net_get : %d\n\n",net_get("32 genkey prt"));

   sprintf( buf+net_sprintq(buf,"\"text\"\t to \\escape"), " prt" );
   printf("net_get : %d\n\n",net_get(buf));

   net_quit();
   SDL_Quit();
   return 0;
}
