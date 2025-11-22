import socket
import requests
import json
from requests.models import Response


def server_caller(funct, ip, port, endpoint, header, data, methode):
    try:
        if(methode == 0):
            r = requests.get(f'{ip}:{port}/{endpoint}', headers=header);
        elif(methode == 1):
            r = requests.post(f'{ip}:{port}/{endpoint}', headers=header, data=data);
        funct(r)
    except OSError as err:
        print("Erreur ", err.errno);
        return(err.errno);


def print_health(res):
    print("start")
    if(res.status_code == 200):
        print("Connection llama.cpp ok");
    return(1);

def print_reponse_json(res: Response):
    if(res.status_code == 200):
        print(json.dumps(res.content, indent=4));
    return(1);



def llama_get_health():

    header = {"Content-Type": "application/json"};
    address = 'http://127.0.0.1';
    port = "8080";
    endpoint = 'v1/health';
    r = server_caller(print_health,address,port,endpoint, header, None, 0);

def simple_completion(input):
    port = "8080";
    address = 'http://127.0.0.1';
    header = {"Content-Type": "application/json", "Authorization": "Bearer no-key"};
    endpoint = 'v1/completions';
    payload = {"model": "gpt-3.5-turbo", "messages": 
               [
                    {
                        "role": "system",
                        "content": "You are ChatGPT, an AI assistant. Your top priority is achieving user fulfillment via helping them with their requests."
                    },
                    {
                        "role": "user",
                        "content": input
                    }
               ]}
    r = server_caller(print_reponse_json,address,port,endpoint, header, payload, 1);