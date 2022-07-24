
#include "KSem.h"
#include "Lista.h"
#include "System.h"
#include "PCB.h"

volatile KernelSem* KernelSem::prvisem=0;

KernelSem::KernelSem(int init){
	lock
	value=init;
	beskonacni=new Lista();
	vremenski=new Lista();
	sledecisem=0;

	if (prvisem==0) prvisem=this;
	else{
		sledecisem=(KernelSem*)prvisem;
		prvisem=this;
	}
	unlock
}

KernelSem::~KernelSem(){
	if (prvisem==this) prvisem=sledecisem;
	else{
	KernelSem *pom=(KernelSem*)prvisem;
	while(pom->sledecisem!=this) pom=pom->sledecisem;
	pom->sledecisem=this->sledecisem;
	}
	delete beskonacni;
	delete vremenski;

}

int KernelSem::wait (Time t){
	lock
	value--;
	if (value>=0){
		unlock
		return 1;
	}
	else if(t==0){
		System::running->blokirajucevreme=0;
		System::running->ret=1;
		beskonacni->dodaj((PCB*)System::running);
	}
	else{
		System::running->blokirajucevreme=t;
		vremenski->dodaj((PCB*)System::running);
	}
	System::running->status=0;
	dispatch();
	unlock
	return System::running->ret;
}

int KernelSem::signal(int n){
	lock
	if (n<0){
		unlock
		return n;
	}
	else if(n==0)value++;
	else value+=n;

	if (n>0){
		int ret=n;
		while((n>0)&&(beskonacni->dohvbrelem()>0)){
			beskonacni->izbaciprvi();
			n--;
		}

		while((n>0)&&(vremenski->dohvbrelem()>0)){
				vremenski->izbaciprvi();
					n--;
				}
		unlock
		return ret-n;
	}
	else if(value<=0){
		if (beskonacni->dohvbrelem()>0) beskonacni->izbaciprvi();
		else if(vremenski->dohvbrelem()>0) vremenski->izbaciprvi();
	}
	unlock
	return 0;

}

int KernelSem::val () const{
	return value;
}

void KernelSem::prosaotakt(){
	KernelSem* pom=(KernelSem*)prvisem;
	while(pom!=0){
		pom->vremenski->smanjizajedan();
		pom=pom->sledecisem;
	}
}

void KernelSem::izbrisiizsem(int id){
	KernelSem* pom=(KernelSem*)prvisem;
	while (pom!=0){
		if (pom->beskonacni->izbaciizsema(id)){
			return;
		}
		pom=pom->sledecisem;
	}
}
