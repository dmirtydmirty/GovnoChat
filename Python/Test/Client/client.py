import socket
import sys
target_host = "localhost"
target_port = 15001
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((target_host, target_port))
while True:
    msg = sys.stdin.readline()
    bytes2send = msg.encode()
    client.sendall(bytes2send)
    response = client.recv(4096)
    print(response)

