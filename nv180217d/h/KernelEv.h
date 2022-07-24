#ifndef KERNELEV_H_
#define KERNELEV_H_

//#include "event.h"
#include "IVTEntry.h"

#define PREPAREENTRY(brulaza,fleg) \
	void interrupt prr##brulaza(...); \
	IVTEntry ulaz##brulaza(brulaza, prr##brulaza); \
	void interrupt prr##brulaza(...) { \
		ulaz##brulaza.signall(); \
		ulaz##brulaza.pokrenistaru(fleg); \
	}


class PCB;
class IVTEntry;

class KernelEv {
private:

	int value;
	int blokiran;

	PCB* napravio;
	IVTEntry *ulaz;


public:

	KernelEv(IVTNo ivtNo);

	~KernelEv ();

	void wait ();

	void signal();

};

#endif /* KERNELEV_H_ */
