/*
questo programma contiene l'algoritmo per la gestione delle prenotazioni che permette di massimizzare il guadagno
in base a chi occupa per più tempo il posto (ad esempio un campo da calcio)
*/

#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int M[1000][1000]={0};
int S[1000];
int F[1000];

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

void stampa2(int m,int n)//stampa la matrice
{
  for(int i=0;i<=m;i++)
  {
      for(int j=0;j<=n;j++)
        cout<<" "<<M[i][j];
      cout<<endl;
  }
}

int max(int a, int b){return a>b?a:b;}

int massimizza(int *s, int *f, int n)
{
    for(int t=1;t<=f[n-1];t++)//f[n-1] dato che abbiamo ordinato l'array sarà questo il numero più alto
    {
        for(int i=1;i<=n;i++)//cominciamo da 1 perchè la prima riga e colonna devono rimanere 0
        {
            if(t<f[i-1])
                M[t][i]=M[t][i-1];
            else
                M[t][i]=max(M[t][i-1],M[s[i-1]][i-1]+(f[i-1]-s[i-1]));
        }
    }
    return M[f[n-1]][n];
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
            selectionsort(F,S,N);
            out<<massimizza(S,F,N)<<endl;
        }


    in.close();
    out.close();
}
