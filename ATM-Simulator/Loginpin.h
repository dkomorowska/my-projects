//---------------------------------------------------------------------------

#ifndef LoginpinH
#define LoginpinH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TFormPIN : public TForm
{
__published:	// IDE-managed Components
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
	void __fastcall Btn_cancelClick(TObject *Sender);
	void __fastcall Btn_clearclick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormPIN(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPIN *FormPIN;
//---------------------------------------------------------------------------
#endif
