
#ifndef KSEM_H_
#define KSEM_H_
//#include "Semaphore.h"
#include "semaphor.h"

class Lista;

class KernelSem {

	int value;
	Lista* beskonacni;
	Lista* vremenski;
	KernelSem* sledecisem;

public:
	KernelSem(int init);
	~KernelSem();

	int wait (Time t);
	int signal(int n);
	int val () const;
	static void prosaotakt();

	volatile static KernelSem* prvisem;

	static void izbrisiizsem(int id);

};

#endif /* KSEM_H_ */
