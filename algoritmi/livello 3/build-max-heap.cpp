/*programma che crea un build max heap utilizzando un array e tutti i metodi che ne conseguono
  l'input è formato da:
                        tipo numeroelementi elementi .......
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <math.h>
using namespace std;


template <class H> class MaxBinaryHeap{
	private:
		H *A;//nonostante qui non venga usato è meglio usare un array di puntatori per il preblema del NULL in caso di dato non trovato
		int heapsize;//dimensione dell'heap
		int left(int i) { return i<<1; }//shift a sinistra  equivalente a 2*i
		int right(int i) { return (i<<1)|1; }//shift a sinistra + or(che in questo caso è come fare +1) equivalente a (2*i)+1
		int parent(int i) { return i>>1; }//shift a destra  equivalente a floor(i/2)

		void scambia(int i, int j) {//dati gli indici scambiamo gli elementi all'interno degli array
			H tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}

		void heapify(int i) {//trasforma il sottoalbero in un heap se non lo è  (è una funzione ricorsiva)
			if(i>heapsize) return;//se sforiamo la dimensione del heap (caso base)
			int l = left(i);//variabile l (left) per il "nodo" di sinistra
			int r = right(i);//variabile r (right) per il "nodo" di destra
			int max = i;//max è uguale a i per evitare di mettere nella riga successiva
			if(l<heapsize && A[max]<A[l]) max=l;//in precedenza c'era un errore qui. in pratica utilizzanzo l<=heapsize si sforava la dimensione dell'array, stessa cosa vale per r
			if(r<heapsize && A[max]<A[r]) max=r;//qui e nella riga prima, controlliamo quale tra destra e sinistra è il più grande...
			if(max==i) return;//se si trova già nella posizione corretta siamo ad un caso base
			scambia(i,max);// ...e lo scambia con la "testa" del sottoalbero
			heapify(max);//applichiamo la ricorsione
		}


	public:

		MaxBinaryHeap(H* v,int size) {//passo l'array e la dimensione+1
			A = new H[size];//creo l'array della classe
			A=v;//e inserisco dentro gli elementi
			heapsize = size;//heapsize adesso è quanto il numero degli elementi+1
		}

		void buildheap()//costruiamo l'heap
		{
		    for(int i=floor(heapsize/2);i>0;i--)//chiamiamo l'heapify dalla metà sinistra perchè dalla parte destra sono delle foglie è quindi sono per definizione degli heap
                heapify(i);
		}

		void print(ostream& out) {//stampiamo gli elementi
			for(int i=1; i<heapsize; i++)//partendo dall'indice 1 visto che lo 0 non è utilizzato
				out << A[i] << " ";
			out << endl;
		}

};

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");
	int N;
	string tipo;

	for(int i=0;i<100;i++)
    {
        in>>tipo>>N;
        if(tipo=="int")
        {
			int v[N];
            for(int j=1;j<=N;j++)//j parte da uno perchè usiamo gli indici nelle operazioni, e l'indice 0 darebbe problemi
            {
                in>>v[j];
            }
			MaxBinaryHeap<int> *m=new MaxBinaryHeap<int>(v,N+1);//creo dopo l'istanza della classe perchè prima ho bisogno dell'array pieno
			m->buildheap();
            m->print(out);
        }

        if(tipo=="double")
        {
			double v[N];
            for(int j=1;j<=N;j++)
            {
                in>>v[j];
            }
			MaxBinaryHeap<double> *m=new MaxBinaryHeap<double>(v,N+1);
			m->buildheap();
            m->print(out);
        }

        if(tipo=="bool")
        {
			bool v[N];
            for(int j=1;j<=N;j++)
            {
                in>>v[j];
            }
			MaxBinaryHeap<bool> *m=new MaxBinaryHeap<bool>(v,N+1);
			m->buildheap();
            m->print(out);
        }

        if(tipo=="char")
        {
			char v[N];
            for(int j=1;j<=N;j++)
            {
                in>>v[j];
            }
			MaxBinaryHeap<char> *m=new MaxBinaryHeap<char>(v,N+1);
			m->buildheap();
            m->print(out);
        }
    }

	in.close();
	out.close();
}
