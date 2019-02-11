
#!/bin/python

# Developer:  Everett Williams
# Last Modified:  101441FEB19 (Day/Time/Month/Year)
# Program Name: chatclient.c
# Assignment:  CS372 Project 1
# Description:  Client implementation for a simple chat system using a TCP.
# This program represents the side side coding.
# client server architecture.
# References:
#   https://beej.us/guide/bgnet/
#   https://medium.com/@yashitmaheshwary/simple-chat-server-using-sockets-in-c-f72fc8b5b24e
#   https://docs.python.org/2.7/library/socket.html?highlight=socket%20shutdown%20arguments
#   https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/


import socket
import sys

def establishConnection(connection, hostHandle):
    clientHandle = connection.recv(1024)
    connection.send(hostHandle)
    return clientHandle

if __name__ == "__main__":
    hostHandle = 'Bubba'  #Server handle.  Must be at most 10 characters.
    HOST = ''

    if len(sys.argv) != 2:
        print "Arguement count is incorrect.  Must enter an additional arguement <portnumber>"
        exit(1)

    PORT = int(sys.argv[1])
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.bind((HOST, PORT))
    serverSocket.listen(1)
    while 1:
        connection, addr = serverSocket.accept()
        clientHandle = establishConnection(connection, hostHandle);  #Establish initial connection
        print 'Creating a connection with:', clientHandle
        while 1:
           message = connection.recv(2048)
           if message == '':
               print clientHandle,'closed the connection'
               print '\n_____Server awaiting new connection_____'
               break
           message = message.decode()
           print message,
           print hostHandle + '>',
           message = raw_input()
           if message == '\\quit':
               connection.send(message.encode())
               print '\n_____Server awaiting new connection_____'
               break
           message = hostHandle + '> ' + message
           connection.send(message.encode())
    serverSocket.shutdown(1)
    serverSocket.close()
