//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "General.h"
#include "KadnetClient.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
KadnetApiClient client;   //тут костыль - передаем сюда IdHTTP только после того, как щелкнут первую кнопку TestConnection (Button1Click)
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button1Click(TObject *Sender)
{
	client = KadnetApiClient(IdHTTP1); //Боже мой,какой костыль! будь ты проклят C++Builder
	ApiResponse result = client.TestConnection();
	if (result.Result()) {
	Label1->Caption = result.Data()+"\n"+result.Date();
	}
	else
	{
		Label1->Caption = "Не смог получить данные с сервера";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	UnicodeString login = "testapi@kadnet.ru";
	UnicodeString password = "Api2015test";
	UnicodeString version = "DemoCppApp";

	ApiResponse result = client.Auth(login,password,version);
	Label2->Caption = client.GetToken();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	ApiResponse result = client.GetRequestsTypes();
	Label3->Caption = result.Data();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	ApiResponse result = client.GetObjectsTypes();
	Label4->Caption = result.Data();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	ApiResponse result = client.GetRequestsTariffs();
	Label5->Caption = result.Data();
	client.GetRequestContent("11f68398-fca5-4db2-9d34-05d5b3ad9f63","Pdf");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	ApiResponse checkReq = client.CheckRequests("24:50:0000000:58340;24:50:0000000:58360-58365","Иванов И.И., договор №3315","6aa0e204-4d11-4e97-8348-1c2d9bce3655","");
	Label6->Caption = checkReq.Data();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	/* Перед созданием надо проверять объекты функцией CheckRequests() */
	bool selfSigned = false;
	UnicodeString tariffId="427EC010-AC65-4CAC-A61B-210D297BA824";
	ApiResponse createReq = client.CreateRequest(selfSigned,tariffId,"24:50:0000000:58340","Иванов И.И., договор №3315","6aa0e204-4d11-4e97-8348-1c2d9bce3655","");
	Label7->Caption = createReq.Data();
		/*
		Тут все значения из списка, который в request.Data надо сложить в ComboBox.
	*/
	Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
		ApiResponse checkReq = client.GetRequests(15,0);
		Label8->Caption = checkReq.Data();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
		ApiResponse checkReq = client.GetRequest("c2431c4d-3fdd-44ba-964e-14b5fc618e35");
		Label9->Caption = checkReq.Data();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
	UnicodeString token = "";
	/*
	//Вариант 1. Читаем токен и передаем его в конструктор. Использовать при создании
	//тут мы его, как будто прочитали из ini файла
	//тут создаем объект, передавая данные в конструктор
	client = KadnetApiClient(IdHTTP1,token);
	*/

	/**/
	//Вариант 2. Тут мы устанавливаем токен к уже существующему объекту
	client = KadnetApiClient(IdHTTP1);
	client.SetToken(token);


	ApiResponse result = client.TestConnection();
	if (result.Result()) {
	Label1->Caption = result.Data()+"\n"+result.Date();
	}
	else
	{
		Label1->Caption = "Не смог получить данные с сервера";
	}
	/**/
}
//---------------------------------------------------------------------------

