# CS372_Project_1

#Server
#To run the SERVER execute the following command:
    1. python chatserve.py <PORTNUM>
    2. python chatserve.py 58058  (Example)
    Server was tested on flip3

#Client
#To run the CLIENT execute the following commands:
    1. gcc -o chatclient chatclient.c  (Compliles the program)
    2  ./chatclient <HOSTNAME> <PORTNUM>  (Executes the program)
    3. chatclient flip3.engr.oregonstate.edu 58058  (Example)
    Client was tested on flip2

# Steps:
 1. Run the server on an Oregonstate flip server.  This must occur first.
 2. Run the client in a different terminal window on a different Oregonestate flip server.
 3. Client prompts user for hostname and sends to client for initialization message.
 4. Server returns server hostname to complete initialization message.
 5. Client sends first chat message.  All messages have the senders hostname prepended from the source.
 6. Either client or server can stop the chat by executing \quit.  Server continues to accept connections.
 7. Server is closed by typing ctrl-c.
