#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <math.h>
using namespace std;


template <class H> class MaxBinaryHeap{
	private:
		H *A;//è meglio usare un array di puntatori per il fatto del NULL
		int heapsize;
		int chiamateheap;
		int len;
		int left(int i) { return i<<1; }
		int right(int i) { return (i<<1)|1; }
		int parent(int i) { return i>>1; }

		void scambia(int i, int j) {
			H tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}


		void heapify(int i) {
			if(i<0 || i>heapsize) return;
			chiamateheap++;
			int l = left(i);
			int r = right(i);
			int max = i;
			if(l<=heapsize && A[max]<A[l]) max=l;//l'errore era qui perchè sforava
			if(r<=heapsize && A[max]<A[r]) max=r;
			if(max==i) return;
			scambia(i,max);
			heapify(max);
		}


	public:

		MaxBinaryHeap(H* v,int size) {
			A=v;
			heapsize = size;
			chiamateheap=0;
		}

		H extractMax() {
			if(heapsize==0) return -1;
			scambia(1, heapsize);
			heapsize--;
			heapify(1);
			return A[heapsize+1];
		}

		void buildheap()
		{
		    for(int i=floor(heapsize/2);i>0;i--)
                heapify(i);
		}

		void print(ostream& out) {
			out<<chiamateheap<<endl;
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
			m->buildheap();
			for(int j=0; j<N; j++)
                m->extractMax();
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
			m->buildheap();
			for(int j=0; j<N; j++)
                m->extractMax();
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
			m->buildheap();
			for(int j=0; j<N; j++)
                m->extractMax();
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
			m->buildheap();
			for(int j=0; j<N; j++)
                m->extractMax();
            m->print(out);
        }
    }

	in.close();
	out.close();
}
