/*
 * Siglist.h
 *
 *  Created on: Apr 28, 2020
 *      Author: OS1
 */

#ifndef SIGLIST_H_
#define SIGLIST_H_
#include "Sig.h"

class Siglist {
private:
	struct Elem{
			SignalHandler info;
			Elem* sled;
			Elem(SignalHandler e):info(e), sled(0){};
		};
	Elem* prvi, *poslednji;
	int brelem;
public:
	Siglist();
	virtual ~Siglist();
	void dodaj(SignalHandler e);
	void izbacisve();
	void swap(SignalHandler hand1, SignalHandler hand2);
	void obradi();
};

#endif /* SIGLIST_H_ */
