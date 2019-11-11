/*programma che crea un build min heap utilizzando un array e tutti i metodi che ne conseguono
  l'input è formato da:
                        tipo numeroelementi elementi .......

  questa volta però non viene passato un array più grande come veniva fatto in MaxBinaryHeap
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <math.h>
using namespace std;


template <class H> class MinBinaryHeap{
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
			int min = i;//min è uguale a i per evitare di mettere nella riga successiva
			if(l<=heapsize && A[min]>A[l]) min=l;//questo è il punto che differisce dal build-max-heap
			if(r<=heapsize && A[min]>A[r]) min=r;//differisce anche per il fatto che qui si usa il <= invece del <
			if(min==i) return;//se si trova già nella posizione corretta siamo ad un caso base
			scambia(i,min);
			heapify(min);//applichiamo la ricorsione
		}


	public:

		MinBinaryHeap(H* v,int size) {
			A=v;//e inserisco dentro gli elementi
			heapsize = size;//heapsize adesso è quanto il numero degli elementi+1
		}

		void buildheap()//costruiamo l'heap
		{
		    for(int i=floor(heapsize/2);i>0;i--)//chiamiamo l'heapify dalla metà sinistra perchè dalla parte destra sono delle foglie è quindi sono per definizione degli heap
                heapify(i);
		}

		void print(ostream& out) {//stampiamo gli elementi
			for(int i=1; i<=heapsize; i++)//partendo dall'indice 1 visto che lo 0 non è utilizzato, ma anche qui c'è la differenza del <=
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
			int v[N+1];//a differenza del build-max-heap qui partiamo con un array più grande di 1
            for(int j=1;j<=N;j++)//j parte da uno perchè usiamo gli indici nelle operazioni, e l'indice 0 darebbe problemi
            {
                in>>v[j];
            }
			MinBinaryHeap<int> *m=new MinBinaryHeap<int>(v,N);//a differenza del build-max-heap qui passiamo N e non N+1
			m->buildheap();
            m->print(out);
        }

        if(tipo=="double")
        {
			double v[N+1];
            for(int j=1;j<=N;j++)
            {
                in>>v[j];
            }
			MinBinaryHeap<double> *m=new MinBinaryHeap<double>(v,N);
			m->buildheap();
            m->print(out);
        }

        if(tipo=="bool")
        {
			bool v[N+1];
            for(int j=1;j<=N;j++)
            {
                in>>v[j];
            }
			MinBinaryHeap<bool> *m=new MinBinaryHeap<bool>(v,N);
			m->buildheap();
            m->print(out);
        }

        if(tipo=="char")
        {
			char v[N+1];
            for(int j=1;j<=N;j++)
            {
                in>>v[j];
            }
			MinBinaryHeap<char> *m=new MinBinaryHeap<char>(v,N);
			m->buildheap();
            m->print(out);
        }
    }

	in.close();
	out.close();
}
