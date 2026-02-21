//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TLabel *LblNameValue;
	TLabel *LblEmailValue;
	TLabel *LblCardValue;
	TLabel *LblBalanceValue;
	TButton *Btn_withdraw;
	TButton *Btn_deposit;
	TButton *Btn_logout;
	TListBox *ListHistory;
	TButton *Button1;
	TImage *background;
	TLabel *Label3;
	TLabel *Label1;
	void __fastcall BtnLogout(TObject *Sender);
	void __fastcall BtnWithdraw(TObject *Sender);
	void __fastcall BtnDeposit(TObject *Sender);
	void __fastcall BtnRefreshHistory(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
	void SetUserData(const String &name, const String &email,
					 const String &card, double balance);
    void LoadHistory();
};

//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
