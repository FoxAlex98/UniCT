#include<iostream>
#include<fstream>

using namespace std;

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");
  int N,contapassi=0,indice;
  for(int k=0;k<3;k++)
  {
      in>>N;
      int v[N],M[N],I[N];
      contapassi=0;

      for(int i=0;i<N;i++)//acquisizione
        {
         in>>v[i];
         M[i]=v[i];
        }

      for(int i=0;i<10;i++)//ordinamento
		{
         for(int j=0;j<10;j++)
			{
             if(M[j]<M[j+1])
                {
                 int temp=M[j];
                 M[j]=M[j+1];
                 M[j+1]=temp;
                }
			}
        }



    }

  in.close();
  out.close();
  return 0;
}
