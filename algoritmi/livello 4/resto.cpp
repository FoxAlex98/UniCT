#include<iostream>
#include<fstream>

using namespace std;

const int MAX=1001;//pi� alto del massimo possibile

int resto(int *m, int n, int r)//m = array di monete, n=# tagli di monete disponibili, r=resto
{
    int *resti=new int[r+1];//array di resti +1 perch� a noi interessa l'ultima posizione

    int mon;
    resti[0]=MAX;//lo zero � MAX perch� appunto non c'� resto in questo caso
    for(int i=1;i<=r;i++)//scorriamo il "resto" del vettore resti (lol)
    {
        mon=MAX;//di default � massimo
        for(int j=0;j<n;j++)//scorriamo le possibili monete
        {
            if(m[j]==i)//se la moneta � esattamente quanto il resto
                mon=1;
            else if(m[j]<i)//se la moneta � minore del resto
                mon=min(mon,resti[i-m[j]]+1);//allora sar� = al minimo tra le monete e il resto del caso del resto "restante"
        }
        resti[i]=mon;//alla fine sar� uguale al minore di tutti
    }
    return resti[r];//ritorniamo solo il finale, ovvero quello che ci interessa
}

int min(int a, int b)
{
    return a<b?a:b;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int R,N;

    for(int i=0;i<100;i++)
    {
        in>>R>>N;

        int *m=new int[N];

        for(int j=0;j<N;j++)
            in>>m[j];

        out<<resto(m,N,R)<<endl;
    }



    in.close();
    out.close();
}
