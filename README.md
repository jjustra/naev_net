# naev_net
Simple library for HTTP-based networking, made for Naev game.

Adds SDL_net as dependecy.

Configuration is at beginning of net.c file.

File main.c contains basic example.

### Basic idea is like this :
* You send commands to HTTP server, where script (currently in PHP) will process them
* You get Lua code as response
* You run said code inside Naev Lua interpreter

### What this can be used for :
* Postal service
* Guild vaults
* etc.

### Possible limitations :
* It's slow (network-wise), so no real-time
* It's HTTP not HTTPS

## Server
Currently there is simplified [forth](https://en.wikipedia.org/wiki/Forth_(programming_language)) system interpreter on server side.

tldr :
* you send `1 1 add prt`
* `1` is number - put it on stack
* next `1` is also number - on stack it goes
* `add` is function - call it
  - it will take two items from top of stack
  - adds them
  - puts result on top of stack
* `prt` is also function call it
  - it will print first thing from top of stack (`2` in this case)

## Todo
Some ideas on how to progress. 

### Autoreg
Automatic pilot registration. Gets access token to user.
* Game starts (or is loaded)
* Check if save contains access key
* If not, send 'autoreg' command to server
* Save returned key and use it from now on

### Other approach to server execution ?
Is interpreter on server good way to go?
It offers flexibility.
But I may just overthinked it.
