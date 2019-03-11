#ifndef POLINOM_H
#define POLINOM_H
#include<iostream>
#include<cmath>

using namespace std;

template<typename C>
class Polinom
{
        C *v;                      //vector in care pozitile reprezita coeficinti lui x la puterea i
        int grad;                       //gradul polinnomului
    public:
        Polinom<C>(int g)                 //constructor cu un singur parametru
        {
            int i;
            grad = g;
            v = new C[grad+1];
            for(i = 0;i <= grad;i++)
            {
                v[i] = 0;
            }
        };
        Polinom<C>(int g, C *a)      //constructor cu doi parametrii
        {   int i;
            grad = g;
            v = new C [grad+1];
            for(i=0 ; i <= grad ; i++)
            {
                v[i]=a[i];
            }
        };
        Polinom<C>()                     //constructor fara parametri
        {
            grad=0;
        };
        ~Polinom<C>()                     //destructor
        {
            delete[]v;
        };
        Polinom<C>(const Polinom &A)      //constructor de copiere
        {
            int i;
            this->grad = A.grad;
            this->v = new C[(this->grad)+1];
            for(i = 0;i <= this->grad;i++)
            {
                this->v[i] = A.v[i];
            }
        };
        Polinom<C> operator +(const Polinom<C> A);  //supraincarcarea operatorului + pentru doua polinoame
        Polinom<C> operator *(const Polinom<C> A);  //supraincarcarea operatorului * pentru doua polinoame
        Polinom<C> operator *(C n);   //supraincarcarea operatorului * pentru un scalar cu polinnom
        Polinom<C> operator -(const Polinom<C> A);  //supraincarcarea operatorului - (in plus , facuta pentru impartire)
        Polinom<C> operator /(const Polinom<C> A);  //supraincarcarea operatorului / pentru doua polinoame
        Polinom<C> operator =(const Polinom<C> A);  //supraincarcarea operatorului =
        C operator [](int i);         //supraincarcarea operatorului [] pentru a obtine valoarea de grad i;
        int grad_maxim(Polinom<C> A);      //metoda pentru gradul maxim(in plus, pentru adunare si scadere)
        C calc_valoare(C n);        //metoda pentru calcularea polinomului intr-un punct
        void adaugare(int i, C n); //metoda pentru adugarea unui element n pe pozitia i
        void eliminare(int i);          //metoda pentru a elemina un element de grad i
        int grad_polinom();             //metoda care returneaza gradul polinnomului
        template<typename W>friend istream &operator>>(istream &is,const Polinom<W> &A);  //functia prieten pentru operatorul de citire
        friend ostream &operator<<(ostream &os,const Polinom<C> &A)  //functia prieten pentru operatorul de scriere
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
        };
};

template<typename C>
istream &operator>>(istream &is,const Polinom<C> &A)  //functia prieten pentru operatorul de citire
{
            int i;
            for(i=0;i<=A.grad;i++)
            {
                is>>A.v[i];
            }
            return is;
};

template<typename C>
Polinom<C> Polinom<C>::operator+(Polinom<C> A)   //supraincarcare operatorului + pentru a calcula suma a doua polinoame
{                                       //functia returneaza tot un polinom
    int i, grad_maxim;
    grad_maxim=this->grad_maxim(A);     //salvam intr-o variabila gradul cel mai mare dintre cele doua polinoame
    Polinom<C> Rezultat(grad_maxim);       //Rezultat il initializam cu gradul cel mai mare
    for(i=0;i<=grad;i++)
    {
        Rezultat.v[i]=v[i];             //salvam obiectul curent in rezultat
    }
    for(i=0;i<=A.grad;i++)
    {
        Rezultat.v[i]=Rezultat.v[i]+A.v[i];    //si adunam rezultatul cu polinomul A
    }
    return Rezultat;
}

template<typename C>
Polinom<C> Polinom<C>::operator -(Polinom A)
{
    int i, grad_maxim;
    grad_maxim=this->grad_maxim(A);     //salvam intr-o variabila gradul cel mai mare dintre cele doua polinoame
    Polinom<C> Rezultat(grad_maxim);       //Rezultat il initializam cu gradul cel mai mare
    for(i=0;i<=grad;i++)
    {
        Rezultat.v[i] = v[i];     //salvam obiectul curent in rezultat
    }
    for(i=0;i<=A.grad;i++)
    {
        Rezultat.v[i] = Rezultat.v[i] - A.v[i];    //si scadem rezultatul cu polinomul A
    }
    return Rezultat;
}

template<typename C>
Polinom<C> Polinom<C>::operator =(Polinom<C> A)  //supraincarcarea operatorului =
{
    grad=A.grad;  //egalam gradele
    v=new C [A.grad+1];   //reinitializa v cu gradul polinomului cu care il egalam
    for(int i=0;i<=grad;i++)
    {
        v[i]=A.v[i];  //aici salvam in v valorile polinomului cu care il egalam
    }
    return *this;  //returnam obiectul curent
}

template<typename C>
Polinom<C> Polinom<C>::operator/(Polinom<C> A)   //supraincarecarea operatorului /
{
      Polinom<C> Copie_this((*this));      //facem o copie pentru obiectul curent
      Polinom<C> Rezultat(this->grad - A.grad);   //acesta va fii rezultatul
      Polinom<C> Temporar(this->grad - A.grad);   //si in temporar se va salva o singura valoare mai mare decat 0
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

template<typename C>
C Polinom<C>::operator[](int i)  //supraincarcarea operatorului []
{
    if(i>grad)
    {
        return 0;     //daca i e mai mare decat grad returneaza 0 altfel returneaza coeficientul gradului i
    }
    return v[i];
}

template<typename C>
Polinom<C> Polinom<C>::operator*(Polinom<C> A)    //supraincarcarea operatorului *
{
    int i, grad_maxim1, j ;
    grad_maxim1=grad_maxim(A.grad + grad);   //grad maxim il initializam cu suma gradelor celor doua polinoame
    Polinom<C> Rezultat(grad_maxim1);    //rezultatul va avea gradul maxim
    for(i=0;i<=grad;i++)
    {
        for(j=0;j<=A.grad;j++)
        {
            Rezultat.v[i+j] = Rezultat.v[i+j] + v[i] * A.v[j];
        }
    }
    return Rezultat;
}

template<typename C>
Polinom<C> Polinom<C>::operator*(C n)   //supraincarcarea * pentru inmultirea cu scalar
{
    int i;
    Polinom<C> Rezultat(this->grad);   //rezultatul va avea gradul obiectului curent
    for(i=0;i<=grad;i++)
    {
        Rezultat.v[i]=this->v[i]*n;   //si vom inmulti fiecare elemnet cu n
    }
    return Rezultat;
}

template<typename C>
int Polinom<C>::grad_maxim(Polinom<C> A)      //aceasta functie am creato in plus pentru a vedea care este gradul maxim dintre doua polinoame
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

template<typename C>
C Polinom<C>::calc_valoare(C n)        //functia calc_valoare va returna valoarea polinomului intr-un punct dat
{
    int i, sum=0;
    for(i=0;i<=grad;i++)
    {
        sum+=v[i]*pow(n, i);
    }
    return sum;
}

template<typename C>
void Polinom<C>::adaugare (int i, C n)   //adauga n pe gradul i
{
    int j;
    C *p;
    grad++;
    p=new C[grad+1];       //luam un nou vector care il initializam cu grad++
    for(j=0;j<grad;j++)
    {
        p[j]=v[j];          //salvam vectorul curent in el
    }
    delete v;           //stergem vectorul curent pentru a nu ocupa memoria degeaba
    for(j=grad;j>=i;j--)
    {
        p[j]=p[j-1];    //mutam la dreapta toate elementele adica le marim gradul cu 1
    }
    p[i]=n;          //inntroducem n pe gradul i
    v=new C[grad+1];   //reinitializam v cu nnoul grad
    for(j=0;j<=grad;j++)
    {
        v[j]=p[j];   //punem in v noul polinom obtinut
    }
    delete p;    //stergem p
}

template<typename C>
void Polinom<C>::eliminare(int i)  //eliminam gradul i
{
    v[i]=0;   //punem 0 la gradul i si nu il va mai afisa
    if(i==grad)
    {
        grad--;
    }
}

template<typename C>
int Polinom<C>::grad_polinom()             //functia care obtine gradul polinomului
{
    if(v[grad]==0)
    {
        grad--;
    }
    return grad;
}
#endif // POLINOM_H
