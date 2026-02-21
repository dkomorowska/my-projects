//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Lbl_deposit;
	TLabel *Lbl_amount;
	TEdit *EditAmount2;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TButton *Button11;
	TButton *Button12;
	TButton *Button0;
	TButton *CLEAR;
	TButton *BACK;
	TButton *CONFIRM;
	TButton *Button4;
	TImage *background;
	TLabel *Label3;
	void __fastcall btn_back(TObject *Sender);
	void __fastcall btn_confirm(TObject *Sender);
	void __fastcall btn_clear(TObject *Sender);
	void __fastcall btn_digit(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
