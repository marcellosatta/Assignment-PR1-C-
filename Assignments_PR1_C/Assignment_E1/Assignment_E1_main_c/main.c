#include <stdio.h>
#include <string.h>
#define DIM 100
//Tutte le funzioni, che rappresentano un automa per il riconoscimento delle stringhe generate dall'espressione regolare  [A-Z]{4}ab+[^d]{3}, prendono in input un carattere e lo stato attuale e ritornano un intero che rappresenta lo stato successivo
int stato_iniziale(char, int);
int stato_1(char, int);
int stato_2(char, int);
int stato_3(char, int);
int stato_4(char, int);
int stato_5(char, int);
int stato_6(char, int);
int stato_7(char, int);
int stato_8(char, int);
//Tutte le funzioni, che rappresentano un automa per il riconoscimento della sottostringa abDD, prendono in input un carattere e lo stato attuale e ritornano un intero che rappresenta lo stato successivo
int stato_iniziale_abDD(char, int);
int stato_1_abDD(char, int);
int stato_2_abDD(char, int);
int stato_3_abDD(char, int);

int main()
{
    //Input stringa da riconoscere, il controllo di ogni carattere appartenente all'alfabeto dell'espressione regolare è garantito dall'automa stesso
    char string[DIM];
    printf("Stringa:\n");
    scanf("%s", string);
    //calcolo la lunghezza della stringa presa in input
    unsigned long int ln = strlen(string);
    //inizializzo lo stato iniziale a 0
    int s = 0;
    //array di puntatori a funzioni che chiama, per ogni carattere passato in input, la funzione che calcola lo stato successivo
    int(*automa[10])(char, int) = {stato_iniziale, stato_1, stato_2, stato_3, stato_4, stato_5, stato_6, stato_7, stato_8};
    //ciclo la stringa fino al suo ultimo carattere
    for(size_t i = 0 ; i < ln ; i++)
    {
        //switch che, passando ad ogni funzione il carattere i-esimo e lo stato presente, calcola lo stato successivo
        switch(s)
        {
            case 0:
                s = (*automa[0])(string[i], s);
                break;
            case 1:
                s = (*automa[1])(string[i], s);
                break;
            case 2:
                s = (*automa[2])(string[i], s);
                break;
            case 3:
                s = (*automa[3])(string[i], s);
                break;
            case 4:
                s = (*automa[4])(string[i], s);
                break;
            case 5:
                s = (*automa[5])(string[i], s);
                break;
            case 6:
                s = (*automa[6])(string[i], s);
                break;
            case 7:
                s = (*automa[7])(string[i], s);
                break;
            case 8:
                s = (*automa[8])(string[i], s);
                break;
        }
        //se sono arrivato all'ultimo stato significa che la stringa è riconosciuta, ma se leggo in input altri caratteri, la stringa non è generata dall'espressione regolare
        if(s == 9 && i != ln-1)
        {
            s = -1;
            break;
        }
    }
    //se all'uscita dal for lo stato è uguale a -1 oppure se non sono arrivato almeno allo stato 6, in cui leggo b+, significa che la stringa non appartiene al linguaggio
    if(s == -1 || s < 6)
    {
        printf("stringa non appartenente al linguaggio\n");
        return 0;
    }
    //altrimenti la stringa appartiene al linguaggio
    else
    {
        //definisco l'automa che riconosce la sottostringa abDD
        //inizializzo lo stato a 0
        int s_abDD = 0;
        //array di puntatori a funzioni che chiama, per ogni carattere passato in input, la funzione che calcola lo stato successivo
        int(*automa_abDD[10])(char, int) = {stato_iniziale_abDD, stato_1_abDD, stato_2_abDD, stato_3_abDD};
        //ciclo la stringa fino al suo ultimo carattere
        for(size_t i = 0 ; i < ln ; i++)
        {
             //switch che, passando ad ogni funzione il carattere i-esimo e lo stato presente, calcola lo stato successivo
            switch(s_abDD)
            {
                case 0:
                    s_abDD = (*automa_abDD[0])(string[i], s_abDD);
                    break;
                case 1:
                    s_abDD = (*automa_abDD[1])(string[i], s_abDD);
                    break;
                case 2:
                    s_abDD = (*automa_abDD[2])(string[i], s_abDD);
                    break;
                case 3:
                    s_abDD = (*automa_abDD[3])(string[i], s_abDD);
                    break;
            }
        }
        //stampa riferita alla stringa generata dall'espressione regolare  [A-Z]{4}ab+[^d]{3}
        printf("stringa appartenente al linguaggio\n");
        //se sono arrivato (con l'automa che riconosce la sottostringa abDD) allo stato finale, significa che la sottostringa abDD è presente
        if(s_abDD == 4)
        {
            printf("sottostringa abDD presente\n");
        }
        //altrimenti non è presente
        else
        {
            printf("nessuna sottostringa abDD\n");
        }
        return 0;
    }
   
}
//DESCRIZIONE DEGLI STATI DELL'AUTOMA CHE RICONOSCE LE STRINGHE GENERATE DALL'ESPRESSIONE REGOLARE [A-Z]{4}ab+[^d]{3}
//stato inziale
int stato_iniziale(char c, int stato)
{
    //se il carattere in input è [A-Z], passo allo stato successivo
    if(c > 64 && c < 91)
    {
        return 1;
    }
    //altrimenti rimango nello stato 0
    else if((c > 96 && c < 123) || (c > 47 && c < 58))
    {
        return 0;
    }
    //se il carattere non è compreso nell'alfabeto, restituisco -1
    else
    {
        return -1;
    }
}
//stato 1
int stato_1(char c, int stato)
{
    //se il carattere in input è [A-Z], passo allo stato successivo
    if(c > 64 && c < 91)
    {
        return 2;
    }
    //altrimenti rimango nello stato 0
    else if((c > 96 && c < 123) || (c > 47 && c < 58))
    {
        return 0;
    }
    //se il carattere non è compreso nell'alfabeto, restituisco -1
    else
    {
        return -1;
    }
}
//stato 2
int stato_2(char c, int stato)
{
    //se il carattere in input è [A-Z], passo allo stato successivo
    if(c > 64 && c < 91)
    {
        return 3;
    }
    //altrimenti rimango nello stato 0
    else if((c > 96 && c < 123) || (c > 47 && c < 58))
    {
        return 0;
    }
    //se il carattere non è compreso nell'alfabeto, restituisco -1
    else
    {
        return -1;
    }
}
//stato 3
int stato_3(char c, int stato)
{
    //se il carattere in input è [A-Z], passo allo stato successivo
    if(c > 64 && c < 91)
    {
        return 4;
    }
    //altrimenti rimango nello stato 0
    else if((c > 90 && c < 123) || (c > 47 && c < 58))
    {
        return 0;
    }
    //se il carattere non è compreso nell'alfabeto, restituisco -1
    else
    {
        return -1;
    }
}
//stato 4
int stato_4(char c, int stato)
{
    //se il carattere è 'a', vado allo stato successivo
    if(c == 97)
    {
        return 5;
    }
    //se il carattere è [0-9] o [b-z], torno allo stato 0
    else if((c > 97 && c < 123) || (c > 47 && c < 58))
    {
        return 0;
    }
    //se il carattere è [A-Z], torno allo stato 1
    else if(c > 64 && c < 91)
    {
        return 1;
    }
    //altrimenti, se il carattere non è compreso nell'alfabeto, restituisco -1
    else
    {
        return -1;
    }
    
}
//stato 5
int stato_5(char c, int stato)
{
    //se il carattere è b, vado allo stato successivo
    if(c == 98)
    {
        return 6;
    }
    //se il carattere è 'a' 0 [c-z] o [0-9], torno allo stato 0
    else if((c == 97) || (c > 98 && c < 123) || (c > 47 && c < 58))
    {
        return 0;
    }
    //se il carattere è [A-Z], ritorno allo stato 1
    else if(c > 64 && c < 91)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
//stato 6
int stato_6(char c, int stato)
{
    //se il carattere è 'b', rimango nello stato 6
    if(c == 98)
    {
        return 6;
    }
    //altrimenti, se il carattere non è b, ma sempre appartenente all'alfabeto, vado nello stato successivo
    else if((c == 97) || (c == 99) || (c > 100 && c < 123) || (c > 47 && c < 58) || (c > 64 && c < 91))
    {
        return 7;
    }
    //se il carattere non è compreso nell'alfabeto, restituisco -1
    else
    {
        return -1;
    }
}
// stato 7
int stato_7(char c, int stato)
{
    //se il carattere non è d ([^d]), vado allo stato successivo
    if((c > 96 && c < 100) || (c > 100 && c < 123) || (c > 47 && c < 58) || (c > 64 && c < 91))
    {
        return 8;
    }
    //se il carattere non è compreso nell'alfabeto o è 'd', restituisco -1
    else
    {
        return -1;
    }
}
//stato 8
int stato_8(char c, int stato)
{
    //se il carattere non è d ([^d]), vado allo stato successivo
    if((c > 96 && c < 100) || (c > 100 && c < 123) || (c > 47 && c < 58) || (c > 64 && c < 91))
    {
        return 9;
    }
    //se il carattere non è compreso nell'alfabeto o è 'd', restituisco -1
    else
    {
        return -1;
    }
}
//DESCRIZIONE DEGLI STATI DELL'AUTOMA CHE RICONOSCe LA SOTTOSTRINGA abDD
//stato iniziale
int stato_iniziale_abDD(char c, int stato)
{
    //se il carattere è 'a', vado allo stato successivo
    if(c == 97)
    {
        return 1;
    }
    //se il carattere non è 'a', rimango nello stato 0 iniziale
    else if((c > 97 && c < 123) || (c > 47 && c < 58) || (c > 64 && c < 91))
    {
        return 0;
    }
    //se il carattere non appartiene all'alfabeto del linguaggio restituisco -1
    else
    {
        return -1;
    }
}

int stato_1_abDD(char c, int stato)
{
    //se il carattere è 'b', vado allo stato successivo
    if(c == 98)
    {
        return 2;
    }
    //se il carattere è [c-z] o [A-Z] o [0-9], ritorno nello stato 0
    else if((c > 98 && c < 123) || (c > 47 && c < 58) || (c > 64 && c < 91))
    {
        return 0;
    }
    //se il carattere è a ritorno nello stato 1
    else if(c == 97)
    {
        return 1;
    }
    //se il carattere non appartiene all'alfabeto del linguaggio restituisco -1
    else
    {
        return -1;
    }
}

int stato_2_abDD(char c, int stato)
{
    //se il carattere è 'D', vado allo stato successivo
    if(c == 68)
    {
        return 3;
    }
    //se il carattere è [b-z] o [A-Z] o [0-9], ritorno nello stato 0
    else if((c > 97 && c < 123) || (c > 47 && c < 58) || (c > 64 && c < 91))
    {
        return 0;
    }
    //se il carattere è a ritorno nello stato 1
    else if(c == 97)
    {
        return 1;
    }
    //se il carattere non appartiene all'alfabeto del linguaggio restituisco -1
    else
    {
        return -1;
    }
}

int stato_3_abDD(char c, int stato)
{
    //se il carattere è 'D', vado allo stato successivo, il finale, ciò significa che la stringa è stata riconosciuta
    if(c == 68)
    {
        return 4;
    }
    //se il carattere è [b-z] o [A-Z] o [0-9], ritorno nello stato 0
    else if((c > 97 && c < 123) || (c > 47 && c < 58) || (c > 64 && c < 91))
    {
        return 0;
    }
    //se il carattere è a ritorno nello stato 1
    else if(c == 97)
    {
        return 1;
    }
    //se il carattere non appartiene all'alfabeto del linguaggio restituisco -1
    else
    {
        return -1;
    }
}
