
#include "IVTEntry.h"
#include "DOS.H"
#include "System.h"
#include "KernelEv.h"
#include "event.h"

IVTEntry** IVTEntry::sviivt= new IVTEntry*[256];

IVTEntry::IVTEntry(IVTNo ivtNo, InterruptRoutine nova){
	lock
	#ifndef BCC_BLOCK_IGNORE
	stara = getvect(ivtNo);
	setvect(ivtNo,nova);
	#endif
	broj=ivtNo;
	mojdogadjaj=0;
	sviivt[ivtNo]=this;
	unlock
}

IVTEntry::~IVTEntry(){
	lock
	#ifndef BCC_BLOCK_IGNORE
	setvect(broj,stara);
	#endif
	sviivt[broj]=0;
	unlock
}

void IVTEntry::signall(){
	if (mojdogadjaj!=0)
		mojdogadjaj->signal();
}

void IVTEntry::pokrenistaru(int p){
	lock
	if (p==1)
		stara();
	unlock
}
