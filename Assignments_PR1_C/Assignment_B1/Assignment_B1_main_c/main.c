#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define DIM 20
#define DIMPATH 100

//struttura contenente l'occorrenza trovata
struct occorrenza
{
    //in particolare:
    int a_partire; //posizione di partenza dell'occorrenza(riga o colonna che sia)
    int in; //in che riga o colonna si trova l'occorrenza
    int val; //il valore dell'occorrenza
    int n_occ; //il numero di occorrenze
    struct occorrenza *next;
};
//rinominazione struttura
typedef struct occorrenza occ;
//rinominazione puntatore alla struttura
typedef occ *oPtr;

//funzione che, prendendo come parametri il puntatore alla lista, posizione di partenza dell'occorrenza, in che riga o colonna s trova l'occorrenza, il valore e il numero di occorrenze, inserisci ordinatamente all'interno della lista un nuovo nodo, allocando lo spazio della struttura su riportata
void insert(oPtr *, int, int ,int ,int);
//funzione che stampa a video le occorrenze ordinate. Prende come parametri i puntatori alla lista delle righe e delle colonne
void visualizza(oPtr *, oPtr *);
//funzione che elimina le occorrenze contate più volte poichè inutili. Prende come parametro un puntatore alla lista
void elimina_doppi(oPtr *);
//funzione che controlla se la matrice è quadrata
bool is_perfect_square(int n);


int main(int argc, const char * argv[])
{
    //puntatore alla lista contenente le occorrenze presenti nelle righe
    occ *rowPtr = NULL;
    //puntatore alla lista contenente le occorrenze presenti nelle colonne
    occ *colPtr = NULL;
    //intero temporaneo che legge gli elementi della matrice (serve solamente per contare gli elementi per verificare che la matrice sia quadrata)
    int tmp_int = 0;
    //puntatore al file
    FILE *fp;
    //apertura del file con controllo
    if((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("Impossibile aprire il file %s.", argv[1]);
        return 0;
    }
    //intero che conta il numero di elementi presenti all'interno della matrice
    int count_elem_matrix = 0;
    //leggo da file la matrice per contare di quanti elementi e\' composta
    while(fscanf(fp, "%d%*c", &tmp_int) == 1)
    {
        count_elem_matrix++;
    }
    //numero di righe/colonne della matrice
    int row_col = sqrt(count_elem_matrix);
    //definizione matrice
    int **matrice;
    //se la funzione is_perfect_square restituisce 0 oppure le righe (e colonne) della matrice sono minori o uguali a 3 il file non e\' valido
    if(is_perfect_square(count_elem_matrix) == 0 || row_col <= 3) //controllo se la matrice Ë quadrata
    {
        printf("File non valido.\n");
        return 0;
    }
    //altrimenti
    else
    {
        //alloco lo spazio per la matrice
        matrice = (int **) malloc(row_col*sizeof(int *)); //allocazione spazio righe
        for(int i = 0; i < row_col; i++)
        {
            matrice[i] = (int*) malloc(row_col*sizeof(int)); //allocazione spazio colonne
        }
        //porto il puntatore all'inizio del file
        rewind(fp);
        //inserisco i valori nella matrice
        for(int i = 0; i < row_col; ++i)
        {
            for(int j = 0; j < row_col; ++j)
            {
                fscanf(fp, "%d", &matrice[i][j]);
            }
        }
    }
    //stampa matrice
    for(int i = 0; i < row_col; ++i)
    {
        for(int j = 0; j < row_col; ++j)
        {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
    //m contiene il numero minimo di occorrenze da trovare
    int m;
    //input m con controllo (non può essere minore di 2 e maggiore della lunghezza delle righe (e colonne)
    printf("Inserire M: ");
    while(scanf("%d", &m) != 1 || m < 2 || m > row_col)
    {
        printf("Inserire un intero maggiore di 2 e minore della lunghezza delle righe (o colonne) della matrice.\n");
        while(getchar() != '\n');
    }
    //scorro la matrice per trovare le occorrenze
    //il primo for scorre le righe
    for(int i = 0 ; i < row_col; i++)
    {
        //il secondo for scorre le colonne
        for(int j = 0; j < row_col; j++)
        {
            //contiene le occorenze nella riga
            int cx = 0;
            //contiene le occorenze nella colonna
            int cy = 0;
            //conta le occorenze nella riga
            for(int x = i; x < row_col; x++)
            {
                //se due celle della matrice si equivalgono
                if(matrice[i][j] == matrice[x][j])
                {
                    //incremento l'occorrenza
                    cx++;
                }
                else
                {
                    //altrimenti impongo la condizione di uscita del ciclo
                    x = row_col;
                }
            }
            //controllo se le occorenze sono uguali o superiori al minimo m
            if(cx >= m)
            {
                //Ho trovato un'occorenza nella riga i lunga cx
                insert(&colPtr, i, j, matrice[i][j], cx);
            }
            //conta le occorenze nella colonna
            for(int y = j; y < row_col; y++)
            {
                //se due celle della matrice si equivalgono
                if(matrice[i][j] == matrice[i][y])
                {
                    //incremento l'occorrenza
                    cy++;
                }
                else
                {
                    //altrimenti impongo la condizione di uscita del ciclo
                    y = row_col;
                }
            }
            //controllo se le occorenze sono uguali o superiori al minimo m
            if(cy >= m)
            {
                //Ho trovato un occorenza nella colonna j lunga cy
                insert(&rowPtr, j, i, matrice[i][j], cy);
            }
        }
    }
    fclose(fp);
    //chiamo la funzione elimina_doppi per entrambe le liste, quella contenente le occorrenze delle righe e quella contenente le occorrenze delle colonne
    elimina_doppi(&rowPtr);
    elimina_doppi(&colPtr);
    //chiamo la funzione che stampa a video le liste
    printf("\n");
    visualizza(&rowPtr, &colPtr);
    return 0;
}

//funzione che prende un intero che rappresenta il numero di elementi presenti nella matrice e restituisce un booleano, in particolare 1 se la matrice e\' quadrata, 0 se non lo e\'
bool is_perfect_square(int n)
{
    //assegno n ad un float
    float n_float = n;
    //creo un float che conterra\' la radice quadrata del float
    float sqrt_n_float;
    //creo un int che conterra\' la radice quadrata di n
    int sqrt_n;
    //calcolo le radici quadrate
    sqrt_n_float = sqrtf(n_float);
    sqrt_n = sqrtf(n);
    //se sono uguali significa che la matrice è quadrata
    if(sqrt_n_float == sqrt_n)
    {
        return 1;
    }
    //altrimenti non lo e\'
    else
    {
        return 0;
    }
}

//funzione che, prendendo come parametri il puntatore alla lista, posizione di partenza dell'occorrenza, in che riga o colonna e trova l'occorrenza, il valore e il numero di occorrenze, inserisci ordinatamente all'interno della lista un nuovo nodo, allocando lo spazio della struttura su riportata
void insert(oPtr *ptr, int a_partire, int in, int val, int n_occ)
{
    //alloco lo spazio per un nuovo nodo
    oPtr newPtr = malloc(sizeof(occ));
    
    //se ho spazio in memoria
    if(newPtr != NULL)
    {
        //assegno alla struttura contenuta nel nuovo nodo i valori passati come parametro
        newPtr->a_partire = a_partire;
        newPtr->in = in;
        newPtr->val = val;
        newPtr->n_occ = n_occ;
        
        //creo il puntatore CORR che scorre la lista
        oPtr corrPtr = *ptr;
        //creo il puntatore PREC che segue il puntatore CORR
        oPtr precPtr = NULL;
        //finchè puntatore CORR non arriva alla fine della lista oppure, come da testo: "Ordinare la stampa dei risultati dal maggior numero di occorrenze in ordine decrescente. A numero di occorrenze identico, stampare prima le colonne e poi le righe, in ordine decrescente del numero di colonna/riga. Le occorrenze identiche di lunghezza sulla stessa riga/colonna vengono stampate in ordine crescente della posizione di partenza."
        while(corrPtr != NULL && n_occ < corrPtr->n_occ && ((n_occ != corrPtr->n_occ) || (in < corrPtr->in)) && ((n_occ != corrPtr->n_occ) || (in != corrPtr->in) || (a_partire > corrPtr->a_partire)))
        {
            //assegno PREC a CORR
            precPtr = corrPtr;
            //scorro la lista con CORR
            corrPtr = corrPtr->next;
        }
        //se PREC e\' uguale a NULL significa che la lista è vuota e devo inserire in testa
        if(precPtr == NULL)
        {
            newPtr->next = *ptr;
            *ptr = newPtr;
        }
        //altrimenti inserisco in mezzo alla lista
        else
        {
            precPtr->next = newPtr;
            newPtr->next = corrPtr;
        }
    }
    //... non ho spazio in memoria
    else
    {
        printf("MEMORIA ESAURITA!\n");
        return;
    }
}

//funzione che stampa a video le occorrenze ordinate. Prende come parametri i puntatori alla lista delle righe e delle colonne
void visualizza(oPtr *rowPtr, oPtr *colPtr)
{
    //creo due puntatori che assegno ai puntatori delle due liste (righe e colonne)
    oPtr vrowPtr = *rowPtr;
    oPtr vcolPtr = *colPtr;
    //termina quando ho ciclato tutte e due le liste
    while(vcolPtr != NULL || vrowPtr != NULL)
    {
        //se sono arrivato alla fine della lista delle colonne stampo tutta la lista delle righe
        if(vcolPtr == NULL)
        {
            while(vrowPtr != NULL)
            {
                
                printf("Ci sono %d occorrenze consecutive di %d in riga %d a partire della colonna %d\n", vrowPtr->n_occ, vrowPtr->val, vrowPtr->in, vrowPtr->a_partire);
                vrowPtr = vrowPtr->next;
            }
        }
        else
        {
            //se sono arrivato alla fine della lista delle righe stampo tutta la lista delle colonne
            if(vrowPtr == NULL)
            {
                while(vcolPtr != NULL)
                {
                    printf("Ci sono %d occorrenze consecutive di %d in colonna %d a partire della riga %d\n", vcolPtr->n_occ, vcolPtr->val, vcolPtr->in, vcolPtr->a_partire);
                    vcolPtr = vcolPtr->next;
                }
            }
            else
            {
                //se il numero di occorenze delle colonne è maggiore stampo questa e passo alla posizione successiva
                if(vcolPtr->n_occ > vrowPtr->n_occ)
                {
                    printf("Ci sono %d occorrenze consecutive di %d in colonna %d a partire della riga %d\n", vcolPtr->n_occ, vcolPtr->val, vcolPtr->in, vcolPtr->a_partire);
                    vcolPtr = vcolPtr->next;
                }
                else
                {
                    //se il numero di occorenze delle righe è maggiore stampo questa e passo alla posizione successiva
                    if(vcolPtr->n_occ < vrowPtr->n_occ)
                    {
                        printf("Ci sono %d occorrenze consecutive di %d in riga %d a partire della colonna %d\n", vrowPtr->n_occ, vrowPtr->val, vrowPtr->in, vrowPtr->a_partire);
                        vrowPtr = vrowPtr->next;
                    }
                    else
                    {
                        //se il numero di occorenze è uguale stampo le colonne
                        if(vcolPtr->n_occ == vrowPtr->n_occ)
                        {
                            printf("Ci sono %d occorrenze consecutive di %d in colonna %d a partire della riga %d\n", vcolPtr->n_occ, vcolPtr->val, vcolPtr->in, vcolPtr->a_partire);
                            vcolPtr = vcolPtr->next;
                        }
                    }
                }
            }
        }
    }
}

//funzione che elimina le occorrenze contate più volte poichè inutili. Prende come parametro un puntatore alla lista
void elimina_doppi(oPtr *ptr)
{
    //puntatore che scorro con il ciclo più esterno
    oPtr guardiaPtr = *ptr;
    //puntatore che scorre la lista e confronta con cio\' che e\' puntato da guardiaPtr
    oPtr scorrePtr = *ptr;
    //puntatore che punta al nodo precedente rispetto a scorrePtr
    oPtr precPtr = NULL;
    //puntatore che segue scorrePtr
    oPtr segueScorrePtr = NULL;
    
    //ciclo più esterno: scorro tutta la lista
    for(guardiaPtr = *ptr ;guardiaPtr != NULL; guardiaPtr = guardiaPtr->next)
    {
        //assegno il puntatore alla testa a scorrePtr
        scorrePtr = *ptr;
        //secondo ciclo: scorro la lista con segueScorrePtr
        for(segueScorrePtr = scorrePtr ; segueScorrePtr != NULL ; segueScorrePtr = segueScorrePtr->next)
        {
            //confronto la guardia con scorrePtr e finche non trovo un nodo che rispetta le seguendi condizioni
            while(scorrePtr != NULL && !(guardiaPtr->val == scorrePtr->val && guardiaPtr->n_occ > scorrePtr->n_occ && guardiaPtr->in == scorrePtr->in && guardiaPtr->a_partire < scorrePtr->a_partire))
            {
                //assegno precPtr a scorrePtr
                precPtr = scorrePtr;
                //scorro la lista con scorrePtr
                scorrePtr = scorrePtr->next;
            }
            //se scorrePtr e\' uguale a NULL significa che non ho trovato niente da eliminare, anceh segueScorrePtr e\' uguale a NULL, quindi esco dal ciclo interno, scorro la guardia e vado avanti
            if(scorrePtr == NULL)
            {
                ;
            }
            //altrimenti, ho trovato un nodo da eliminare
            else
            {
                //salto il nodo da eliminare
                precPtr->next = scorrePtr->next;
                //lo elimino
                free(scorrePtr);
                //faccio scorrere il puntatore avanti
                scorrePtr = precPtr->next;
            }
        }
    }
}
