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
		int len;
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


	public:

		MaxBinaryHeap(int size) {
			A = new H[size];
			len = size;
			heapsize = 0;
			chiamateheap = 0;
		}

		H extractMax() {
			if(heapsize==0) return -1;
			scambia(1, heapsize);
			heapsize--;
			heapify(1);
			return A[heapsize+1];
		}

		MaxBinaryHeap<H>* enqueue(H x) {
			heapsize += 1;
			A[heapsize] = x;
			int i = heapsize;
			while(i>1 && A[i]>A[parent(i)]) {
				scambia(i, parent(i));
				i = parent(i);
			}
			return this;
		}

		int size() {
			return heapsize;
		}

		void print(ostream& out) {
		    out<<chiamateheap<<" ";
			for(int i=1; i<=heapsize; i++)
				out << A[i] << " ";
			out << endl;
		}
};


int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N;
	string tipo,op;

	for(int i=0;i<100;i++)
    {
        in>>tipo>>N;
        if(tipo=="int")
        {
            MaxBinaryHeap<int> *m=new MaxBinaryHeap<int>(N);
            for(int j=0;j<N;j++)
            {
                in>>op;
                if(op=="extract")
                    m->extractMax();
                else
                {
                    stringstream ss(op.substr(2));
                    int n;
                    ss>>n;
                    m->enqueue(n);
                }
            }
            m->print(out);
        }

        if(tipo=="double")
        {
            MaxBinaryHeap<double> *m=new MaxBinaryHeap<double>(N);
            for(int j=0;j<N;j++)
            {
                in>>op;
                if(op=="extract")
                    m->extractMax();
                else
                {
                    stringstream ss(op.substr(2));
                    double n;
                    ss>>n;
                    m->enqueue(n);
                }
            }
            m->print(out);
        }

        if(tipo=="bool")
        {
            MaxBinaryHeap<bool> *m=new MaxBinaryHeap<bool>(N);
            for(int j=0;j<N;j++)
            {
                in>>op;
                if(op=="extract")
                    m->extractMax();
                else
                {
                    stringstream ss(op.substr(2));
                    bool n;
                    ss>>n;
                    m->enqueue(n);
                }
            }
            m->print(out);
        }

        if(tipo=="char")
        {
            MaxBinaryHeap<char> *m=new MaxBinaryHeap<char>(N);
            for(int j=0;j<N;j++)
            {
                in>>op;
                if(op=="extract")
                    m->extractMax();
                else
                {
                    stringstream ss(op.substr(2));
                    char n;
                    ss>>n;
                    m->enqueue(n);
                }
            }
            m->print(out);
        }
    }



	in.close();
	out.close();
}
