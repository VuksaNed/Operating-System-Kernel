#include "PCB.h"
#include "Lista.h"
#include "DOS.H"
#include "System.h"
#include "Sig.h"


PCB::PCB(StackSize stackSize, Time timeSlice, Thread* n){
	lock
	if (identifikator==0){///za mejn
		id=identifikator++;
		vreme=0;
		blokirajucevreme=0;
		status=1;
		ss=0;
		bp=0;
		sp=0;
		velicinasteka=0;
		nit=0;
		cekaniPCBovi=new Lista();
		ret=1;
		signal= new Sig(0);
		roditelj=0;
		sviPCBovi->dodaj(this);

	}else {
	velicinasteka=stackSize/sizeof(unsigned);
	stek=new unsigned[velicinasteka];
	#ifndef BCC_BLOCK_IGNORE
	stek[velicinasteka-1]=0x200; //setovanje I bita
	stek[velicinasteka-2] = FP_SEG(&pozivna);
	stek[velicinasteka-3] = FP_OFF(&pozivna);
	sp = FP_OFF(stek+velicinasteka-12);
	ss = FP_SEG(stek+velicinasteka-12);
	#endif
	bp=sp;
	blokirajucevreme=0;
	vreme=timeSlice;
	nit=n;
	id=identifikator++;
	cekaniPCBovi=new Lista();
	ret=1;
	status=4;
	signal= new Sig(n);
	roditelj=System::running->nit;
	sviPCBovi->dodaj(this);
	}
	unlock
}



PCB::PCB(unsigned x){ ////idle
	lock
	stek=new unsigned[512];
	velicinasteka=512;
	#ifndef BCC_BLOCK_IGNORE
	stek[velicinasteka-1]=0x200; //setovanje I bita
	stek[velicinasteka-2] = FP_SEG(&petlja);
	stek[velicinasteka-3] = FP_OFF(&petlja);
	sp = FP_OFF(stek+velicinasteka-12);
	ss = FP_SEG(stek+velicinasteka-12);
	#endif
	bp=sp;
	blokirajucevreme=0;
	vreme=1;
	nit=0;
	id=-1;
	cekaniPCBovi=new Lista();
	ret=1;
	signal= new Sig(0);
	roditelj=System::running->nit;
	status=3;
	unlock
}

PCB::~PCB(){
	lock
	if (id!=0) delete stek;
	delete cekaniPCBovi;
	delete signal;
	unlock
}

void PCB::pozivna(){
	System::running->nit->run();

	lock
	System::running->status=2;
	while (System::running->cekaniPCBovi->dohvbrelem()>0)System::running->cekaniPCBovi->izbaciprvi();
	Sig::dozvoli=1;
	if (System::running->roditelj!=0) System::running->roditelj->signal(1);
	System::running->nit->signal(2);
	Sig::dozvoli=0;
	dispatch();
	unlock
}

void PCB::petlja(){
	while(1){

	}
}

ID PCB::identifikator=0;
Lista* PCB::sviPCBovi=new Lista();
