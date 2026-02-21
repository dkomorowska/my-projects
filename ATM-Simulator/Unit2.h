//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>

extern String gName;
extern String gEmail;
extern String gCard;
extern double gBalance;

//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TButton *Button0;
	TButton *Btn_cancel;
	TButton *btn_clearclic;
	TButton *Button10;
	TEdit *EditPIN;
	TEdit *EditCardNumber;
	TImage *Image1;
	TLabel *Label3;
	void __fastcall btn_digitclick(TObject *Sender);
	void __fastcall btn_cancelclick(TObject *Sender);
	void __fastcall btn_clearclick(TObject *Sender);
	void __fastcall btn_enterclick(TObject *Sender);
private:
	int pinTry = 0;
public:
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;

String GetHistoryFileName();
void AppendHistory(const String &type, int amount);
bool UpdateUserBalanceInFile(const String &card, double newBalance);

//---------------------------------------------------------------------------
#endif
