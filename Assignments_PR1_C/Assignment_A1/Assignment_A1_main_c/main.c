#include <stdio.h>
#include <math.h>
//dimensione dei numeri in binario (32 rappresentano i bit)
#define DIM 32

//calcola e stampa un numero binario in complemento a 2 da un numero intero decimale passato come parametro
void two_s_complement(long long int);
//calcola e stampa l'opposto di un numero binario in complemento a 2 da un intero decimale passato come parametro
void binary_opposite(long long int);
//calcola e stampa l'opposto di un intero decimale passato come parametro
void decimal_opposite(long long int);


int main()
{
    
    //numero intero da passare come parametro alle funzioni
    long long int num;
    printf("Inserisci un numero intero: ");
    //input con controllo
    while(scanf("%lld", &num) != 1)
    {
        printf("Inserisci un numero intero: ");
        scanf("%*[^\n]%*c");
    }
    
    //intero in input che serve per chiamare le funzioni tramite array di puntatore a funzione
    int choice;
    //array di puntatori a funzioni (menu)
    void (*menu[3])(long long int) = {two_s_complement, decimal_opposite, binary_opposite};
    do {
        //output menù
        printf("Scegli un\'opzione:\n\t\t1) Inserisci un nuovo numero.\n\t\t2) Stampa rappresentazione in complemento a due.\n\t\t3) Calcola opposto.\n\t\t4) Stampa rappresentazione in complemento a due dell'opposto.\n\t\t5) Esci.\n");
        //input choice con controllo
        printf("Scelta: ");
        while (scanf("%d", &choice) != 1)
        {
            printf("Inserisci un numero intero: ");
            scanf("%*[^\n]%*c");
        }
        //l'array di puntatori a funzioni menu chiama la funzione selezionata
        if (choice < 5 && choice > 1)
        {
            (*menu[choice - 2])(num);
        }
        //se choice == 1, inserimento nuovo numero
        else if(choice == 1)
        {
            printf("Inserisci un numero intero: ");
            while(scanf("%lli", &num) != 1)
            {
                printf("Inserisci un numero intero: ");
                scanf("%*[^\n]%*c");
            }
        }
    
        //se choice == 5 stampa saluto, uscita dal programma
        else if(choice == 5)
        {
            printf(" Bye\n");
            return 0;
        }
    } while (choice <= 5 && choice > 0);
}

//calcola e stampa un numero binario in complemento a 2 da un numero intero decimale passato come parametro
void two_s_complement(long long int num)
{
    //output
    printf(" La rappresentazione di %lli in complemento a due (MSB) è: ", num);
    
    //definisco un array binary_num dove inseriro\' gli 0 e gli 1 che comporranno il numero in binario
    int binary_num[DIM];
    //se il numero è maggiore di 0:
    if(num >= 0)
    {
        //ciclo l'array
        for(size_t i = 0 ; i <= DIM-1 ; ++i)
        {
            //assegno 0 se il modulo del numero per 2 da resto 0
            if(num % 2 == 0)
            {
                binary_num[DIM-1-i] = 0;
            }
            //altrimenti assegno 1
            else
            {
                binary_num[DIM-1-i] = 1;
            }
            //ad ogni passata dimezzo il nuemro
            num = num / 2;
        }
    }
    //altrimenti, se il numero è negativo, calcolo il complemento a 2 del valore assoluto
    else
    {
        //cambio il segno al numero negativo
        num = -num;
        //ciclo l'array
        for(size_t i = 0 ; i <= DIM-1 ; ++i)
        {
            //assegno 0 se il modulo del numero per 2 da resto 0
            if(num % 2 == 0)
            {
                binary_num[DIM-1-i] = 0;
            }
            //altrimenti assegno 1
            else
            {
                binary_num[DIM-1-i] = 1;
            }
            //ad ogni passata dimezzo il nuemro
            num = num / 2;
        }
        //calcolo il complemento (scambio 0 e 1)
        for(size_t i = 0 ; i < DIM ; ++i)
        {
            if(binary_num[i] == 0)
            {
                binary_num[i] = 1;
            }
            else
            {
                binary_num[i] = 0;
            }
        }
        //sommo 1 al numero per completare il complemento a 2 (shift)
        for(size_t i = DIM-1 ; i >= 0 ; i--)
        {
            if(binary_num[i] == 0)
            {
                binary_num[i] = 1;
                break;
            }
            else
            {
                binary_num[i] = 0;
            }
        }

    }
    //stampa
    for(size_t i = 0 ; i < DIM ; i++)
    {
        if(i % 4 == 0)
        {
            printf(" %d", binary_num[i]);
        }
        else
        {
            printf("%d", binary_num[i]);
        }
    }
    printf("\n\n");
}


//calcola e stampa l'opposto di un numero binario in complemento a 2 da un intero decimale passato come parametro
void binary_opposite(long long int num)
{
    //output
    printf(" La rappresentazione dell'opposto di %lli in complemento a due (MSB) è: ", num);
    
    //prima trovo il numero in valore assoluto, come nella funzione two_s_complement
    //definisco un array binary_num dove inseriro\' gli 0 e gli 1 che comporranno il numero in binario
    int binary_num[DIM];
    //se il numero è maggiore di 0:
    if(num >= 0)
    {
        //ciclo l'array
        for(size_t i = 0 ; i <= DIM-1 ; ++i)
        {
            //assegno 0 se il modulo del numero per 2 da resto 0
            if(num % 2 == 0)
            {
                binary_num[DIM-1-i] = 0;
            }
            //altrimenti assegno 1
            else
            {
                binary_num[DIM-1-i] = 1;
            }
            //ad ogni passata dimezzo il nuemro
            num = num / 2;
        }
    }
    //altrimenti, se il numero è negativo, calcolo il complemento a 2 del valore assoluto
    else
    {
        //cambio il segno al numero negativo
        num = -num;
        //ciclo l'array
        for(size_t i = 0 ; i <= DIM-1 ; ++i)
        {
            //assegno 0 se il modulo del numero per 2 da resto 0
            if(num % 2 == 0)
            {
                binary_num[DIM-1-i] = 0;
            }
            //altrimenti assegno 1
            else
            {
                binary_num[DIM-1-i] = 1;
            }
            //ad ogni passata dimezzo il nuemro
            num = num / 2;
        }
        //calcolo il complemento (scambio 0 e 1)
        for(size_t i = 0 ; i < DIM ; ++i)
        {
            if(binary_num[i] == 0)
            {
                binary_num[i] = 1;
            }
            else
            {
                binary_num[i] = 0;
            }
        }
        //sommo 1 al numero per completare il complemento a 2 (shift)
        for(size_t i = DIM-1 ; i >= 0 ; i--)
        {
            if(binary_num[i] == 0)
            {
                binary_num[i] = 1;
                break;
            }
            else
            {
                binary_num[i] = 0;
            }
        }
    }
    //calcolo opposto
    //calcolo il complemento (scambio 0 e 1)
    for(size_t i = 0 ; i < DIM ; ++i)
    {
        if(binary_num[i] == 0)
        {
            binary_num[i] = 1;
        }
        else
        {
            binary_num[i] = 0;
        }
    }
    //sommo 1 al numero per completare il complemento a 2 (shift)
    for(size_t i = DIM-1 ; i >= 0 ; i--)
    {
        if(binary_num[i] == 0)
        {
            binary_num[i] = 1;
            break;
        }
        else
        {
            binary_num[i] = 0;
        }
    }    //stampa dell'opposto
    for(size_t i = 0 ; i < DIM ; i++)
    {
        if(i % 4 == 0)
        {
            printf(" %d", binary_num[i]);
        }
        else
        {
            printf("%d", binary_num[i]);
        }
    }
    printf("\n\n");
}
//calcola e stampa l'opposto di un intero decimale passato come parametro
void decimal_opposite(long long int num)
{
    //se il numero e\' uguale al minimo minore rappresentabile in complemento a due, esso e\' l'opposto di se stesso, in quanto l'intervallo rappresentabile in forma complemento a 2  e\' sbilanciato verso i negativi, proprio rispetto a questo numero. L'eccezione non annulla il funzionamento del complemento a 2
    if(num == -(pow(2,DIM)/2))
    {
        printf(" L'opposto di %lli è %lli\n", num, num);
    }
    //output
    else
    {
        printf(" L'opposto di %lli è %lli\n", num, -num);
    }
}
