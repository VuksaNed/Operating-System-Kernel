#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "DOS.H"

typedef void interrupt (*InterruptRoutine)(...);

#define lock asm pushf; asm cli;

#define unlock asm popf;

class PCB;
class Thread;

class System {

public:
	static void inc();
	static void restore();
	static void interrupt timer(...);


	static /*volatile*/ PCB* main;
	static volatile PCB* running;
	static volatile PCB* idle;
	static volatile int zahtevanapromena;
	static volatile int quantum;

	static volatile int obradasig;

	//static void tick() {}

	static /*volatile*/ InterruptRoutine stararutina;

	static Thread* mainnit;

	////static int usermainn(int argc, char** argv);/////////
	static volatile unsigned int lockflag;
};

#endif /* SYSTEM_H_ */
