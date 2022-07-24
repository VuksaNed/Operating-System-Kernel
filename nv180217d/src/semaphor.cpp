#include "semaphor.h"
#include "KSem.h"
#include "System.h"

 Semaphore::Semaphore (int init){
	// lock
	 myImpl=new KernelSem(init);
	// unlcok
 }

Semaphore::~Semaphore (){
	delete myImpl;
}

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

int Semaphore::signal(int n){
	return myImpl->signal(n);
}

int Semaphore::val () const{
	return myImpl->val();
}
