# naev_net
Simple library for HTTP-based networking, made for Naev game.

Configuration is at beginning of net.c file.

File main.c contains basic example.

### Basic idea is like this :
*   You send commands to HTTP server, where script (currently in PHP) will process them
*   You get Lua code as response
*   You run said code inside Naev Lua interpreter

### What this can be used for :
*   Postal service
*   Guild vaults

### Possible limitations :
*   It's slow (network-wise), so no real-time
*   It's HTTP not HTTPS

## Todo
Some ideas on how to progress. 

### Autoreg
Automatic installation registration. Gets access token to user.
* Game starts (or is loaded)
* Check if save contains access key
* If not send 'autoreg' command to server
* Save returned key and use it from now on
