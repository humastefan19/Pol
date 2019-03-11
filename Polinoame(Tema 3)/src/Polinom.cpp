#include "Polinom.h"
#include<cmath>

template<typename C, typename P> Polinom<C,P>::Polinom(int g)    //constructorul avand ca parametru gradul poliomului
{
    int i;
    grad = g;
    nr_monoame=nr;
    v = new vect<C,P>[nr_monoame+1];
    for(i = 0;i <= nr_monoame;i++)
    {
        v[i].coeficient = 0;
        v[i].puteri = 0
    }
}

template<typename C, typename P> Polinom<C,P>::Polinom(int g, vect<C,P> *a, int nr)  //constructor cu doi parametri unul pentru grad si celalalt pentru coeficienti
{
    int i;
    grad = g;
    nr_monoame = nr;
    v = new vect<C,P>[nr_monoame+1];
    for(i=0 ; i <= nr_monoame ; i++)
    {
        v[i].coeficient=a[i].coeficient;
        v[i].putere=a[i].putere
    }
}

template<typename C, typename P> Polinom<C,P>::Polinom()   //constructor fara parametri initializeaza gradul cu 0
{
    grad=0;
    nr_monoame=0;
}

template<typename C, typename P> Polinom<C,P>::~Polinom()                     //destructorul care va distruge vectorul alocat dinamic
{
     delete []v;
}

template<typename C, typename P> Polinom<C,P>::Polinom(const Polinom &A)      //constructor de copiere
{
    int i;
    this->grad = A.grad;
    this->nr_monoame=A.nr_monoame;
    this->v = new vect<C,P>[(this->nr_monoame)+1];
    for(i = 0;i <= this->nr_monoame;i++)
    {
      this->v[i].coeficient = A.v[i].coeficient;
      this->v[i].putere = A.v[i].putere;
    }
}

template<typename C, typename P> Polinom<C,P> Polinom<C,P>::operator+(Polinom A)   //supraincarcare operatorului + pentru a calcula suma a doua polinoame
{                                       //functia returneaza tot un polinom
    int i, grad_maxim;
    grad_maxim=this->grad_maxim(A);     //salvam intr-o variabila gradul cel mai mare dintre cele doua polinoame
    Polinom Rezultat(grad_maxim);       //Rezultat il initializam cu gradul cel mai mare
    for(i=0;i<=grad;i++)
    {
        Rezultat.v[i].coeficient=v[i].coeficient;             //salvam obiectul curent in rezultat
        Rezultat.v[i].putere=v[i].putere;
    }
    for(i=0;i<=A.grad;i++)
    {
        Rezultat.v[i].coeficient=Rezultat.v[i].coeficient+A.v[i].coeficient;    //si adunam rezultatul cu polinomul A
    }
    return Rezultat;
}

template<typename C, typename P> Polinom<C,P> Polinom<C,P>::operator -(Polinom A)
{
    int i, grad_maxim;
    grad_maxim=this->grad_maxim(A);     //salvam intr-o variabila gradul cel mai mare dintre cele doua polinoame
    Polinom Rezultat(grad_maxim);       //Rezultat il initializam cu gradul cel mai mare
    for(i=0;i<=grad;i++)
    {
        Rezultat.v[i].coeficient = v[i].coeficient;     //salvam obiectul curent in rezultat
        Rezultat.v[i].putere = v[i].putere;
    }
    for(i=0;i<=A.grad;i++)
    {
        Rezultat.v[i].coeficient = Rezultat.v[i].coeficient - A.v[i].coeficient;    //si scadem rezultatul cu polinomul A
    }
    return Rezultat;
}

template<typename C, typename P> Polinom<C,P> Polinom<C,P>::operator =(Polinom A)  //supraincarcarea operatorului =
{
    grad=A.grad;  //egalam gradele
    v=new vect<C,P>[A.grad+1];   //reinitializa v cu gradul polinomului cu care il egalam
    for(int i=0;i<=grad;i++)
    {
        v[i].coeficient=A.v[i].coeficient;  //aici salvam in v valorile polinomului cu care il egalam
        v[i].putere=A.v[i].putere;
    }
    return *this;  //returnam obiectul curent
}

template<typename C, typename P> Polinom<C,P> Polinom<C,P>::operator/(Polinom A)   //supraincarecarea operatorului /
{
      Polinom Copie_this((*this));      //facem o copie pentru obiectul curent
      Polinom Rezultat(this->grad - A.grad);   //acesta va fii rezultatul
      Polinom Temporar(this->grad - A.grad);   //si in temporar se va salva o singura valoare mai mare decat 0
      while(Copie_this.grad>=A.grad)
      {
         Temporar = Polinom(Copie_this.grad - A.grad); //reinitializam de fiecare data temporar
         Temporar.v[ Copie_this.grad - A.grad ] = Copie_this.v[ Copie_this.grad ] / A.v[ A.grad ];  //impartim coeficenti termenilor de grad maxim
         Rezultat = Rezultat + Temporar;  //adunam la rezultat impartirea
         Copie_this = Copie_this - ( Temporar * A );  //inmultim impartitorul cu valoarea de la impartire coeficientilor de grad maxim
                                                      //si facem scaderea dintre copia obiectului curent si aceasta inmultire
                                                      //apoi salvam tot in cpoia obiectului curent
         if(Copie_this[Copie_this.grad]==0)           //verificam daca gradul maxim  are coeficintul 0
         {
             Copie_this.grad--;      //daca da il scadem
         }
      }
      return Rezultat;   //returnam rezultatul
}

template<typename C, typename P> <C,P> Polinom<C,P>::operator[](int i)  //supraincarcarea operatorului []
{
    if(i>grad)
        {
            return 0;     //daca i e mai mare decat grad returneaza 0 altfel returneaza coeficientul gradului i
        }
    return v[i];
}

template<typename C, typename P> Polinom<C,P> Polinom<C,P>::operator*(Polinom A)    //supraincarcarea operatorului *
{
    int i, grad_maxim1 , grad_min ;
    grad_maxim1=grad_maxim(A.grad + grad);   //grad maxim il initializam cu suma gradelor celor doua polinoame
    Polinom Rezultat(grad_maxim1);    //rezultatul va avea gradul maxim
    for(i=0;i<=grad;i++)
        for(j=0;j<=A.grad;j++)
    {
        Rezultat.v[i+j].coeficient = v[i].coeficient*A.v[j].coeficient;
        Rezultat.v[i+j].putere = v[i].putere+A.v[j].putere;
    }
    return Rezultat;
}

template<typename C, typename P> Polinom<C,P> Polinom<C,P>::operator*(double n)   //supraincarcarea * pentru inmultirea cu scalar
{
    int i;
    Polinom Rezultat(this->grad);   //rezultatul va avea gradul obiectului curent
    for(i=0;i<=grad;i++)
    {
        Rezultat.v[i]=this->v[i]*n;   //si vom inmulti fiecare elemnet cu n
    }
    return Rezultat;
}

template<C,P> int Polinom<C,P>::grad_maxim(Polinom A)      //aceasta functie am creato in plus pentru a vedea care este gradul maxim dintre doua polinoame
{                                       //ea va returna gradul
    if(this->grad>=A.grad)
    {
       return this->grad;
    }
    else
    {
        return A.grad;
    }
}

template<typename C, typename P> int Polinom<C,P>::calc_valoare(int n)        //functia calc_valoare va returna valoarea polinomului intr-un punct dat
{
    int i, sum=0;
    for(i=0;i<=grad;i++)
    {
        sum+=v[i].coeficient*pow(n, v[i].putere);
    }
    return sum;
}

template<typename C, typename P> void Polinom<C,P>::adaugare (C i, P n)   //adauga n pe gradul i
{
    int j;
    vect<C,P> *p;
    grad++;
    p=new vect<C,P>[grad+1];       //luam un nou vector care il initializam cu grad++
    for(j=0;j<grad;j++)
    {
        p[j].coeficient=v[j].coeficient;          //salvam vectorul curent in el
        P[j].putere=v[j].putere;
    }
    delete v;           //stergem vectorul curent pentru a nu ocupa memoria degeaba
    for(j=grad;j>=i;j--)
    {
        p[j]=p[j-1];    //mutam la dreapta toate elementele adica le marim gradul cu 1
    }
    p[i]=n;          //inntroducem n pe gradul i
    v=new vect<C,P>[grad+1];   //reinitializam v cu nnoul grad
    for(j=0;j<=grad;j++)
    {
        v[j]=p[j];   //punem in v noul polinom obtinut
    }
    delete p;    //stergem p
}

template<typename C, typename P> void Polinom<C,P>::eliminare(int i)  //eliminam gradul i
{
    v[i]=0;   //punem 0 la gradul i si nu il va mai afisa
    if(i==grad)
    {
        grad--;
    }
}

template<typename C, typename P> int Polinom<C,P>::grad_polinom()             //functia care obtine gradul polinomului
{
    if(v[grad]==0)
    {
        grad--;
    }
    return grad;
}

istream &operator>>(istream &is,const Polinom &A)   //supraincarcarea operatorului >> pentru citirea unui polinom
{
    int i;
    for(i=0;i<=A.grad;i++)
    {
        is>>A.v[i];
    }
    return is;
}

ostream &operator<<(ostream &os,const Polinom &A)   //supraincarcare operatorului << pentru afisarea unui polinom
{
    int i;
    for(i=A.grad;i>=0;i--)
    {
        if(A.v[i]!=0)
        {
            if(i==0)
            {

                if(A.v[1]==0)
                {
                   os<<" + ";
                }
                os<<A.v[i];
            }
            else if(i==1)
            {
                os<<A.v[i]<<" * X";
                if(A.v[0]>0)
                {
                    os<<" + ";
                }
            }
            else
            {
                 os<<A.v[i]<<" * X^"<<i<<' ';
                 if(A.v[i-1]>=0)
                 {
                     os<<" + ";
                 }
            }
        }
    }
    return os;
}
