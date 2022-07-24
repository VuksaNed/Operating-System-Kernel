
#include "Siglist.h"

Siglist::Siglist() {
	prvi=0;
	poslednji=0;
	brelem=0;
}

Siglist::~Siglist() {
	Elem* pom=prvi;
	while (prvi!=0){
		pom=prvi;
		prvi=prvi->sled;
		delete pom;
	}
}

void Siglist::dodaj(SignalHandler e){
	if(prvi==0)prvi=poslednji=new Elem(e);
		else poslednji=poslednji->sled=new Elem(e);
		brelem++;
}

void Siglist::izbacisve(){
	Elem* pom=prvi;
		while (prvi!=0){
			pom=prvi;
			prvi=prvi->sled;
			delete pom;
		}
	brelem=0;
	prvi=poslednji=0;
}

void Siglist::swap(SignalHandler hand1, SignalHandler hand2){
	Elem*pom1=prvi;
	Elem*pom2=prvi;
	Elem*tek=prvi;
	while((tek!=0)&&((pom1->info!=hand1)||(pom2->info!=hand2))){
		if (pom1->info!=hand1) pom1=pom1->sled;
		if (pom2->info!=hand2) pom2=pom2->sled;
		tek=tek->sled;
	}
	if((pom1!=0)&&(pom2!=0)){
		SignalHandler s=pom1->info;
		pom1->info=pom2->info;
		pom2->info=s;
	}

}

void Siglist::obradi(){
	Elem *tek=prvi;
	while (tek!=0){
		tek->info();
		tek=tek->sled;
	}
}
