#include <string>
#include "GrafoList.h"
using namespace std;

int main(int argc , char *argv[])
{

	GrafoList<string,double> G(10);

	NodoG n1,n2,n3,n4,n5,n6;

	G.insNodo(n1);
	G.scriviEtichetta(n1,"a");
	G.insNodo(n2);
	G.scriviEtichetta(n2,"b");
	G.insNodo(n3);
	G.scriviEtichetta(n3,"c");
	G.insNodo(n4);
	G.scriviEtichetta(n4,"d");
	G.insNodo(n5);
	G.scriviEtichetta(n5,"e");
	G.insNodo(n6);
	G.scriviEtichetta(n6,"f");

	G.insArco(n1,n2, 1.0);
	G.insArco(n1,n3, 0.9);
	G.insArco(n1,n5, 0.3);
	G.insArco(n2,n4, 0.1);
	G.insArco(n2,n6, 0.2);
	G.insArco(n3,n4, 1.0);
	G.insArco(n3,n6, 0.7);
	G.insArco(n4,n1, 0.5);
	G.insArco(n5,n2, 0.4);
	G.insArco(n5,n3, 0.2);
	G.insArco(n6,n4, 0.1);

	cout << "\nNumNodi " << G.numNodi();
	cout << "\nNumArchi " << G.numArchi();

	GrafoList<string,double>::ListaNodi L = G.Adiacenti(n2);

	GrafoList<string,double>::ListaNodiPos p;


	cout << "\nAdiacenti di " << G.leggiEtichetta(n2) << " --> ";
	p = L.begin();
	while (!L.end(p)){
		cout <<  G.leggiEtichetta(*(L.read(p))) << " ";
		p = L.next(p);
	}

	cout << endl;
	cout << endl;

	system("pause");
	return 0;
}

