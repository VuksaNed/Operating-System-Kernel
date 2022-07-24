/*
 * Sig.h
 *
 *  Created on: Apr 28, 2020
 *      Author: OS1
 */

#ifndef SIG_H_
#define SIG_H_

typedef void (*SignalHandler)();
typedef unsigned SignalId;
class Siglist;
class Thread;
class Listint;

class Sig {
private:
	int lokalniblok[16];
	int stigao[16];
	int fleg;
	Siglist* hendleri[16];
	Thread *mojanit;
	Listint* obradii;
public:
	Sig(Thread *t);
	virtual ~Sig();

	void signal(SignalId signal);

	void registerHandler(SignalId signal, SignalHandler handler);
	void unregisterAllHandlers(SignalId id);

	void swap(SignalId id, SignalHandler hand1, SignalHandler hand2);

	void blockSignal(SignalId signal);
	static void blockSignalGlobally(SignalId signal);

	void unblockSignal(SignalId signal);
	static void unblockSignalGlobally(SignalId signal);

	static int globalniblok[16];
	static void blokiraj();
	static void obradi();
	static int dozvoli;
};

#endif /* SIG_H_ */
