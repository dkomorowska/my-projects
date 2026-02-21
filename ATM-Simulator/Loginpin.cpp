//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Loginpin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPIN *FormPIN;
//---------------------------------------------------------------------------
__fastcall TFormPIN::TFormPIN(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPIN::Btn_cancelClick(TObject *Sender)
{
	FormStart->Show();
	this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFormPIN::Btn_clearclick(TObject *Sender)
{
	EdtPIN->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormPIN::Button3Click(TObject *Sender)
{
    TButton *btn = (TButton*)Sender;
	EdtPIN->Text = EdtPIN->Text + btn->Caption;
}
//---------------------------------------------------------------------------
