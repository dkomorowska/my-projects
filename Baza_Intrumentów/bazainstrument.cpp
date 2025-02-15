#ifndef ClassInstrument
	#include <string.h>
	#endif

//************metody bazatowar************
using namespace std;

bazainstrument::bazainstrument()
{
    licznosc=0;
	current=-1;
	licznoscFound=0;
	currentFound=-1;
	licznoscKosz=0;
	currentKosz=-1;
}

void bazainstrument::czysccalosc()
{
	tab.erase(tab.begin(), tab.end());
	licznosc=0;
	current=-1;
}

void bazainstrument::dodajkolejny (char *naz, char* mod, char* mar, char* rodz, float cen, float wag, int szt)
{
	instrument t;
	
	t.pobierz(naz, mod, mar, rodz, cen, wag ,szt);
	tab.push_back(t);
	licznosc++;
	current=licznosc-1;
}

float bazainstrument::sumawartosc()
{
	float suma_wart=0;
	for (i=0;i<licznosc;i++)
		suma_wart+=tab[i].wartosc();
		return suma_wart;
}

int bazainstrument::getLicznosc()
{
	return licznosc;
}

instrument& bazainstrument::getInstrumenty(int i)
{
	return tab[i];
}

instrument& bazainstrument::getTab()
{
	return tab.at(current);
}

void bazainstrument::saveFile()
{
	FILE *fp; 
	fp=fopen("dl.dat", "wb");
	licznosc=tab.size();
	fwrite(&licznosc, sizeof(licznosc), 1, fp);
	for(int i=0; i<tab.size(); i++)
		fwrite(&tab[i], sizeof(tab[i]), 1, fp);
	fclose(fp);
}

void bazainstrument::readFile()
{
	FILE *fp;
	tab.erase(tab.begin(), tab.end());
	instrument t;
	licznosc=0;
	current=-1;
	fp=fopen("dl.dat", "rb");
	fread(&licznosc, sizeof(licznosc), 1, fp);
	for(int i=0; i<licznosc; i++)
	{
		fread(&t, sizeof(t), 1, fp);
		tab.push_back(t);
	}
	fclose(fp);
	if(licznosc>0)
		current=0;
	else
		current=-1;
}

void bazainstrument::saveZaznaczone()
{
    FILE *fp;
    fp=fopen("archiwum.dat", "wb");
    int licznik=0;
    //zliczanie zaznaczonych
    for (int i = 0; i < licznosc; i++)
    {
        if (tab[i].getZaznaczony())
        {
            licznik++;
        }
    }
    //zapisz liczbę
    fwrite(&licznik, sizeof(int), 1, fp);

    //zapisz tylko zaznaczone elementy
    for (int i = 0; i < licznosc; i++)
    {
        if (tab[i].getZaznaczony())
        {
            fwrite(&tab[i], sizeof(tab[i]), 1, fp);
        }
    }
    fclose(fp);
}

void bazainstrument::readZaznaczone()
{
    FILE *fp;
    instrument t;
    int licznik;

    fp = fopen("archiwum.dat", "rb");
    if (!fp)
    {
        cout<<"nie mozna otworzyć pliku 'archiwum.dat' do odczytu"<<endl;
        return;
    }
    // Odczyt liczby zaznaczonych elementów
    fread(&licznik, sizeof(int), 1, fp);

    // Odczyt elementów i dodanie ich do głównej bazy 'tab'
    for (int i = 0; i<licznik; i++)
    {
        fread(&t, sizeof(t), 1, fp);
        tab.push_back(t);
        licznosc++;
    }
    fclose(fp);
    // Ustawienie bieżącego indeksu jeśli baza nie jest pusta
    if (licznosc > 0)
        current = 0;
    else
        current = -1;

    cout<<"zaznaczone elementy zostaly odczytane i dodane do bazy"<<endl;
}




bool bazainstrument::setCurrent(int index)
{
	if(index>=0 && index<licznosc)
	{
		current=index;
		return true;
	}
	return false;
}

int bazainstrument::getCurrent()
{
	return current;
}

bool bazainstrument::next()
{
	if((current+1)>=licznosc)
		return 0;
	current++;
	return 1;
}

bool bazainstrument::previous()
{
	if((current-1)<0)
		return 0;
	current--;
	return 1;
}

void bazainstrument::deleteCurrent(int i)
{
    kosz.push_back(tab[current]);
    licznoscKosz++;
    
    if (currentKosz == -1)
        currentKosz = 0;

    tab.erase(tab.begin() + current);
    
    // Jeśli usuwamy ostatni element w tablicy, zmniejszamy 'current'
    if (current == licznosc - 1)
        current--;
    licznosc--;

    // Jeśli po usunięciu lista 'tab' jest pusta, ustawiamy 'current' na 0
    if (licznosc == 0)
        current = -1;
}

void bazainstrument::deleteCurrentFound(int i)
{
    // Przenosimy element do kosza
    kosz.push_back(found[currentFound]);
    licznoscKosz++; // Zwiększamy liczbę elementów w koszu

    // Ustawiamy currentKosz na 0, jeśli jest -1 (pierwszy element w koszu)
    if (currentKosz == -1)
        currentKosz = 0;

    // Usuwamy element z listy 'found'
    found.erase(found.begin() + currentFound);

    // Jeśli usuwamy ostatni element w 'found', zmniejszamy 'currentFound'
    if (currentFound == licznoscFound - 1)
        currentFound--;
    
    licznoscFound--; // Zmniejszamy liczbę elementów w 'found'
    
    // Jeśli usuwamy element z 'tab', zmniejszamy liczbę elementów
    if (current == licznosc - 1)
        current--;  
    licznosc--;  // Zmniejszamy liczbę elementów w 'tab'
}


void bazainstrument::deleteCurrentKosz()
{
    // Usuwamy element na pozycji 'currentKosz' z kosza
    kosz.erase(kosz.begin() + currentKosz);
    licznoscKosz--;  // Zmniejszamy liczbę elementów w koszu

    // Jeśli 'currentKosz' wskazywał na ostatni element, ustawiamy 'currentKosz' na przedostatni
    if (currentKosz >= licznoscKosz && licznoscKosz > 0)
        currentKosz = licznoscKosz - 1;

    // Jeśli kosz jest pusty, ustawiamy 'currentKosz' na -1
    if (licznoscKosz == 0)
        currentKosz = -1;
}

void bazainstrument::deleteWszystkoKosz() {
    // Sprawdzamy, czy kosz zawiera jakiekolwiek elementy
    while (licznoscKosz > 0) {
        deleteCurrentKosz();  // Usuwamy pierwszy element kosza
    }
}

void bazainstrument::przywrocKosz(int i)
{
    // Przenosimy element z kosza do tablicy 'tab'
    tab.push_back(kosz[i]);
    licznosc++;  // Zwiększamy liczbę elementów w 'tab'

    // Ustawiamy 'current' na pierwszą pozycję, jeśli jest -1
    if (current == -1)
        current = 0;

    // Usuwamy element z kosza
    kosz.erase(kosz.begin() + i);

    // Zmniejszamy liczbę elementów w koszu
    licznoscKosz--;

    // Jeśli 'currentKosz' było większe niż 'i', to zmniejszamy 'currentKosz'
    if (currentKosz >= i && currentKosz > 0)
        currentKosz--;

    // Jeśli kosz jest pusty, ustawiamy 'currentKosz' na -1
    if (licznoscKosz == 0)
        currentKosz = -1;
}

// Przechodzi do następnego elementu w koszu
bool bazainstrument::nextKosz() 
{
    if ((currentKosz + 1) >= licznoscKosz)
        return false;
    currentKosz++;
    return true;
}

// Przechodzi do poprzedniego elementu w koszu
bool bazainstrument::previousKosz() 
{
    if ((currentKosz - 1) < 0)
        return false;
    currentKosz--;
    return true;
}

// Zwraca obecny indeks w koszu
int bazainstrument::getCurrentKosz() 
{
    return currentKosz;
}

void bazainstrument::czyscKosz()
{
 	kosz.clear();
}

// Zwraca liczbę elementów w koszu
int bazainstrument::getLicznoscKosz() 
{
    return licznoscKosz;
}

instrument bazainstrument::getKosz() 
{
   return kosz.at(currentKosz); 
}

instrument bazainstrument::getInstrumentKosz(int i)
{
	return kosz[i];	
}

bool bazainstrument::setCurrentKosz(int index)
{
    if(index >= 0 && index < licznoscKosz)
    {
        currentKosz = index;
        return true;
    }
    return false;
}

void bazainstrument::sortSztuk()
{
    instrument pom;
    for(int nr = 0; nr<licznosc - 1; nr++)
    {
        for(int i = 0; i<licznosc - nr - 1; i++)
        {
            if(tab[i].getSztuk()>tab[i + 1].getSztuk())
            {
                pom=tab[i];
                tab[i]=tab[i + 1];
                tab[i + 1]=pom;
            }
        }
    }
}

void bazainstrument::sortCena()
{
    instrument pom;
    for(int nr=0; nr<licznosc-1; nr++)
    {
        for(int i=0; i<licznosc-nr-1; i++)
        {
            if(tab[i].getCena()>tab[i + 1].getCena())
            {
                pom=tab[i];
                tab[i]=tab[i + 1];
                tab[i + 1]=pom;
            }
        }
    }
}

bool bazainstrument::sortNazwa()
{
    instrument pom;
    for(int nr=0; nr<licznosc-1; nr++)
    {
        for(int i=0; i<licznosc-nr-1; i++)
        {
            if(strcmp(tab[i].getNazwa(), tab[i + 1].getNazwa())>0)
            {
                pom=tab[i];
                tab[i]=tab[i + 1];
                tab[i + 1]=pom;
            }
        }
    }
    return 1;
}


int	bazainstrument::searchCena(float min, float max)
	{
		licznoscFound = 0;
		currentFound=-1;
		found.erase(found.begin(), found.end());

		for(int i=0; i<licznosc; i++)
		{
			if(tab[i].getCena() >= min && tab[i].getCena() <= max)
			{
				found.push_back(tab[i]);
				licznoscFound++;
			}
		}
		if(licznoscFound)
		{
			currentFound=0;
			return 1;
		}
		else
			return 0;
	}

	bool	bazainstrument::searchNazwa(char szukanaNazwa[])
	{
	licznoscFound = 0;
	currentFound = -1;
	found.erase(found.begin(), found.end());
	for(int i=0; i<licznosc; i++)
	{
		if(strcmp(szukanaNazwa, tab[i].getNazwa())==0)
		{
			found.push_back(tab[i]);
			licznoscFound++;
		}
	}
	if(licznoscFound>0)
	{
		currentFound=0;
		return 1;
	}
	else
		return 0;
	}
	
	int		bazainstrument::getLicznoscFound()
	{
		return licznoscFound;
	}
	
	int		bazainstrument::getCurrentFound()
	{
		return currentFound;
	}
	
	instrument&	bazainstrument::getInstrumentFound(int i)
	{
		return found[i];
	}
	
	instrument	bazainstrument::getFound()
	{
		return found.at(current);
	}
	
	bool	bazainstrument::nextFound()
	{
		if((currentFound+1)>=licznoscFound)
			return 0;
		currentFound++;
		return 1;
	}
	
	bool	bazainstrument::previousFound()
	{
		if((currentFound-1)<0)
			return 0;
		currentFound--;
		return 1;
	}
		

