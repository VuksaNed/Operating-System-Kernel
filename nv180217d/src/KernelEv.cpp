/*
 * KernelEv.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: OS1
 */

#include "KernelEv.h"
#include "System.h"
#include "PCB.h"
#include "thread.h"
#include "SCHEDULE.H"
#include "IVTEntry.h"

KernelEv::KernelEv(IVTNo ivtNo){
	lock
	value=0;
	blokiran=0;
	napravio=(PCB*)System::running;
	ulaz=IVTEntry::sviivt[ivtNo];
	unlock

}

KernelEv::~KernelEv(){
	lock
	delete ulaz;
	unlock
}

void KernelEv::wait(){
	lock
	if (System::running!=napravio){
		if (value==1){
			value=0;
		}
		else{
			blokiran=1;
			System::running->status=0;
			dispatch();
		}
	}
	unlock
}

void KernelEv::signal(){
	lock
	if (value==1){
		unlock
		return;
	}
	if (blokiran==0) value++;
	else {
		blokiran=0;
		napravio->status=3;
		Scheduler::put(napravio);
	}
	unlock
}
