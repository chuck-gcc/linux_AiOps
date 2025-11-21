import socket

def run_serveur():

    server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server_ip = "127.0.0.0"
    port = 8000

    server.bind((server_ip, port))

    server.listen(0);

    print(f"serveur is lising")
    i = True
    while i == True:
        client_socket, client_address = server.accept()
        request = client_socket.recv(1024)
        request = request.decode("utf-8")
        print(request)
        print(client_address)

        response = "accept".encode("utf-8")
        client_socket.send(response)
        client_socket.close()
        
        # convert and send accept response to the client
        # convert and send accept response to the client
    server.close()
run_serveur()
