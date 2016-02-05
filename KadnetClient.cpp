#include "KadnetClient.h"
//---- ApiResponce class -------------------------------------------------------
ApiResponse::ApiResponse () {
	__result = false;
	__data = "";
	__date;
}

ApiResponse::ApiResponse (UnicodeString json) {
	try
	{
   TJSONObject *JSON = (TJSONObject*)TJSONObject::ParseJSONValue(json);
   TJSONPair *data = JSON->Get("Data");
   __data = data->JsonValue->ToString();
   TJSONPair *date = JSON->Get("Date");
   __date = date->JsonValue->ToString();
   TJSONPair *res = JSON->Get("Result");
   SetResult(res->JsonValue->ToString());
	}
	catch (Exception *ex)
	{}
}

bool ApiResponse::Result(){return __result;}
UnicodeString ApiResponse::Data() {return __data;}
UnicodeString ApiResponse::Date() { return __date;}

void ApiResponse::SetResult(UnicodeString str)
{
	if(str=="true")
	{
		__result = true;
	}
	else{
        __result = false;
    }
}

void ApiResponse::SetData(UnicodeString str)
{
	__data = str;
}

void ApiResponse::SetDate(UnicodeString str)
{
	__date = str;
}

/******************************************************************************/
//---- KadnetApiClient class ---------------------------------------------------

KadnetApiClient::KadnetApiClient(){ url = "https://api.kadnet.ru/v1/";}
KadnetApiClient::KadnetApiClient(TIdHTTP* IdHTTP){ IdHTTPConnect = IdHTTP; SetConnectionSettings();}  //����� ������ �����������, ��������� ���.
KadnetApiClient::KadnetApiClient(UnicodeString urlparam){ url = urlparam; }
KadnetApiClient::KadnetApiClient(TIdHTTP* IdHTTP, UnicodeString tokenparam){ IdHTTPConnect = IdHTTP; SetConnectionSettings(); token=tokenparam; IdHTTPConnect->Request->CustomHeaders->Values["Authorization"]=token;}

void KadnetApiClient::SetConnectionSettings ()
{
	try{
	TIdSSLIOHandlerSocketOpenSSL *ssl= new TIdSSLIOHandlerSocketOpenSSL(NULL);
	IdHTTPConnect->IOHandler = ssl;
	IdHTTPConnect->ReadTimeout=6000;
	IdHTTPConnect->Request->ContentType="application/json";
	IdHTTPConnect->Request->Accept="application/json";
	IdHTTPConnect->Request->CharSet="utf-8";
	IdHTTPConnect->Request->CustomHeaders->FoldLines=false;
	//�������������� ��� ���� ��������
	IdHTTPConnect->Request->CustomHeaders->Values["Api-Key"]="";
	}
	catch (Exception *ex)
	{}
}

/*
	��������� Token-� ��� KadnetClient
*/
void KadnetApiClient::SetToken (UnicodeString tokenparam)
{
	token = tokenparam;
	IdHTTPConnect->Request->CustomHeaders->Values["Authorization"]=token;
}

/*
	�������� ���������� � ������ Kadnet
		����������� ����������� ��� �������� ������
		���� ������� ������������ � ������� �������� �����������
		� ����� �������
*/
ApiResponse KadnetApiClient::TestConnection(){
	try{
		ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/auth/GetTest"));
		return response;
	}
	catch (Exception *ex)
	{}
	ApiResponse response;
	return response;
}

/*
	����������� �� ����� Kadnet
		���������� �����, ������ � ������ ��
		����������� ���������� JSON
			Result: true;
			Data: [Token];
			Date: [����� �������]
	��������� ������� �������� ������ ����� ��������� TOKEN
*/
ApiResponse KadnetApiClient::Auth(UnicodeString Login, UnicodeString Password, UnicodeString Software){
	try{
	TMemoryStream *result = new TMemoryStream();
	TJSONObject *myjson = new TJSONObject();
	myjson->AddPair("login",Login);
	myjson->AddPair("password",Password);
	myjson->AddPair("software",Software);
	TStringStream *params = new TStringStream(myjson->ToString());
	IdHTTPConnect->Post("https://api.kadnet.ru/v1/auth",params,result);
	result->Position=0;
	TStringStream *answer = new TStringStream();
	answer->CopyFrom(result,result->Size);

	ApiResponse response = ApiResponse(answer->DataString);
	if (response.Result()) {
			//token = response.Data();
			token = StringReplace(response.Data(), "\"", "", TReplaceFlags() <<rfReplaceAll );
			IdHTTPConnect->Request->CustomHeaders->Values["Authorization"]=token;
	}
	return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

/*
	�������� ������ � ����� ��������
	��� ����� �������� ���������� � ��������, ������� ����� �������: ������ �������� �� ����, ������ �������� � ���. ��������� � �.�.
*/
ApiResponse KadnetApiClient::GetRequestsTypes()
{
	try{
	ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/Types"));
	return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

/*******************************************************************************
	�������� ������ � ����� ��������
	��� ���������� �� ��������, �� ������� �� ����������� ����������: ��������, ���������, ������, ������� � �.�.
*/
ApiResponse KadnetApiClient::GetObjectsTypesGkn()
{   try{
	ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/ObjectsGkn"));
	return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

ApiResponse KadnetApiClient::GetObjectsTypesEgrp()
{   try{
	ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/ObjectsEgrp"));
	return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}
/*********************************************************************************
	�������� ������ � �������
	� ������� ������� ������ ���� �����, �� ���� ������������, ������� ������� ����� ������� � ������������, ��� ����� ������ ������
*/
ApiResponse KadnetApiClient::GetRequestsTariffs()
{
	try{
	ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/Tariffs"));
	return response;
	}
		catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

/*********************************************************************************
	�������� ������ � ��������
*/
ApiResponse KadnetApiClient::GetRegions()
{
	try{
		ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/Regions"));
			return response;
	}
		catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}



/*
	�������� ���������� �������
	����������� ������ ���� � �������
*/
//TMemoryStream KadnetApiClient::GetRequestContent(UnicodeString reqId) ��� ������ ����
void  KadnetApiClient::GetRequestContent(UnicodeString reqId, UnicodeString format) //��� ��� ������������
{
	try{
	// ���� ������ ���
	TMemoryStream* ms = new TMemoryStream;
	IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/GetContent/"+reqId+"/"+format,ms);
	ms->Position=0;
	//��� ����� ��������� ������ � ����
	//return ms;
	//���� ����� ���������� ������ ���
	ms->SaveToFile("test.pdf");
	}
	catch(Exception *ex)
	{}
}


ApiResponse KadnetApiClient::CheckRequests(UnicodeString kadNumbers, UnicodeString comment, UnicodeString requestTypeId, UnicodeString objectTypeId)
{
	try{
	 TMemoryStream *result = new TMemoryStream();
	TJSONObject *myjson = new TJSONObject();
	/*
					kadNubmers = kadNubmers,
				comment = comment,
				requestsTypeId = requestsTypeId,
				objectTypeId = objectTypeId
*/
	myjson->AddPair("kadNumbers",kadNumbers);
	myjson->AddPair("comment",comment);
	myjson->AddPair("requestsTypeId",requestTypeId);
	myjson->AddPair("objectTypeId",objectTypeId);
	TStringStream *params = new TStringStream(myjson->ToString());
	IdHTTPConnect->Post("https://api.kadnet.ru/v1/Requests/Check",params,result);
	result->Position=0;
	TStringStream *answer = new TStringStream();
	answer->CopyFrom(result,result->Size);

	ApiResponse response = ApiResponse(answer->DataString);
	return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

ApiResponse KadnetApiClient::CreateRequest(bool selfSigned, UnicodeString tariffId, UnicodeString kadNumber, UnicodeString comment, UnicodeString requestTypeId, UnicodeString objectTypeId)
{
	try{
	TMemoryStream *result = new TMemoryStream();
	TJSONObject *myjson = new TJSONObject();
	myjson->AddPair("selfSigned",selfSigned?"true":"false");
	myjson->AddPair("kadNumbers",kadNumber);
	myjson->AddPair("comment",comment);
	myjson->AddPair("requestsTypeId",requestTypeId);
	myjson->AddPair("objectTypeId",objectTypeId);
	myjson->AddPair("tariffCode",tariffId);
	TStringStream *params = new TStringStream(myjson->ToString());
	IdHTTPConnect->Post("https://api.kadnet.ru/v1/Requests/Create",params,result);
	result->Position=0;
	TStringStream *answer = new TStringStream();
	answer->CopyFrom(result,result->Size);

	ApiResponse response = ApiResponse(answer->DataString);
	return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

ApiResponse KadnetApiClient::GetRequests(UnicodeString limitRequests, UnicodeString skipRequests)
{
	try{
	ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/GetRequests/" + limitRequests + "/" + skipRequests));
	return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

ApiResponse KadnetApiClient::GetRequests(UnicodeString requestTypeId, UnicodeString limitRequests, UnicodeString skipRequests)
{
	try{
	ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/GetRequestsByType/" + requestTypeId + "/" + limitRequests + "/" + skipRequests));
	return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

ApiResponse KadnetApiClient::GetRequest(UnicodeString requestId)
{
try{
	ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/GetRequest/" + requestId));
	return response;
}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}
/*	�������� token ����������� � �������*/
UnicodeString KadnetApiClient::GetToken() { return token; }

int Tools::Test()
{
	return 1;
}

UnicodeString Tools::PrintJSON(UnicodeString json)
{
	UnicodeString result;
	TJSONArray* JSON = (TJSONArray*)TJSONObject::ParseJSONValue(json); //����������� ������ � JSON ������
	int count = JSON->Size();
	result = "JSONCount = " + count;                                          //������� ������� �������� � json-�
	for (int i=0; i < count; i++) {                                    //����� ���������� ������ ������
		TJSONValue* oneEntry = JSON->Get(i);                           //�������� ���� ������
		TJSONArray*  objProperties =  (TJSONArray*)oneEntry;                 //������� ��� ��� �������
	   //	int len = objProperties->Count;                                      //������ ����� ���������� ��� ��������
	   //	for (int k=0; k < len; k++) {
	   //		TJSONValue *oneProperty = objProperties->Get(k);                //�������� ���� ��������
	   //		result = oneProperty->Value();                             //�������� ��� ��������
	   //	}
	}
	return "count="+UnicodeString(count)+"\t"+result;
/*	try{
		TJSONObject *JSON = (TJSONObject*)TJSONObject::ParseJSONValue(json); //����������� ������ � JSON ������
		int size = JSON->Size(); //�������� ���������� �������� � JSON
	}
	catch (Exception *ex)
	{}
	return "OK";*/
}
