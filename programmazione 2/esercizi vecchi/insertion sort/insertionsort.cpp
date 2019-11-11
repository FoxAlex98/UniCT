#include<iostream>
#include<fstream>

using namespace std;

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  for(int z=0;z<10;z++)
  {
      int N,conta=0, i, temp, j;
      in>>N;
      int A[N];
      for(int g=0;g<N;g++)
        in>>A[g];

       for (i = 1; i < N; i++)
       {
       temp = A[i];
       j = i-1;
       while (j >= 0 && A[j] > temp)
       {
           A[j+1] = A[j];
           conta++;
           j = j-1;
       }
       A[j+1] = temp;
       }
       out<<conta<<endl;
  }

  in.close();
  out.close();
  return 0;
}
