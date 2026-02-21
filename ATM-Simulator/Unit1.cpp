//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Btn_insertcardClick(TObject *Sender)
{
	Form2->Show();
	this->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Btn_exitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


