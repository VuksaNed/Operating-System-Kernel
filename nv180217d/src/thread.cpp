#include "thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "System.h"
#include "Lista.h"
#include "Sig.h"
//
#include "IOSTREAM.H"
//

void Thread::start(){
	lock
	this->myPCB->status=3;
	Scheduler::put(this->myPCB);
	unlock
}

void Thread::waitToComplete(){
	lock
	if ((myPCB->status!=2)&&(myPCB->nit!=System::running)){
		System::running->status=0;
		this->myPCB->cekaniPCBovi->dodaj((PCB*)System::running);
		dispatch();
	}
	unlock
}

Thread::~Thread(){
	lock
	waitToComplete();
	PCB::sviPCBovi->izbaci(myPCB->id);
	delete myPCB;
	unlock
}

 ID Thread::getId(){
	 return myPCB->id;
 }

ID Thread::getRunningId(){
	//lock
	return System::running->id;
	//unlock
}


Thread * Thread::getThreadById(ID id){
	 return PCB::sviPCBovi->dohvNit(id);
 }

void Thread::signal(SignalId signal){
	lock
	myPCB->signal->signal(signal);
	unlock
}

void Thread::registerHandler(SignalId signal, SignalHandler handler){
	lock
	myPCB->signal->registerHandler(signal, handler);
	unlock
}
void Thread::unregisterAllHandlers(SignalId id){
	lock
	myPCB->signal->unregisterAllHandlers(id);
	unlock
}

void Thread::swap(SignalId id, SignalHandler hand1, SignalHandler hand2){
	lock
	myPCB->signal->swap(id, hand1, hand2);
	unlock
}

void Thread::blockSignal(SignalId signal){
	lock
	myPCB->signal->blockSignal(signal);
	unlock
}
void Thread::blockSignalGlobally(SignalId signal){
	lock
	Sig::blockSignalGlobally(signal);
	unlock
}

void Thread::unblockSignal(SignalId signal){
	lock
	myPCB->signal->unblockSignal(signal);
	unlock
}
void Thread::unblockSignalGlobally(SignalId signal){
	lock
	Sig::unblockSignalGlobally(signal);
	unlock
}

Thread::Thread (StackSize stackSize, Time timeSlice){
	lock
	myPCB=new PCB(stackSize, timeSlice, this);
	unlock
}

void dispatch (){
	lock
	System::zahtevanapromena=1;
	System::timer();
	unlock
}
