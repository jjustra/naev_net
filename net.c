#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_net.h>
#include <openssl/ssl.h>
#include <stdio.h>

#include "net.h"


/*
 * Configuration
 */

#define HOST "localhost"
#define PORT 8080
#define URI "/naev.php"
#define BUF_SZ 1024*1024 /* Send/recv buffer size */


IPaddress ip;
char buf[BUF_SZ];
char b64_cl[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"; /* Character list for url-safe base64 encoding */


/**
 * @brief Encodes s_in into base64 and writes it to s_out.
 *    @param s_in  Pointer to input buffer.
 *    @param s_out Pointer to output buffer.
 * @return Pointer to end of output buffer
 * @usage b64e("ABC",buf);
 */
char *b64e(char *s_in, char *s_out){
   int i=0;
   if (s_in[i]==0) return s_out;
   if (s_in[i+1]==0 || s_in[i+2]==0) {
      *s_out++= b64_cl[ s_in[i] >> 2 ];
      if (s_in[i+1]==0) {
         *s_out++ = b64_cl[ ( ( s_in[i]   & 0b000011 ) << 4 ) ];
      } else
      if (s_in[i+2]==0) {
         *s_out++ = b64_cl[ ( ( s_in[i]   & 0b000011 ) << 4 ) + ( ( s_in[i+1] >> 4 ) & 0b001111 ) ];
         *s_out++ = b64_cl[ ( ( s_in[i+1] & 0b001111 ) << 2 ) ];
      }
      return s_out;
   }
   *s_out++ = b64_cl[    s_in[i] >> 2 ];
   *s_out++ = b64_cl[ ( (s_in[i]   & 0b000011 ) << 4 ) + ( (s_in[i+1] >> 4) & 0b001111 ) ];
   *s_out++ = b64_cl[ ( (s_in[i+1] & 0b001111 ) << 2 ) + ( (s_in[i+2] >> 6) & 0b000011 ) ];
   *s_out++ = b64_cl[ (  s_in[i+2] & 0b111111 ) ];
   return b64e( s_in+3, s_out );
}

/**
 * @brief Send request to HOST server and puts response string into Lua.
 *    @param data String to be send to server.
 * @return -1 on error, else number of received bytes
 * @usage net_get("motd");
 */
int net_get(char *data)
{
   int sz,ret;
   char *p;
   TCPsocket sock;

   /* Begin construction of HTTP 1.1 request */
   p = buf + sprintf( buf, "GET %s?d=", URI );

   /* Encode data to base64 and append */
   p = b64e( data, p );

   /* Finally add rest of request header */
   sprintf( p, " HTTP/1.1\r\nHost: %s\r\n\r\n", HOST );

   /* Get length of our request */
   sz=strlen( buf );

   /* Open socket */
   sock=SDLNet_TCP_Open(&ip);
   if (sock == NULL) return -1;

   /* Send request */
   ret = SDLNet_TCP_Send( sock, buf, sz );

   /* If not send all - error */
   if (ret < sz)
      ret = -1;
   else {

      /* Receive response as long as there are some data */
      ret = 0;
      do {
         sz = SDLNet_TCP_Recv( sock, buf+ret, BUF_SZ );
         ret += sz;
      } while (sz > 0);
      buf[ret] = 0;

   }

   /* If Send is ok and Recv is ok try to process */
   if (ret > 0) {

      /* Find end of HTTP response header */
      p=strstr( buf, "\r\n\r\n" );

      /* If found - process, else error */
      if (p != NULL) {
         // HERE LUA SHOULD BE PLUGGED
         printf( "recv : %s\n", p+4 );
      } else
         ret = -1;

   }

   /* Cleanup */
   SDLNet_TCP_Close( sock );

   return ret;
}

/**
 * @brief Inits SDL_net and prepares HOST.
 * @return -1 on error
 */
int net_init()
{
   if (SDLNet_Init()==-1) return -1;
   if (SDLNet_ResolveHost( &ip, HOST, PORT ) == -1 ) return -1;
   return 0;
}

/**
 * @brief Clean up - Shuts down SDL_net.
 */
void net_quit()
{
   SDLNet_Quit();
}
