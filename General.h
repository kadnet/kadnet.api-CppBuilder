//---------------------------------------------------------------------------

#ifndef GeneralH
#define GeneralH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TIdHTTP *IdHTTP1;
	TLabel *Label1;
	TButton *Button2;
	TLabel *Label2;
	TButton *Button3;
	TLabel *Label3;
	TButton *Button4;
	TLabel *Label4;
	TButton *Button5;
	TLabel *Label5;
	TButton *Button6;
	TLabel *Label6;
	TButton *Button7;
	TLabel *Label7;
	TButton *Button8;
	TLabel *Label8;
	TButton *Button9;
	TLabel *Label9;
	TButton *Button10;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
