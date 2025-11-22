import socket
import openai
import threading

def launch_thread(log):


    client = openai.OpenAI(
        base_url="http://localhost:8080/v1", # "http://<Your api-server IP>:port"
        api_key = "sk-no-key-required"
    )

    completion = client.completions.create(
    model="davinci-002",
    prompt="I believe the meaning of life is",
    max_tokens=8
    )

    print(completion.choices[0].text)

def run_serveur():

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
        print(request)

        response = "accept".encode("utf-8")
        client_socket.send(response)
        client_socket.close()
        
        # convert and send accept response to the client
        # convert and send accept response to the client
    server.close()

run_serveur()
