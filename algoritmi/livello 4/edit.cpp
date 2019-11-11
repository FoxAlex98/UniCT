#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int c[1000][1000];//in attesa di un altra soluzione

int min(int a,int b, int c)
{
    int tmp;
    a<b?tmp=a:tmp=b;
    return tmp<c?tmp:c;
}

int edit(string x, string y, int N, int M)
{
    for(int i=0;i<=N;i++)    c[i][0]=i;
    for(int j=0;j<=M;j++)    c[0][j]=j;

    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
          if(x[i-1]==y[j-1])
            c[i][j]=c[i-1][j-1];
          else
            c[i][j]=min(c[i-1][j],c[i][j-1],c[i-1][j-1])+1;
        }
    }

    return c[N][M];
}

/*
void print(int N, int M)
{
    for(int i=0;i<=N;i++)
        {
            for(int j=0;j<=M;j++)
                cout<<c[i][j]<<" ";
            cout<<endl;
        }
}
*/

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N,M;
    string s1,s2;

    for(int i=0;i<100;i++)
    {
        in>>N>>M;
        in>>s1>>s2;
        out<<edit(s1,s2,N,M)<<endl;
        //print(N,M);
    }


    in.close();
    out.close();
}
