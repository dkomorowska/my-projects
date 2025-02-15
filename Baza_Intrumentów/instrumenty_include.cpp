#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <vector>

#include "instrumenty.hpp"
#include "bazainstrument.hpp"

using namespace std;


void gotoxy(int x, int y);

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x-1;
	c.Y = y-1;
	SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
}

void piszInstrumentyXY(instrument t, int x, int y);


void piszInstrumentyXY(instrument t, int x, int y) 
{
    
    gotoxy(x, y + 1);
	cout << "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    gotoxy(x, y + 2);
    cout << "   | \033[36mNazwa   \033[0m : " << t.getNazwa();
    gotoxy(x + 54, y + 2); 
	cout << "|";
    gotoxy(x, y + 3);
    cout << "   | \033[36mModel   \033[0m : " << t.getModel();
    gotoxy(x + 54, y + 3); 
	cout << "|";
    gotoxy(x, y + 4);
    cout << "   | \033[36mMarka   \033[0m : " << t.getMarka();
    gotoxy(x + 54, y + 4); 
	cout << "|";
    gotoxy(x, y + 5);
    cout << "   | \033[36mRodzaj  \033[0m : " << t.getRodzaj();
    gotoxy(x + 54, y + 5); 
	cout << "|";
    gotoxy(x, y + 6);
    cout << "   | \033[36mCena    \033[0m : " << t.getCena() << " zl";
    gotoxy(x + 54, y + 6); 
	cout << "|";
    gotoxy(x, y + 7);
    cout << "   | \033[36mWaga    \033[0m : " << t.getWaga() << " kg";
    gotoxy(x + 54, y + 7); 
	cout << "|";
    gotoxy(x, y + 8);
    cout << "   | \033[36mSztuk   \033[0m : " << t.getSztuk();
    gotoxy(x + 54, y + 8); 
	cout << "|";
    gotoxy(x, y + 9);
    cout << "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
}	

main(int argc, char** argv)
{
	char n[20], zn, r[20], mr[20], md[20], szukanaNazwa[30];
	float c, w, min, max;
	int sz, i, rozmiar;
	
	bazainstrument baza;

	do
	{
		cout << "\033[36m" R"(	
			|-----|\---|~~~~|-------------|\---|~~~~|----|
			|-----|/--_|---_|---M-E-N-U---|/--_|---_|----|
			|---(_)--(_)--(_)-----------(_)--(_)--(_)----|
    )"<<"\033[0m"<<endl;
		cout<<endl<<"				1. czyszczenie calej tablicy"<<endl;
		cout<<"				2. dodanie nowego elementu"<<endl;
		cout<<"				3. wypisanie calej tablicy"<<endl;
		cout<<"				4. suma wartosci"<<endl;
		cout<<"				6. save to file"<<endl;
		cout<<"				7. read from file"<<endl;
		cout<<"				8. display current"<<endl;
		cout<<"				s. set current"<<endl;
		cout<<"				p. przegladaj"<<endl;
		cout<<"				f. FIND - nazwa, cena"<<endl;
		cout<<"				z. przegladaj - znalezione"<<endl;
		cout<<"				a. SORT ascending - nazwa, cena, sztuk"<<endl;
		cout<<"				m. ZAZNACZONE"<<endl;
		cout<<"				k. KOSZ"<<endl<<endl;
		cout<<"				5. koniec"<<endl;
		zn=getch();
	
		system("cls");
		switch (zn)
	{
		case '1': 	
							if (baza.getLicznosc() == 0) 
					    {
					        cout<<"brak elementow w bazie"<<endl; 
					        break;
					    }
						cout<<"czy na pewno chcesz wyczyscic tablice?"<<endl<<"t - TAK           n - NIE"<<endl;
						zn=getch();
						switch(zn)
						{
							
							case 't':	baza.czysccalosc();
										system("cls");
										cout<<"wyczyszczono"<<endl;
								break;
							case 'n':
								system("cls");
								break;
						}
			break;
		case '2': 	fflush(stdin);
					cout<<"\033[36m"<<"			DODAWANIE NOWEGO INSTRUMENTU : "<<"\033[0m"<<endl<<endl;
					cout<<"nazwa    : ";
					gets(n);
					cout<<"model    : ";
					gets(md);
					cout<<"marka    : ";
					gets(mr);
					cout<<"rodzaj   : ";
					gets(r);
					do {
			        cout<<"cena     : ";
			        cin>>c;
			        if (c <= 0) 
					{
			            cout << "nieprawidlowa cena! wprowadz wartosc dodatnia"<<endl;
			            cin.clear();
			            fflush(stdin);
			        } else {
			            break;
			        }
			    	} while (true);
			
			    do {
			        cout<<"waga     : ";
			        cin>>w;
			        if (w <= 0) 
					{
			            cout << "nieprawidlowa waga! wprowadz wartosc dodatnia"<<endl;
			            cin.clear();
			            fflush(stdin);
			        } else {
			            break;
			        }
			  	  }while(true);
					
					do {
					cout<<"sztuk    : ";
					cin>>sz;
					if (sz<=0) 
			        {
			            cout<<"nieprawidlowa ilosc sztuk! wprowadz wartosc dodatnia"<<endl;
			            cin.clear();
			            fflush(stdin);
			        } 
			        else 
			        {
			            break;
			        }
			    	} while (true);
					cin.ignore();
					
					baza.dodajkolejny(n,md,mr,r,c,w,sz);
			break;
		case '3':
			 	system("cls");
			    if (baza.getLicznosc() == 0)
			    {
			        cout<<"brak instrumentow w bazie"<<endl;
			    }
			    else
			    {
			    	for (i=0; i<baza.getLicznosc(); i++)
			    	{
						cout<<"\033[31m"<<"			instrument nr "<<i+1<<" :\033[0m"<<endl<<endl;
			            cout<<"	nazwa  :	"<<baza.getInstrumenty(i).getNazwa()<<"    "<<endl;
			            cout<<"	model  :	"<<baza.getInstrumenty(i).getModel()<<"    "<<endl;
			            cout<<"	marka  :	"<<baza.getInstrumenty(i).getMarka()<<"    "<<endl;
			            cout<<"	rodzaj :	"<<baza.getInstrumenty(i).getRodzaj()<<"    "<<endl;
			            cout<<"	cena   :	"<<baza.getInstrumenty(i).getCena()<<"zl    "<<endl;
			            cout<<"	waga   :  	"<<baza.getInstrumenty(i).getWaga()<<"kg    "<<endl;
			            cout<<"	sztuk  : 	"<<baza.getInstrumenty(i).getSztuk()<<"    "<<endl;
			            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
			        }
			    }
			    cout<<"nacisnij ENTER, aby wrocic do menu"<<endl;
    			cin.ignore();
    			system("cls");
		    break;
		case '4': 	cout<<"suma wszystkich wartosci = "<<baza.sumawartosc()<<"zl"<<endl;
			break;
		case '6': 	cout<<"czy na pewno chcesz nadpisac plik?"<<endl<<"t - TAK           n - NIE"<<endl;
						zn=getch();
						switch(zn)
						{
							
							case 't':	baza.saveFile();
										cout<<"zapisano"<<endl;
								break;
							case 'n':
								break;
						}
			break;
		case '7': 	cout<<"czy na pewno chcesz wczytac plik?"<<endl<<"t - TAK           n - NIE"<<endl;
						zn=getch();
						switch(zn)
						{
							case 't': 	baza.readFile();
										cout<<"odczytano"<<endl;
								break;
							case 'n':	
								break;
						}
			break;
		case '8': 	i=baza.getCurrent();
					    if (baza.getLicznosc() == 0) 
					    {
					        cout<<"brak elementow w bazie"<<endl;
					        cout<<"nacisnij ENTER, aby wrocic do menu"<<endl;
					        getch();
					        system("cls");
					        break;
					    }
					else
						piszInstrumentyXY(baza.getInstrumenty(i), 5, 10); //dorobic boole brak kolejnych i brak poprzednich
						cout<<"			nacisnij ENTER by wyjsc";
						getch();
						system("cls");
			break;
		case 'm':
			{
						bool zaznaczone = false;
			    for (int i = 0; i < baza.getLicznosc(); i++) 
			    {
			        if (baza.getInstrumenty(i).getZaznaczony()) 
			        {
			            zaznaczone=true;
			            break;
			        }
			    }
			
			    if (!zaznaczone) 
			    {
			        cout<<"brak zaznaczonych elementow w bazie"<<endl;
			        cout<<"nacisnij ENTER, aby wrocic do menu"<<endl;
			        getch();
			        break;
			    }
			    cout<<"\033[36m"<<"wybierz operacje:"<<"\033[0m"<<endl;
			    cout<<"1 - usun zaznaczone elementy"<<endl;
			    cout<<"2 - zapisz zaznaczone elementy do pliku"<<endl;
			    cout<<"3 - odczytaj zaznaczone elementy i dodaj do bazy"<<endl;
			    cout<<"4 - wyswietl liste zaznaczonych elementow"<<endl;
			    
			    zn = getch();
			
			    switch (zn)
			    {
			        case '1':
			        {
			            cout<<"czy na pewno chcesz usunac wszystkie zaznaczone elementy? (t - TAK    n - NIE)"<<endl;
			            zn = getch();
			            switch (zn) 
			            {
			                case 't':
			                    for (int i = baza.getLicznosc() - 1; i >= 0; i--) 
			                    {
			                        if (baza.getInstrumenty(i).getZaznaczony()) 
			                        {
			                            baza.deleteCurrent(i);
			                        }
			                    }
			                    system("cls");
			                    cout<<"usunieto wszystkie zaznaczone elementy"<<endl;
			                    break;
			
			                case 'n':
			                	system("cls");
			                    cout<<"operacja anulowana"<<endl;
			                    break;
			
			                default:
			                    cout<<"nieznana opcja"<<endl;
			                    break;
			            }
			            break;
			        }
			
			        case '2':
			        {
			            cout<<"czy na pewno chcesz zapisac zaznaczone elementy do pliku? (t - TAK   n - NIE)"<<endl;
			            zn = getch();
			            switch (zn) 
			            {
			                case 't':
			                    baza.saveZaznaczone();
			                    system("cls");
			                    cout<<"zaznaczone elementy zostaly zapisane do pliku 'zaznaczone.dat'"<<endl;
			                    break;
			
			                case 'n':
			                	system("cls");
			                    cout<<"anulowano"<<endl;
			                    break;
			
			                default:
			                    cout<<"nieznana opcja"<<endl;
			                    break;
			            }
			            break;
			        }
			        case '3':
        			{
			            cout<<"czy na pewno chcesz odczytac zaznaczone elementy z pliku? (t - TAK    n - NIE)"<<endl;
			            zn = getch();
			            switch (zn) 
			            {
			                case 't':
			                    baza.readZaznaczone();
			                    break;
			
			                case 'n':
			               		system("cls");
			                    cout<<"anulowano"<<endl;
			                    break;
			
			                default:
			                    cout<<"nieznana opcja"<<endl;
			                    break;
			            }
			            break;
					}
					    break;
					case '4':
			        {
			            system("cls");
			            cout<<"\033[36m"<<"lista zaznaczonych elementow:" <<"\033[0m"<<endl;
			
			            int licznik = 0;
			            for (int i = 0; i < baza.getLicznosc(); i++) 
			            {
			                if (baza.getInstrumenty(i).getZaznaczony()) 
			                {
			                    cout<<"\033[31m"<<"            instrument nr " << ++licznik << " :\033[0m"<<endl<<endl;
			                    cout<<"    nazwa  :    "<<baza.getInstrumenty(i).getNazwa() << "    "<<endl;
			                    cout<<"    model  :    "<<baza.getInstrumenty(i).getModel() << "    "<<endl;
			                    cout<<"    marka  :    "<<baza.getInstrumenty(i).getMarka() << "    "<<endl;
			                    cout<<"    rodzaj :    "<<baza.getInstrumenty(i).getRodzaj() << "    "<<endl;
			                    cout<<"    cena   :    "<<baza.getInstrumenty(i).getCena() << "zl    "<<endl;
			                    cout<<"    waga   :    "<<baza.getInstrumenty(i).getWaga() << "kg    "<<endl;
			                    cout<<"    sztuk  :    "<<baza.getInstrumenty(i).getSztuk() << "    "<<endl;
			                    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
			                }
			            }
			
			            if (licznik == 0) 
			            {
			                cout<<"brak zaznaczonych elementow"<<endl;
			            }
			
			            cout<<"nacisnij ENTER, aby wrocic do menu"<<endl;
			            getch();
			            system("cls");
			            break;
			        }
				    case 'q':
			            system("cls");
			            break;
				}
			}break;
		case 'p': 
		{ 
		    if (baza.getLicznosc() == 0) 
			{
		        cout<<"brak instrumentow w bazie - nie mozna rozpoczac przegladania"<<endl;
		    } 
			else 
			{
		        cout<<"\033[36m"<<"TRYB PRZEGLADANIA"<<" \033[0m"<<endl;
		        baza.setCurrent(0);
		        bool przegladanie = true;
		        while (przegladanie) 
				{
		            system("cls");
		            int i = baza.getCurrent();
		            if (i == -1) 
					{
		                cout<<"brak elementow do wyswietlenia"<<endl;
		                przegladanie = false;
		            } else 
					{
		                instrument &currentInstrument = baza.getInstrumenty(i);
		                piszInstrumentyXY(currentInstrument, 25, 10);
		
					cout<<"					ZAZNACZENIE --------- [ ";
					if (currentInstrument.getZaznaczony()) 
					{
					    cout<<"X";
					} else 
					{
					    cout<<" ";
					}
					cout<<" ]"<<endl<<endl;		            
					}
					
		            cout<<"\033[36m"<<"	'n' - nastepny   'b' - poprzedni  'z' - zaznacz/odznacz  'u' - update  'd' - delete   'q' - quit"<<" \033[0m"<<endl;
		            zn = getch();
		            switch (zn) {
		                case 'n':
		                    baza.next();
		                    i = baza.getCurrent();
		                    break;
		                case 'b':
		                    baza.previous();
		                    i = baza.getCurrent();
		                    break;
		                case 'z':
						{
						    instrument &currentInstrument = baza.getInstrumenty(i); // Pobranie referencji do instrumentu
						    currentInstrument.zmianaZaznaczony();                  // Zmiana stanu zaznaczenia
						    cout<<(currentInstrument.getZaznaczony() ? "zaznaczony" : "odznaczony")<<endl;
						    getch();
						    break;
						}
		                case 'u': {
		                    system("cls");
		                    
		                    cout<<"\033[36m"<<"\n\n\n\n\n\n\n\n\n						AKTUALIZACJA ELEMENTU"<<" \033[0m"<<endl<<endl;
		                    cout<<"						1 - Nazwa\n";
		                    cout<<"						2 - Model\n";
		                    cout<<"						3 - Marka\n";
		                    cout<<"						4 - Rodzaj\n";
		                    cout<<"						5 - Cena\n";
		                    cout<<"						6 - Waga\n";
		                    cout<<"						7 - Sztuk\n";
		                    cout<<"						8 - Nadpisz caly element\n";
		                    zn=getch();
		                    switch (zn) 
							{
		                        case '1': 
								{
		                            cout<<"			Nowa nazwa: ";
		                            gets(n);
		                            baza.getTab().setNazwa(n);
		                            break;
		                        }
		                        case '2': 
								{
		                            cout<<"			Nowy model: ";
		                            gets(md);
		                            baza.getTab().setModel(md);
		                            break;
		                        }
		                        case '3': 
								{
		                            cout<<"			Nowa marke: ";
									gets(mr);
		                            baza.getTab().setMarka(mr);
		                            break;
		                        }
		                        case '4': 
								{
		                            cout<<"			Nowy rodzaj: ";
									gets(r);
		                            baza.getTab().setRodzaj(r);
		                            break;
		                        }
		                        case '5': 
								{
								    do {
								        cout<<"		Nowa cena: ";
								        cin>>c;
								        if (c <= 0) {
								            cout<<"		nieprawidlowa cena! wprowadz wartosc dodatnia"<<endl;
								        }
								    } while (c <= 0);
								    cin.ignore();
								    baza.getTab().setCena(c);
								    break;
								}
								case '6': 
								{
								    do {
								        cout<<"		Nowa waga: ";
								        cin>>w;
								        if (w<=0) {
								            cout<<"		nieprawidlowa waga! wprowadz wartosc dodatnia"<<endl;
								        }
								    } while (w <= 0);
								    cin.ignore();
								    baza.getTab().setWaga(w);
								    break;
								}
								case '7': 
								{
								    do {
								        cout<<"		Nowa ilosc sztuk: ";
								        cin>>sz;
								        if (sz <= 0) 
										{
								            cout<<"		nieprawidlowa ilosc sztuk! wprowadz wartosc dodatnia"<<endl;
								        }
								    } while (sz<=0);
								    cin.ignore();
								    baza.getTab().setSztuk(sz);
								    break;
								}
		                        case '8': 
								{
		                            cout<<"			Nowa nazwa: ";
		                            gets(n);
		                            baza.getTab().setNazwa(n);
		                            cout<<"			Nowy model: ";
		                            gets(md);
		                            baza.getTab().setModel(md);
		                            cout<<"			Nowa marka: ";
		                            gets(mr);
		                            baza.getTab().setMarka(mr);
		                            cout<<"			Nowy rodzaj: ";
		                            gets(r);
		                            baza.getTab().setRodzaj(r);
							        do {
								        cout<<"			Nowa cena: ";
								        cin>>c;
								        if (c <= 0) {
								            cout<<"			nieprawidlowa cena! wprowadz wartosc dodatnia"<<endl;
								        }
								    } while (c <= 0);
								    cin.ignore();
								    baza.getTab().setCena(c);
							
								    do {
								        cout<<"			Nowa waga: ";
								        cin>>w;
								        if (w<=0) 
										{
								            cout<<"			nieprawidlowa waga! wprowadz wartosc dodatnia"<<endl;
								            cin.clear();
								            fflush(stdin);
								        } else {
								            break;
								        }
								  	  }while(true);
										
										do {
										cout<<"			Nowa sztuk: ";
										cin>>sz;
										if (sz<=0) 
								        {
								            cout<<"			nieprawidlowa ilosc sztuk! wprowadz wartosc dodatnia"<<endl;
								            cin.clear();
								            fflush(stdin);
								        } 
								        else 
								        {
								            break;
								        }
								    	} while (true);
										cin.ignore();    
										      
			                            break;
	                        		}
			                                                          
			                            cout<<"			nieznana opcja"<<endl;
			                            break;
			                    }                    
		                    break;
		                    }
		                
		                case 'd': 
						{  // Dodanie opcji 'd' do przeniesienia elementu do kosza
		                    cout<<"czy chcesz przeniesc ten element do kosza? (t - TAK, n - NIE)"<<endl;
		                    zn = getch();
		                    switch (zn) 
		                    {
		                        case 't':
		                            baza.deleteCurrent(i);  // Przenosi bieĹĽÄ…cy element do kosza
		                            cout<<"element przeniesiony do kosza"<<endl;
		                            break;
		                        case 'n':
		                            cout<<"anulowano przeniesienie"<<endl;
		                            break;
		                        default:
		                            cout<<"nieznana opcja"<<endl;
		                            break;
		                    }
		                    break;
		                }
		                case 'q':
		                    przegladanie = false;
		                    system("cls");
		                    break;
		                default:
		                    cout<<"nieznana opcja"<<endl;
		                    break;
		            }
		        }
		    }
		    break;
		}
		case 's':	cout<<"podaj indeks elementu: ";
						cin>>i;
						baza.setCurrent(i);
						if(i==-1)
							cout<<"brak elementow"<<endl;
						else
							if (i>baza.getLicznosc())
								cout<<"za wysoki index!"<<endl;
							else 
								if(i<=0)
									cout<<"ujemny index!"<<endl;	
								else							
									piszInstrumentyXY(baza.getInstrumenty(i), 5, 10);
			break;
		case 'a': 
					if (baza.getLicznosc() == 0) 
			    {
			        cout<<"brak elementow w bazie"<<endl;
			        cout<<"nacisnij ENTER, aby wrocic do menu"<<endl;
			        getch();
			        break;
			    }
			    system("cls");
			    cout<<"\033[36m"<<"wybierz rodzaj SORT:"<<" \033[0m"<<endl<<endl;
			    cout<<"		1 - sortuj po cenie"<<endl;
			    cout<<"		2 - sortuj po nazwie"<<endl;
			    cout<<"		3 - sortuj po liczbie sztuk"<<endl<<endl;
			    cout<<"		q - quit"<<endl;
			
			    zn = getch();
			    switch(zn)
			    {
			        case '1':
			            baza.sortCena();
			            system("cls");
			            cout<<"posortowano"<<endl;
			            break;
			        case '2':
			            baza.sortNazwa();
			            system("cls");
			            cout<<"posortowano"<<endl;
			            break;
			        case '3':
			            baza.sortSztuk();
			            system("cls");
			            cout<<"posortowano"<<endl;
			            break;
			        case 'q':
			        	system("cls");
			            break;
			        default:
			            cout<<"nieznana opcja"<<endl;
			            break;
			    }
			    break;
		case 'z':
		{
				i=baza.getCurrentFound();
				if (i==-1)
				{
					cout<<"brak elementow, nacisnij ENTER by wyjsc"<<endl;
					getchar();
				}
				else
				{
					do
					{
						system("cls");
						if(baza.getCurrentFound()==-1)
						{
							cout<<"brak elementow, nacisnij ENTER by wyjsc";
							getch();
							break;
						}
						instrument &currentInstrument = baza.getInstrumentFound(i);
			            piszInstrumentyXY(currentInstrument, 25, 10);
			
						cout<<"					ZAZNACZENIE --------- [ ";
						if (currentInstrument.getZaznaczony()) 
						{
						    cout<<"X";
						} else 
						{
						    cout<<" ";
						}
						cout<<" ]"<<endl<<endl;
						
						cout<<"\033[36m"<<"	'n' - nastepny   'b' - poprzedni  'z' - zaznacz/odznacz  'u' - update  'd' - delete   'q' - quit"<<" \033[0m"<<endl;
						zn=getch();
						switch(zn)
						{
							case 'b':
								baza.previousFound();
								i=baza.getCurrentFound();
								break;
							case 'n':
								baza.nextFound();
								i=baza.getCurrentFound();
								break;	
							case 'z':  // Zaznaczenie/odznaczenie bieĹĽÄ…cego elementu
		                    currentInstrument.zmianaZaznaczony();
		                    cout<<(currentInstrument.getZaznaczony() ? "zaznaczony" : "odznaczony")<<endl;
		                    getch();
		                    break;
							case 'd': 
							{  // Dodanie opcji 'd' do przeniesienia elementu do kosza
			                    cout<<"czy chcesz przeniesc ten element do kosza? (t - TAK    n - NIE)"<<endl;
			                    zn = getch();
			                    switch (zn) 
			                    {
			                        case 't':
										baza.deleteCurrentFound(i);
										cout<<"usunieto";
										i=baza.getCurrentFound();
										break;
									case 'n':
										break;
			                        default:
			                            cout<<"nieznana opcja"<<endl;
			                            break;
			                    }
			                    break;
			                }
							case 'u': {
			                    system("cls");
			                    
			                    cout<<"\033[36m"<<"\n\n\n\n\n\n\n\n\n						AKTUALIZACJA ELEMENTU"<<" \033[0m"<<endl<<endl;
			                    cout<<"						1 - Nazwa\n";
			                    cout<<"						2 - Model\n";
			                    cout<<"						3 - Marka\n";
			                    cout<<"						4 - Rodzaj\n";
			                    cout<<"						5 - Cena\n";
			                    cout<<"						6 - Waga\n";
			                    cout<<"						7 - Sztuk\n";
			                    cout<<"						8 - Nadpisz caly element\n";
			                    zn=getch();
			                    
			                    int idx = baza.getCurrentFound();
			                    if (idx == -1)
			                    {
			                        cout<<"brak elementu do aktualizacji"<<endl;
			                        break;
			                    }
			                    
			                    instrument &currentInstrument = baza.getInstrumentFound(idx);
			                    
			                    switch (zn) 
								{
			                        case '1': 
									{
			                            cout<<"			Nowa nazwa: ";
			                            gets(n);
			                            currentInstrument.setNazwa(n);
			                            break;
			                        }
			                        case '2': 
									{
			                            cout<<"			Nowy model: ";
			                            gets(md);
			                            currentInstrument.setModel(md);
			                            break;
			                        }
			                        case '3': 
									{
			                            cout<<"			Nowa marke: ";
										gets(mr);
			                            currentInstrument.setMarka(mr);
			                            break;
			                        }
			                        case '4': 
									{
			                            cout<<"			Nowy rodzaj: ";
			                            gets(r);
			                            currentInstrument.setRodzaj(r);
			                            break;
			                        }
			                        case '5': 
								{
								    do {
								        cout<<"		Nowa cena: ";
								        cin>>c;
								        if (c <= 0) {
								            cout<<"		nieprawidlowa cena! wprowadz wartosc dodatnia"<<endl;
								        }
								    } while (c <= 0);
								    cin.ignore();
								    currentInstrument.setCena(c);
								    break;
								}
								case '6': 
								{
								    do {
								        cout<<"		Nowa waga: ";
								        cin>>w;
								        if (w<=0) {
								            cout<<"		nieprawidlowa waga! wprowadz wartosc dodatnia"<<endl;
								        }
								    } while (w <= 0);
								    cin.ignore();
								    currentInstrument.setWaga(w);
								    break;
								}
								case '7': 
								{
								    do {
								        cout<<"		Nowa ilosc sztuk: ";
								        cin>>sz;
								        if (sz <= 0) 
										{
								            cout<<"		nieprawidlowa ilosc sztuk! wprowadz wartosc dodatnia"<<endl;
								        }
								    } while (sz<=0);
								    cin.ignore();
								    currentInstrument.setSztuk(sz);
								    break;
								}
			                       case '8': 
								{
		                            cout<<"			Nowa nazwa: ";
		                            gets(n);
		                            currentInstrument.setNazwa(n);
		                            cout<<"			Nowy model: ";
		                            gets(md);
		                            currentInstrument.setModel(md);
		                            cout<<"			Nowa marka: ";
		                            gets(mr);
		                            currentInstrument.setMarka(mr);
		                            cout<<"			Nowy rodzaj: ";
		                            gets(r);
		                            currentInstrument.setRodzaj(r);
		                            
							        do {
								        cout<<"			Nowa cena: ";
								        cin>>c;
								        if (c <= 0) {
								            cout<<"			nieprawidlowa cena! wprowadz wartosc dodatnia"<<endl;
								        }
								    } while (c <= 0);
								    cin.ignore();
								    currentInstrument.setCena(c);
								    
									do {
								        cout<<"			Nowa waga: ";
								        cin>>w;
								        if (w <= 0) {
								            cout<<"			nieprawidlowa waga! wprowadz wartosc dodatnia"<<endl;
								        }
								    } while (w <= 0);
								    cin.ignore();
								    currentInstrument.setWaga(w);
										
										
									do {
								        cout<<"			Nowa sztuk: ";
								        cin>>sz;
								        if (sz <= 0) {
								            cout<<"			nieprawidlowa ilosc sztuk! wprowadz wartosc dodatnia"<<endl;
								        }
								    } while (sz <= 0);
								    cin.ignore();
								    currentInstrument.setSztuk(sz);
								    
	                        		}
			                        default:                            
		                            cout<<"			nieznana opcja"<<endl;
		                            break; 
		                            
		                        
                        		}     
		                    }                    
		                    break;
						}
						
					}while(zn!='q');
					system("cls");
				}
				break;
			}
				
		case 'f': 
					if (baza.getLicznosc() == 0) 
			    {
			        cout<<"brak elementow w bazie"<<endl;
			        cout<<"nacisnij ENTER, aby wrocic do menu"<<endl;
			        getch();
			        break;
			    }
				system("cls");
					cout<<"\033[36m"<<"co chcesz wyszukac?"<<" \033[0m"<<endl<<endl;
					cout<<"		1 - wyszukaj nazwe"<<endl;
					cout<<"		2 - wyszukaj cene"<<endl<<endl;
					cout<<"		q - quit"<<endl;
				zn=getch();
				switch(zn)
				{
					case '1':
						system("cls");
						cout<<"szukana nazwa: ";
						fflush(stdin);
						gets(szukanaNazwa);
						i=baza.searchNazwa(szukanaNazwa);
						if(i==0)
							cout<<"nie znaleziono";
						else
							cout<<"znaleziono";
						getchar();
						break;
					case '2':
						system("cls");
						cout<<"min: ";
						cin>>min;
						cout<<"max: ";
						cin>>max;
						i=baza.searchCena(min,max);
						if(i==1)
						{
							cout<<"znaleziono";
							getchar();
						}
						else if(min<0)
						{
							cout<<"za niska wartosc";
							getchar();
						}
						else if(max>=20000)
						{
							cout<<"za wysoka wartosc";
							getchar();
						}
						else if(min>max)
						{
							cout<<"max jest mniejszy niz min";
							getchar();
						}	
						else
						{
							cout<<"nie znaleziono";
							getchar();
						}
						getchar();
						break;
					case 'q':
						system("cls");
						break;
				}
				break;	
		
		
		
		
		case 'k':
		    if (baza.getLicznoscKosz() == 0) 
			{
		        cout<<"Kosz jest pusty"<<endl;
		    } else 
			{
		        cout<<"\033[36m"<<"KOSZ:"<<"\033[0m"<<endl<<endl;
		        cout<<"		1 - lista usunietych elementow"<<endl;
		        cout<<"		2 - przegladanie usunietych elementow"<<endl;
		        cout<<"		3 - usun wszystkie elementy z kosza"<<endl<<endl;
		        cout<<"		q - quit"<<endl;
		        zn = getch();
		        system("cls");
		        switch(zn) 
				{
		            case '1': 
					{ // WyĹ›wietlanie listy usuniÄ™tych elementĂłw
		                system("cls");
		                if (baza.getLicznoscKosz() == 0) 
						{
		                    cout<<"kosz jest pusty"<<endl;
		                } else 
						{
		                    for (int i = 0; i < baza.getLicznoscKosz(); i++) 
							{
		                        cout<<"\033[31m"<<"Element nr "<<i + 1<<" :\033[0m"<<endl<<endl;
		                        cout<< "nazwa  : "<<baza.getInstrumentKosz(i).getNazwa()<<endl;
		                        cout<< "model  : "<<baza.getInstrumentKosz(i).getModel()<<endl;
		                        cout<< "marka  : "<<baza.getInstrumentKosz(i).getMarka()<<endl;
		                        cout<< "rodzaj : "<<baza.getInstrumentKosz(i).getRodzaj()<<endl;
		                        cout<< "cena   : "<<baza.getInstrumentKosz(i).getCena()<<" zl"<<endl;
		                        cout<< "waga   : "<<baza.getInstrumentKosz(i).getWaga()<<" kg"<<endl;
		                        cout<< "sztuk  : "<<baza.getInstrumentKosz(i).getSztuk()<<endl;
		                        cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
		                    }
		                }
		                cout << "nacisnij 'q', aby wrocic do menu" << endl;
				        zn = getch();
				        while (zn!='q') 
					    {
					        zn=getch();
					    }
					    system("cls"); 
					    break;
					}
		            
		            case '2':  // Tryb przeglÄ…dania usuniÄ™tych elementĂłw
		            {
		                system("cls");
		                baza.setCurrentKosz(0);
		                bool przegladanieKosz = true;
		                while (przegladanieKosz) 
						{
		                    system("cls");
		                    int i = baza.getCurrentKosz();
		                    if (i == -1) 
							{
		                        cout<<"brak elementow w koszu do wyswietlenia"<<endl;
		                        przegladanieKosz = false;
		                    } else 
							{
		                        piszInstrumentyXY(baza.getInstrumentKosz(i), 25, 10);
		                    }
		                    cout<<"\033[36m"<<"			'n' - nastepny   'b' - poprzedni   'u' - usun stale  'r' - przywroc 'q' - wyjscie "<<"\033[0m"<<endl;
		                    zn = getch();
		                    switch (zn) 
							{
		                        case 'n':
		                            baza.nextKosz();
		                            break;
		                        case 'b':
		                            baza.previousKosz();
		                            break;
		                        case 'u': 
								{
		                            cout<<"czy na pewno chcesz usunac ten element na stale? (t - TAK    n - NIE)"<<endl;
		                            zn = getch();
		                            switch (zn) 
									{
		                                case 't':
		                                    baza.deleteCurrentKosz();
		                                    cout<<"usunieto element z kosza"<<endl;
		                                    break;
		                                case 'n':
		                                    break;
		                                default:
		                                    cout<<"nieznana opcja"<<endl;
		                                    break;
		                            }
		                            break;
		                        }
		                        case 'r':
								{
								    cout<<"czy na pewno chcesz przywrocic ten element do bazy? (t - TAK    n - NIE)"<<endl;
								    zn = getch(); 
								
								    switch (zn) 
								    {
								        case 't':
								            {
								                int idx = baza.getCurrentKosz();
								                if (idx >= 0) 
								                {
								                    baza.przywrocKosz(idx);
								                    cout<<"element zostal przywrocony do bazy"<<endl;
								                } 
								                else 
								                {
								                    cout<<"brak elementu do przywrocenia"<<endl;
								                }
								            }
								            break;
								        case 'n':
								            cout<<"operacja przywracania zostala anulowana"<<endl;
								            break;
								        default:
								            cout<<"nieznana opcja"<<endl;
								            break;
								    }
								    break;
								}
		                        case 'q':
		                            przegladanieKosz = false;
		                            system("cls");
		                            break;
		                        default:
		                            cout<<"nieznana opcja"<<endl;
		                            break;
		                    }
		                }
		                break;
		            }
		            case '3':
		            {
		                cout<<"czy na pewno chcesz usunac wszystkie elementy z kosza na stale? (t - TAK    n - NIE)"<<endl;
		                zn = getch();
		                switch (zn) 
		                {
		                    case 't':
		                        baza.deleteWszystkoKosz();
		                        cout << "wszystkie elementy zostaly usuniete z kosza"<<endl;
		                        cout << "kliknij ENTER, aby wrocic do menu"<<endl;
		                        getch();
		                        system("cls");
		                        break;
		                    case 'n':
		                        cout<<"anulowano operacje"<<endl;
		                        break;
		                    default:
		                        cout<<"nieznana opcja"<<endl;
		                        break;
		                }
		                break;
		            }
		            case 'q':
		                break;
		            default:
		                cout<<"nieznana opcja"<<endl;
		                break;
		        }
		    }
		    break;
		
		
		
		case '5':	
					cout<<"\033[36m"<<"czy na pewno chcesz zakonczyc program?"<<" \033[0m"<<endl<<endl;
				    cout<<"ESC - wyjdz          n - NIE"<<endl;
				    zn=getch();
					switch(zn)
			    {
			        case 27:
			            cout<<"\n 				DO WIDZENIA"<<endl;
			            break;
			        case 'n':
			            system("cls");
			            break;
			        default:
			            cout << "nieznana opcja - powrot do menu glownego"<<endl;
			            system("cls");
			            break;
			    }
			break;
		}
		
	}while(zn!=27);
}