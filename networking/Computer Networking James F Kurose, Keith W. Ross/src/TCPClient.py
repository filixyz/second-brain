from socket import *

serverName = ''
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
message = input('Write in the sentence you want capitalized: ')
clientSocket.send(message.encode())
response = clientSocket.recv(1024)
print('from server: ', response.decode())
clientSocket.close()
