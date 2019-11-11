/* 	Appunti del Corso di Programmazione II (M-Z) - Docente Simone Faro
	UniversitÃ  degli Studi di Catania - Dipartimento di Matematica e Informatica
	Corso di Laurea Triennale in Informatica
*/

// QuickSort

#include <iostream>

using namespace std;

template <class T> void quicksort(T v[], int top, int bottom);
template <class T> int partition(T v[], int top, int bottom);
void scambia(int v[], int x, int y);
void stampa(int v[], int n);

template <class T> void stampa(T v[], int a, int b, T pivot)
{
    for(int i=a;i<b;i++)
        {
            cout<<v[i]<<" ";
            if(v[i]<pivot && v[i+1]>pivot)//stampa uno stacco tra una partizione e l'altra
                cout<<"    ";
        }
    cout<<endl;
}

int main () {
	int v[10] = {3,6,7,2,1,8,4,9,5,0};
	stampa(v,10);
	quicksort(v,0,9);
	stampa(v,10);
	return 0;
}

void stampa(int v[], int n)
{
    for(int i=0;i<n;i++)
        cout<<v[i]<<" ";
    cout<<endl;
}

void scambia(int v[], int x, int y)
{
    int temp=v[x];
    v[x]=v[y];
    v[y]=temp;
}

template <class T>
void quicksort(T v[], int top, int bottom) {
	int middle;
	if (top < bottom) {
		middle = partition(v, top, bottom);
		quicksort(v, top, middle);   		// sort top partition
		quicksort(v, middle+1, bottom);    	// sort bottom partition
    }
	return;
}


template <class T>
int partition(T v[], int top, int bottom) {
	T x = v[top];//scegliamo come pivot il primo elemento della partizione
	cout<<"il pivot e' "<<x<<endl;
	int i = top - 1;//i parte dall'inizio -1
    int j = bottom + 1;//j parte dalla fine +1
    do {
    	do j--;//scorriamo all'indietro
		while (x < v[j]);//finchè non troviamo un elemento più piccolo

        do i++;//scorriamo in avanti
        while (x > v[i]);//finchè non troviamo un elemento più grande

        if (i < j)//se non hanno sforato le proprie partizioni
            scambia(v, i, j);// e li scambiamo di posto
            //mettendoli nella partizione giusta
	} while (i < j);
	stampa(v,top,bottom,x);//stampa personalizzata
    return j;//j alla fine si troverà nel mezzo
}
