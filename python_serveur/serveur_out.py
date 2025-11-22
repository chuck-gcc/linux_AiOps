import requests
import json
from requests.models import Response

def server_caller(funct, ip, port, endpoint, header, data, methode):
    try:
        if(methode == 0):
            r = requests.get(f'{ip}:{port}/{endpoint}', headers=header);
        elif(methode == 1):
            print("start post")
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

def print_reponse_json(res):
    if(res.status_code == 200):
        res = res.json()
        print(json.dumps(res, indent=4));
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
    endpoint = 'v1/chat/completions';
    payload = {
        "model": "gpt-3.5-turbo",
        "messages": [
            # {"role": "system", "content": "Tu est le meilleur professeur de chimie de l'université de fribourg"},
            # {"role": "user", "content": "hello"}
            {"role": "system", "content": "Tu est le meilleur professeur de chimie de l'université de fribourg"},
            {"role": "user", "content": "Fait moi un cour sur la sinthese du paracetamole"}
        ]
    }
    j = json.dumps(payload)

    r = server_caller(print_reponse_json,address,port,endpoint, header,j , 1);