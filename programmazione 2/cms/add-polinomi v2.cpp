#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>

using namespace std;//non funzionante ma con idea diversa
                    //in realtà la funzione inserimento dovrebbe funzionare
class Monomio{
private:
    int coefficiente,esponente;
    Monomio *next;
public:

    Monomio(int c, int e)
    {
        coefficiente=c;
        esponente=e;
        next=NULL;
    }

    void setNext(Monomio *next)
    {
        this->next=next;
    }

    Monomio* getNext()
    {
        return next;
    }

    void segno()
    {
        coefficiente=coefficiente*(-1);
    }

    int getcof()
    {
        return coefficiente;
    }

    int getesp()
    {
        return esponente;
    }

    void stampa()
    {
        cout<<"sono un monomio con coff "<<coefficiente<<" e esponente "<<esponente<<endl;
    }
};


int trovaparti(string s, int &pos)
{
    int c=0,n;
    string str="";
    bool flag=false;

    if(s[0]=='+')
        {
            c=1;
        }
    else if(s[0]=='-')
            {
                c=1;
                flag=true;
            }
            if(s[0]=='x')
            {
                pos=c;
                return 0;
            }
    while(s[c]>47 && s[c]<58)
    {
        str+=s[c];
        c++;
    }
    n=stoi(str);
    if(flag)//cambiamo segno se prima era -
        n=n*(-1);
        pos=c;
    return n;
}

int contamonomi(string s)
{
    int i=0,contatore=0;
    if((s[0]=='+')||(s[0]=='-'))
    {
        i++;
    }
    while(i<s.length())
    {
        if((s[i]=='+')||(s[i]=='-'))
        {
            contatore++;
        }
        i++;
    }
    return contatore+1;
}

class Polinomio
{
    private:
        Monomio *inizio;
    public:

        Polinomio()
        {
            inizio=new Monomio(0,0);
            inizio->setNext(NULL);
        }



        void insert(int c, int e)
        {
            Monomio *n=new Monomio(c,e);
            if(inizio->getNext()==NULL)
            {
                inizio->setNext(n);
            }
            else
            {
                Monomio *tmp=inizio;
                while(tmp->getNext()!=NULL)
                    tmp=tmp->getNext();
                 tmp->setNext(n);
            }
        }

        Polinomio* cambiasegno()
        {
            Monomio *tmp=inizio;
            while(tmp!=NULL)
            {
                tmp->segno();
                tmp=tmp->getNext();
            }
            return this;
        }

        int* vettore()
        {
            Monomio *tmp=inizio;
            int *v=new int[20];
            while(tmp!=NULL)
            {
                v[tmp->getesp()]=tmp->getcof();
                tmp=tmp->getNext();
            }
            return v;
        }

        void stampapol()
        {
            Monomio *tmp=inizio->getNext();
            while(tmp!=NULL)
                {
                  tmp->stampa();
                  tmp=tmp->getNext();
            }
        }
    //cout<<"fatto"<<endl;
        void inserimento(string s, int numeromonomi)
        {
            int pos;
            int cof,esp;
            Polinomio *p=new Polinomio();
            cof=esp=0;
            for(int i=0;i<numeromonomi;i++)
            {
                cout<<"numero monomi "<<numeromonomi<<endl;
                cof=trovaparti(s,pos);
                if(s[pos]!='x')
                {
                    insert(cof,0);
                    s=s.substr(pos,s.length());
                }
                else if(s[pos]=='x')
                        {
                            if(s[pos+1]!='^')
                            {
                                insert(cof,1);
                                s=s.substr(pos+1,s.length());
                            }
                            else
                                {
                                    s=s.substr(pos+2,s.length());
                                    esp=trovaparti(s,pos);
                                    insert(cof,esp);
                                    s=s.substr(pos,s.length());
                                }
                        }
                        cof=esp=0;

            }
            //cout<<"fine polinomio "<<endl;
        }


};

        int* sommavettori(int* v1, int* v2)
        {
            for(int i=0;i<20;i++)
            {
                v1[i]=v1[i]+v2[i];
            }
            return v1;
        }

        Polinomio* somma(Polinomio* p1,Polinomio* p2)
        {
            int *v=new int[20];
            Polinomio *p=new Polinomio();
            v=sommavettori(p1->vettore(),p2->vettore());
            for(int i=0;i<20;i++)
            {
                if(v[i]!=0)
                {
                    p->insert(v[i],i);
                }
            }
            return p;
        }

int max(int a, int b)
{
    if(a>b)
        return a;
    else
        return b;
}

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int N;
  string s;

  for(int k=0;k<3;k++)
  {
      Polinomio *p=new Polinomio();
      Polinomio *som=new Polinomio();
      in>>N;
      for(int z=0;z<N+(N-1);z++)
      {
        in>>s;
        if(s!="+" && s!="-")
        {
            s=s.substr(1,s.length()-2);
            cout<<s<<endl;
            p->inserimento(s,contamonomi(s));
        }
      }
      p->stampapol();
      som=somma(som,p);
      som->stampapol();
  }

  in.close();
  out.close();
  return 0;
}
