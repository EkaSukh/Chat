# Chat
The chat has two parts of the program: client part and server part.

TCP/IP socket,
classes,
template,
STL map, STL vector,
file input/output

# Build
$ make

Logic of interraction between the server and a client is that the server should not keep a state of a client after the request from the client is proccessed.
With this logic the server part can work with many open clients applications. 
