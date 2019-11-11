#include<iostream>
#include<fstream>

using namespace std;

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int N,M,i,j,z;

  for(int k=0;k<10;k++)
  {
      z=0;
      in>>N>>M;
      int A[N],B[M],C[N+M];
      for(i=0;i<N;i++)
      {
          in>>A[i];
      }
      for(j=0;j<M;j++)
      {
          in>>B[j];
      }
      i=j=0;
      while(i<N && j<M)
      {
          if(A[i]<B[j])
            C[z++]=A[i++];
          else
            C[z++]=B[j++];
      }
      while(i<N) C[z++]=A[i++];//per riempire il vettore dopo
      while(j<M) C[z++]=B[j++];
      for(z=0;z<N+M;z++)
        out<<C[z]<<" ";
      out<<endl;
  }

  in.close();
  out.close();
  return 0;
}
