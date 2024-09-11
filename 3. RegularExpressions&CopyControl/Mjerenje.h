#ifndef MJERENJE_H
#define MJERENJE_H

#include <iostream>
#include <string>

class Mjerenje {
public:
	typedef int iznos; //
	Mjerenje(std::ifstream &);//
	Mjerenje(const Mjerenje &); //
	Mjerenje& operator=(const Mjerenje&); //
	Mjerenje(Mjerenje&&) noexcept; //
	Mjerenje& operator=(Mjerenje &&) noexcept; //
	~Mjerenje(); //
	Mjerenje& dodaj(iznos); //
	Mjerenje& ispis(std::ostream &); //
private:
	static int brojac; //
	int id;
	std::string naziv;
	int br_mjerenja;
	iznos *mjerenja;
	int	*br_ref;
};

#endif