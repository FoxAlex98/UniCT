#include<iostream>
#include<cstdlib>
#include<fstream>

using namespace std;

template <class F> class Nodo{
private:
    F key;
    Nodo *next;
public:

    Nodo()
    {
        key=-1;
        next=NULL;
    }

    Nodo(F key)
    {
        this->key=key;
        next=NULL;
    }

    void setNext(Nodo* next)
    {
        this->next=next;
    }

    Nodo* getNext()
    {
        return next;
    }

    void setKey(F key)
    {
        this->key=key;
    }

    F getKey()
    {
        return key;
    }
};

template <class H> class Lista{
private:
    Nodo<H> *head;
    Lista *next;
    H id;
public:
    Lista()
    {
        head=new Nodo<H>();
        next=NULL;
        id=-1;
    }

    Lista(H id)
    {
        head=new Nodo<H>();
        next=NULL;
        this->id=id;
    }

    void setNext(Lista* next)
    {
        this->next=next;
    }

    Lista* getNext()
    {
        return next;
    }

    void setId(H id)
    {
        this->id=id;
    }

    H getId()
    {
        return id;
    }

    void insert(H key)
    {
        Nodo<H> *n=new Nodo<H>(key);//crea il nuovo nodo
        if(head->getNext()==NULL)//se non c'è niente nella lista
        {
            head->setNext(n);//fa un inserimento normale
        }
        else
        {
            Nodo<H> *tmp=head;//creiamo un nodo per scorrere
            while((tmp->getNext()!=NULL)&&(tmp->getNext()->getKey()<key))//finchè non arriviamo alla fine o al nodo con la chiave maggiore della chiave
                    tmp=tmp->getNext();//scorriamo
                    if(tmp->getNext()==NULL)//se siamo arrivati alla fine
                        tmp->setNext(n);//inseriamo normalmente
                    else
                    {
                        n->setNext(tmp->getNext());//altrimenti n punta al successivo
                        tmp->setNext(n);//tmp punta a n
                    }
        }
    }

    void stampa(ostream& out)
    {
        Nodo<H> *tmp=head->getNext();//stampiamo il tutto a partire dalla posizione dopo la testa
                out<<"("<<getId();
                while(tmp!=NULL)
                {
                    out<<","<<tmp->getKey();
                    tmp=tmp->getNext();
                }
                out<<") ";
    }
};


template <class T> class Grafo{
private:
    Lista<T> *testa;
public:
    Grafo()
    {
        testa=new Lista<T>();
    }

    void ins(T id)
    {
        Lista<T> *l=new Lista<T>(id);
        if(testa->getNext()==NULL)//se non c'è niente nella lista
        {
            testa->setNext(l);//fa un inserimento normale
        }
        else
        {
            Lista<T> *tmp=testa;//creiamo un nodo per scorrere
            while((tmp->getNext()!=NULL)&&(tmp->getNext()->getId()<id))//finchè non arriviamo alla fine o al nodo con la chiave maggiore della chiave
                    tmp=tmp->getNext();//scorriamo
                    if(tmp->getNext()==NULL)//se siamo arrivati alla fine
                        tmp->setNext(l);//inseriamo normalmente
                    else
                    {
                        l->setNext(tmp->getNext());//altrimenti n punta al successivo
                        tmp->setNext(l);//tmp punta a n
                    }
        }
    }

    void inserisciarco(T nodo1, T nodo2)
    {
        Lista<T> *tmp=testa;
        while((tmp->getNext()!=NULL)&&(tmp->getId()!=nodo1))
                    tmp=tmp->getNext();
                    tmp->insert(nodo2);

    }

    void stampa(ostream& out)
    {
        Lista<T> *tmp=testa->getNext();//stampiamo il tutto a partire dalla posizione dopo la testa
                while(tmp!=NULL)
                {
                    //cout<<tmp->getId()<<" "<<endl;
                    tmp->stampa(out);
                    tmp=tmp->getNext();
                }
                out<<endl;
    }
};

/*stoi(c1.substr(1))  (NUMERO diventa numero;
stoi(c2.substr(0,c2.length()))   NUMERO) diventa numero */

int main()
{
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int N,Narchi;
    string c1,c2,tipo;

    for(int k=0;k<100;k++)
    {
        in>>N>>Narchi>>tipo;
        if(tipo=="int")
        {
                int M;
                Grafo<int> *g=new Grafo<int>();
                for(int i=0;i<N;i++)
                {
                    in>>M;
                    g->ins(M);
                }
                for(int j=0;j<Narchi;j++)
                    {
                        in>>c1>>c2;
                        g->inserisciarco(stoi(c1.substr(1)),stoi(c2.substr(0,c2.length())));
                    }
                g->stampa(out);
        }
        else if(tipo=="double")
        {
                double M;
                Grafo<double> *g=new Grafo<double>();
                for(int i=0;i<N;i++)
                {
                    in>>M;
                    g->ins(M);
                }
                for(int j=0;j<Narchi;j++)
                    {
                        in>>c1>>c2;
                        g->inserisciarco(stod(c1.substr(1)),stod(c2.substr(0,c2.length())));
                    }
                g->stampa(out);
        }
        else if(tipo=="char")
        {
                char M;
                Grafo<char> *g=new Grafo<char>();
                for(int i=0;i<N;i++)
                {
                    in>>M;
                    g->ins(M);
                }
                for(int j=0;j<Narchi;j++)
                    {
                        in>>c1>>c2;
                        g->inserisciarco(c1[1],c2[0]);
                    }
                g->stampa(out);
        }

    }

    in.close();
    out.close();
}
