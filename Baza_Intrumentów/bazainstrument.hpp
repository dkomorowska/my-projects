#ifndef ClassBazaInstrument
	#define BlassBazaInstrument
	#include <vector>

class bazainstrument
{
	protected:
		int 	rozmiar;
		int 	licznosc;
		int 	licznoscFound;
		int 	current;		//indeks elementu aktualnego, dziedzina liczby
		int 	currentFound;		//wartosc -1 oznacza brak elementu aktualnego
		int		currentKosz;
		int		licznoscKosz;
		
		vector 		<instrument> tab;
		vector 		<instrument> found;
		vector  	<instrument> kosz;
		
	private:
		int i;
	public:
		bazainstrument();
		void 	dodajkolejny(char* naz, char* mod, char* mar, char* rodz, float cen, float wag, int szt);
		void 	czysccalosc();
		instrument& getInstrumenty(int i);
		instrument& getTab();
		int 	getLicznosc();
		float 	sumawartosc();
		void 	saveFile();
		void 	readFile();
		bool 	setCurrent(int index);
		bool 	next();
		bool 	previous();
		int 	getCurrent();
		void 	deleteCurrent(int i);
		void 	deleteCurrentFound(int i);
		void 	sortSztuk();
		void 	sortCena();		//rosnaco
		bool 	sortNazwa();	//rosnaco
		int 	searchCena(float min, float max);		//lepszy bylby int
		bool 	searchNazwa(char szukanaNazwa[]);
		int 	getLicznoscFound();
		int 	getCurrentFound();
		instrument& getInstrumentFound(int i);
		instrument getFound();
		bool 	nextFound();
		bool 	previousFound();
		
		//kosz
		instrument 	getInstrumentKosz(int i);
		instrument 	getKosz();
		bool 	nextKosz();
		bool 	previousKosz();
		void 	deleteCurrentKosz();
		void 	przywrocKosz(int i);
		int		getCurrentKosz();
		int		getLicznoscKosz();
		void 	czyscKosz();
		bool	setCurrentKosz(int index);
		void	deleteWszystkoKosz();
		
		//zaznaczone
		void 	saveZaznaczone();
		void 	readZaznaczone();
		void	saveZnalezione();
		void	readZnalezione();
};

#endif
#include "bazainstrument.cpp"