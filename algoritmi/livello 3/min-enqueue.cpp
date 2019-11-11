/*programma che crea un build min heap utilizzando un array e tutti i metodi che ne conseguono
  ma usando l'enqueue al posto del buildheap e l'heapify
  l'input è formato da:
                        tipo numeroelementi elementi .......
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <math.h>
using namespace std;


template <class H> class MinBinaryHeap{
	private:
		H *A;
		int heapsize;//usiamo heapsize per indicare la dimensione del heap che cresce man mano che vengono inseriti gli elementi
		int len;//usiamo len per indicare la dimensione massima dell'heap
		int left(int i) { return i<<1; }
		int right(int i) { return (i<<1)|1; }
		int parent(int i) { return i>>1; }

		void scambia(int i, int j) {
			H tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}

		void heapify(int i) {
			if(i>heapsize) return;
			int l = left(i);
			int r = right(i);
			int min = i;
			if(l<=heapsize && A[min]>A[l]) min=l;//qui c'è la differenza tra in min e il max
			if(r<=heapsize && A[min]>A[r]) min=r;
			if(min==i) return;
			scambia(i,min);
			heapify(min);
		}


	public:

		MinBinaryHeap(int size) {
			A = new H[size];
			len = size;//len è la dimensione massima
			heapsize = 0;//heapsize parte da 0 in quanto aggiungiamo gli elementi uno alla volta e non tutti insieme
		}

		void enqueue(H x) {//inseriamo l'elemento all'interno dell'array
			heapsize += 1;//aumentiamo l'heapsize adesso perchè cosi partiamo dall'indice 1
			A[heapsize] = x;// inseriamo l'elemento usando heapsize come indice
			int i = heapsize;//partiamo sempre dalla fine
			while(i>1 && A[i]<A[parent(i)]) {//e facciamo una sorta di heapify
				scambia(i, parent(i));//lo scambiamo con il padre se è maggiore di lui
				i = parent(i);//e facciamo la stessa cosa sullo stesso che adesso è diventato padre
			}
		}

		void print(ostream& out) {
			for(int i=1; i<=heapsize; i++)
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
            MinBinaryHeap<int> *m=new MinBinaryHeap<int>(N);//possiamo crearlo prima
            int n;
            for(int j=0;j<N;j++)//non è necessario incominciare a contare da 1 qui
            {
                in>>n;
                m->enqueue(n);
            }
            m->print(out);
        }

        if(tipo=="double")
        {
            MinBinaryHeap<double> *m=new MinBinaryHeap<double>(N);
            double n;
            for(int j=0;j<N;j++)
            {
                in>>n;
                m->enqueue(n);
            }
            m->print(out);
        }

        if(tipo=="bool")
        {
            MinBinaryHeap<bool> *m=new MinBinaryHeap<bool>(N);
            bool n;
            for(int j=0;j<N;j++)
            {
                in>>n;
                m->enqueue(n);
            }
            m->print(out);
        }

        if(tipo=="char")
        {
            MinBinaryHeap<char> *m=new MinBinaryHeap<char>(N);
            char n;
            for(int j=0;j<N;j++)
            {
                in>>n;
                m->enqueue(n);
            }
            m->print(out);
        }
    }



	in.close();
	out.close();
}

