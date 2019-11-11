#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int findmin(int *v,int n,int inizio)//restituisce l'indice del minimo di un array partendo da una parte specifica (inizio)
{
	int min=v[inizio];
	int ind=inizio;
		for(int i=inizio;i<n;i++)
			{
				if(v[i]<min)
					{
						min=v[i];
						ind=i;
					}
			}
	return ind;
}

void swap(int &a, int &b,int &c, int &d)//passiamo per riferimento
{
	int tmp=a;
	a=b;
	b=tmp;

	tmp=c;
	c=d;
	d=tmp;
}

void selectionsort(int *v,int *v2, int n)
{
	for(int i=0;i<n;i++)
		{
			int ind=findmin(v,n,i);//troviamo ogni volta il minimo della sottosequenza
			swap(v[i],v[ind],v2[i],v2[ind]);//e lo scambiamo con l'elemento attuale
		}
}

void stampa(int *v, int n)//stampa l'array
{
  for(int i=0;i<n;i++)
    cout<<" "<<v[i];
  cout<<endl;
}

int max(int a, int b){return a>b?a:b;}

int cardinalita(int *f, int *s, int n)
{
    int num=0;
    int end=0;
    for(int i=0;i<n;i++)//scorriamo l'array sfruttando il fatto che le attività sono ordinate in base alla fine
    {
        if(s[i]>=end)//se inizia dopo l'ultima attività finita
            {
                end=f[i];//la nuova fine è la fine di quest'attività
                num++;//aumentiamo il numero di attività compatibili (la cardinalità in questo caso)
            }
    }
    return num;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    for(int k=0;k<100;k++)
    {
        in>>N;
        int *S=new int[N];//array dell'inizio attività
        int *F=new int[N];//array della fine dell'attività

        for(int i=0;i<N;i++)
        {
            string s1,s2;
            in>>s1>>s2;
            stringstream ss(s1.substr(1)+" "+s2.substr(0,s2.length()-1));
            int a1,a2;
            ss>>a1>>a2;
            S[i]=a1;
            F[i]=a2;
        }

        //stampa(S,N);
        //stampa(F,N);
        selectionsort(F,S,N);
        //stampa(S,N);
        //stampa(F,N);
        out<<cardinalita(F,S,N)<<endl;
    }

    in.close();
    out.close();
}
