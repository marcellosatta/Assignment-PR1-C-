#include <stdio.h>
#include <string.h>
//massima dimensione stringa
#define DIM 100

//queste funzioni prendono come parametri un carattere e un intero che rappresentano il carattere in input e lo stato attuale dell'automa. Ritornano lo stato successivo. Riconoscono le stringhe generate dalla grammatica regolare S -> [a-z]S | [0-1]S | 1.
int stato_iniziale_1_4(char, int);
int stato_2(char, int);
int stato_3(char, int);

int main(void)
{
    //input della stringa
    char string[DIM];
    scanf("%s", string);
    //definizione dello stato, inizialmente 0
    int state = 0;
    //lunghezza della stringa
    unsigned long int length = strlen(string);
    //la stringa, per essere riconosciuta come stringa generata dall'espressione regolare deve terminare con 1.
    if(string[length-1] != '1')
    {
        printf("Stringa NON appartenente al linguaggio definito dall'espressione ([a-z] | [0-1])*1\n");
        return 0;
    }
    //definisco l'array di interi che conterra\' le posizioni in cui comincia l'eventuale sottostringa riconosciuta
    int pos_sotto_stringa[length/3];
    //variabile che conta il numero di volte in cui la sottostringa viene riconosciuta
    int count_riconosciuta = 0;
    //definisco un array di puntatori a funzioni che chiama le funzioni che restituiscono lo stato successivo
    int(*FSmachine[3])(char, int)  = {stato_iniziale_1_4, stato_2, stato_3};
    //ciclo la stringa carattere per carattere
    for(int i = 0 ; i < length ; i++)
    {
        
        switch(state)
        {
            //cio\' che la funzione restituisce, ovvero lo stato successivo, viene assegnato alla variabile state ad ogni passata
            case 0:
            case 1:
            case 4:
                state = (*FSmachine[0])(string[i], state);
                break;
            case 2:
                state = (*FSmachine[1])(string[i], state);
                break;
            case 3:
                state = (*FSmachine[2])(string[i], state);
                break;
        }
        //se una funzione restituisce -1 significa che la stringa non è generata dalla grammatica regolare, poiche\' contiene un carattere non presente nell'alfabeto
        if(state == -1)
        {
            printf("Stringa NON appartenente al linguaggio definito dall'espressione ([a-z] | [0-1])*1\n");
            return 0;
        }
        //altrimenti, la stringa è generata dalla grammatica regolare
        else
        {
            //se lo stato finale == 4, la sottostringa e\' stata riconosciuta
            if(state == 4)
            {
                //assegno la posizione in cui la sottostringa e\' stata riconosciuta
                pos_sotto_stringa[count_riconosciuta] = i - 2;
                count_riconosciuta++;
            }
            
        }
    }
    //stampa "la stringa appartiene al linguaggio"
    printf("Stringa appartenente al linguaggio definito dall'espressione ([a-z] | [0-1])*1\n");
    //se il contatore e\' maggiore di 0 significa che l'automa ha riconosciuto almeno una sottostringa
    if(count_riconosciuta > 0)
    {
        //stampo posizioni sottostringa
        printf("Sottostringa '011' presente, posizione/i:     ");
        for(int j = 0 ; j < count_riconosciuta ; ++j)
        {
            printf("\t%d", pos_sotto_stringa[j]);
        }
    }
    //nessuna stringa e\' stata riconosciuta
    else
    {
        printf("Nessuna sottostringa '011' presente\n");

    }
    return 0;
}


//descrizione stato inziale che coincide con lo stato 1 e lo stato 4
int stato_iniziale_1_4(char c, int s)
{
    //char input 0 output stato 2
    if(c == '0')
    {
        return 2;
    }
    //char input [a-z] || 1 output stato 1
    else if((c >= 97 && c <= 122) || c == '1')
    {
        return 1;
    }
    //char input qualsiasi altro carattere output -1
    else
    {
        return -1;
    }
}
//descrizione dello stato 2
int stato_2(char c, int s)
{
    //char input 0, output stato 2
    if(c == '0')
    {
        return 2;
    }
    // char input [a-z] output stato 1
    else if(c >= 97 && c <= 122)
    {
        return 1;
    }
    //char input 1, output stato 3
    else if(c == '1')
    {
        return 3;
    }
    //char input qualsiasi altro carattere output -1
    else
    {
        return -1;
    }
}
//descrizione dello stato 3
int stato_3(char c, int s)
{
    //char input 0, output stato 2
    if(c == '0')
    {
        return 2;
    }
    //char input [a-z] output stato 1
    else if(c >= (97) && c <= 122)
    {
        return 1;
    }
    //char input 1, sottostringa 011 riconosciuta
    else if(c == '1')
    {
        return 4;
    }
    //char input qualsiasi altro carattere output -1
    else
    {
        return -1;
    }
}
