//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
#include "Unit3.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
	EditAmount2->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm5::btn_back(TObject *Sender)
{
    EditAmount2->Text = "";
    Form3->Show();
    this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm5::btn_confirm(TObject *Sender)
{
//czy jest wpisane cokolwiek
	if (EditAmount2->Text == "")
    {
        ShowMessage("Enter amount!");
        return;
    }

//zamiana na liczbe
    int amount = StrToIntDef(EditAmount2->Text, 0);
    if (amount <= 0)
    {
        ShowMessage("Amount must be > 0");
        return;
    }

//wielokrotnosc 10
    if (amount % 10 != 0)
    {
        ShowMessage("Amount must be multiple of 10!");
        return;
	}

//jesli ok, zamiana salda
	gBalance += amount;

	AppendHistory("DEPOSIT", amount);
	UpdateUserBalanceInFile(gCard, gBalance);

//odswiezenie menu
    Form3->SetUserData(gName, gEmail, gCard, gBalance);

    ShowMessage("Deposit completed!");

//powrót
	EditAmount2->Text = "";
    Form3->Show();
    this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm5::btn_clear(TObject *Sender)
{
	EditAmount2->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm5::btn_digit(TObject *Sender)
{
	TButton *btn = (TButton*)Sender;
	EditAmount2->Text = EditAmount2->Text + btn->Caption;
}
//---------------------------------------------------------------------------


