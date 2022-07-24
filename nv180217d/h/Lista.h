/*
 * Lista.h
 *
 *  Created on: Apr 13, 2020
 *      Author: OS1
 */

#ifndef LISTA_H_
#define LISTA_H_

class PCB;
class Thread;

class Lista {
	struct Elem{
		PCB* info;
		Elem* sled;
		Elem(PCB* e):info(e), sled(0){};
	};
	Elem* prvi, *poslednji;
	int brelem;
public:
	Lista();
	void dodaj(PCB* e);
	void izbaci(int i);
	void izbaciprvi();
	Thread* dohvNit(int i);
	int dohvbrelem()const;
	void smanjizajedan();
	~Lista();

	void stampaj();

	int izbaciizsema(int i);
};

#endif /* LISTA_H_ */
