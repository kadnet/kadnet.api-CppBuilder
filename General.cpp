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
	client = KadnetApiClient(IdHTTP1);
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
	UnicodeString software = "DemoCppApp";
	UnicodeString softwareVersion = "0.1.1";

	ApiResponse result = client.Auth(login,password,software,softwareVersion);
	Label2->Caption = client.GetToken();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	/*
	ApiResponse result = client.GetRequestsTypes();
	UnicodeString data = result.Data();
	Label3->Caption = result.Data();
	*/
	/*
	ApiResponse req4sign = client.GetRequestsToSign();
	Label3->Caption = req4sign.Data();
	*/
	UnicodeString signCont = "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MjAxNS5jcmwwLKAqoCiGJmh0dHA6Ly90ZW5zb3IucnUvY2EvdGVuc29yY2EzLTIwMTUuY3JsMDmgN6A1hjNodHRwOi8vY3JsLnRlbnNvci5ydS90YXg0L2NhL2NybC90ZW5zb3JjYTMtMjAxNS5jcmwwOqA4oDaGNGh0dHA6Ly9jcmwyLnRlbnNvci5ydS90YXg0L2NhL2NybC90ZW5zb3JjYTMtMjAxNS5jcmwwOqA4oDaGNGh0dHA6Ly9jcmwzLnRlbnNvci5ydS90YXg0L2NhL2NybC90ZW5zb3JjYTMtMjAxNS5jcmwwggGgBggrBgEFBQcBAQSCAZIwggGOMC8GCCsGAQUFBzABhiNodHRwOi8vdGF4NC50ZW5zb3IucnUvb2NzcC9vY3NwLnNyZjAtBggrBgEFBQcwAoYhaHR0cDovL3RheDQudGVuc29yLnJ1L3RzcC90c3Auc3JmMD8GCCsGAQUFBzAChjNodHRwOi8vdGF4NC50ZW5zb3IucnUvY2VydGVucm9sbC90ZW5zb3JjYTMtMjAxNS5jcnQwMgYIKwYBBQUHMAKGJmh0dHA6Ly90ZW5zb3IucnUvY2EvdGVuc29yY2EzLTIwMTUuY3J0MDsGCCsGAQUFBzAChi9odHRwOi8vY3JsLnRlbnNvci5ydS90YXg0L2NhL3RlbnNvcmNhMy0yMDE1LmNydDA8BggrBgEFBQcwAoYwaHR0cDovL2NybDIudGVuc29yLnJ1L3RheDQvY2EvdGVuc29yY2EzLTIwMTUuY3J0MDwGCCsGAQUFBzAChjBodHRwOi8vY3JsMy50ZW5zb3IucnUvdGF4NC9jYS90ZW5zb3JjYTMtMjAxNS5jcnQwKwYDVR0QBCQwIoAPMjAxNjAxMjgwNjM0MDBagQ8yMDE3MDEyODA2MzQwMFowggEzBgUqhQNkcASCASgwggEkDCsi0JrRgNC40L/RgtC+0J/RgNC+IENTUCIgKNCy0LXRgNGB0LjRjyAzLjYpDFMi0KPQtNC+0YHRgtC+0LLQtdGA0Y/RjtGJ0LjQuSDRhtC10L3RgtGAICLQmtGA0LjQv9GC0L7Qn9GA0L4g0KPQpiIg0LLQtdGA0YHQuNC4IDEuNQxP0KHQtdGA0YLQuNGE0LjQutCw0YIg0YHQvtC+0YLQstC10YLRgdGC0LLQuNGPIOKEliDQodCkLzEyNC0yNzM4INC+0YIgMDEuMDcuMjAxNQxP0KHQtdGA0YLQuNGE0LjQutCw0YIg0YHQvtC+0YLQstC10YLRgdGC0LLQuNGPIOKEliDQodCkLzEyOC0yMzUyINC+0YIgMTUuMDQuMjAxNDAIBgYqhQMCAgMDQQCnPAGV8Phin+WwYNbQlzgwBK+gojBSPZr803nC8kcGHJ/gjINrWyAi68UZGadNKwgWlAs8NmwOBmgeEbQDkjII";
	ApiResponse sign = client.SaveSign("c2431c4d-3fdd-44ba-964e-14b5fc618e35",signCont,"asdf","0.0.0.1-alfa");
	Label3->Caption = sign.Data();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	ApiResponse result = client.GetObjectsTypesEgrp();
	Label4->Caption = result.Data();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	//ApiResponse result = client.GetRequestsTariffs();
	ApiResponse result = client.GetRegions();
	Label5->Caption = result.Data();
	//client.GetRequestContent("11f68398-fca5-4db2-9d34-05d5b3ad9f63","Pdf");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	ApiResponse checkReq = client.CheckRequests("24:50:0000000:58340;24:50:0000000:58360-58365","яяя","6aa0e204-4d11-4e97-8348-1c2d9bce3655","00000000-0000-0000-0000-000000000000");
	Label6->Caption = checkReq.Data();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	/* Перед созданием надо проверять объекты функцией CheckRequests() */
	bool selfSigned = false;
	//сначала проверяем какие тарифы доступны для этого типа запроса
	ApiResponse tariffList = client.GetRequestsTariffs("6aa0e204-4d11-4e97-8348-1c2d9bce3655");
	//результат надо как то отобразить пользователю информацию из tariffList.Data (там JSON) и дать ему выбрать нужный тариф.
	//например, он выбрал тариф "Все включено 190р."
	//теперь создаем запрос
	UnicodeString tariffCode = "KptAllInclusive";
	ApiResponse createReq = client.CreateRequest(selfSigned,tariffCode,"24:50:0000000:58340","yyy","6aa0e204-4d11-4e97-8348-1c2d9bce3655","00000000-0000-0000-0000-000000000000");
	Label7->Caption = createReq.Data();
		/*
		Тут все значения из списка, который в request.Data надо сложить в ComboBox.
	*/
	Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
		ApiResponse checkReq = client.GetRequestsByType("ГКН",10,0);
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
	//UnicodeString token = "";
	/*
	//Вариант 1. Читаем токен и передаем его в конструктор. Использовать при создании
	//тут мы его, как будто прочитали из ini файла
	//тут создаем объект, передавая данные в конструктор
	client = KadnetApiClient(IdHTTP1,token);
	*/

	/**/
	//Вариант 2. Тут мы устанавливаем токен к уже существующему объекту
	//client = KadnetApiClient(IdHTTP1);
	//client.SetToken(token);


	ApiResponse result = client.GetRequestsTariffs("31efe079-ea67-4fb8-9c9d-c38e194dba5c");
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

void __fastcall TForm1::Button11Click(TObject *Sender)
{
	 TMemoryStream* file = client.GetRequestContent("4fdcf88e-c075-4c11-8d98-4ae063cd1121","pdf");
	 file->SaveToFile("test.zip");
}
//---------------------------------------------------------------------------

