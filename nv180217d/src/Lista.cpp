#include "Lista.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "IOSTREAM.H"///////
Lista::Lista(){
	prvi=0;
	poslednji=0;
	brelem=0;
}

void Lista::dodaj(PCB* e){
	if(prvi==0)prvi=poslednji=new Elem(e);
	else poslednji=poslednji->sled=new Elem(e);
	brelem++;
}

void Lista::izbaci(int i){
	if (prvi==0) return;
	if (prvi->info->id==i){
		Elem* pom=prvi;
		prvi=prvi->sled;
		if (prvi==0) poslednji=0;
		delete pom;
		return;
	}
	else{
		Elem* pom=prvi->sled;
		Elem* preth=prvi;
		while((pom!=0)&&(pom->info->id!=i)){
			pom=pom->sled;
			preth=preth->sled;
		}
		if (pom==0) return;
		if (pom==poslednji){
			poslednji=preth;
			poslednji->sled=0;
			delete pom;
		}
		else{
			preth->sled=pom->sled;
			delete pom;
		}

	}
}

void Lista::izbaciprvi(){
	if (prvi!=0){
		Elem* pom=prvi;
		prvi=prvi->sled;
		pom->info->status=3;
		Scheduler::put(pom->info);
		brelem--;
		delete pom;
		if (prvi==0)poslednji=0;
	}
}

Thread* Lista::dohvNit(int i){
	Elem* pom=prvi;
	while((pom!=0)&&(pom->info->id!=i)){
		pom=pom->sled;
	}
	if (pom!=0) return pom->info->nit;
	else return 0;
}

int Lista::dohvbrelem()const{
	return brelem;
}

Lista::~Lista(){
	Elem* pom=prvi;
	while (prvi!=0){
		pom=prvi;
		prvi=prvi->sled;
		delete pom;
	}
}

void Lista::stampaj(){
	Elem* pom=prvi;
	while(pom!=0){
		cout<<pom->info->id<<endl;
		pom=pom->sled;
	}
}

void Lista::smanjizajedan(){
	Elem* pom=prvi;;
	while(pom!=0){
		pom->info->blokirajucevreme--;
		if (pom->info->blokirajucevreme==0){
					pom->info->status=3;
					pom->info->ret=0;
					Scheduler::put(pom->info);
		}
		pom=pom->sled;
	}
}

int Lista::izbaciizsema(int i){
	if (prvi==0) return 0;
	if (prvi->info->id==i){
		Elem* pom=prvi;
		prvi=prvi->sled;
		if (prvi==0) poslednji=0;
		delete pom;
		return 1;
	}
	else{
		Elem* pom=prvi->sled;
		Elem* preth=prvi;
		while((pom!=0)&&(pom->info->id!=i)){
			pom=pom->sled;
			preth=preth->sled;
		}
		if (pom==0) return 0;
		if (pom==poslednji){
			poslednji=preth;
			poslednji->sled=0;
			delete pom;
		}
		else{
			preth->sled=pom->sled;
			delete pom;
		}

	}
	return 1;
}
