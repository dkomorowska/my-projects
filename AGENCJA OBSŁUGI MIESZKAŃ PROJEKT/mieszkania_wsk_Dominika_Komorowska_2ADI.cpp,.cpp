#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <stdio.h>
#include <windows.h>


struct kolekcja
{
char nazwa[20];
float cena;
int liczba_pokoi;
int powierzchnia;
int rok_budowy;

};

using namespace std;

void losuj(kolekcja mieszkan[], int *liczba_danych);
void generujPosortowane(kolekcja mieszkan[], int *liczba_danych);
void generujOdwrotniePosortowane(kolekcja mieszkan[], int *liczba_danych);
bool dodajkolekcja(kolekcja mieszkan[], kolekcja *nowy, int *liczba_danych, int *rozmiar);
void wypisz(kolekcja kolekcjay[], int *ile);
float sumaWartosci(kolekcja mieszkan[], int *liczba_danych);
float sredniaCena(kolekcja mieszkan[], int *liczba_danych);
void wyszukajCena(kolekcja mieszkan[], int *ile_danych, kolekcja wyszukane[], int *ile_wyszukanych, float *min, float *max);//szukany przedział <min,max>
void minmaxCena(kolekcja mieszkan[], int *liczba_danych, float *min, float *max);
void przecena(kolekcja mieszkan[], int *liczba_danych, float *procent);
void selectionsort(kolekcja mieszkan[], int *liczba_danych);
void bubbleSort(kolekcja mieszkan[], int *liczba_danych);
void insertSort(kolekcja mieszkan[], int *liczba_danych);
bool writeFile(kolekcja mieszkan[], int *liczba_danych);
bool readFile(kolekcja mieszkan[], int *liczba_danych);
void wypiszPlikTxt();
void nameSort(kolekcja mieszkan[], int *liczba_danych);
void wyszukajnazw(kolekcja mieszkan[], int *liczba_danych, string szukana);

main()
{      
	kolekcja *mieszkan, *wyszukane, nowy;
	float *suma, *srednia, minimum, maksimum, procent;
	string szukana;
	int *rozmiar=new int(0);
	int *liczba_danych=new int(0);
	int *liczba_wyszukanych=new int(0);
	string *nazwa;
	bool odczyt;
	
	char znak;
	cout<<"AGENCJA OBSLUGI KOLEKCJI APARTAMENTOW"<<endl<<endl;
	srand(time(NULL));
	do
	{
	fflush(stdin);
	cout<<endl<<endl<<"Nacisnij ENTER"<<endl;
	getchar();
	system("CLS");
	cout<<"0. Dynamiczne tworzenie kolekcji"<<endl;
	cout<<"1. Losowanie calej kolekcji"<<endl;
	cout<<"2. Generowanie calej kolekcji posortowanej"<<endl;
	cout<<"3. Generowanie calej kolekcji odwrotnie posortowanej"<<endl;
	cout<<"4. Dopisanie mieszkan do kolekcji"<<endl;
	cout<<"5. Wypisanie tablicy mieszkan"<<endl;
	cout<<"6. Suma wartosci w calej kolekcji"<<endl;
	cout<<"7. Srednia cena kolekcji"<<endl;
	cout<<"8. Maksymalna i minimalna cena"<<endl;
	cout<<"9. Zmiana ceny o dany procent"<<endl;
	cout<<"a. Wyszukiwanie wedlug przedzialu cen"<<endl;
	cout<<"b. Sortowanie rosnace wedlug cen - proste wybieranie"<<endl;
	cout<<"c. Sortowanie rosnace wedlug cen - bubble sort"<<endl;
    cout<<"d. Sortowanie rosnace wedlug cen - insert sort"<<endl;
	cout<<"e. Zapisz do pliku"<<endl;
    cout<<"f. Odczytaj z pliku"<<endl;
    cout<<"g. Sortowanie wedlug nazw - bubble sort"<<endl;
    cout<<"h. Wyszukaj po dokladnej nazwie"<<endl;
    cout<<"r. READ ME"<<endl;
	znak=getch();
	switch(znak)
{
	case '0': cout<<"Jaki rozmiar magazynu? ";
		cin>>*rozmiar; 
		if(*rozmiar<=0 || *rozmiar>100) 
		{
			cout<<"ERROR: Rozmiar magazynu musi byc wiekszy od zera i nie wiekszy niz 100!"<<endl;
			break;
		}
		mieszkan=new kolekcja[*rozmiar+1];
		wyszukane=new kolekcja[*rozmiar+1];
		*liczba_danych=0;
		*liczba_wyszukanych=0;
			break;
	case '1': 
	if(*rozmiar==0) 
		{
			cout<<"ERROR: Najpierw utworz magazyn!"<<endl;
			break;
		}
	do
	{
	cout<<"Ile apartamentow wylosowac? ";
	cin>>*liczba_danych;
	if (*liczba_danych>*rozmiar || *liczba_danych<0)
		cout<<"ERROR: Liczba apartamentow nie moze przekraczac rozmiaru magazynu!"<<endl;    	//nie zabezpieczone mniej niz 0
	}while (*liczba_danych>*rozmiar || *liczba_danych<0);
		
	losuj(mieszkan, liczba_danych);
	cout<<endl<<"WYLOSOWANO"<<endl;
		break;
	case '2': 
		if(*rozmiar==0) 
		{
			cout<<"ERROR: Najpierw utworz magazyn!"<<endl;
			break;
		}
	do {
        cout<<"Ile danych generowac? ";
        cin>>*liczba_danych;
        if (*liczba_danych>*rozmiar)
		{
            cout<<"ERROR: Liczba danych nie moze przekraczac rozmiaru magazynu!"<<endl; 				
        }
        else if (*liczba_danych<0)
        {
        	cout<<"ERROR: Liczba danych nie moze byc mniejsza niz 0"<<endl;
		}
        } while (*liczba_danych>*rozmiar || *liczba_danych<0);
		generujPosortowane(mieszkan, liczba_danych);
		cout<<endl;
		cout<<endl<<"WYGENEROWANO"<<endl;
			break;
	case '3': 
		if(*rozmiar==0) 
		{
			cout<<"ERROR: Najpierw utworz magazyn!"<<endl;
			break;
		}
	do {
        cout<<"Ile danych generowac? ";
        cin>>*liczba_danych;
        if (*liczba_danych>*rozmiar) 
		{
            cout<<"ERROR: Liczba danych nie moze przekraczac rozmiaru magazynu!"<<endl;
        }
        }while (*liczba_danych>*rozmiar);
        generujOdwrotniePosortowane(mieszkan, liczba_danych);
        cout<<endl<<"WYGENEROWANO"<<endl;
            break;
	case '4':
		if(rozmiar==0) 
		{
			cout<<"ERROR: Najpierw utworz magazyn!"<<endl;
			break;
		}
			cout<<"Nazwa: ";
			fflush(stdin);
			gets(nowy.nazwa);
			do
			{
			cout<<"Cena: ";
			cin>>nowy.cena;
			if (nowy.cena<=100000 || nowy.cena>=900000)
				cout<<"ERROR: Cena musi byc pomiedzy $100,000 a $900,000!"<<endl;
			}while (nowy.cena<=100000 || nowy.cena>=900000);
			do
			{
			cout<<"Liczba pokoi: ";
			cin>>nowy.liczba_pokoi;
			if (nowy.liczba_pokoi<=0 || nowy.liczba_pokoi>10)
				cout<<"ERROR: Liczba pokoi musi byc wieksza od zera i mniejsza niz 10!"<<endl;
			} while (nowy.liczba_pokoi<=0 || nowy.liczba_pokoi>10);
			do
			{
			cout<<"Powierzchnia w m^2 (80, 500): ";
			cin>>nowy.powierzchnia;
			if (nowy.powierzchnia<80 || nowy.powierzchnia>500)
				cout<<"ERROR: Powierzchnia musi byc wieksza od 80m^2 i mniejsza niz 500m^2!"<<endl;
			} while (nowy.powierzchnia<80 || nowy.powierzchnia>500);
			do
			{
			cout<<"Rok budowy: ";
			cin>>nowy.rok_budowy;
			if (nowy.rok_budowy<1990 || nowy.rok_budowy>=2024) 
	    		cout<<"ERROR: Podano nieprawidlowy rok budowy!"<<endl;
	    	} while (nowy.rok_budowy<1990 || nowy.rok_budowy>=2024);
		cin.ignore();
		dodajkolekcja(mieszkan, &nowy, liczba_danych, rozmiar);
		cout<<"DOPISANY"<<endl;
			break;
	case '5': wypisz(mieszkan, liczba_danych);
		cout<<endl;
			break;
	case '6': 
		if(rozmiar==0 || liczba_danych==0) 
		{
			cout<<"ERROR: Najpierw utworz magazyn i kolekcje!"<<endl;
			break;
		}
		cout<<endl<<"Suma wartosci mieszkan = "<<sumaWartosci(mieszkan, liczba_danych)<<endl<<endl;
			break;
	case '7': 
		if(rozmiar==0 || liczba_danych==0) 
		{
			cout<<"ERROR: Najpierw utworz magazyn i kolekcje!"<<endl;
			break;
		}
		cout<<endl<<"Srednia cena = "<<sumaWartosci(mieszkan, liczba_danych)<<endl<<endl;
			break;
	case '8': 
		minmaxCena(mieszkan, liczba_danych, &minimum, &maksimum);
		cout<<"Cena minimalna = $"<<minimum<<". Cena maksymalna = $"<<maksimum<<endl;
			break;
	case '9':
		if(rozmiar==0 || liczba_danych==0) 
		{
			cout<<"ERROR: Najpierw utworz magazyn i kolekcje!"<<endl;
			break;
		}
		do
		{
		cout<<"O jaki procent przeceniasz? (ujemny obniza, max -99,9): ";
		cin>>procent;
		if (procent< -99.99 || procent>=0.00)
			cout<<"ERROR: Przecena musi byc mneijsza niz 0% i wieksza niz 99.99%"<<endl;
		}while (procent< -99.99 || procent>=0.00);
		przecena(mieszkan, liczba_danych, &procent);
		cout<<"PRZECENIONE"<<endl;
			break;
	case 'a': 
		do
		{
			cout<<"Podaj przedzial szukany."<<endl<<"od wartosci: ";
			cin>>minimum; 
			cout<<"do wartosci: ";
			cin>>maksimum;
			if (minimum<0 || maksimum<0 || minimum>maksimum)
	                cout<<"ERROR: Niepoprawny przedzial!"<<endl;
	    }while (minimum<0 || maksimum<0 || minimum>maksimum);
			wyszukajCena(mieszkan, liczba_danych, wyszukane, liczba_wyszukanych, &minimum, &maksimum);
			wypisz(wyszukane, liczba_wyszukanych);
			cout<<endl;
			break;
	case 'b': 
	if (*liczba_danych == 0)
                {
                    cout<<"ERROR: Najpierw utworz i uzupelnij kolekcje!"<<endl;
                    break;
                }
		selectionsort(mieszkan, liczba_danych);
		cout<<"POSORTOWANO"<<endl;
			break;
	case 'c':
			if (*liczba_danych == 0)
                {
                    cout<<"ERROR: Najpierw utworz i uzupelnij kolekcje!"<<endl;
                    break;
                }
            cout<<"POSORTOWANO (Bubble Sort)"<<endl;
            break;
    case 'd':
    		if (*liczba_danych == 0)
                {
                    cout<<"ERROR: Najpierw utworz i uzupelnij kolekcje!"<<endl;
                    break;
                }
        insertSort(mieszkan, liczba_danych);
            cout<<"POSORTOWANO (Insert Sort)"<<endl;
            break;
	case 'r':
    	wypiszPlikTxt();
    		break;
	case 'e':
		odczyt=writeFile(mieszkan, liczba_danych);
        if (odczyt==false)
        {
            cout<<"ERROR: Blad podczas zapisu do pliku!"<<endl;
        }
        else
        {
        	cout<<"ZAPISANO"<<endl;
		}
            break;
    case 'f':
    	odczyt=readFile(mieszkan, liczba_danych);
        if (odczyt==false)
        {
        	cout<<"ERROR: Blad podczas odczytu z pliku!"<<endl;
        }
        else
        	cout<<"ODCZYTANO"<<endl;
            break;
    case 'g':
    	if (*liczba_danych == 0)
                {
                    cout<<"ERROR: Najpierw utworz i uzupelnij kolekcje!"<<endl;
                    break;
                }
    	nameSort(mieszkan, liczba_danych);
    		cout<<"POSORTOWANO (nameSort)"<<endl;
    		break;
    case 'h':
    	cout<<"Jaki kraj chcesz wyszukac? "<<endl;
		cin>>szukana;
		cout<<endl;
    	wyszukajnazw(mieszkan, liczba_danych, szukana);
    	if (szukana != mieszkan->nazwa)
			cout<<"ERROR: Nie ma takiego Apartamrntu"<<endl;
    		break;
	case 27: cout<<"DO WIDZENIA"<<endl;
			break;
	default: cout<<"ERROR: Zly wybor!"<<endl;
}

getchar();

}
	while(znak!=27);
	
	cout<<endl<<"NACISNIJ KLAWISZ BY WYJSC"<<endl;
	delete[] mieszkan;
	delete[] wyszukane;
	system("PAUSE>>NULL");
}

void losuj(kolekcja mieszkan[], int *liczba_danych)
{
	char naz[20], numer[13];
	for (int i=1; i<=*liczba_danych; i++)
	{
	strcpy(naz, "Apartament ");
	itoa(i, numer, 10);
	strcat(naz, numer);
	strcpy(mieszkan[i].nazwa, naz);
	mieszkan[i].cena=100000+(rand()%400001);
	mieszkan[i].liczba_pokoi=1+(rand()%10);
	mieszkan[i].powierzchnia=81+(rand()%420);
	mieszkan[i].rok_budowy=1991+(rand()%34);
	}
}

void generujPosortowane (kolekcja mieszkan[], int *liczba_danych)
{
	char naz[20], numer[13];
	for (int i=1; i<=*liczba_danych; i++)
	{
	strcpy(naz, "Apartament ");
	itoa(i, numer, 10);
	strcat(naz,  numer);
	strcpy(mieszkan[i].nazwa, naz);
	mieszkan[i].cena= 100000+((i-1) *400000.0/(*liczba_danych-1));
	mieszkan[i].liczba_pokoi=i;
	mieszkan[i].rok_budowy=1990+((i - 1)*(2024-1990) / (*liczba_danych-1));
    mieszkan[i].powierzchnia=80+((i - 1)*420 / (*liczba_danych-1));
	}
}

void generujOdwrotniePosortowane(kolekcja mieszkan[], int *liczba_danych)
{
	char naz[20], numer[13];
	for (int i=1; i<=*liczba_danych; i++)
	{
	strcpy(naz, "Apartament ");
	itoa(i, numer, 10);
	strcat(naz, numer);
	strcpy(mieszkan[i].nazwa, naz);
	mieszkan[i].cena=500000-((i-1) *400000.0/(*liczba_danych-1));
	mieszkan[i].liczba_pokoi=*liczba_danych - i+1;
	mieszkan[i].rok_budowy=2024-((i-1)*(2024-1990) / (*liczba_danych-1));
    mieszkan[i].powierzchnia=500-((i-1)*420 / (*liczba_danych-1));
	}
}

bool dodajkolekcja(kolekcja mieszkan[], kolekcja *nowy, int *liczba_danych, int *rozmiar)
{
	if (*liczba_danych>=*rozmiar)
		return false;
	(*liczba_danych)++;
	mieszkan[*liczba_danych]=*nowy;
	return true;
}
void wypisz(kolekcja towary[], int *ile)
{
	cout<<"\t \t \t   Cena:      Pokoje:    Powierzchnia:    Rok budowy:"<<endl;
	for(int i=1; i<=*ile; i++)
{
	cout<<towary[i].nazwa<<"  \t  \t $"<<towary[i].cena
	<<"\t "<<towary[i].liczba_pokoi<<"\t    "<<towary[i].powierzchnia<<"m^2\t     "<<towary[i].rok_budowy<<"r     |"<<endl<<endl;
	cout<<"-------------------------------------------------------------------------------|"<<endl<<endl;
}
}

float sumaWartosci(kolekcja mieszkan[], int *liczba_danych)
{
	int i;
	float suma=0;
	for (i=1; i<=*liczba_danych; i++)
		suma+=mieszkan[i].cena;
	return suma;
}

float sredniaCena(kolekcja mieszkan[], int *liczba_danych)
{
	float srednia, suma=0;
	for (int i=1; i<=*liczba_danych; i++)
		suma+=mieszkan[i].cena;
		srednia=(suma/ *liczba_danych);
	return srednia;
}

void minmaxCena(kolekcja mieszkan[], int *liczba_danych, float *min, float *max)
{
	int i;
    *min=mieszkan[1].cena;
    *max=mieszkan[1].cena;
    for(i=2; i<=*liczba_danych ; i++)
    {
        if(mieszkan[i].cena>*max)
            *max=mieszkan[i].cena;

        else
        if(mieszkan[i].cena<*min)
            *min=mieszkan[i].cena;
    }
}

void wyszukajCena(kolekcja mieszkan[], int *ile_danych, kolekcja wyszukane[], int *ile_wyszukanych, float *min, float *max)
{
 
       *ile_wyszukanych = 0;
    for (int i=0; i<*ile_danych; i++)
    {
        if (mieszkan[i].cena>=*min && mieszkan[i].cena<=*max)
        {
            wyszukane[*ile_wyszukanych] = mieszkan[i];
            (*ile_wyszukanych)++;
        }
    }
}

void przecena(kolekcja mieszkan[], int *liczba_danych, float *procent)
{
	for (int i=1; i<=*liczba_danych; i++)
		mieszkan[i].cena+=mieszkan[i].cena *  *procent/100;
}

void selectionsort(kolekcja mieszkan[], int *liczba_danych)
{
	kolekcja min;
	int indeks, i, nr;
	for (nr=1; nr<*liczba_danych; nr++)
	{
		min=mieszkan[nr];
		indeks=nr;
		for (i=nr+1; i<=*liczba_danych; i++)
			if (mieszkan[i].cena < min.cena)
			{
				min=mieszkan[i];
				indeks=i;
			}
		mieszkan[indeks]=mieszkan[nr];
		mieszkan[nr]=min;
	}
}

void bubbleSort(kolekcja mieszkan[], int *liczba_danych)
{
    kolekcja pom;
    for(int nr=1; nr<=*liczba_danych; nr++)
        for(int i=1; i<=*liczba_danych-nr; i++)
            if(mieszkan[i].cena>mieszkan[i+1].cena)
            {
                pom=mieszkan[i];
                mieszkan[i]=mieszkan[i+1];
                mieszkan[i+1]=pom;
            }
}    

void insertSort(kolekcja mieszkan[], int *liczba_danych)
{
    int i;
    for(int nr=2, i; nr<=*liczba_danych; nr++)
    {
        mieszkan[0]=mieszkan[nr];
        i=nr-1;
        while(mieszkan[i].cena>mieszkan[0].cena)
        {
            mieszkan[i+1]=mieszkan[i];
            i--;
        }
        mieszkan[i+1]=mieszkan[0];
    }
}


void wypiszPlikTxt()
{
    FILE *fp;
    char c;
    fp=fopen("README.txt","r");
    if (fp==NULL)
    {
        cout<<"Nie można otworzyć pliku"<<endl;
        return;
    }
    do
    {
        c=getc(fp);
        Sleep(30);
        if (c!=EOF)
            cout<<c;
    } while (c!=EOF);
    fclose(fp);
}

bool writeFile(kolekcja mieszkan[], int *liczba_danych)
{
    FILE *fp;
    fp=fopen("kolekcjamieszkan.dat", "wb");
    if(fp==NULL)
    {
        return false;
    }
    fwrite(liczba_danych, sizeof(*liczba_danych), 1, fp);
    for(int i=1; i<=*liczba_danych; i++)
        fwrite(&mieszkan[i], sizeof(kolekcja), 1, fp);
    fclose(fp);
    return true;
} 

bool readFile(kolekcja mieszkan[], int *liczba_danych)
{
    FILE *fp;
    fp=fopen("kolekcjamieszkan.dat", "rb");
    if(fp==NULL)
    {
        return false;
    }
    fread(liczba_danych, sizeof(*liczba_danych), 1, fp);
    for(int i=1; i<=*liczba_danych; i++)
        fread(&mieszkan[i], sizeof(kolekcja), 1, fp);
    fclose(fp);
    return true;
}

void nameSort(kolekcja mieszkan[], int *liczba_danych)
{
    kolekcja pom;
    for(int nr=1; nr<=*liczba_danych; nr++)
  {
    for(int i=1; i<=*liczba_danych-nr; i++)
    {
      if (strcmp(mieszkan[i].nazwa, mieszkan[i+1].nazwa) > 0)
      {
        pom=mieszkan[i];
        mieszkan[i]=mieszkan[i+1];
        mieszkan[i+1]=pom;
      }
    }
  }    

}

void wyszukajnazw(kolekcja mieszkan[], int *liczba_danych, string szukana)
{
    for(int i=1; i<=*liczba_danych; i++)
    {
        if(szukana==mieszkan[i].nazwa)
        {
			cout<<"\t \t \t   Cena:      Pokoje:    Powierzchnia:    Rok budowy:"<<endl;
			cout<<mieszkan[i].nazwa<<"  \t  \t $"<<mieszkan[i].cena<<"\t "<<mieszkan[i].liczba_pokoi<<"\t    "<<mieszkan[i].powierzchnia<<"m^2\t     "<<mieszkan[i].rok_budowy<<"r     |"<<endl<<endl;
			cout<<"-------------------------------------------------------------------------------|"<<endl<<endl;
        }
    }        
}    