#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<sstream>

using namespace std;

template <class T>
class Grafo
{
private:
    bool **adj;
    T *array;
    int n;

       void selectionSort(T* v, int n)
{
    // NON STABILE, IN-PLACE
    // CASO MIGLIORE: Ω(n^2), CASO MEDIO: Θ(n^2), CASO PEGGIORE: O(n^2)
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

    void stampaArchi(ostream& out)
    {
        for(int i=0;i<n;i++)
        {
            out<<"("<<array[i];
            for(int j=0;j<n;j++)
            {
                if(adj[i][j])
                    out<<","<<array[j];
            }
            out<<") ";
        }
        out<<endl;
    }

    void stampa()
    {
        for(int i=0;i<n;i++)
        {
            cout<<"v "<<array[i]<<endl;
        }
        /*
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<adj[i][j]<<" ";
            }
            cout<<endl;
        }*/
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
       g->stampaArchi(out);
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
       //g->stampa();
       g->stampaArchi(out);
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
          //g->stampa();
       for(int i=0;i<nop;i++)
       {
          double d1,d2;
          in>>arco;
          d1=stod(arco.substr(1));
          in>>arco;
          d2=stod(arco.substr(0,arco.length()-1));
          g->inserisciArco(d1,d2);
       }
       g->stampaArchi(out);
      }
  }

  in.close();
  out.close();
  return 0;
}
