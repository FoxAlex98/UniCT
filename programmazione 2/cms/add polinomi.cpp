#include<iostream>
#include<fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class Monomio{
public:
    int coeff,esp;
    Monomio *succ;

    Monomio(int coeff,int esp,Monomio *succ)
    {
        this->coeff=coeff;
        this->esp=esp;
        this->succ=succ;
    }
};


class Polinomio{
private:
    Monomio *head=NULL;

public:

    Polinomio()
    {
        head=NULL;
    }

    Polinomio* inserimento (int c,int e)
    {
        Monomio *temp;
        if(head==NULL)
            head=new Monomio(c,e,NULL);
        else{
                temp=head;
                while(temp->succ!=NULL)
                    {temp=temp->succ;}
                temp->succ=new Monomio( c,e,NULL);
            }
            return this;
    }

     void stampa(ostream& fout)
     {
        Monomio * temp=head;
        bool flag=false;
        while(temp!=NULL)
        {
            if(flag && temp->coeff>0 && temp->coeff!=1)
            {fout<<'+';}

            if(abs(temp->coeff)==1 )
            {
                if(temp->coeff>0 && flag )
                    fout<<'+';
                else if (temp->coeff<0)
                    fout<<'-';
                if(temp->esp==0)
                    fout<<1;
            }
            if(abs(temp->coeff)!=1)
                fout<<temp->coeff;
            if(temp->esp==1 )
                {fout<<'x';}
            else if(temp->esp>0)
                fout<<'x'<<'^'<<temp->esp;

            flag=true;
            temp=temp->succ;
        }
        fout<<endl;
    }


        Polinomio* operator+(const Polinomio p1)
        {
            Monomio *temp=head;
            Monomio *temp1=p1.head;
            Polinomio *p=new Polinomio();
            int valori[20]={0};

            while(temp!=NULL)
                {
                    valori[temp->esp]+=temp->coeff;
                    temp=temp->succ;
                }
             while(temp1!=NULL)
                {
                    valori[temp1->esp]+=temp1->coeff;
                    temp1=temp1->succ;
                }

                for(int i=19;i>=0;i--)
                    {
                        if(valori[i]!=0)
                        p->inserimento(valori[i],i);
                    }

            return p;
        }


};

void converti(Polinomio  *p ,int n ,string tps,char *Op,int &l,ifstream& fin);


int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n;
    string tps;
    for(int i=0;i<100;i++)
        {
            fin>>n;
            char Op[n-1];
            int l=0;
            tps="1";
            //cout<<"Task : "<<i+1<<endl;
            Polinomio *p[n];
            Polinomio *Tp[n];

                for(int q=0;q<n;q++)
                    {
                        p[q]=new Polinomio();
                    }
                 for(int q=0;q<n;q++)
                    {
                        converti(p[q],n,tps,Op,l,fin);
                    }
                for(int z=0;z<n;z++)
                    {
                        if(Op[z]=='*' )
                        {
                            p[z]=(*p[z])+(*p[z+1]);
                            if(z<n-2)
                            {
                                for(int t=z;t<n;t++)
                                    {
                                        p[t+1]=p[t+2];
                                    }
                                Op[z]=Op[z+1];
                            }
                            n--;
                        }
                    }
                 for(int z=0;z<n-1;z++)
                    {
                        p[z+1]=(*p[z])+(*p[z+1]);
                    }
                    p[n-1]->stampa(fout);
            }
            fin.close();
            fout.close();
            return 0 ;

            };



void converti(Polinomio  *p ,int n ,string tps ,char *Op,int &q,ifstream& fin)
    {
        int tcn=0,ten=0;
        string tc="0",te,ts,s;
        char c;
        fin>>c>>s;

        if(c!='(')
            {
                Op[q]=c;
                q++;
            }

        s=c+s;
        tc="0";
        ts="1";
        int co=0;

        while(s[co]!=')')
        {
         te="0";
         if(c=='-')
            tps="-1";
         if(s[co]=='-' && co!=0)
            ts="-1";
         if(s[co]=='+')
            ts="1";

         while(s[co+1]>47 && s[co+1]<59 && s[co]!='^')
            {
                tc+=s[co+1];
                co++;
            }

            tcn=stoi(tc);

            if(s[co]=='x' && !(s[co-1]>47 && s[co-1]<59))
                tc="1";

            if(s[co]=='x' && s[co+1]!='^')
            {
                te="1";
                ten=stoi(te);
                tcn=stoi(tc);
                p->inserimento(stoi(tps)*stoi(ts)*tcn,ten);
                tcn=ten=0;
                tc=te="0";
            }

            if(s[co]=='^')
            {
                while(s[co+1]>47 && s[co+1]<59)
                {
                    te+=s[co+1];
                    ten=stoi(te);
                    tcn=stoi(tc);
                    co++;
                }
            p->inserimento(stoi(tps)*stoi(ts)*tcn,ten);
            tcn=ten=0;
            tc=te="0";
            }

            if(s[co+1]==')'&& tcn!=0)
            p->inserimento(stoi(tps)*stoi(ts)*tcn,ten);
            co++;
        }
    }
