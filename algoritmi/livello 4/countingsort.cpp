#include<iostream>
#include<fstream>

using namespace std;


void print(int *v, int n, ostream& out)
{
    for(int i=0;i<n;i++)
        out<<v[i]<<" ";
}


void CountingSort(int *v, int n, ostream& out)
{
    int max,min;
    max=min=v[0];
    for(int i=1;i<n;i++)
    {
        if(v[i]>max)
            max=v[i];
        else if(v[i]<min)
            min=v[i];
    }
    int k=max-min+1;
    int c[k];
    for(int i=0;i<k;i++)    c[i]=0;
    for(int i=0;i<n;i++)    c[v[i]-min]++;
    for(int i=1;i<k;i++)    c[i]+=c[i-1];
    int b[n];

    for(int i=n-1;i>=0;i--)
    {
        b[c[v[i]-min]-1]=v[i];
        c[v[i]-min]--;
    }
    print(c,k,out);
    print(b,n,out);
    out<<endl;
}


int main()
{
 ifstream in("input.txt");
 ofstream out("output.txt");

 for(int i=0;i<100;i++)
 {
     int N;
     in>>N;
     int v[N];
     for(int j=0;j<N;j++)
        in>>v[j];
     CountingSort(v,N,out);
 }

 in.close();
 out.close();
}
