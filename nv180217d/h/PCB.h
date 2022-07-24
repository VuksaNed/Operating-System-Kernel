
#ifndef PCB_H_
#define PCB_H_
#include "thread.h"

class Lista;
class Thread;
class Sig;

class PCB {
private:
	static ID identifikator;

	ID id;
	Time vreme;
	Time blokirajucevreme;
	unsigned int status;//blokirana=0 running=1 finished=2 ready=3 new=4
	unsigned int ss,sp,bp;
	unsigned int* stek;
	StackSize velicinasteka;
	Thread* nit;
	Lista* cekaniPCBovi;
	unsigned ret;
	Thread* roditelj;
	Sig* signal;

public:
	PCB(StackSize stackSize, Time timeSlice,Thread* n);
	PCB();
	PCB(unsigned x);
	~PCB();

	static void pozivna();
	static void petlja();
	static Lista* sviPCBovi;

	//prijatelji
	friend class Thread;
	friend class Lista;
	friend class System;
	friend class KernelSem;
	friend class KernelEv;
	friend class Sig;

	//
	//friend class Testerna;

};

#endif /* PCB_H_ */
