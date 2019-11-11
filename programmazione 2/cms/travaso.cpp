#include <iostream>
#include <fstream>
using namespace std;

template <class H>
class Nodo{
    protected:
        H key;
        Nodo<H>* next;
    public:
        Nodo(H key){
            this->key=key;
            this->next;
        }

        //Get
        H getKey(){return key;}
        Nodo<H>* getNext(){return next;}
        void setNext(Nodo<H>* next){this->next = next;}
};

template <class H>
class Stack{
    protected:
        Nodo<H>* head;
    public:
        Stack(){head = NULL;}

        void push(H x)
        {
            Nodo<H>* n = new Nodo<H>(x);

            n->setNext(head);//bisogna sempre settare che il successivo di n sia la testa
            head = n;//e la n è la nuova testa
        }

        H pop()
        {
            if(head != NULL){//se ci sono altri nodi
                H key = head->getKey();
                Nodo<H>* tmp = head;
                head = head->getNext();
                delete tmp;
                return key;
            }
            return -1;
        }


        bool Pilavuota(){return head == NULL;}//restituisce se la pila è vuota
};

template <class H>
class Coda{
    protected:
        Nodo<H>* head;
    public:
        Coda(){this->head = NULL;}

        void enqueue(H x)
        {
            Nodo<H>* n = new Nodo<H>(x);

            if(head == NULL)//se non c'è nulla
                head = n;
            else{
                Nodo<H>* tmp = head;

                while(tmp->getNext() != NULL)
                    tmp = tmp->getNext();

                tmp->setNext(n);//il successivo è n
            }
        }


        H dequeue(){
                    if(head != NULL)//se c'è altro a parte head
                    {
                        H key = head->getKey();//salviamo la key
                        Nodo<H>* tmp = head;//salviamo la testa attuale
                        head = head->getNext();//scorriamo
                        delete tmp;//e la cancelliamo
                        return key;
                    }
                    return (H) -1;
                   }


        void print(ofstream& out)
        {
            Nodo<H>* tmp = head;

            while(tmp != NULL){
                out << tmp->getKey() << " ";
                tmp = tmp->getNext();
            }
            out << endl;
        }
};

template <class H>
class PilaCoda{
    protected:
        Stack<H>* pila;
        Coda<H>* coda;
    public:
        PilaCoda(){
            pila = new Stack<H>();
            coda = new Coda<H>();
        }

        //Get
        Stack<H>* getPila(){return pila;}
        Coda<H>* getCoda(){return coda;}

        void Travasa()
        {
            if(!pila->Pilavuota())
            {
                while(!pila->Pilavuota()){
                    coda->enqueue(pila->pop());
                }
            }
        }
};

int getDuepunti(string x){
    for(int i = 0; i < x.length(); i++)
        if(x[i] == ':')
            return i;
    return 0;
}

string getOp(string x){
    return x.substr(0, getDuepunti(x));
}

string getVal(string x){
    return x.substr(getDuepunti(x)+1, x.length());
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string type;
        in >> type;
        int n;
        in >> n;

        if(type == "int"){
            PilaCoda<int> t;
            for(int j = 0; j < n; j++){
                string tmp;
                in >> tmp;
                if(tmp == "pop")
                    t.getPila()->pop();
                else if(tmp == "dequeue")
                    t.getCoda()->dequeue();
                else if(tmp == "travasa")
                    t.Travasa();
                else{
                    string op = getOp(tmp);
                    string _val = getVal(tmp);
                    int val = stoi(_val);

                    if(op == "p")
                        t.getPila()->push(val);
                    else if(op == "e")
                        t.getCoda()->enqueue(val);
                }
            }
            t.getCoda()->print(out);
        }
        else if(type == "bool"){
            PilaCoda<bool> t;
            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;
                if(tmp == "pop")
                    t.getPila()->pop();
                else if(tmp == "dequeue")
                    t.getCoda()->dequeue();
                else if(tmp == "travasa")
                    t.Travasa();
                else{
                    string op = getOp(tmp);
                    string _val = getVal(tmp);
                    bool val = stoi(_val);

                    if(op == "p")
                        t.getPila()->push(val);
                    else if(op == "e")
                        t.getCoda()->enqueue(val);
                }
            }
            t.getCoda()->print(out);
        }

        else if(type == "double"){
            PilaCoda<double> t;
            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;
                if(tmp == "pop")
                    t.getPila()->pop();
                else if(tmp == "dequeue")
                    t.getCoda()->dequeue();
                else if(tmp == "travasa")
                    t.Travasa();
                else{
                    string op = getOp(tmp);
                    string _val = getVal(tmp);
                    double val = stod(_val);

                    if(op == "p")
                        t.getPila()->push(val);
                    else if(op == "e")
                        t.getCoda()->enqueue(val);
                }
            }
            t.getCoda()->print(out);
        }

        else if(type == "char"){
            PilaCoda<char> t;
            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;
                if(tmp == "pop")
                    t.getPila()->pop();
                else if(tmp == "dequeue")
                    t.getCoda()->dequeue();
                else if(tmp == "travasa")
                    t.Travasa();
                else{
                    string op = getOp(tmp);
                    string _val = getVal(tmp);
                    char val = _val[0];

                    if(op == "p")
                        t.getPila()->push(val);
                    else if(op == "e")
                        t.getCoda()->enqueue(val);
                }
            }
            t.getCoda()->print(out);
        }
    }



}
