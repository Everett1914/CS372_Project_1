# Everett Williams
# CS372_Project_1

# To run the SERVER execute the following command:
    python chatserve.py <PORTNUM>
    python chatserve.py 58058  (Example)
# To run the CLIENT execute the following commands:
    gcc -o chatclient chatclient.c  (Compliles the program)
    ./chatclient <HOSTNAME> <PORTNUM>  (Executes the program)
    ./chatclient flip3.engr.oregonstate.edu 58058  (Example)

# Steps:
 1. Run the server on an Oregonstate flip server.  This must occur first.
 2. Run the client in a different terminal window on a different Oregonestate flip server.
 3. Client prompts user for hostname and sends to client for initialization message.
 4. Server returns server hostname to complete initialization message.
 5. Client sends first chat message.  All messages have the senders hostname prepended from the source.
 6. Either client or server can stop the chat by executing \quit.  Server continues to accept connections.
 7. Server is closed by typing ctrl-c.
