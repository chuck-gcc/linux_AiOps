import socket
from serveur_log import thread_log

def run_serveur_in():

    server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server_ip = "127.0.0.1"
    port = 8000

    server.bind((server_ip, port))

    server.listen(10);

    print(f"serveur is lising")

    i = True
    while i == True:
        client_socket, client_address = server.accept()
        request = client_socket.recv(1024)
        request = request.decode("utf-8")

        response = "accept".encode("utf-8")
        client_socket.send(response)
        client_socket.close()
        thread_log(request)
        # convert and send accept response to the client
        # convert and send accept response to the client
    server.close()



