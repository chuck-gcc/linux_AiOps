from serveur_in import *
from serveur_out import *
from serveur_log import *

def main():
    #run_serveur_in();
    if(llama_get_health()):
        print("Erreur connection au serveur")
        return(1);
    r = simple_embedding("hello",-1);
    
    print("Valeur de retour", r);
    
    #simple_completion("redige un article sur la phiqie quantique, en particulier usr l'intrication quantique")

main()