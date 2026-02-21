//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "loginpin.h"

#include "ATMSimulator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormStart *FormStart;
//---------------------------------------------------------------------------
__fastcall TFormStart::TFormStart(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormStart::Btn_exitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall TFormStart::Btn_insertcardClick(TObject *Sender)
{
	FormPIN->Show();
	this->Hide();
}
//---------------------------------------------------------------------------

