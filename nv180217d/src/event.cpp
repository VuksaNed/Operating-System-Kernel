/*
 * event.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: OS1
 */

#include "event.h"
#include "System.h"
#include "KernelEv.h"
#include "IVTEntry.h"

Event::Event (IVTNo ivtNo){
	lock
	myImpl=new KernelEv(ivtNo);
	IVTEntry::sviivt[ivtNo]->mojdogadjaj=this;
	unlock
}

Event::~Event (){
	lock
	delete myImpl;
	unlock
}

void Event::wait (){
	lock
	myImpl->wait();
	unlock
}

void Event::signal(){
	lock
	myImpl->signal();
	unlock
}
