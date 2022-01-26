# naev_net
Simple library for HTTP-based networking, made for Naev game.

###Basic idea is like this :
*   You send commands to HTTP server, where (probably PHP) script will process them
*   You get Lua code as response
*   You run said code inside Naev Lua interpreter

###What this can be used for :
*   Postal service
*   Guild vaults

###Some limitations :
*   It's slow (network-wise), so no real-time
*   It's HTTP not HTTPS
