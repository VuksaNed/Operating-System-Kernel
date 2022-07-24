/*
 * Sig.cpp
 *
 *  Created on: Apr 28, 2020
 *      Author: OS1
 */

#include "Sig.h"
#include "Siglist.h"
#include "System.h"
#include "PCB.h"
#include "Lista.h"
#include "KSem.h"
#include "thread.h"
#include "SCHEDULE.H"
#include "Listint.h"

int Sig::globalniblok[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int Sig::dozvoli=0;

void Sig::blokiraj(){
	System::running->status=2;
	while (System::running->cekaniPCBovi->dohvbrelem()>0)System::running->cekaniPCBovi->izbaciprvi();
	Sig::dozvoli=1;
	if (System::running->roditelj!=0)System::running->roditelj->signal(1);
	System::running->nit->signal(2);
	Sig::dozvoli=0;
	System::obradasig=0;
	dispatch();

}

Sig::Sig(Thread *t) {
	lock
	for (int i=0;i<16;i++){
		lokalniblok[i]=0;
		hendleri[i]=new Siglist();
		stigao[i]=0;
	}
	obradii=new Listint();
	mojanit=t;
	hendleri[0]->dodaj(blokiraj);
	fleg=0;
	unlock
}

Sig::~Sig() {
	lock
	for (int i=0;i<16;i++){
			delete hendleri[i];
		}
	delete obradii;
	unlock
}

void Sig::signal(SignalId signal){
	lock
	if (((signal!=1)&&(signal!=2))||(dozvoli)){
		stigao[signal]=1;
		obradii->dodaj(signal);
		fleg=1;
		if (mojanit->myPCB->status==0){
				mojanit->myPCB->status=3;
				KernelSem::izbrisiizsem(mojanit->getId());
				Scheduler::put(mojanit->myPCB);
			}
	}

	unlock
}

void Sig::registerHandler(SignalId signal, SignalHandler handler){
	lock
	hendleri[signal]->dodaj(handler);
	unlock
}


void Sig::unregisterAllHandlers(SignalId id){
	lock
	for(int i=0;i<16;i++)
		hendleri[i]->izbacisve();
	unlock
}

void Sig::swap(SignalId id, SignalHandler hand1, SignalHandler hand2){
	lock
	hendleri[id]->swap(hand1, hand2);
	unlock
}

void Sig::blockSignal(SignalId signal){
	lock
	lokalniblok[signal]=1;
	unlock
}

void Sig::blockSignalGlobally(SignalId signal){
	lock
	globalniblok[signal]=1;
	unlock
}

void Sig::unblockSignal(SignalId signal){
	lock
	lokalniblok[signal]=0;
	unlock
}

void Sig::unblockSignalGlobally(SignalId signal){
	lock
	globalniblok[signal]=0;
	unlock
}

void Sig::obradi(){
	System::obradasig=1;
	Sig *s=System::running->signal;
	int x=0;
	if (s->fleg){
		for(int j=0;j<s->obradii->brelemm();){
			int i=s->obradii->dohv(j);
			if ((s->stigao[i]!=0)&&(s->lokalniblok[i]==0)&&(globalniblok[i]==0)){
				s->hendleri[i]->obradi();
				s->stigao[i]=0;
				s->obradii->izbaci();
			}
			else j++;
			if (s->stigao[i]!=0) x=1;
		}
	}
	s->fleg=x;
	System::obradasig=0;
}
