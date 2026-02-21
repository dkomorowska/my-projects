//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <fstream>         //plik
#include <sstream>         //plik
#include <vector>
#include <System.SysUtils.hpp>
using namespace std;

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

String gName = "";
String gEmail = "";
String gCard = "";
double gBalance = 0;
int pinTry = 0;

bool FindUser(const String &card, const String &pin,
			  String &outName, String &outEmail, double &outBalance);

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btn_digitclick(TObject *Sender)
{
    TButton *btn = (TButton*)Sender;
	EditPIN->Text = EditPIN->Text + btn->Caption;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btn_cancelclick(TObject *Sender)
{
    Form1->Show();
	this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btn_clearclick(TObject *Sender)
{
	EditPIN->Text = "";
    EditCardNumber->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btn_enterclick(TObject *Sender)
{
	{
		if (EditPIN->Text.Length() != 4)
		{
			ShowMessage("PIN must have 4 digits!");
			return;
		}

		String name, email;
		double balance = 0;

		bool ok = FindUser(EditCardNumber->Text, EditPIN->Text, name, email, balance);

		if (ok)
		{
			pinTry = 0;

			gName = name;
			gEmail = email;
			gCard = EditCardNumber->Text;
			gBalance = balance;

			ShowMessage("Success!");
			Form3->SetUserData(name, email, EditCardNumber->Text, balance);
			Form3->Show();
			this->Hide();
		}
		else
		{
			pinTry++;
			ShowMessage("Wrong card num or PIN!");

			if (pinTry >= 3)
			{
				ShowMessage("Card blocked. Closing.");
				Application->Terminate();
			}
		}
	}
}
//---------------------------------------------------------------------------
bool FindUser(const String &card, const String &pin,
                          String &outName, String &outEmail, double &outBalance)
{
	ifstream file("users.txt"); //Debug
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line))
    {
		if (line.empty()) continue;        //jesli linia pusta pomijam

		stringstream ss(line);              //rozbijanie linii po ";"
		string fCard, fPin, fName, fEmail, fBalance;      // zmienne na dane z pliku

		getline(ss, fCard, ';');
        getline(ss, fPin, ';');
		getline(ss, fName, ';');
        getline(ss, fEmail, ';');
        getline(ss, fBalance, ';');

		if (String(fCard.c_str()) == card && String(fPin.c_str()) == pin)       //fcard==card && fpin==pin
		{
			outName = String(fName.c_str());                                    //string -> char -> string*
            outEmail = String(fEmail.c_str());
			outBalance = StrToFloat(String(fBalance.c_str()));
            return true;
		}
    }
    return false;
}
//---------------------------------------------------------------------------
String GetHistoryFileName()
{
    return "history_" + gCard + ".txt";
}
//---------------------------------------------------------------------------
void AppendHistory(const String &type, int amount)
{
	String fileName = "history_" + gCard + ".txt";

	ofstream file(AnsiString(fileName).c_str(), ios::app);      //problem z formatem //inna biblioteka, konwersja przez zapisem do pliku

	if (!file.is_open()) return;
		String line = "";

	if (type == "WITHDRAW")
		line = "W | -" + IntToStr(amount);
	else
		line = "D | +" + IntToStr(amount);

	//saldo po operacji
	line += " | " + FormatFloat("0.00", gBalance);              //zawsze 2 miejsca

	file<<AnsiString(line).c_str()<<endl;                       //  list->Add(line);
	file.close();						  						//list->SaveToFile(fileName);

}
//---------------------------------------------------------------------------
bool UpdateUserBalanceInFile(const String &card, double newBalance)
{
	ifstream inFile("users.txt");
	if (!inFile.is_open())
		return false;

    vector<string> allLines;
	string line;

	while (getline(inFile, line))
	{
		allLines.push_back(line);     //dodaje na koniec jak ios::app (ofstream)
	}
	inFile.close();

	//szukaie u¿ytkownika
	for (int i = 0; i < (int)allLines.size(); i++)
	{
		string temp = allLines[i];
		string storedCard = temp.substr(0, temp.find(";"));    //temp=cala linia

        if (String(storedCard.c_str()) == card)
		{
			//rozbijanie linii
			string fCard, fPin, fName, fEmail, fBalance;
			stringstream ss(temp);

            getline(ss, fCard, ';');
			getline(ss, fPin, ';');
			getline(ss, fName, ';');
			getline(ss, fEmail, ';');
			getline(ss, fBalance, ';');

			//nowe saldo
			String balanceStr = FormatFloat("0.00", newBalance);

			//u³o¿enie nowej lini
			String newLine = String(fCard.c_str())+ ";"+ String(fPin.c_str())+ ";"+
						String(fName.c_str())+ ";"+ String(fEmail.c_str())+ ";"+ balanceStr;

			//zamiana lini
            allLines[i] = AnsiString(newLine).c_str();
            break;
		}
	}

	ofstream outFile("users.txt", ios::trunc);    //ios::trunc, nadpisz plik od nowa
	if (!outFile.is_open())
		return false;

		for (string &ln : allLines)
		{
			outFile<<ln<<endl;
		}

	outFile.close();
	return true;
}
