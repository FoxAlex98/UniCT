#include <iostream>
#include <fstream>
using namespace std;

template <class H>
class Nodo{
    protected:
        H elemento;
        Nodo<H>* succ;
    public:
        Nodo(H el): elemento(el){
            this->succ = NULL;
        }

        //Get
        H getElemento(){return elemento;}
        Nodo<H>* getSucc(){return succ;}

        //Set
        void setSucc(Nodo<H>* succ){this->succ = succ;}
};

template <class H>
class Lista{
    protected:
        Nodo<H>* testa;
    public:
        Lista(){testa = NULL;}

        void ins(H);
        void canc(H);
        void print(ofstream&);
        int getK();
};

template <class H> void Lista<H>::ins(H x){
    Nodo<H>* nuovo = new Nodo<H>(x);

    if(testa == NULL)
        testa = nuovo;
    else if(x < testa->getElemento()){
        nuovo->setSucc(testa);
        testa = nuovo;
    }
    else{
        Nodo<H>* iter = testa;

        while(iter->getSucc() != NULL && iter->getSucc()->getElemento() < x)
            iter = iter->getSucc();
        nuovo->setSucc(iter->getSucc());
        iter->setSucc(nuovo);
    }
}

template <class H> void Lista<H>::canc(H x){
    if(testa->getElemento() == x){
        Nodo<H>* tmp = testa;
        testa = testa->getSucc();
        delete tmp;
    }
    else{
        Nodo<H>* iter = testa;

        while(iter->getSucc() != NULL && iter->getSucc()->getElemento() != x)
            iter = iter->getSucc();

        if(iter->getSucc() != NULL){
            Nodo<H>* tmp = iter->getSucc();
            iter->setSucc(tmp->getSucc());
            delete tmp;
        }
    }
}

template <class H> void Lista<H>::print(ofstream &out){
    Nodo<H>* iter = testa;

    while(iter != NULL){
        out << iter->getElemento() << " ";
        iter = iter->getSucc();
    }
}

template <class H> int Lista<H>::getK(){
    int contatore = 0;
    Nodo<H>* iter = testa;

    while(iter != NULL){
        contatore++;
        iter = iter->getSucc();
    }

    return contatore;
}

template <class H>
class NodoB{
    protected:
        Lista<H>* lista;
        NodoB<H>* succ;
    public:
        NodoB(){
            lista = new Lista<H>();
            this->succ = NULL;
        }

        //Get
        Lista<H>* getLista(){return lista;}
        NodoB<H>* getSucc(){return succ;}

        //Set
        void setSucc(NodoB<H>* succ){this->succ = succ;}
};

template <class H>
class ListaB{
    protected:
        NodoB<H>* testa;
        int k;
    public:
        ListaB(int x){
            testa = NULL;
            k = x;
        }

        void ins(H);
        void canc(H);
        void print(ofstream&);
};

template <class H> void ListaB<H>::ins(H x){
    if(testa == NULL){
        NodoB<H>* nuovo = new NodoB<H>();
        testa = nuovo;
    }
    else if(testa->getLista()->getK() >= k){
        NodoB<H>* nuovo = new NodoB<H>();
        nuovo->setSucc(testa);
        testa = nuovo;
    }

    testa->getLista()->ins(x);
}

template <class H> void ListaB<H>::canc(H x){
    NodoB<H>* iter = testa;

    while(iter != NULL){
        iter->getLista()->canc(x);

        iter = iter->getSucc();
    }


    while(testa != NULL && testa->getLista()->getK() <= 0){
        NodoB<H>* tmp = testa;
        testa = testa->getSucc();
        delete tmp->getLista();
        delete tmp;
    }
    if(testa != NULL){
        iter = testa->getSucc();
        NodoB<H>* tmp = testa;

        while(iter != NULL){
            if(iter->getLista()->getK() <= 0){
                tmp->setSucc(tmp->getSucc());
                delete iter;
                iter = tmp->getSucc();
            }
            else{
                tmp = iter;
                iter = iter->getSucc();
            }
        }
    }
}

template <class H> void ListaB<H>::print(ofstream &out){
    NodoB<H>* iter = testa;

    while(iter != NULL){
        iter->getLista()->print(out);
        iter = iter->getSucc();
    }
    out << endl;
}

int main(){


    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string type; in >> type;
        int k; in >> k;

        if(type == "int"){
            ListaB<int> t(k);
            string op; in >> op;

            while(op != "#"){
                int val; in >> val;
                if(op == "ins")
                    t.ins(val);
                else
                    t.canc(val);
                in >> op;
            }
            t.print(out);
        }
        else if(type == "double"){
            ListaB<double> t(k);
            string op; in >> op;

            while(op != "#"){
                double val; in >> val;
                if(op == "ins")
                    t.ins(val);
                else
                    t.canc(val);
                in >> op;
            }
            t.print(out);
        }
    }

}
