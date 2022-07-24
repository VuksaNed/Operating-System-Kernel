/*
 * Listint.h
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */

#ifndef LISTINT_H_
#define LISTINT_H_

class Listint {
private:
	struct Elem{
		int e;
		Elem* sled;
		Elem(int x):e(x),sled(0){};
	};
	Elem* prvi, * posl;
	int brelem;
public:
	Listint();
	~Listint();
	void dodaj(int x);
	int brelemm();
	int dohv(int i);
	int izbaci();
};

#endif /* LISTINT_H_ */
