import socket

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = '127.0.0.1'
port = 8080

serversocket.bind((host, port))
serversocket.listen()

while True:
    clientsocket, addr = serversocket.accept()
    print("Connection form %s" % str(addr))

    receivedmsg = clientsocket.recv(1000)
    print("Message from client: ", receivedmsg)

    msg = 'Thanks for connecting\n'
    clientsocket.send(msg.encode('ascii'))
    clientsocket.close()