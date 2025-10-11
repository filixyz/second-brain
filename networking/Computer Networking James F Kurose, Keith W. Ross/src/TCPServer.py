from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print('Server is now serving')
while True:
    connectionSocket, addr = serverSocket.accept()
    message = connectionSocket.recv(1024)
    response = message.decode().upper()
    print(response)
    connectionSocket.send(response.encode())
    connectionSocket.close()
