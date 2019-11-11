#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;


template<class H> class Coppia{//classe coppia che si occupa della gestione delle coppie
	private:
		H a,b;// elementi della coppia
	public:

		Coppia(H a, H b)
		{
			this->a=a;
			this->b=b;
		}

		H getA(){return a;}
		H getB(){return b;}

		bool operator<(Coppia<H>& c2)//faccio l'overloading dell'operatore < che verrà usato poi nell'heapify
		{
		    //date le coppie (a1,b1) e (a2,b2) l'operatore restituirà true, se a1<a2 o se (a1=a2 e b1<b2), restituirà false altrimenti
			if(getA()<c2.getA() || (getA()==c2.getA() && (getB()<c2.getB())))
				return true;
			else
				return false;
		}

		void stampaCoppia(ostream& out)
		{
			out<<"("<<getA()<<" "<<getB()<<") ";//stampiamo le coppie con parentesi ma senza virgole interne
		}
};


template <class H> class MaxBinaryHeap{
	private:
		H **A;//sta volta uso un array di puntatori
		int heapsize;
		int len;//lo uso per salvare la lunghezza per poi usarlo nell'heapsort
		int chiamateheap;
		int left(int i) { return i<<1; }
		int right(int i) { return (i<<1)|1; }
		int parent(int i) { return i>>1; }

		void scambia(int i, int j) {
			H* tmp = A[i];//cambiamento dovuto ai puntatori
			A[i] = A[j];
			A[j] = tmp;
		}

		void heapify(int i) {
			if(i>heapsize) return;
			chiamateheap++;
			int l = left(i);
			int r = right(i);
			int max = i;
			if(l<=heapsize && *A[max]<*A[l]) max=l;//per usare l'overloading devo usare l'operatore di dereferenza
			if(r<=heapsize && *A[max]<*A[r]) max=r;
			if(max==i) return;
			scambia(i,max);
			heapify(max);
		}


		H* extractMax(){//qui l'elemento non viene rimosso, ma solo spostato all'ultima posizione
            if(heapsize == 0) return NULL;//adesso posso usare il NULL dato che sto lavorando con dei puntatori
            scambia(1, heapsize);//viene spostato qui
            heapsize--;
            heapify(1);//in questo modo l'elemento più alto viene portato in "cima"
            return A[heapsize+1];
        }


	public:

		MaxBinaryHeap(H** v,int size) {//adesso mi faccio passare dal main un array di puntatori
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
                A[i]->stampaCoppia(out);//uso la freccia perchè lavoro coi puntatori
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
			Coppia<int> **v=new Coppia<int>*[N+1];//uso un array di puntatori
            for(int j=1;j<=N;j++)
            {
            	string s1,s2;
                in>>s1>>s2;
                stringstream ss(s1.substr(1)+" "+s2.substr(0,s2.length()-1));//uso uno stringstream concatenando cosi: "s1 s2"
                int a1,a2;
                ss>>a1>>a2;//mettendo lo spazio in mezzo posso fare tutto in una sola riga

                v[j]=new Coppia<int>(a1,a2);//uso un puntatore per ogni coppia
            }
			MaxBinaryHeap<Coppia<int> > *m=new MaxBinaryHeap<Coppia<int> >(v,N);// in questo caso H=Coppia<tipo>
			m->heapsort();
            m->print(out);
        }

        if(tipo=="double")
        {
			Coppia<double> **v=new Coppia<double>*[N+1];
            for(int j=1;j<=N;j++)
            {
            	string s1,s2;
                in>>s1>>s2;
                stringstream ss(s1.substr(1)+" "+s2.substr(0,s2.length()-1));
                double a1,a2;
                ss>>a1>>a2;

                v[j]=new Coppia<double>(a1,a2);
            }
			MaxBinaryHeap<Coppia<double> > *m=new MaxBinaryHeap<Coppia<double> >(v,N);
			m->heapsort();
            m->print(out);
        }

        if(tipo=="bool")
        {
			Coppia<bool> **v=new Coppia<bool>*[N+1];
            for(int j=1;j<=N;j++)
            {
            	string s1,s2;
                in>>s1>>s2;
                stringstream ss(s1.substr(1)+" "+s2.substr(0,s2.length()-1));
                bool a1,a2;
                ss>>a1>>a2;

                v[j]=new Coppia<bool>(a1,a2);
            }
			MaxBinaryHeap<Coppia<bool> > *m=new MaxBinaryHeap<Coppia<bool> >(v,N);
			m->heapsort();
            m->print(out);
        }

        if(tipo=="char")
        {
			Coppia<char> **v=new Coppia<char>*[N+1];
            for(int j=1;j<=N;j++)
            {
            	string s1,s2;
                in>>s1>>s2;
                stringstream ss(s1.substr(1)+" "+s2.substr(0,s2.length()-1));
                char a1,a2;
                ss>>a1>>a2;

                v[j]=new Coppia<char>(a1,a2);
            }
			MaxBinaryHeap<Coppia<char> > *m=new MaxBinaryHeap<Coppia<char> >(v,N);
			m->heapsort();
            m->print(out);
        }

    }

	in.close();
	out.close();
}
