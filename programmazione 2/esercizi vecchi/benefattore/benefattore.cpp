#include<iostream>
#include<fstream>

using namespace std;

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int N,i,j,conta=0;
  float peso,temp,somma=0;

  for(int k=0;k<10;k++)
  {
      in>>peso;
      in>>N;
      conta=somma=0;
      float arr[N]={0};

      for(int z=0;z<N;z++)//acquisizione
              in>>arr[z];

       for (i = 1; i < N; i++)//ordinamento
       {
       temp = arr[i];
       j = i-1;
       while (j >= 0 && arr[j] > temp)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = temp;
       }

       do
       {
           somma+=arr[conta];
           conta++;
       }while(somma+arr[conta]<=peso);

       out<<conta<<" "<<somma<<endl;
  }


  in.close();
  out.close();
  return 0;
}
