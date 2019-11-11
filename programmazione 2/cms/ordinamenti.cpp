#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>

using namespace std;


void fusione(int *v, int sx, int cx, int dx)//uniamo i due frammenti
{
 int b[dx-sx+1];//array ausiliario della grandezza di entrambi i pezzi assieme
 int k=0;//indice per scorrere l'array ausiliario
 int i=sx;//indice per la prima parte
 int j=cx+1;//indice per la seconda parte

 while(i<=cx && j<=dx)//scorriamo contemporaneamente entrambe le parti
  {
    if(v[i]<v[j])//controlliamo gli elementi del primo pezzo e del secondo pezzo
    {
     b[k]=v[i];//salviamo prima la parte più piccola nell'array ausiliario
     i++;//e scorriamo un pezzo
    }
    else
      {
       b[k]=v[j];
       j++;//o l'altro
      }
      k++;//l'indice dell'array ausiliario scorre sempre
  }

  //a questo punto siamo arrivati alla fine di uno dei due array, ma non sappiamo quale
  while(i<=cx)//quindi scorriamoli entrambi fino alla fine
   {
    b[k]=v[i];//e salviamo gli eventuali elementi restanti
    i++,k++;
  }

  while(j<=dx)
  {
    b[k]=v[j];
    j++;k++;
  }

  int c=sx;//adesso trasferiamo il contenuto ordinato dall'array ausiliario a quello di partenza
  while(c<=dx)
    {
     v[c]=b[c-sx];//sostituiamo il tutto ogni volta dalla parte interessata e non dall'inizio
     c++;
    }

}


void mergesort(int *v, int sx, int dx)//dividiamo ricorsivamente in due parti
{
 if(sx<dx)//fino a quando sx è strettamente minore di dx
  {
   int cx=(sx+dx)/2;//calcoliamo il centro
   mergesort(v,sx,cx);//parte sinistra
   mergesort(v,cx+1,dx);//parte destra
   fusione(v,sx,cx,dx);//una volta che si arriva a questa parte si può ricostruire il tutto
  }

}

void stampa(int *v, int n)
{
  for(int i=0;i<n;i++)
    cout<<" "<<v[i];
  cout<<endl;
}

int* randomArray(int size)//restituisce un array di size posizioni
{
    int * v = new int[size];

    for(int i = 0; i < size; i++)
        v[i] = rand()%100+1;

    return v;
}


int findmin(int *v,int n,int inizio)//restituisce l'indice del minimo di un array partendo da una parte specifica (inizio)
{
	int min=v[inizio];
	int ind=inizio;
		for(int i=inizio;i<n;i++)
			{
				if(v[i]<min)
					{
						min=v[i];
						ind=i;
					}
			}
	return ind;
}

void swap(int &a, int &b)//passiamo per riferimento
{
	int tmp=a;
	a=b;
	b=tmp;
}

void selectionsort(int *v, int n)
{
	for(int i=0;i<n;i++)
		{
			int ind=findmin(v,n,i);//troviamo ogni volta il minimo della sottosequenza
			swap(v[i],v[ind]);//e lo scambiamo con l'elemento attuale
		}
}

void bubblesort(int *v,int n)
{
	for(int i=0;i<n;i++)
	{
	 for(int j=0;j<n-1;j++)//n-1 per non farlo sforare quando fa lo swap
		{
		 if(v[j]>v[j+1])
			swap(v[j],v[j+1]);
		}
		//stampa(v,n);
	}
}

void bubblesortsentinella(int *v,int n)
{
	bool flag=false;
	for(int i=0;i<n;i++)
	{
	 flag=false;
	 for(int j=0;j<n-1;j++)
		{
		 if(v[j]>v[j+1])
			{
			 swap(v[j],v[j+1]);
			 flag=true;
			}
		}
		if(!flag)//se la sentinella è rimasta falsa non si sono fatte modifiche
		break;//quindi ci possiamo fermare
	  	//stampa(v,n);
	}
}

void bubbleSortricorsivo(int arr[], int n)
{
   //caso base
    if (n == 1)
        return;

    //un passo del bubble sort, alla fine di questo passo, l'elemento più grande sarà spostato alla fine
    for (int i=0; i<n-1; i++)
        if (arr[i] > arr[i+1])
            swap(arr[i], arr[i+1]);

    //ora che l'ultimo elemento è al posto giusto chiamiamo ricorsivamente la funzione sul restante sottoarray
    bubbleSortricorsivo(arr, n-1);
}


void insertionsort(int* v, int n)
{
	for(int i=1;i<n;i++)//partiamo da 1 perchè dopo j partirà da i-1
	{
		int temp=v[i];//salviamo il valore del primo elemento
		int j=i-1;
		while(j>=0 && temp<v[j])
		{
			v[j+1]=v[j];//facciamo lo shift degli elementi a destra per fare posto al nuovo elemento
			j--;//decremento
		}
		v[j+1]=temp;
	}
}

void insertionSortRicorsivo(int* arr, int n)
{
    // caso base, se ci troviamo in un array di un elemento o meno
    if (n <= 1)
        return;

    //ordiniamo i primi n-1 elementi
    insertionSortRicorsivo( arr, n-1 );

    //inseriamo l'ultimo elemento nella sua corretta posizione nell'array ordinato
    int last = arr[n-1];
    int j = n-2;//scorriamo al solito dalla fine all'inizio

    //shiftiamo gli elementi come al solito
    while (j >= 0 && arr[j] > last)
    {
        arr[j+1] = arr[j];
        j--;
    }
    arr[j+1] = last;//e mettiamo l'elemento nella posizione giusta
}

void selectionsort_ricorsivo(int* a, int n, int index = 0)//se non scriviamo niente all'index, allora di default sarà 0
{
    //caso base quando l'indice(dell'inizio) è uguale al numero di elementi
    if (index == n)
       return;

    //troviamo l'indice del minimo del sottoarray che parte da index
    int k = findmin(a, n-1, index);

    //e scambiamo se l'indice e l'indice del minimo (k) sono diversi
    if (k != index)
       swap(a[k], a[index]);

    //chiamiamo ricorsivamente la funzione sul sottoarray che inizia dal numero successivo
    selectionsort_ricorsivo(a, n, index + 1);
}

int main()
{
 int n=15;
 int *v=randomArray(n);
 stampa(v,n);
 //insertionSortRicorsivo(v,n);
 //selectionsort_ricorsivo(v,n+1);
 //mergesort(v,0,n-1);
 //selectionsort(v,n);
 //bubblesort(v,n);
 //bubblesortsentinella(v,n);
 //bubbleSortricorsivo(v,n);
 //insertionsort(v,n);
 cout<<endl;
 stampa(v,n);
}
