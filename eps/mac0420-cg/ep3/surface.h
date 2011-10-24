#ifndef SURFACE_H_
#define SURFACE_H_

#include <iostream>

class Surface {
public:
	Surface() {}
	~Surface() {}
	double ambiente, difusao, especular, brilho,
		reflexao, transmissao, refracao;


	friend std::ostream& operator<< (std::ostream& io, Surface& s) {
		return io << "Amb: " << s.ambiente << ", Diff: " << s.difusao <<
				", Espec: " << s.especular << ", Brilho: " << s.brilho <<
				", Reflexao: " << s.reflexao << ", Tramissao: " << s.transmissao <<
				", Refracao: " << s.refracao;
	}
	friend std::istream& operator>> (std::istream& io, Surface& s) {
		return io >> s.ambiente >> s.difusao >> s.especular >>
				s.brilho >> s.reflexao >> s.transmissao >> s.refracao;
	}
};

#endif /* SURFACE_H_ */
