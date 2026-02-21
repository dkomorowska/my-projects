//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Lbl_withdraw;
	TLabel *Lbl_amount;
	TEdit *EditAmount;
	TButton *btn_clearr;
	TButton *btn_confirmm;
	TButton *btn_backk;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TButton *Button11;
	TButton *Button12;
	TButton *Button0;
	TImage *background;
	TLabel *Label3;
	void __fastcall btn_digit(TObject *Sender);
	void __fastcall btn_clear(TObject *Sender);
	void __fastcall btn_back(TObject *Sender);
	void __fastcall btn_confirm(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
extern String gName;
extern String gEmail;
extern String gCard;
extern double gBalance;
extern int pinTry;
//---------------------------------------------------------------------------
#endif
