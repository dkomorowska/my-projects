#ifndef ClassInstrumenty
	
	#define ClassInstrumenty

class instrument
{
	protected: //private:
		char	model[20];
		char 	marka[20];
		char 	nazwa[20];
		char 	rodzaj[20];
		float 	cena;
		float 	waga;
		int 	sztuk;
		
		bool zaznaczony; //flaga dotyczy pojedynczego instrumentu a nie całej bazy
		
	public:
		instrument();
		instrument(char* mod, char* mar, char* rodz, char *naz, float cen, float wag, int szt);
		void  	czysc();
		void  	setNazwa(char *naz);
		void 	setModel(char* mod);
        void 	setMarka(char* mar);
        void 	setRodzaj(char* rodz);
        bool 	setCena(float cena);
        bool 	setWaga(float waga);
		void  	setSztuk(int szt);
		void  	pobierz(char* naz, char* mod, char* mar, char* rodz, float cen, float wag , int szt);
		char* 	getNazwa();
		char* 	getModel();
        char* 	getMarka();
        char* 	getRodzaj();
		float 	getCena();
		int   	getSztuk();
		float 	getWaga();
		float 	wartosc();
		
				//flaga
		void 	setZaznaczony(bool status);   // ustawienie flagi
    	bool 	getZaznaczony();        
    	void 	zmianaZaznaczony();           // przełączanie
};
#include "instrumenty.cpp"	
#endif