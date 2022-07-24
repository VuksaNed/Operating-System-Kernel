/*
 * IVTEntry.h
 *
 *  Created on: Apr 18, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "System.h"

typedef unsigned char IVTNo;
class Event;


class IVTEntry {

	InterruptRoutine stara;
	Event* mojdogadjaj;
	IVTNo broj;

	static IVTEntry** sviivt;

public:
	IVTEntry(IVTNo ivtNo, InterruptRoutine nova);
	~IVTEntry();

	void signall();
	void pokrenistaru(int p);

	friend class Event;
	friend class KernelEv;
};

#endif /* IVTENTRY_H_ */
