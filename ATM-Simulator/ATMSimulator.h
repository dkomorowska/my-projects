//---------------------------------------------------------------------------

#ifndef ATMSimulatorH
#define ATMSimulatorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TFormStart : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TButton *Btn_insertcard;
	TButton *Btn_exit;
	void __fastcall Btn_exitClick(TObject *Sender);
	void __fastcall Btn_insertcardClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormStart(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormStart *FormStart;
//---------------------------------------------------------------------------
#endif
