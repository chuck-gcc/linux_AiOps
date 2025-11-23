import requests
import json
from requests.models import Response

GET = 0
POST= 1

#func en argument est un pointeur vers la fonction de traitement dediée à l'apelle
def server_caller(funct, ip, port, endpoint, header, data, methode):
    try:
        if(methode == 0):
            r = requests.get(f'{ip}:{port}/{endpoint}', headers=header);
        elif(methode == 1):
            print("start post")
            r = requests.post(f'{ip}:{port}/{endpoint}', headers=header, data=data);
        return funct(r)
    except OSError as err:
        return(err.errno);


def print_health(res: Response) -> int:
    try:
        if(res.status_code == 200):
            print("Connection llama.cpp ok");
        return(0);
    except OSError as err:
        print(err)
    return(err);   


def print_reponse_json(res:Response) -> int:
    try:
        if(res.status_code == 200):
            res= res.json()
            s = json.dumps(res)
            print(res[0]['embedding'][0]);
            return(0);
        else:
            print("Error",res.content);
    except OSError as err:
        print(err)
    return(err);



def llama_get_health() -> int:

    header = {"Content-Type": "application/json"};
    address = 'http://127.0.0.1';
    port = "8080";
    endpoint = 'health';
    r = server_caller(print_health,address,port,endpoint, header, None, GET);
    return(r)

def llama_get_props() -> int:

    header = {"Content-Type": "application/json"};
    address = 'http://127.0.0.1';
    port = "8080";
    endpoint = 'props';
    r = server_caller(print_reponse_json,address,port,endpoint, header, None, GET);
    return(r)

def simple_embedding(log: str, norm : int):

    header = {"Content-Type": "application/json",  "Authorization": "Bearer no-key"};
    address = 'http://127.0.0.1';
    port = "8080";
    endpoint = 'embedding';
    payload = {
        "content": log,
        "embd_normalize": norm
    }
    j = json.dumps(payload)
    r = server_caller(print_reponse_json,address,port,endpoint, header, j, POST);
    return(r)


def simple_completion(input:str):
    port = "8080";
    address = 'http://127.0.0.1';
    header = {"Content-Type": "application/json", "Authorization": "Bearer no-key"};
    endpoint = 'v1/chat/completions';
    payload = {
        "model": "gpt-oss-20b",
        "messages": [
            # {"role": "system", "content": "Tu est le meilleur professeur de chimie de l'université de fribourg"},
            # {"role": "user", "content": "hello"}
            {"role": "system", "content": "Tu est le meilleur professeur de chimie de l'université de fribourg"},
            {"role": "user", "content": "Fait moi un cour sur la sinthese du paracetamole"}
        ],
        "stream": "true"
    }
    j = json.dumps(payload)
    r = server_caller(print_reponse_json,address,port,endpoint, header,j , POST);