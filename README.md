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

How to forth (tldr) :
* you send `1 2 add prt`
* `1` is number - put it on stack
* `2` is also number - on stack it goes
* `add` is function - call it
  - it will take two items from top of stack (first `2`, then `1`)
  - adds them
  - puts result (`3`) on top of stack
* `prt` is also function call it
  - it will print first thing from top of stack (`3` in this case)

Also see : [Todo 2](#other-approach-to-server-execution-)

### Word list
* add - adds two numbers
* sub - substarcts two numbers
* mul - multiply two numbers
* div - divide two numbers
* mod - modulo of two numbers
* prt - print item on top of stack to output
* motd - prints Message Of The Day
* autoreg - generates access key and make file for it
* getkey - generate random key of given length

## Todo
Some ideas on how to progress. 

### Autoreg
Automatic pilot registration. Gets access token to user.
* Game starts (or is loaded)
* Check if save contains access key
* If not, send 'autoreg prt' command to server
* Save returned key and use it from now on

### Other approach to server execution ?
Is interpreter a good way to go?

It is small and offers flexibility.

But I may just overthought it.
