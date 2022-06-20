#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DIM 100

// struttura contenente parola letta da file, frequenza della parola e puntatore alla struttura contenente la parola successiva
struct data_text
{
    //Variabile contenente la parola salvata
    char parola[DIM];
    //Variabile che contiene il totale delle occorrenze della parola nel testo
    int frequenza;
    //Variabile che dichiara il puntatore al prossimo nodo della lista.
    struct data_text *next;
};

//typdef utilizzati per facilitare l'implementazione della lista dinamica
typedef struct data_text words;
typedef words *structPtr;

//dichiarazione della funzione che inserisce un nuovo nodo all'interno della lista (Parametri -> Lista e stringa della parola da inserire)
void insert(structPtr *, char []);
//dichiarazione della funzione che visualizza la lista (Parametri -> Lista e lunghezza massima)
void visualizzalista(structPtr, unsigned long int);
//Mette la frequenza di tutte le parole trovate a 1 (Parametri -> Lista)
void init_frequenza(words *);
//elimina i doppioni presenti nella lista e, alla parola eliminata incrementa la frequenza(parametri -> lista)
void Elimina_Doppi(words*);
//calcola percentuale frequenza, (parametri -> lista, massimo)
void freq_lunghezza(words *, unsigned long int);


int main(int argc, const char * argv[])
{
    
    
    //Dichiarazione del puntatore al file
    FILE *fp;
    //Assegno al file pointer il percorso del file e la modalita\' di utilizzo dello stesso ("read") e controllo se il file viene aperto correttamente
    if((fp=fopen(argv[1], "r")) == NULL)
    {
        printf("ERRORE APERTURA FILE!\n");
        return 0;
    }
    //Dichiaro ed inizializzo a zero la parola che conterra\' la lunghezza della parola piu\' grande trovata scorrendo il file.
    unsigned long int max = 0;
    //Dichiaro ed inizializzo a NULL la lista che andra\' a contenere le parole lette da file
    words *lPtr = NULL;
    //Variabile che conterra\' temporaneamente la parola analizzata.
    char tmpword[DIM];
    //Scansiono il file con fscanf che restituisce la stringa letta fino al primo spazio o \n
    while(fscanf(fp, "%s", tmpword) == 1)
    {
        //Controllo la lunghezza della parola e ne salvo il valore nella variabile ln (length)
        unsigned long int ln = strlen(tmpword);
        //dichiaro e inizializzo a 0 una variabile che contiene quanti caratteri sono stati eliminati dalla stringa letta poiche\' non alfanumerici
        int ln_eliminata = 0;
        //ciclo la parola letta carattere per carattere
        for(size_t i = 0 ; i < ln ; i++)
        {
            //finchè ogni carattere non e\' alfanumerico
            while (!( (tmpword[i] >= 'a' && tmpword[i] <= 'z') || (tmpword[i] >= 'A' && tmpword[i] <= 'Z') || tmpword[i] == '\0' || (tmpword[i] >= '0' && tmpword[i] <= '9')) )
                
            {
                //incremento la lunghezza dei caratteri da eliminare
                ln_eliminata++;
                //dichiaro variabile che cicla le posizioni del prossimo for
                size_t j;
                //ciclo la parola a partire dal carattere che devo eliminare e shifto i restanti caratteri
                for(j = i; tmpword[j] != '\0'; ++j)
                {
                    tmpword[j] = tmpword[j+1];
                    
                }
                //l\'ultimo carattere della stringa dovra'\ essere quello nullo
                tmpword[j] = '\0';
            }
            //la funzione tolower rende minuscolo qualsiasi carattere maiuscolo
            tmpword[i] = tolower(tmpword[i]);
        }
        //sottraggo alla lunghezza iniziale la lunghezza raprresentante la somma di tutti i caratteri eliminari
        ln -= ln_eliminata;
        //se la lunghezza della parola è maggiore del massimo
        if(max < ln)
        {
            //assegno la lunghezza al massimo
            max = ln;
        }
        
        //Dopo aver "ripulito" la parola la inserisco nella lista
        insert(&lPtr, tmpword);
    }
    fclose(fp);
    //Inizio la manipolazione e studio dei dati acquisiti
    
    //Eliminio i doppioni delle parole all'interno della lista e modifico la frequenza della parola in questione
    Elimina_Doppi(lPtr);
    //Calcolo la percentuale della frequenza di ogni parola nella lista e stampo la tabella con i risultati (Output #1)
    freq_lunghezza(lPtr, max);
    //Stampo lo stato attuale della lista con un '*' per ogni occorrenza della parola (Output #2)
    visualizzalista(lPtr, max);
    
    //Fine delle operazioni del programma.
    
    printf("\n");
    return 0;
}

//funzione di inserimento in lista, prende come parametro la parola letta e il punattore al primo nodo della lista
void insert(structPtr *ptr, char str[])
{
    //alloco lo spazio in memoria per il nuovo nodo
    structPtr newPtr = malloc(sizeof(words));
    //se ho ancora spazio in memoria
    if(newPtr != NULL)
    {
        //assegno alla struttura del nuovo nodo la parola letta da file
        strcpy(newPtr->parola, str);
        newPtr->next = NULL;
        //creo e assegno a NULL precPtr
        structPtr precPtr = NULL;
        //creo e assegno al puntatore al primo elemento della lista il puntatore corrPtr che scorrera\' la lista
        structPtr corrPtr = *ptr;
        //while cicla finche\' corrPtr punta a NULL oppure finche\' non trova una parola che non rispetta l'ordine alfabetico
        while(corrPtr != NULL && strcmp(str, corrPtr->parola) > 0)
        {
            //assegno precPtr a corrPtr
            precPtr = corrPtr;
            //scorro la lista con corrPtr
            corrPtr = corrPtr->next;
        }
        //se precPtr == NULL, inserisco in testa alla lista
        if(precPtr == NULL)
        {
            newPtr->next = *ptr;
            *ptr = newPtr;
        }
        //altrimenti inserisco in mezzo
        else
        {
            precPtr->next = newPtr;
            newPtr->next = corrPtr;
        }
    }
    //...non ho piu\' spazio in memoria
    else
    {
        printf("Memoria esaurita!\n");
    }
}

//funzione che stampa a video la lista di parole, prende come parametro il puntatore al primo elemento della lista e la lunghezza della parola piu\' lunga
void visualizzalista(structPtr ptr, unsigned long int max)
{
    //OUTPUT
    printf("\n\n%*s%10s", (int)max, "Parola", "Frequenza");
    while(ptr != NULL)
    {
        printf("\n");
        printf("%*s ", (int)max, ptr->parola);
        for(int i=0; i < ptr -> frequenza; i++)
            printf("*");
        ptr = ptr->next;
    }
    
}

void init_frequenza(words *ptr)
{
    //Ciclo finche\' la lista non arriva all'ultimo nodo [puntatore->(NULL)]
    while(ptr != NULL)
    {
        //La frequenza di ogni parola inizialmente e\' a 1
        ptr->frequenza = 1;
        ptr = ptr->next;
    }
}


void Elimina_Doppi(words *ptr)
{
    //Inizializzo la frequenza della lista (ogni parola ha frequenza iniziale 1)
    init_frequenza(ptr);
    
    //Puntatore CORR allo stato iniziale della lista
    words* corrPtr = ptr;
    //Puntatore SUCC al prossimo stato della lista
    words* succPtr = corrPtr->next;
    //Puntatore TMP nullo
    words* tmpPtr = NULL;
    
    //Ciclo la lista finche\' il nodo successivo non e\' NULL (ultimo nodo in lista)
    while(succPtr != NULL)
    {
        //Se la parola del nodo attuale e quella del nodo successivo sono uguali entro nell'if
        if(strcmp ( corrPtr->parola, (corrPtr->next) -> parola ) == 0)
        {
            //metto il valore del successivo nella variabile temporanea
            tmpPtr = succPtr;
            //Assegno al puntatore next del nodo corrente il puntatore next del nodo successivo
            corrPtr->next = succPtr->next;
            //faccio scorrrere il puntatore successivo
            succPtr = succPtr->next;
            //A questo punto posso liberare lo spazio di memoria utilizzato dal nodo della lista temporaneo
            free(tmpPtr);
            //Aumento la frequenza del nodo corrente (perche\' ho trovato un doppione e l\'ho eliminato)
            corrPtr -> frequenza++;
            
        }
        //Se la parola del nodo corrente e la successiva non sono uguali passo ai prossimi nodi
        else
        {
            corrPtr = succPtr;
            succPtr = succPtr->next;
        }
        
    }
}

void freq_lunghezza(words *lPtr, unsigned long int max)
{
    //Dichiaro l'array di interi con lunghezza max+1 (lunghezza parola piu\' grande trovata nel file).
    //L'array avra\' in pos 0 la frequenza delle parole di lunghezza 0, in pos 1 la frequenza delle parole di lunghezza 1 etc..
    int frequenze[max+1];
    //Inizializzo l'array a 0
    for(int i = 0 ; i < max ; i++)
    {
        frequenze[i] = 0;
    }
    
    //Dichiaro una variabile float e la inizializzo a zero. Conterra\' il totale delle frequenze di tutte le parole.
    float tot = 0;
    
    //Ciclo la lista fino alla fine
    while(lPtr != NULL)
    {   //Salvo la lunghezza della parola del nodo corrente.
        unsigned long int lunghezza = strlen(lPtr->parola);
        //Aggiungo la frequenza della parola allo spazio dell'array delle parole di quella frequenza.
        frequenze[lunghezza] += lPtr->frequenza;
        //Aggiungo la frequenza della parola attuale al totale delle frequenze
        tot += (float)( lPtr->frequenza );
        //Sposto il puntatore al nodo successivo
        lPtr = lPtr->next;
    }
    
    //Stampo la tabulazione della tabella che conterra\' la Lunghezza e la Frequenza delle parole del testo
    
    printf("%*s %12s\n", (int)max, "Lunghezza", "Frequenza(%)");
    //se il massimo è 0, significa che il testo è composto da n parole lunghe 0: la percentuale sara\' dunque 100.00%
    if(max == 0)
    {
        printf("%d %.2f%%\n", 0, 100.00);
    }
    //altrimenti
    else
    {
        float perc_tot = 0;
        //stampa lunghezza e percentuale frequenza parole
        for(int i = 0; i < max; i++)
        {
            float percentuale = frequenze[i] / ((tot) / 100);
            if(percentuale != 0)
            {
                
                printf("%*d %.2f%%\n", (int)max, i, percentuale);
                perc_tot += percentuale;
            }
        }
        //stampa ultima lunghezza parola
        printf("%*lu %.2f%%\n", (int)max, max, 100.0-perc_tot);
    }
    
}
