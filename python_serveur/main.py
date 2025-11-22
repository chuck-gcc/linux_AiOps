from serveur_in import *
from serveur_out import *
from serveur_log import *

def main():

    #run_serveur_in();
    if(llama_get_health()):
        return(1);
    
    simple_completion("redige un article sur la phiqie quantique, en particulier usr l'intrication quantique")

main()