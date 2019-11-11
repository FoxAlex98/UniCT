#include<iostream>
#include<fstream>

using namespace std;

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");
  int N,Xi,Yi,Xf,Yf;
  for(int i=0;i<10;i++)
  {
      in>>N;
      int M[100][100]={0};
      int max=M[0][0];
      for(int j=0;j<N;j++)
      {
          in>>Xi>>Yi>>Xf>>Yf;
          for(int k=Yi;k<=Yf;k++)
          {
            for(int z=Xi;z<=Xf;z++)
              {
                  M[k][z]++;
                  if(M[k][z]>max)
                    max=M[k][z];
              }
          }
      }
      out<<max<<endl;
  }

  in.close();
  out.close();
  return 0;
}
