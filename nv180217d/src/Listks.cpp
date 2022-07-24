
#include "Listks.h"
#include "KSem.h"

Listks::Listks(){
	prvi=0;
	poslednji=0;
	brelem=0;
}

Listks::~Listks(){
	Elem* pom=prvi;
	while (prvi!=0){
		pom=prvi;
		prvi=prvi->sled;
		delete pom;
	}
}

void Listks::dodaj(KernelSem*e){
	if(prvi==0)prvi=poslednji=new Elem(e);
	else poslednji=poslednji->sled=new Elem(e);
	brelem++;
}

void Listks::izbaci(KernelSem* e){
	if (prvi->info==e) prvi=prvi->sled;
	else{
		Elem *pom=prvi;
		while(pom->sled->info!=e)pom=pom->sled;
		pom->sled=pom->sled->sled;
	}
	brelem--;
}


int Listks::dohvbr(){
	return brelem;
}


KernelSem* Listks::dohvkernel(int i){
	Elem* pom=prvi;
	for (int ii=0;ii<i;ii++)pom=pom->sled;
	return pom->info;
}
