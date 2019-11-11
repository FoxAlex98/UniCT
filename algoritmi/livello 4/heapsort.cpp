#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <math.h>
using namespace std;


template <class H> class MaxBinaryHeap{
	private:
		H *A;
		int heapsize;
		int len;//lo uso per salvare la lunghezza per poi usarlo nell'heapsort
		int chiamateheap;
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
			chiamateheap++;
			int l = left(i);
			int r = right(i);
			int max = i;
			if(l<=heapsize && A[max]<A[l]) max=l;
			if(r<=heapsize && A[max]<A[r]) max=r;
			if(max==i) return;
			scambia(i,max);
			heapify(max);
		}


		H extractMax(){//qui l'elemento non viene rimosso, ma solo spostato all'ultima posizione
            if(heapsize == 0) return -1;
            scambia(1, heapsize);//viene spostato qui
            heapsize--;
            heapify(1);//in questo modo l'elemento più alto viene portato in "cima"
            return A[heapsize+1];
        }


	public:

		MaxBinaryHeap(H* v,int size) {
			A=v;
			heapsize = size;
			len=heapsize+1;//se non metto il +1 non stampa l'ultimo elemento
			chiamateheap=0;
		}

		void buildheap()//costruiamo l'heap
		{
		    for(int i=floor(heapsize/2);i>0;i--)//chiamiamo l'heapify dalla metà sinistra perchè dalla parte destra sono delle foglie è quindi sono per definizione degli heap
                heapify(i);
		}

		void heapsort(){
            buildheap();//costruiamo l'heap
            for(int i = 1; i<len; i++)
               extractMax();//"estraiamoli" uno per volta
        }

        void print(ostream& out){

            out<<chiamateheap<<" ";

            for(int i = 1; i<len; i++)//stampiamo tutto quando heapsize è uguale a 0
                out<<A[i]<<" ";
            out<<endl;
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
			int v[N+1];
            for(int j=1;j<=N;j++)
            {
                in>>v[j];
            }
			MaxBinaryHeap<int> *m=new MaxBinaryHeap<int>(v,N);
			m->heapsort();
            m->print(out);
        }

        if(tipo=="double")
        {
			double v[N+1];
            for(int j=1;j<=N;j++)
            {
                in>>v[j];
            }
			MaxBinaryHeap<double> *m=new MaxBinaryHeap<double>(v,N);
			m->heapsort();
            m->print(out);
        }

        if(tipo=="bool")
        {
			bool v[N+1];
            for(int j=1;j<=N;j++)
            {
                in>>v[j];
            }
			MaxBinaryHeap<bool> *m=new MaxBinaryHeap<bool>(v,N);
			m->heapsort();
            m->print(out);
        }

        if(tipo=="char")
        {
			char v[N+1];
            for(int j=1;j<=N;j++)
            {
                in>>v[j];
            }
			MaxBinaryHeap<char> *m=new MaxBinaryHeap<char>(v,N);
			m->heapsort();
            m->print(out);
        }
    }

	in.close();
	out.close();
}
