#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
//Dimensione max stringhe
#define DIM 100
//massimo quantita\' pseudocasuale
#define MAX 100001
//struttura prodotto
struct elenco
{
    char nome[DIM]; //stringa che contiene il nome del prodotto
    float prezzo; //float che indica il prezzo del prodotto
    int quantita; //int che indica la quantità del prodotto
    int codice; //int che indica il codice del prodotto
    struct elenco *next; //puntatore al successivo elemento della lista
};
//Variabile globale che conta il totale dei prodotti presenti in lista. Definita globale perche\' viene incrementata nella funzione inserisci e decrementata nella elimina, nonche\' inizializzata nella crea_l. Ho preferito questa soluzione rispetto a quella di passare un parametro in piu\' a tutte le funzioni (anche a quelle in cui il suddetto parametro non sarebbe servito).
int TOT_prodotti = 0;
//Rinomino la struttura
typedef struct elenco prodotto;
//Rinomino un puntatore alla struttura
typedef prodotto *prodPtr;

//La funzione variazione_q permette di cambiare la quantità di un prodotto
void variazione_q(prodPtr *, int);
//La funzione variazione_p permette di cambiare il prezzo di un prodotto
void variazione_p(prodPtr *, int);
//La funzione inserisci permette di inserire un nuovo prodotto nella lista
void inserisci(prodPtr *, int);
//La funzione elimina permette di eliminare un prodotto dalla lista
void elimina(prodPtr *, int);
//La funzione ricerca permette di ricercare un prodotto nella lista
void ricerca(prodPtr *, int);
//La funzione crea_l permette di creare la lista dopo la lettura del file
void crea_l(prodPtr *, int, char[], float, int);
//La funzione visualizza_l permette di stampare a video la lista
void visualizza_l(prodPtr);
//La funzione contatore_pro conta il numero totale di prodotti presenti all'interno della lista
void contatore_prod(prodPtr);
//La funzione stampa_lista_rovesciata_soglia stampa i prodotti la cui quantità e\' minore della soglia (inserita da utente o di default = 10) che sono presenti nella lista per codice in ordine decrescente
void print_l_reverse(prodPtr *, int);

int main()
{
    //funzione srand con seme dieci che randomizza interi da assegnare poi alla quantità
    srand(10);
    //Puntatore al primo elemento della lista
    prodotto *lPtr = NULL;
    //variabile che definisce la scelta della funzione da eseguire all'interno del menu\'
    int scelta;
    //Stringa che conterra\' il percorso del file da cui leggere i prodotti
    char path[DIM];
    //Inserimento percorso del file da tastiera
    printf("Inserisci percorso del file contenente l'elenco dei prodotti\n");
    scanf("%s", path);
    strcat(path, "/elencoProdotti.csv");
    //Puntatore al file
    FILE *fp;
    //Apertura del file in lettura con controllo (in caso il file non esista o il percorso sia sbagliato)
    if((fp = fopen(path, "r")) == NULL)
    {
        printf("\nERRORE APERTURA FILE\n");
        return 0;
    }
    else
    {
        //variabile temporanea che conterra\' il codice del prodotto letto da file
        int tmp_codice = 0;
        //stringa temporanea che conterra\' il nome del prodotto letto da file
        char tmp_nome[DIM];
        //variabile temporanea che conterra\' il prezzo del prodotto letto da file
        float tmp_prezzo;
        //stringa temporanea che conterra\' tutta la riga letta da file che verra\' in seguito divisa in token
        char tmp_str[DIM];
        //soglia inizializzata a 10 che servirà per la funzione stampa_lista_rovesciata_soglia
        int soglia = 10;
        //stringa che raccoglie i token durante la lettura da file
        char *token;
        //variabile che tiene traccia del numero di token letti e garantisce che ogni campo (codice, nome, prezzo) sia inserito nell\'apposito temporaneo
        int n_tok = 1;
        //Inizio a ciclare il file. Finche\' fgets non legge NULL
        while(fgets(tmp_str, DIM, fp) != NULL)//Con fgets leggo da file tutta una riga e la metto nella stringa tmp_str
        {
            //Ciclo la stringa per token. Poiche\' i file csv contengono campi separati da virgole, il carattere separatore che passo alla funzione strtok sara\' la virgola
            for(token = strtok(tmp_str,","); token != NULL; token = strtok(NULL,","))
            {
                //assegno una quantita\' (intero pseudo-casuale)
                int tmp_quantita = (rand() % MAX);
                //se leggo il primo token (ovvero il modulo di 3 di n_tok e\' 1)
                if(n_tok % 3 == 1)
                {
                    //attraverso la funzione atoi che trasforma una stringa in intero, assegno il codice letto al temporaneo
                    tmp_codice = atoi(token);
                }
                //se leggo il secondo token (ovvero il modulo di 3 di n_tok è 2)
                else if(n_tok % 3 == 2)
                {
                    //attraverso la funzione strcpy che copia la stringa 2 nella stringa 1 copio il nome del prodotto sulla stringa temporanea
                    strcpy(tmp_nome, token);
                }
                //se leggo il terzo token (ovvero il modulo di 3 di n_tok è 0)
                else if(n_tok % 3 == 0)
                {
                    //ancora attraverso la funzione atoi assegno il prezzo del prodotto al temporaneo
                    tmp_prezzo = atoi(token);
                    //Una volta aver letto un prodotto dal file chiamo la funzione crealista che aggiunge i campi del prodotto al nodo della lista
                    crea_l(&lPtr, tmp_codice, tmp_nome, tmp_prezzo, tmp_quantita);
                }
                //incremento n_tok
                n_tok++;
            }
        }
        //Quando ho finito di leggere da file , lo chiudo
        fclose(fp);
        //Menu\' di array di puntatori a funzione
        void(*menu[6])(prodPtr *, int) = {variazione_q, variazione_p, inserisci, elimina, ricerca, print_l_reverse};
        
        do //Costrutto do while che cicla il menu\' finche\' non si seleziona la scelta che implementa l'uscita dal programma
        {
            //Stampa del menu\'
            printf("\nScegliere un opzione:\n0 - variazione della quantita\' di un prodotto;\n1 - variazione del prezzo di un prodotto;\n2 - inserimento di un nuovo prodotto;\n3 - eliminazione di un prodotto;\n4 - Ricerca di un prodotto;\n5 - Stampa prodotti sotto alla soglia;\n6 - Visualizza lista\n7 - Esci;\n");
            //Controllo scelta
            while(scanf("%d", &scelta) != 1 || scelta < 0 || scelta > 7)
            {
                printf("Scelta errata!\n");
                scanf("%*[^\n]%*c");
            }
            //Chiamata delle prime quattro funzioni
            if(scelta >= 0 && scelta < 5)
            {
                printf("Inserisci il codice del prodotto che si vuole inserire, eliminare, ricercare o di cui si vuole modificare la quantita\' o il prezzo:\n");
                //Controllo inserimento codice
                while(scanf("%d", &tmp_codice) != 1 || tmp_codice < 0)
                {
                    printf("Codice errato! Inserisci un codice numerico maggiore di 0.\n");
                    scanf("%*[^\n]%*c");
                }
                (*menu[scelta])(&lPtr, tmp_codice);
            }
            //Chiamata funzione stampa sotto soglia
            else if(scelta == 5)
            {
                printf("Inserisci la soglia:\n");
                while(scanf("%d", &soglia) != 1 || soglia < 0)
                {
                    printf("Scelta errata!\n");
                    scanf("%*[^\n]%*c");
                }
                (*menu[scelta])(&lPtr, soglia);
            }
            else if(scelta == 6)
            {
                
                visualizza_l(lPtr);
            }
            //Uscita dal programma
            else if(scelta == 7)
            {
                //Conto il numero di prodotti all\'interno della lista
                contatore_prod(lPtr);
                //Variabile che conta i prodotti sotto la soglia
                int totale_prodotti_soglia = 0;
                //inserimento percorso in cui salvare il file daOrdinare.bin
                printf("Inserisci il percorso in cui vuoi salvare il file daOrdinare.bin:\n");

                char path_da_ordinare[DIM];
                scanf("%s", path_da_ordinare);
                strcat(path_da_ordinare, "/daOrdinare.bin");
                //Apertura file in scrittura daOrdinare.bin con controllo
                if((fp = fopen(path_da_ordinare, "wb")) == NULL)
                {
                    printf("\nERRORE SCRITTURA FILE\n");
                    return 0;
                }
                //While per stampare su file tramite fprintf i prodotti della lista la cui quantita\' sotto la soglia indicata
                while(lPtr != NULL)
                {
                    if(lPtr->quantita < soglia)
                    {
                        fprintf(fp, "%8s: %8d\t%8s: %25s\t%8s: %8.2f €\t%8s: %8d\t%10s: %d\n","codice", lPtr->codice, "nome", lPtr->nome, "prezzo", lPtr->prezzo, "quantita", lPtr->quantita, "da ordinare", ((soglia-lPtr->quantita) + 1));
                        //incremento il numero di prodotti la cui quantita\' e\' sotto la soglia
                        totale_prodotti_soglia++;
                    }
                    lPtr = lPtr->next;
                }
                //Dopo aver finito di scrivere su file, chiudo
                fclose(fp);
                //inserimento percorso in cui salvare il file numeroTotale.txt
                printf("Inserisci il percorso in cui vuoi salvare il file numeroTotale.txt:\n");
                char path_numero_totale[DIM];
                scanf("%s", path_numero_totale);
                strcat(path_numero_totale, "/numeroTotale.txt");
                //Apertura file in scrittura numeroTotale.txt con controllo
                if((fp = fopen(path_numero_totale,"w")) == NULL)
                {
                    printf("\nERRORE SCRITTURA FILE\n");
                    return 0;
                }
                //Scrivo nel file i totali
                fprintf(fp, "Numero totale di prodotti: %d\n", TOT_prodotti);
                fprintf(fp, "Numero totale di prodotti sotto la soglia: %d\n", totale_prodotti_soglia);
                //Chiudo il file
                fclose(fp);
                //Se non e\' mai stata usata funzione di soglia la uso per avere i prodotti sotto la soglia di default
                printf("Numero totale di prodotti: %d\n", TOT_prodotti);
                printf("Numero totale di prodotti sotto la soglia: %d\n", totale_prodotti_soglia);

                
                //Messaggio finale
                printf("\nBye Bye!\n");
                return 0;
            }
        }while(scelta <= 7 && scelta >= 0);
    }
}


//Funzione che prende come parametri il puntatore alla lista dei prodotti, un intero che definira\' il codice del prodotto, una stringa che definira\' il nome del prodotto, un float che definira\' il prezzo del prodotto, un intero che definira\' la quantita\' del prodotto. La funzione e\' una void e ha come compito quello di inserire i prodotti letti da file nel main dentro la lista
void crea_l(prodPtr *ptr, int code, char name[], float price, int quantity)
{
    //creo il puntatore che puntera\' al prodotto in inserimento e alloco lo spazio di memoria necessario per contenere la struttura prodotto
    prodPtr newPtr = malloc(sizeof(prodotto));
    //controllo se ho ancora spazio in memoria
    if(newPtr != NULL)
    {
        //assegno la quantità che ho letto da file al puntatore newPtr che punta alla variabile quantità della struttura
        newPtr->quantita = quantity;
        //assegno il nome che ho letto da file al puntatore newPtr che punta alla stringa nome della struttura
        strcpy(newPtr->nome, name);
        //assegno il codice che ho letto da file al puntatore newPtr che punta alla variabile codice della struttura
        newPtr->codice = code;
        //assegno il prezzo che ho letto da file al puntatore newPtr che punta alla variabile prezzo della struttura
        newPtr->prezzo = price;
        //assegno il puntatore che punta al successivo elemento della lista a NULL
        newPtr->next = NULL;
        //creo i puntatori precPtr e corrPtr che mi servono per inserire un nodo all'intero della lista
        prodPtr precPtr = NULL;
        prodPtr corrPtr = *ptr; //assegno il puntatore alla lista a corrPtr
        //ciclo finche\' corrPtr non e\' uguale a NULL, e finche\' non trovo un prodotto il cui codice e\' maggiore di quello in inserimento (inserimento in ordine crescente per codice)
        while(corrPtr != NULL && code > corrPtr->codice)
        {
            //assegno corrPtr al precPtr
            precPtr = corrPtr;
            //scorro la lista con corrPtr
            corrPtr = corrPtr->next;
        }
        //inserimento in testa alla lista
        if(precPtr == NULL)
        {
            newPtr->next = *ptr;
            *ptr = newPtr;
        }
        //inserimento in mezzo alla lista
        else
        {
            precPtr->next = newPtr;
            newPtr->next = corrPtr;
        }
    }
    //else che segue l'if iniziale
    else
    {
        printf("Memoria esaurita!\n");
    }
}
//Funzione che prende come parametro il puntatore alla lista e la stampa a video
void visualizza_l(prodPtr ptr)
{
    printf("\n");
    //finche\' il puntatore non e\' uguale a NULL (fine lista)
    while(ptr != NULL)
    {
        //stampo gli elementi
        printf("%8s: %8d\t%8s: %25s\t%8s: %8.2f €\t%8s: %8d\n","codice",ptr->codice, "nome", ptr->nome, "prezzo",ptr->prezzo, "quantita\'",ptr->quantita);
        //scorro la lista
        ptr = ptr->next;
    }
    printf("\n");
}

//Funzione che conta il numero di prodotti contenuti nella lista
void contatore_prod(prodPtr Ptr)
{
    //Passo al puntatore int l\'indirizzo della variabile globale che conterrà la cardinalità dei prodotti
    int *punt = &TOT_prodotti;
    *punt = 0;
    //Finche\' il puntatore è diverso da NULL ciclo la lista e aggiungo +1 all\'int GL_totale_prodotti
    while(Ptr != NULL)
    {
        (*punt)++;
        //Assegno al puntatore l'indirizzo del prossimo nodo della lsita
        Ptr = Ptr->next;
    }
}

//Funzione che prende in ingresso il puntatore alla lista e il codice dell\'elemento che si vuole inserire. Il suo compito e\' quello di inserire un elemento nella lista
void inserisci(prodPtr *lPtr, int code)
{
     //creo il puntatore che puntera\' al prodotto in inserimento e alloco lo spazio di memoria necessario per contenere la struttura prodotto
    prodPtr newPtr = malloc(sizeof(prodotto));
    //controllo se ho ancora spazio in memoria
    if (newPtr != NULL)
    {
        //creo i puntatori precPtr e corrPtr che mi servono per inserire un nodo all\'intero della lista
        prodPtr precPtr = NULL;
        prodPtr corrPtr = *lPtr; //assegno il puntatore alla lista a corrPtr
        //ciclo finche\' corrPtr non e\' uguale a NULL per controllare se l\'elemento da inserire e\' gia presente
        while (corrPtr != NULL)
        {
            //se e\' presente all'interno della lista, chiudo la funzione
            if(code == corrPtr->codice)
            {
                printf("\nIl prodotto e' gia' presente nella lista.\n");
                return;
            }
            corrPtr = corrPtr->next;
        }
        //riassegno il puntatore corrente al puntatore che punta al primo prodotto della lista
        corrPtr = *lPtr;
        //ciclo finchè corrPtr non e\' uguale a NULL, e finche\' non trovo un prodotto il cui codice e\' maggiore di quello in inserimento (inserimento in ordine crescente per codice)
        while (corrPtr != NULL && code > corrPtr->codice)
        {
            //assegno correntePtr al precedentePtr
            precPtr = corrPtr;
            //scorro la lista con correntePtr
            corrPtr = corrPtr->next;
        }
        //stringa temporanea per leggere da input il nome del prodotto
        char tmp_nome[DIM];
        //char temporaneo per la pulizio del buffer
        char tmp_c;
        //float temporaneo per leggere in input il prezzo
        float tmp_prezzo;
        //int temporaneo per leggere in input la quantita\'
        int tmp_quantita;
        //Inserimento nome, prezzo, quantita\' del prodotto con controllo
        printf("Inserisci nome del prodotto:\n");
        scanf("%c", &tmp_c); //tmp_char per pulire il buffer
        scanf("%[^\n]", tmp_nome);
    
        printf("Inserisci prezzo del prodotto:\n");
        while(scanf("%f", &tmp_prezzo) != 1 || tmp_prezzo < 0)
        {
            printf("Prezzo errato!\n");
            scanf("%*[^\n]%*c");
        }
        printf("Inserisci quantita\' del prodotto:\n");
        while(scanf("%d", &tmp_quantita) != 1 || tmp_quantita < 0)
        {
            printf("Quantità errata!\n");
            scanf("%*[^\n]%*c");
        }
        //assegno codice, nome, prezzo e quantita\' alla struttura prodotto allocata puntata dal nuovo puntatore
        newPtr->codice = code;
        newPtr->prezzo = tmp_prezzo;
        newPtr->quantita = tmp_quantita;
        strcpy(newPtr->nome, tmp_nome);
        newPtr->next = NULL;
        // inserimento all\'inizio della lista
        if (precPtr == NULL)
        {
            newPtr->next = *lPtr;
            *lPtr = newPtr;
        }
        //inserimento in mezzo alla lista
        else
        {
            precPtr->next = newPtr;
            newPtr->next = corrPtr;
        }
        //incremento il numero totale dei prodotti presenti in lista
        TOT_prodotti++;
        //stampa del prodotto inserito
        printf("Dettagli del prodotto inserito:\n");
        printf("%8s: %8d\t%8s: %25s\t%8s: %8.2f €\t%8s: %8d\n","codice", newPtr->codice, "nome", newPtr->nome, "prezzo",newPtr->prezzo, "quantita\'",newPtr->quantita);
    }
    else
    {
        puts("Memoria esaurita");
    }
}
//Funzione che prende in ingresso il puntatore alla lista e il codice dell'elemento che si vuole eliminare. Il suo compito e\' quello di eliminare un elemento nella lista
void elimina(prodPtr *lPtr, int code)
{
    //se il codice inserito e\' il primo presente nella lista, si elimina il primo prodotto
    if (code == (*lPtr)->codice)
    {
        //stampa prodotto eliminato
        printf("Dettagli del prodotto eliminato:\n");
        printf("%8s: %8d\t%8s: %25s\t%8s: %8.2f €\t%8s: %8d\n","codice", (*lPtr)->codice, "nome", (*lPtr)->nome, "prezzo", (*lPtr)->prezzo, "quantita\'", (*lPtr)->quantita);
        //si assegna il puntatore che punta all\'elemento da eliminare ad un puntatore temporaneo
        prodPtr tempPtr = *lPtr;
        //si fa scorrere il puntatore
        *lPtr = (*lPtr)->next;
        //si elimina il prodotto puntato dal temporaneo
        free(tempPtr);
        //decremento il numero dei prodotti presenti nella lista
        TOT_prodotti--;
    }
    //eliminazione di uno degli altri prodotti presenti nella lista
    else
    {
        //creo e assegno precPtr al puntatore al primo elemento della lista
        prodPtr precPtr = *lPtr;
        //creo e assegno corrPtr all\'elemento successivo della lista
        prodPtr corrPtr = (*lPtr)->next;
        //ciclo finche\' corrPtr non e\' uguale a NULL, e finche\' non trovo il prodotto da eliminare
        while (corrPtr != NULL && corrPtr->codice != code)
        {
            //assegno corrPtr al precPtr
            precPtr = corrPtr;
            //scorro la lista con corrPtr
            corrPtr = corrPtr->next;
        }
        //se il puntatore e\' diverso da null, procedo ad eliminare dalla lista il prodotto selezionato come ho fatto con il primo
        if (corrPtr != NULL)
        {
            prodPtr tempPtr = corrPtr;
            //stampa prodotto eliminato
            printf("Dettagli del prodotto eliminato:\n");
            printf("%8s: %8d\t%8s: %25s\t%8s: %8.2f €\t%8s: %8d\n","codice", corrPtr->codice, "nome", corrPtr->nome, "prezzo",corrPtr->prezzo, "quantita\'",corrPtr->quantita);
            precPtr->next = corrPtr->next;
            free(tempPtr);
            TOT_prodotti--;
        }
        //altrimenti, il codice del prodotto non è presente nella lista
        else
        {
            printf("Codice non presente nell'elenco!\n");
        }
    }
}
//funzione che prende in ingresso il puntatore al primo elemento della lista e il codice da ricercare. Il suo compito e\' quello di cercare e stampare un elemento dalla lista tramite codice
void ricerca(prodPtr *lPtr, int code)
{
    //inizializzo un puntatore searchPtr e lo assegno al puntatore che punta al primo elemento della lista
    prodPtr searchPtr = *lPtr;
    //se il codice inserito identifica il primo prodotto della lista
    if (code == searchPtr->codice)
    {
        //stampo i dati del prodotto
        printf("%8s: %8d\t%8s: %10s\t%8s: %8.2f €\t%8s: %8d\n","codice",searchPtr->codice, "nome", searchPtr->nome, "prezzo",searchPtr->prezzo, "quantita\'",searchPtr->quantita);
    }
    //altrimenti
    else
    {
        //scorro la lista finche\' non trovo il codice inserito o finche\' la lista non termina
        while (searchPtr != NULL && searchPtr->codice != code)
        {
            //scorro
            searchPtr = searchPtr->next;
        }
        
        //se il puntatore e\' diverso da null
        if (searchPtr != NULL)
        {
            //stampo i dati del prodotto
            printf("Dettagli del prodotto cercato:\n");
            printf("%8s: %8d\t%8s: %10s\t%8s: %8.2f €\t%8s: %8d\n","codice",searchPtr->codice, "nome", searchPtr->nome, "prezzo",searchPtr->prezzo, "quantita\'",searchPtr->quantita);
        }
        //altrimenti il prodotto non e\' presente nella lista
        else
        {
            printf("Prodotto non presente nell'elenco!\n");
        }
    }
}


//Funzione che prende in ingresso il puntatore che punta al primo elemento della lista e il codice del prodotto di cui si vuole modificare la quantita\'
void variazione_q(prodPtr *lPtr, int code)
{
    //creo un puntatore qPtr e gli assegno il puntatore al primo elemento della lista
    prodPtr qPtr = *lPtr;
    //se il codice inserito e\' il primo
    if (code == qPtr->codice)
    {
        //input con controllo della nuova quantità
        printf("Inserisci la nuova quantita\':\n");
        while(scanf("%d", &qPtr->quantita) != 1 || qPtr->quantita < 0)
        {
            printf("Quantità errata!\n");
            scanf("%*[^\n]%*c");
        }
        printf("Dettagli del prodotto modificato:\n");
        printf("%8s: %8d\t%8s: %25s\t%8s: %8.2f €\t%8s: %8d\n","codice", qPtr->codice, "nome", qPtr->nome, "prezzo", qPtr->prezzo, "quantita\'", qPtr->quantita);
    }
    //altrimenti
    else
    {
        //scorro la lista finche\' non trovo il codice inserito o finche\' non finisco di scorrerla
        while (qPtr != NULL && qPtr->codice != code)
        {
            qPtr = qPtr->next;
        }
        
        //se il puntatore non e\' uguale a null
        if (qPtr != NULL)
        {
            //input nuova quantità con controllo
            printf("Inserisci la nuova quantita\':\n");
            while(scanf("%d", &qPtr->quantita) != 1 || qPtr->quantita < 0)
            {
                printf("Quantita\' errata!\n");
                scanf("%*[^\n]%*c");
            }
            printf("Dettagli del prodotto modificato:\n");
            printf("%8s: %8d\t%8s: %25s\t%8s: %8.2f €\t%8s: %8d\n","codice", qPtr->codice, "nome", qPtr->nome, "prezzo", qPtr->prezzo, "quantita\'", qPtr->quantita);
        }
        //altrimenti significa che non ho trovato il prodotto all'interno della lista
        else
        {
            printf("Prodotto non presente nell'elenco!\n");
        }
    }
}

//funzione che prende in ingresso il puntatore che punta al primo elemento della lista e il codice del prodotto di cui si vuole modificare il prezzo
void variazione_p(prodPtr *lPtr, int code)
{
    //creo pPtr e gli assegno il puntatore al primo elemento della lista
    prodPtr pPtr = *lPtr;
    //se il codice inserito identifica il primo elemento della lista
    if (code == pPtr->codice)
    {
        //input del nuovo prezzo con controllo
        printf("Inserisci il nuovo prezzo:\n");
        while(scanf("%f", &pPtr->prezzo) != 1 || pPtr->prezzo < 0)
        {
            printf("Prezzo errato!\n");
            scanf("%*[^\n]%*c");
        }
        //stampa dettagli prodotto modificato
        printf("Dettagli del prodotto modificato:\n");
        printf("%8s: %8d\t%8s: %25s\t%8s: %8.2f €\t%8s: %8d\n","codice", pPtr->codice, "nome", pPtr->nome, "prezzo", pPtr->prezzo, "quantita\'", pPtr->quantita);
    }
    //altrimenti
    else
    {
        //scorro la lista finche\' non trovo il codice del prodotto di cui modificare il prezzo o finche\' la lista non termina
        while (pPtr != NULL && pPtr->codice != code)
        {
            //scorro
            pPtr = pPtr->next;
        }
        //se il puntatore e\' diverso da NULL
        if (pPtr != NULL)
        {
            //input con controllo del nuovo prezzo
            printf("Inserisci il nuovo prezzo:\n");
            while(scanf("%f", &pPtr->prezzo) != 1 || pPtr->prezzo < 0)
            {
                printf("Prezzo errato!\n");
                scanf("%*[^\n]%*c");
            }
            //stampa dettagli prodotto modificato
            printf("Dettagli del prodotto modificato:\n");
            printf("%8s: %8d\t%8s: %25s\t%8s: %8.2f €\t%8s: %8d\n","codice", pPtr->codice, "nome", pPtr->nome, "prezzo", pPtr->prezzo, "quantita\'", pPtr->quantita);
        }
        //altrimenti significa che non ho trovato il codice del prodotto
        else
        {
            printf("Prodotto non presente nell'elenco!\n");
        }
    }
}

//Funzione ricorsiva che stampa i prodotti con quantità inferiore alla soglia data (10 di base) con ordine di id decrescente
void print_l_reverse(prodPtr *lPtr, int soglia)
{
    //Dichiaro un puntatore alla lista e gli passo la testa
    prodPtr rPtr = *lPtr;
    if(rPtr == NULL)
    {   //Se il puntatore e\' nullo fine della ricorsione
        return;
    }
    //Se il puntatore non e\' nullo chiamo di nuovo la funzione (arrivo fino a fine lista)
    print_l_reverse(&rPtr -> next, soglia);

    //Se il prodotto attuale ha quantita inferiore alla soglia stampo i suoi dati.
    if((rPtr->quantita) < soglia)
    {
        printf("%8s: %8d\t%8s: %10s\t%8s: %8.2f €\t%8s: %8d\n","codice",rPtr->codice, "nome", rPtr->nome, "prezzo",rPtr->prezzo, "quantita\'",rPtr->quantita);
    }
}
