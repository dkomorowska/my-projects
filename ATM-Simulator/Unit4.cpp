//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "Unit4.h"
#include "Unit3.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
	EditAmount->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm4::btn_digit(TObject *Sender)
{
	TButton *btn = (TButton*)Sender;
	EditAmount->Text = EditAmount->Text + btn->Caption;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::btn_clear(TObject *Sender)
{
	EditAmount->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm4::btn_back(TObject *Sender)
{
    EditAmount->Text = "";
    Form3->Show();
    this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::btn_confirm(TObject *Sender)
{
//czy jest wpisane cokolwiek
	if (EditAmount->Text == "")
    {
        ShowMessage("Enter amount!");
        return;
    }

//zamiana na liczbe
    int amount = StrToIntDef(EditAmount->Text, 0);
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

//limit
	const int LIMIT = 2000;
    if (amount > LIMIT)
	{
        ShowMessage("Amount exceeds limit!");
        return;
    }

//czy jest saldo
    if (amount > gBalance)
    {
        ShowMessage("Not enough balance!");
        return;
    }

//jesli ok, zamiana salda
	gBalance -= amount;

	AppendHistory("WITHDRAW", amount);
	UpdateUserBalanceInFile(gCard, gBalance);

//odswiezenie menu
    Form3->SetUserData(gName, gEmail, gCard, gBalance);

    ShowMessage("Withdraw completed!");

//powrót
    EditAmount->Text = "";
    Form3->Show();
    this->Hide();
}
//---------------------------------------------------------------------------
