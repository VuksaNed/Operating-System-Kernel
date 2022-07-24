
#ifndef LISTKS_H_
#define LISTKS_H_

class KernelSem;

class Listks {
	struct Elem{
		KernelSem* info;
		Elem* sled;
		Elem(KernelSem* e):info(e), sled(0){};
	};
	Elem* prvi, *poslednji;
	int brelem;
public:
	Listks();
	~Listks();
	void dodaj(KernelSem *e);
	void izbaci(KernelSem* e);
	int dohvbr();
	KernelSem* dohvkernel(int i);

};

#endif /* LISTKS_H_ */
