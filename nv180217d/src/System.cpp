#include "System.h"
#include "PCB.h"
#include "DOS.H"
#include "SCHEDULE.H"
#include "KSem.h"
#include "Sig.h"

//////////
//#include "Testerna.h"
#include "IOSTREAM.H"
#include "Lista.h"
#include "semaphor.h"
//#include "Testdv.h"
#include "thread.h"
////////
PCB* System::main=0;
volatile PCB* System::running=0;
volatile PCB* System::idle=0;
volatile int System::zahtevanapromena=0;
/*volatile*/ InterruptRoutine System::stararutina=0;
volatile int System::quantum=0;

volatile int System::obradasig=0;

Thread * System::mainnit=0;
/////
volatile unsigned int System::lockflag=1;
/////
extern void tick();

void interrupt System::timer(...){
/*
	System::lockflag=0;
	cout<<"TIMER "<<quantum<<"  -  "<<zahtevanapromena<<endl;
	System::lockflag=1;
*/
	static unsigned tsp=0;
	static unsigned tss=0;
	static unsigned tbp=0;

	if (!zahtevanapromena){
		asm int 60h;
		quantum--;
		KernelSem::prosaotakt();
		tick();
	}


	if ((zahtevanapromena)||((quantum==0)&&(!zahtevanapromena))){
		if ((lockflag)&&(!obradasig)){


		asm {
				// cuva sp
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}

			running->sp = tsp;
			running->ss = tss;
			running->bp = tbp;

			System::lockflag=0;
			//cout<<"Menjam rutinu sa "<< Thread::getRunningId();
			System::lockflag=1;

			if (((running->status!=0)&&(running->status!=2))&&(running->id!=-1)){
				running->status=3;
				Scheduler::put((PCB*)running);
			}
			running=Scheduler::get();
			if (running==0)running=idle;

			running->status=1;

			System::lockflag=0;
			//cout<<" na "<<Thread::getRunningId()<<endl;
			System::lockflag=1;

			tsp = running->sp;
			tss = running->ss;
			tbp = running->bp;
			zahtevanapromena=0;//////
			quantum = running->vreme;

			asm {
				// restaurira sp
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
				}
			Sig::obradi();
	   }
	}
	else Sig::obradi();

	///if (zahtevanapromena) zahtevanapromena=0;//////
	//zahtevanapromena=0;//////

}

void System::inc(){
	lock

	#ifndef BCC_BLOCK_IGNORE
	stararutina = getvect(0x8);
	setvect(0x8,&timer);
	setvect(0x60, stararutina);
	#endif
	mainnit= new Thread();
	main= mainnit->myPCB;
	idle=new PCB(2);
	running=(volatile PCB*)main;
	unlock

}

void System::restore(){
	lock
	delete System::main;
	delete System::idle;
	delete PCB::sviPCBovi;
	#ifndef BCC_BLOCK_IGNORE
	setvect(0x8,stararutina);
	#endif
	unlock
}
/*
void sig11(){
	System::lockflag=0;
			cout<<"Siiggg111 "<<endl;
			System::lockflag=1;

}

void sig22(){
	System::lockflag=0;
			cout<<"Siiggg222 "<<endl;
			System::lockflag=1;

}

void sig33(){
	System::lockflag=0;
			cout<<"Siiggg333 "<<endl;
			System::lockflag=1;

}*/
/*
int System::usermainn(int argc, char** argv){

	Testerna *t1,*t2;
	t1= new Testerna(t2);
	t2= new Testerna(t1);
	t1->start();
	t2->start();
	t1->registerHandler(5, sig11);
	t1->registerHandler(5, sig22);
	t1->registerHandler(5, sig33);
	t1->signal(5);
	dispatch();
	dispatch();
	t1->swap(5,sig33,sig22);
	t1->signal(5);
	delete t1;
	delete t2;
	System::lockflag=0;
		cout<<"Happy end "<<endl;
		System::lockflag=1;

}*/
