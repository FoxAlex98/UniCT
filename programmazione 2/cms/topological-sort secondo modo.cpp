#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<sstream>

#define BIANCO 0
#define GRIGIO 1
#define NERO 2

using namespace std;

template <class F> class Nodo
{
	private:
		F key;
		Nodo *next;
	public:
		Nodo()
		{
			key=-1;
			next=NULL;
		}

		Nodo(F key)
		{
			this->key=key;
			next=NULL;
		}

		void setKey(F key){this->key=key;}
		F getKey(){return key;}

		void setNext(Nodo *next){this->next=next;}
		Nodo* getNext(){return next;}

};

template <class H> class Pila{
private:
	Nodo<H> *head;

public:
	Pila()
	{
		head=NULL;
	}

	Pila* push(H key)
	{
		Nodo<H> *n=new Nodo<H>(key);
		if(head==NULL)
			{
				head=n;
				return this;
			}
		n->setNext(head);
		head=n;
		return this;
	}

	H pop()
	{
		if(head!=NULL)
		{
			Nodo<H> *tmp=head;
			head=head->getNext();
			H k=tmp->getKey();
			delete tmp;
			return k;
		}
		else
			{
				return (H) -1;
			}

	}

	void stampa()
	{
		Nodo<H> *tmp=head;
		while(tmp!=NULL)
		{
			cout<<tmp->getKey()<<" ";
			tmp=tmp->getNext();
		}
		cout<<endl;
	}

};

template <class T>
class Grafo
{
private:
    bool **adj;
    T *array;
    int n;

    int *color, *d, *f;
	int time;

	Pila<T> *p=new Pila<T>();

    void selectionSort(T* v, int n)
    {
        int i, j, min;
        for(i = 0; i < n-1; i++)
        {
            min = i;
            for(j = i+1; j < n; j++)
            {
                if(v[j] < v[min])
                    min = j;
            }

            swap(v[i], v[min]);
        }
}

void swap(T & left, T & right)
{
    T temp = left;
    left = right;
    right = temp;
}

public:
    Grafo(int n,T *v)
    {
        this->n=n;
        adj = new bool *[n];
        for (int i = 0; i < n; i++)
        {
            adj[i] = new bool[n]();
        }
        array = v;
        selectionSort(array,n);

        color = new int[n];

        d = new int[n];
        for(int i=0; i<n; i++)
            d[i]=0;

        f = new int[n];
        for(int i=0; i<n; i++)
            f[i]=0;

        time = 0;
    }

    Grafo<T>* inserisciArco(T a, T b)
    {
        int posA,posB;
        for(int i=0;i<n;i++)
        {
            if(array[i]==a)
                posA=i;
            if(array[i]==b)
                posB=i;
        }
        adj[posA][posB]=true;
        return this;
    }


		void topologicalsort(ostream &out) {
			//Visto che i grafi sono sempre DAG (grafo aciclico diretto), non serve fare controlli.
			DFS();//facciamo la dfs per verificare non abbia cicli e prendere i tempi in f
			int *s = new int[n];
			for(int i=0; i<n; i++) {
				out << p->pop() << " ";
			}
			out << endl;
		}


    void DFSVisit(int i) {
			color[i] = GRIGIO;
			d[i] = time++;//tempo quando è cominciata la visita del nodo i
			for (int j=0; j<n; j++) {
				if (adj[i][j]) {
					if(!color[j])
						DFSVisit(j);
				}
			}
			f[i] = time++;//tempo quando è finita la visita del nodo i
			p->push(array[i]);
			color[i] = NERO;
 		}

 		void DFS() {
			time = 0;//azzeriamo sempre all'inizio
			for(int i=0; i<n; i++){
				color[i] = BIANCO;
			}
			for(int i=0; i<n; i++)
				if(color[i]==BIANCO)
					DFSVisit(i);
		}
};



int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  for(int k=0;k<100;k++)
  {
      int N,nop;
      string tipo,arco;
      in>>N>>nop>>tipo;

      if(tipo=="int")
      {
       int *v=new int[N];
          for(int i=0;i<N;i++)
          {
              in>>v[i];
          }
       Grafo<int> *g=new Grafo<int>(N,v);
       for(int i=0;i<nop;i++)
       {
          int n1,n2;
          in>>arco;
          n1=stoi(arco.substr(1));
          in>>arco;
          n2=stoi(arco.substr(0,arco.length()-1));
          g->inserisciArco(n1,n2);
       }
       g->topologicalsort(out);
      }
      else if(tipo=="char")
      {
        char *v=new char[N];
          for(int i=0;i<N;i++)
          {
              in>>v[i];
          }
          Grafo<char> *g=new Grafo<char>(N,v);
       for(int i=0;i<nop;i++)
       {
          char c1,c2;
          in>>arco;
          c1=arco[1];

          in>>arco;
          c2=arco[0];
          g->inserisciArco(c1,c2);
       }
       g->topologicalsort(out);
      }

      else if(tipo=="double")
      {
          double *v=new double[N];
          for(int i=0;i<N;i++)
          {
              in>>v[i];
              //cout<<v[i]<<endl;
          }
          Grafo<double> *g=new Grafo<double>(N,v);

       for(int i=0;i<nop;i++)
       {
          double d1,d2;
          in>>arco;
          d1=stod(arco.substr(1));
          in>>arco;
          d2=stod(arco.substr(0,arco.length()-1));
          g->inserisciArco(d1,d2);
       }
       g->topologicalsort(out);
      }
  }

  in.close();
  out.close();
  return 0;
}

int time;

