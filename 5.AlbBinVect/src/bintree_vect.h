#ifndef BINTREE_VECT_H_
#define BINTREE_VECT_H_

#include <iostream>
#include "bintree.h"
#define NIL -1

template <class T>
class bintree_vect: public bintree<T, int>{

public:

	typedef typename bintree<T, int>::value_type value_type;
	typedef typename bintree<T, int>::Nodo Nodo;

	struct _cella{
		Nodo genitore;
		Nodo sinistro;
		Nodo destro;
		value_type valore;
		int num_discendenti;
		int livello;
	};

	typedef struct _cella Cella;

	// costruttori e distruttori
	bintree_vect();
	bintree_vect(int);
	~bintree_vect();

	// operatori
	void create();
	bool empty() const;

	Nodo root() const;
	Nodo parent(Nodo) const;
	Nodo sx(Nodo) const;
	Nodo dx(Nodo) const;
	bool sx_empty(Nodo) const;
	bool dx_empty(Nodo) const;

	void erase(Nodo);

	T read(Nodo) const;
	void write(Nodo , value_type );

	void ins_root(value_type);
	void ins_sx(Nodo, value_type);
	void ins_dx(Nodo, value_type);
	int getLivello(Nodo n){return spazio[n].livello;}

	/*int getLevelUtil(Nodo, int data, int level);
	int getLevel(Nodo, int data);
	 */
	void printSubTree(const Nodo n) const;

private:
	int MAXLUNG;
	Cella *spazio;
	int nNodi;
	Nodo inizio; //radice
	Nodo libera; //prima posizione libera
};

template <class T>
bintree_vect<T>::bintree_vect()
{
	MAXLUNG = 100;
	spazio = new Cella[MAXLUNG];
	create();
}

template <class T>
bintree_vect<T>::bintree_vect(int nNodi): MAXLUNG(nNodi)
{
	spazio = new Cella[nNodi];
	create();
}


template <class T>
bintree_vect<T>::~bintree_vect()
{
	erase(inizio);
	delete[] spazio;
}

template <class T>
void bintree_vect<T>::create()
{
	inizio = NIL;
	for (int i = 0; i < MAXLUNG; i++)
	{
		spazio[i].sinistro = (i+1) % MAXLUNG; //inizializza tutte le parti sinistre a (successiva posizione libera) (sono tutte libere ora)
	}

	libera = 0;
	nNodi = 0;
}

template <class T>
bool bintree_vect<T>::empty() const
{
	return(nNodi == 0);
}

template <class T>
typename bintree_vect<T>::Nodo bintree_vect<T>::root() const
{
	return(inizio);
}

template <class T>
typename bintree_vect<T>::Nodo bintree_vect<T>::parent(Nodo n) const
{
	if (n != inizio)
		return (spazio[n].genitore);
	else
		return(n);
}

template <class T>
typename bintree_vect<T>::Nodo bintree_vect<T>::sx(Nodo n) const
{
	if (!sx_empty(n))
		return (spazio[n].sinistro);
	else
		return(n);
};

template <class T>
typename bintree_vect<T>::Nodo bintree_vect<T>::dx(Nodo n) const
{
	if (!dx_empty(n))
		return (spazio[n].destro);
	else
		return(n);
}

template <class T>
bool bintree_vect<T>::sx_empty(bintree_vect<T>::Nodo n) const
{
	return (spazio[n].sinistro == NIL);
}

template <class T>
bool bintree_vect<T>::dx_empty(bintree_vect<T>::Nodo n) const
{
	return (spazio[n].destro == NIL);
}

template <class T>
void bintree_vect<T>::ins_root(bintree_vect<T>::value_type v)
{
	if (inizio == NIL)
	{
		inizio = libera;
		libera = spazio[libera].sinistro;
		spazio[inizio].sinistro = NIL;
		spazio[inizio].destro = NIL;
		spazio[inizio].valore = v;
		spazio[inizio].num_discendenti = 0;
		spazio[inizio].livello = 0;
		nNodi++;
	}
	else
		throw "a root already exists";
}


template <class T>
void bintree_vect<T>::ins_sx(bintree_vect<T>::Nodo n, bintree_vect<T>::value_type v )
{
	if (inizio == NIL)
		throw "the tree is empty";
	if (n == NIL)
		throw "the node is null";
	if (spazio[n].sinistro != NIL)
		throw "this node already exists";
	if (nNodi >= MAXLUNG)
		throw "reached full size";
	else
	{
		Nodo q = libera;
		libera = spazio[libera].sinistro;
		spazio[n].sinistro = q;
		spazio[q].sinistro = NIL;
		spazio[q].genitore = n;
		spazio[q].destro = NIL;
		spazio[q].valore = v;
		spazio[q].num_discendenti = 0;
		Nodo par = parent(q);
		while(par != root()){
			spazio[par].num_discendenti++;
			par=parent(par);
		}
		spazio[par].num_discendenti++;
		spazio[q].livello = getLivello(parent(q))+1;
		nNodi++;

	}
}

template <class T>
void bintree_vect<T>::ins_dx(bintree_vect<T>::Nodo n, bintree_vect<T>::value_type v )
{
	if (inizio == NIL)
		throw "the tree is empty";
	if (n == NIL)
		throw "the node is null";
	if (spazio[n].destro != NIL)
		throw "this node already exists";
	if (nNodi >= MAXLUNG)
		throw "reached full size";
	else
	{
		Nodo q = libera;
		libera = spazio[libera].sinistro;
		spazio[n].destro = q;
		spazio[q].genitore = n;
		spazio[q].sinistro = NIL;
		spazio[q].destro = NIL;
		spazio[q].valore = v;
		spazio[q].num_discendenti = 0;
		Nodo par = parent(q);
		while(par != root()){
			spazio[par].num_discendenti++;
			par=parent(par);
		}
		spazio[par].num_discendenti++;
		spazio[q].livello = getLivello(parent(q))+1;
		nNodi++;
	}
}

template <class T>
void bintree_vect<T>::erase(bintree_vect<T>::Nodo n)
{
	if (n != NIL) {
		if (!sx_empty(n))
			erase(spazio[n].sinistro);
		if (!dx_empty(n))
			erase(spazio[n].destro);
		if (n != inizio) {
			Nodo p = parent(n);
			if (spazio[p].sinistro == n)
				spazio[p].sinistro = NIL;
			else
				spazio[p].destro = NIL;
		}
		else
			inizio = NIL;
		nNodi--;
		spazio[n].sinistro = libera;
		libera = n;
	}
	else
		throw "the node is null";
}

template <class T>
T bintree_vect<T>::read(bintree_vect<T>::Nodo n) const
{
	if (n != NIL)
		return (spazio[n].valore); // per visualizzare il numero di nodi che si trovano nel
	//sottoalbero di radice n, utilizzare spazio[n].num_discendenti.
	else
		throw "the node is null";
}

template <class T>
void bintree_vect<T>::write(bintree_vect<T>::Nodo n, bintree_vect<T>::value_type a)
{
	if (n != NIL)
		spazio[n].valore = a;
	else
		throw "the node is null";
}

template <class T>
void bintree_vect<T>::printSubTree(const Nodo n) const{
	std::cout << "[" << read(n) << ", ";
	std::cout << "(numero nodi di nodi " << spazio[n].num_discendenti << ") ";
	if (!sx_empty(n))
		printSubTree(sx(n));
	else std::cout << "NIL";
	std::cout << ", ";
	if (!dx_empty(n))
		printSubTree(dx(n));
	else std::cout << "NIL";
	std::cout << " ]";
}

/*
template<class T>
int bintree_vect<T>::getLevelUtil(bintree_vect<T>::Nodo n, int data, int level){
	if(n == NIL)
		return 0;
	if(spazio[n].valore == data)
		return level;
	int downlevel = getLevelUtil(spazio[n].sinistro, data, level+1);
	if(downlevel != 0)
		return downlevel;
	downlevel = getLevelUtil(spazio[n].destro, data, level+1);
	return downlevel;
}

template<class T>
int bintree_vect<T>::getLevel(bintree_vect<T>::Nodo n, int data){
	return getLevelUtil(n, data, 0);
}*/

#endif /* BINTREE_VECT_H_ */
