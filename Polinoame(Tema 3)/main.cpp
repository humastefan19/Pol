#include <iostream>
#include "Polinom.h"

using namespace std;

int main()
{
    double a[]={1.01,2.6,6.2,4.43,2.18},b[]={1.78,2.3,2.234},valori_a,valori_b;
    int poz_a, poz_b;

    cout<<"Polinom cu coeficienti reali: "<<"\n";
    cout<<"\n";

    Polinom<double> A(4 , a);
    cout<<"Primul polinom este: ";
    cout<<A<<"\n";
    Polinom<double> B(2 , b);
    cout<<"Al doilea polinom este: ";
    cout<<B<<"\n";
    valori_a=4.1;
    valori_b=3.34;
    cout<<"Valoarea primului in "<<valori_a<<" este: "<<A.calc_valoare(valori_a)<<"\n";
    cout<<"Valoarea celui de al doilea in "<<valori_b<<" este: "<<B.calc_valoare(valori_b)<<"\n";
    Polinom<double> I(A+B);
    cout<<"Suma celor doua polinoame este: ";
    cout<<I<<"\n";
    valori_a=3;
    valori_b=1;
    cout<<"Coeficientul gradului "<<valori_a<<" in primul polinom este "<<A[valori_a]<<"\n";
    cout<<"Coeficientul gradului "<<valori_b<<" in al doilea polinom este "<<B[valori_b]<<"\n";
    Polinom<double> J;
    J=A*B;
    cout<<"Produsul celor doua polinoame este: ";
    cout<<J<<"\n";
    valori_a=3.23;
    J=A*valori_a;
    cout<<"Primul polinom inmultit cu "<<valori_a<<" este: ";
    cout<<J<<"\n";
    valori_b=2;
    J=B*valori_b;
    cout<<"Al doilea polinom inmultit cu "<<valori_b<<" este: ";
    cout<<J<<"\n";
    J=A/B;
    cout<<"Impartirea celor doua polinoame este: ";
    cout<<J<<"\n";
    poz_a=2;
    valori_a=4.23;
    A.adaugare(poz_a,valori_a);
    cout<<"Adaugam pe pozitia de grad "<<poz_a<<" coeficientul "<<valori_a<<" din primul polinom: "<<A<<"\n";
    poz_a=5;
    A.eliminare(poz_a);
    cout<<"Eliminam pozitia de grad "<<poz_a<<" din primul polinom: "<<A<<"\n";
    cout<<"Gradul primului polinom este: "<<A.grad_polinom()<<"\n";
    cout<<"Gradul celui de al doilea polinom este: "<<B.grad_polinom()<<"\n";

    cout<<"\n";
    cout<<"Polinom cu coeficienti intrgi: "<<"\n";
    cout<<"\n";

    int  c[]={1,2,5,4,2},d[]={1,2,2}, valori_c, valori_d, poz_c, poz_d;
    Polinom<int> C(4 , c);
    cout<<"Primul polinom este: ";
    cout<<C<<"\n";
    Polinom<int> D(2 , d);
    cout<<"Al doilea polinom este: ";
    cout<<D<<"\n";
    valori_c=4;
    valori_d=3;
    cout<<"Valoarea primului in "<<valori_c<<" este: "<<C.calc_valoare(valori_c)<<"\n";
    cout<<"Valoarea celui de al doilea in "<<valori_d<<" este: "<<D.calc_valoare(valori_d)<<"\n";
    Polinom<int> K(C+D);
    cout<<"Suma celor doua polinoame este: ";
    cout<<K<<"\n";
    valori_c=3;
    valori_d=1;
    cout<<"Coeficientul gradului "<<valori_c<<" in primul polinom este "<<C[valori_c]<<"\n";
    cout<<"Coeficientul gradului "<<valori_d<<" in al doilea polinom este "<<D[valori_d]<<"\n";
    Polinom<int> L;
    L=C*D;
    cout<<"Produsul celor doua polinoame este: ";
    cout<<L<<"\n";
    valori_c=3;
    L=C*valori_c;
    cout<<"Primul polinom inmultit cu "<<valori_c<<" este: ";
    cout<<L<<"\n";
    valori_d=2;
    L=D*valori_d;
    cout<<"Al doilea polinom inmultit cu "<<valori_d<<" este: ";
    cout<<L<<"\n";
    L=C/D;
   cout<<"Impartirea celor doua polinoame este: ";
    cout<<L<<"\n";
    poz_c=2;
    valori_c=4;
    C.adaugare(poz_c,valori_c);
    cout<<"Adaugam pe pozitia de grad "<<poz_c<<" coeficientul "<<valori_c<<" din primul polinom: "<<C<<"\n";
    poz_c=5;
    C.eliminare(poz_c);
    cout<<"Eliminam pozitia de grad "<<poz_c<<" din primul polinom: "<<C<<"\n";
    cout<<"Gradul primului polinom este: "<<C.grad_polinom()<<"\n";
    cout<<"Gradul celui de al doilea polinom este: "<<D.grad_polinom()<<"\n";
    return 0;
}
