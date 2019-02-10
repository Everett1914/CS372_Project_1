#server program
import socket
import sys

def exchangeHandles(connection, hostHandle):
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
        clientHandle = exchangeHandles(connection, hostHandle);  #Get the client handle/send server handle
        print 'Creating a connection with:', clientHandle
        while 1:
           message = connection.recv(20480)
           if message == '':
               print clientHandle,'closed connection'
               break
           message = message.decode()
           print message,
           print hostHandle + '>',
           message = raw_input()
           if message == '/quit':
               connection.send(message.encode())
               print '\n_____Server awaiting new connection_____'
               break
           message = hostHandle + '> ' + message
           connection.send(message.encode())
    serverSocket.shutdown(1)
    serverSocket.close()
