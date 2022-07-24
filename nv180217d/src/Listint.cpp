/*
 * Listint.cpp
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */

#include "Listint.h"

Listint::Listint(){
	prvi=posl=0;
	brelem=0;
}

Listint::~Listint(){
	Elem *tek=prvi;
	while(prvi!=0){
		tek=prvi;
		prvi=prvi->sled;
		delete tek;
	}
}
void Listint::dodaj(int x){
	if (prvi==0)prvi=posl=new Elem(x);
	else{
		posl->sled=new Elem(x);
		posl=posl->sled;
	}
	brelem++;
}

int Listint::dohv(int i){
	if (prvi==0) return -1;
	if (i>=brelem) return -1;
	Elem *tek=prvi;
	while(i!=0) tek=tek->sled;
	return tek->e;
}

int Listint::brelemm(){
	return brelem;
}

int Listint::izbaci(){
	Elem*tek;
	if (prvi==0) return -1;
	brelem--;
	tek=prvi;
	prvi=prvi->sled;
	int x=tek->e;
	delete tek;
	return x;
}
