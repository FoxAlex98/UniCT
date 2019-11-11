#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int zaino(int *oggetti, int spazio, int N)
{
    int s=0;
    int *v=oggetti;

    for(int i=0;i<spazio;i++)
    {
      int max=0;
      for(int j=1;j<N;j++)
      {
          if(v[j]>v[max])
            max=j;
      }
      s+=v[max];
      v[max]=0;
    }


    return s;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i=0;i<100;i++)
    {
        int N,S;
        in>>N>>S;
        int *v=new int[N];
        for(int j=0;j<N;j++)
            in>>v[j];
        out<<zaino(v,S,N)<<endl;
    }

    in.close();
    out.close();
}
