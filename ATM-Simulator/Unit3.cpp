//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <fstream>
#include <string>

using namespace std;
#include "Unit3.h"
#include "Unit2.h"
#include "Unit1.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

String FormatCardNumber(const String &card);  //zadeklarowana wczesniej
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TForm3::SetUserData(const String &name, const String &email,
						 const String &card, double balance)
{
    LblNameValue->Caption = name;
	LblEmailValue->Caption = email;
	LblCardValue->Caption = FormatCardNumber(card);
	LblBalanceValue->Caption = FormatFloat("0.00", balance)+ " $";
	LoadHistory();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::BtnLogout(TObject *Sender)
{
	Form2->EditPIN->Text = "";
    Form2->EditCardNumber->Text = "";

	Form1->Show();
	this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::BtnWithdraw(TObject *Sender)
{
	Form4->Show();
	this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::BtnDeposit(TObject *Sender)
{
	Form5->Show();
	this->Hide();
}
//---------------------------------------------------------------------------
void TForm3::LoadHistory()
{
    ListHistory->Clear();
	string line;

	String fileName = GetHistoryFileName();

    ifstream file(AnsiString(fileName).c_str());
    if (!file.is_open())
    {
        ListHistory->Items->Add("No history for this account.");
        return;
    }

	while (getline(file, line))
    {
        if (!line.empty())
            ListHistory->Items->Add(String(line.c_str()));
	}

	file.close();

    if (ListHistory->Items->Count == 0)
	ListHistory->Items->Add("No transactions yet.");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::BtnRefreshHistory(TObject *Sender)
{
	LoadHistory();
}
//---------------------------------------------------------------------------
String FormatCardNumber(const String &card)
{
String format = "";

	for (int i=1; i<=card.Length(); i++)
    {
		format += card[i];

        if (i == 4 || i == 8 || i == 12)
			format += " ";
    }
	return format;
}
