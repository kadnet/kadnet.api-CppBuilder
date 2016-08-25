/* KadnetClient.cpp **** Balandin D.V. [dmitry@kadnet.ru]    12/08/16

			  Copyright (c) KADNET 2014-2016
					  All Rights Reserved

********************************************************************

				FOR WIN32S , WINDOWS95 & WINDOWS NT

********************************************************************

	           ���������� ��� ������ � api.kadnet.ru

*******************************************************************/
#include "KadnetClient.h"
//---- ApiResponce class -------------------------------------------------------
ApiResponse::ApiResponse () {
	__result = false;
	__data = "";
	__date;
}

ApiResponse::ApiResponse (UnicodeString json) {
	try{
		TJSONObject *JSON = 0;
		try
		{
			JSON = (TJSONObject*)TJSONObject::ParseJSONValue(json);
			if (JSON)
			{
				TJSONPair *data = JSON->Get("Data");
				__data = data->JsonValue->ToString();
				TJSONPair *date = JSON->Get("Date");
				__date = date->JsonValue->ToString();
				TJSONPair *res = JSON->Get("Result");
				SetResult(res->JsonValue->ToString());
				delete JSON;
			}
		}
		catch (Exception *ex)
		{
			if (JSON)
			{
				delete JSON;
				JSON = 0;
			}
		}
	}

	catch (Exception *ex)
	{}
}

bool ApiResponse::Result(){return __result;}
UnicodeString ApiResponse::Data() {return __data;}
UnicodeString ApiResponse::Date() { return __date;}

void ApiResponse::SetResult(UnicodeString str)
{
	if(str=="true"){
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

/*******************************************************************************
	���������� ��������� ����������� � ������� Kadnet
*/
void KadnetApiClient::SetConnectionSettings ()
{
	try{
	TIdSSLIOHandlerSocketOpenSSL *ssl= new TIdSSLIOHandlerSocketOpenSSL(NULL);
	IdHTTPConnect->IOHandler = ssl;
	IdHTTPConnect->ReadTimeout=30000;
	IdHTTPConnect->Request->ContentType="application/json";
	IdHTTPConnect->Request->Accept="application/json";
	IdHTTPConnect->Request->CharSet="utf-8";
	IdHTTPConnect->Request->CustomHeaders->FoldLines=false;
	//Api-Key �������������� ��� ���� ��������
	IdHTTPConnect->Request->CustomHeaders->Values["Api-Key"]="MFjpY5JGHzWoCPzdl0RqJJBPcZPTZtUYTGHjW4mbbCW3MWZZZf/RuPtmLrnTqvRgdQVqXCeFzWXD1F92Hxn1R2Zez1nx1MCQfiRdIrHJeDtYPlHAcaAsMaMIYM4yH/AhltvVOokTcKftRQwy2hTv0g==";
	}
	catch (Exception *ex)
	{}
}

/*******************************************************************************
	��������� Token-� ��� KadnetClient
*/
void KadnetApiClient::SetToken (UnicodeString tokenparam)
{
	token = tokenparam;
	IdHTTPConnect->Request->CustomHeaders->Values["Authorization"]=token;
}

/*******************************************************************************
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

/*******************************************************************************
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
		TJSONObject *myjson = 0;
		TStringStream *params = 0;
		TStringStream *answer = 0;
		try
		{
			myjson = new TJSONObject();
			if (myjson)
			{
				myjson->AddPair("login",Login);
				myjson->AddPair("password",Password);
				myjson->AddPair("software",Software);

				TEncoding *LEncoding = NULL;
				params = new TStringStream(myjson->ToString(),LEncoding->UTF8,false);

				UnicodeString empty;
				answer = new TStringStream(empty,LEncoding->UTF8,false);

				IdHTTPConnect->Post("https://api.kadnet.ru/v1/auth",params,answer);

				ApiResponse response = ApiResponse(answer->DataString);
				if (response.Result()) {
					token = StringReplace(response.Data(), "\"", "", TReplaceFlags() <<rfReplaceAll );
					IdHTTPConnect->Request->CustomHeaders->Values["Authorization"]=token;
				}
				delete LEncoding;
				delete myjson;
				delete answer;
				delete params;
				return response;
			}
		}
		catch (Exception *ex)
		{
			if (myjson)
			{
				delete myjson;
				myjson = 0;
			}
			if (params)
			{
				delete params;
				params = 0;
			}
			if (answer)
			{
				delete answer;
				answer = 0;
			}
		}
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

/*******************************************************************************
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

/*******************************************************************************
	�������� ������ � ����� ��������
	��� ���������� �� ��������, �� ������� �� ����������� ����������: ��������, ���������, ������, ������� � �.�.
*/
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
ApiResponse KadnetApiClient::GetRequestsTariffs(UnicodeString tariffId)
{
	try{
		ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/Tariffs/"+tariffId));
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



/*******************************************************************************
	�������� ���������� �������
	����������� ������ Zip-���� � �������
*/
TMemoryStream* KadnetApiClient::GetRequestContent(UnicodeString reqId, UnicodeString format)
{
	try{
	TMemoryStream* ms = 0;
	try
	{
		ms = new TMemoryStream;
		if (ms)	{
			IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/GetContent/"+reqId+"/"+format,ms);
			ms->Position=0;
			return ms;
		}
	}
	catch (Exception *ex)
	{
		if (ms)	{
			delete ms;
			ms = 0;
		}
	}
	return ms;
	}
	catch(Exception *ex)
	{}
}

/*******************************************************************************
	�������� XML ������� � ���� AnsiString
	�� ������������!!!
*/
AnsiString KadnetApiClient::GetRequestBody(UnicodeString reqId)
{
	 try{
		UnicodeString empty;
		TEncoding *LEncoding = NULL;
		TStringStream *answer = new TStringStream(empty,LEncoding->UTF8,false);
		IdHTTPConnect->Get("https://api.kadnet.ru/v1//Requests/GetRequestBody/" + reqId,answer);
		delete LEncoding;
		return answer->DataString.Trim();
	}
	catch(Exception *ex)
	{}
}

/*******************************************************************************
	�������� XML ������� � ���� Base64
	������������ ��� ������� � ��������
*/
ApiResponse KadnetApiClient::GetRequestBodyBase64(UnicodeString reqId)
{
	try{
		ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/GetRequestBodyBase64/" + reqId));
		return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}


/*******************************************************************************
	��������� ������.
	������ ����������� �� �������, ����������� ������������ ������ � �����
*/
ApiResponse KadnetApiClient::CheckRequests(UnicodeString kadNumbers, UnicodeString comment, UnicodeString requestTypeId, UnicodeString objectTypeId)
{
	try{
		TJSONObject *myjson = 0;
		TStringStream *params = 0;
		TStringStream *answer = 0;
		try {
 			myjson = new TJSONObject();
			myjson->AddPair("kadNumbers",kadNumbers);
			myjson->AddPair("comment",comment);
			myjson->AddPair("requestsTypeId",requestTypeId);
			myjson->AddPair("objectTypeId",objectTypeId);
			TEncoding *LEncoding = NULL;
			params = new TStringStream(myjson->ToString(),LEncoding->UTF8,false);

			UnicodeString empty;
			TStringStream *answer = new TStringStream(empty,LEncoding->UTF8,false);

			IdHTTPConnect->Post("https://api.kadnet.ru/v1/Requests/Check",params,answer);
			ApiResponse response = ApiResponse(answer->DataString);

			delete LEncoding;
			delete myjson;
			delete params;
			delete answer;

			return response;

		} catch (Exception *ex) {
			if (myjson) {
				delete myjson;
				myjson = 0;
			}
			if (params) {
				delete params;
				params = 0;
			}
			if (answer) {
				delete answer;
				answer = 0;
			}
		}
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

/*******************************************************************************
	�������� �������
*/
ApiResponse KadnetApiClient::CreateRequest(bool selfSigned, UnicodeString tariffCode, UnicodeString kadNumber, UnicodeString comment, UnicodeString requestTypeId, UnicodeString objectTypeId)
{
	try{
		TJSONObject *myjson = 0;
		TStringStream *params = 0;
		TStringStream *answer = 0;
		try{
			myjson = new TJSONObject();
			myjson->AddPair("selfSigned",selfSigned?"true":"false");
			myjson->AddPair("kadNumber",kadNumber);
			myjson->AddPair("comment",comment);
			myjson->AddPair("requestsTypeId",requestTypeId);
			myjson->AddPair("objectTypeId",objectTypeId);
			myjson->AddPair("tariffCode", tariffCode);

			TEncoding *LEncoding = NULL;
			params = new TStringStream(myjson->ToString(),LEncoding->UTF8,false);

			UnicodeString empty;
			TStringStream *answer = new TStringStream(empty,LEncoding->UTF8,false);

			IdHTTPConnect->Post("https://api.kadnet.ru/v1/Requests/Create",params,answer);

			ApiResponse response = ApiResponse(answer->DataString);

			delete LEncoding;
			delete myjson;
			delete params;
			delete answer;

			return response;
		} catch (Exception *ex) {
			if (myjson) {
				delete myjson;
				myjson = 0;
			}
			if (params) {
				delete params;
				params = 0;
			}
			if (answer) {
				delete answer;
				answer = 0;
			}
		}
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

/*******************************************************************************
	�������� ������ �������� ������������.
	limitRequest - ����������� ����� ��������
	skipRequest - ���������� ������� � ������
*/
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

/*******************************************************************************
	�������� ������ �������� ������������� ����
	limitRequest - ����������� ����� ��������
	skipRequest - ���������� ������� � ������
*/
ApiResponse KadnetApiClient::GetRequestsByType(UnicodeString requestType, UnicodeString limitRequests, UnicodeString skipRequests)
{
	try{
		ApiResponse response = ApiResponse(IdHTTPConnect->Get(TIdURI::URLEncode("https://api.kadnet.ru/v1/Requests/GetRequestsByType/" + requestType + "/" + limitRequests + "/" + skipRequests)));
		return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}


/*******************************************************************************
	�������� ������ ������������
*/
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

/*******************************************************************************
	�������� ������� ����� �������� �������
*/
ApiResponse KadnetApiClient::GetRequestHistory(UnicodeString requestId)
{
	try{
		ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/GetRequestHistory/" + requestId));
		return response;
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

/*******************************************************************************
	������� ������ ������������
*/
ApiResponse KadnetApiClient::DeleteRequest(UnicodeString requestId)
{
	 try{
		 TStringStream *answer = 0;
		 try{
			 UnicodeString empty;
			 TEncoding *LEncoding = NULL;
			 TStringStream *answer = new TStringStream(empty,LEncoding->UTF8,false);

			 IdHTTPConnect->Post("https://api.kadnet.ru/v1/Requests/Delete/" + requestId, answer);

			 ApiResponse response = ApiResponse(answer->DataString);

			 delete LEncoding;
			 delete answer;
			 return response;

		} catch (Exception *ex) {
			if (answer) {
				delete answer;
				answer = 0;
			}
		}
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

/*******************************************************************************
	�������� ������� �������������� ��� ������� ��� ������������
*/
ApiResponse KadnetApiClient::GetRequestsToSign()
{
	try{
		ApiResponse response = ApiResponse(IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/GetRequestsToSign/"));
		return response;
	}
	catch(Exception *ex){}
	ApiResponse response;
	return response;
}


/*******************************************************************************
	�������� ���� ����������� ������� ������� �� ������
ApiResponse KadnetApiClient::SaveSign(UnicodeString requestId, UnicodeString signContent, UnicodeString certContent, UnicodeString cpVersion)
{
	try{
		TMemoryStream *result = 0;
		TJSONObject *myjson = 0;
		TStringStream *params = 0;
		TStringStream *answer = 0;
		try{
			result = new TMemoryStream();
			myjson = new TJSONObject();

			myjson->AddPair("requestId",requestId);
			myjson->AddPair("signContent",signContent);
			myjson->AddPair("certContent",certContent);
			myjson->AddPair("cpVersion",cpVersion);

			params = new TStringStream(myjson->ToString());
			IdHTTPConnect->Post("https://api.kadnet.ru/v1/Requests/SaveSign",params,result);
			result->Position=0;

			answer = new TStringStream();
			answer->CopyFrom(result,result->Size);
			ApiResponse response = ApiResponse(answer->DataString);

			delete result;
			delete myjson;
			delete params;
			delete answer;

			return response;
		} catch (Exception *ex) {
			if (result) {
				delete result;
				result = 0;
			}
			if (myjson) {
				delete myjson;
				myjson = 0;
			}
			if (params) {
				delete params;
				params = 0;
			}
			if (answer) {
				delete answer;
				answer = 0;
			}
		}
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}
*/

/*******************************************************************************
	��������� ������� ������� �� ������
*/
ApiResponse KadnetApiClient::SaveSign(UnicodeString requestId, UnicodeString signContent, UnicodeString certContent, UnicodeString cpVersion)
{
	try{
		TJSONObject *myjson = 0;
		TStringStream *params = 0;
		TStringStream *answer = 0;

		try{
			myjson = new TJSONObject();
			myjson->AddPair("requestId",requestId);
			myjson->AddPair("signContent",signContent);
			myjson->AddPair("certContent",certContent);
			myjson->AddPair("cpVersion",cpVersion);

			TEncoding *LEncoding = NULL;

			TStringStream *params = new TStringStream(myjson->ToString(),LEncoding->UTF8,false);
			UnicodeString empty = 0;
			TStringStream *answer = new TStringStream(empty,LEncoding->UTF8,false);

			IdHTTPConnect->Post("https://api.kadnet.ru/v1/Requests/SaveSign",params,answer);
			ApiResponse response = ApiResponse(answer->DataString);

			delete LEncoding;
			delete myjson;
			delete params;
			delete answer;

			return response;
		} catch (Exception *ex) {
			if (myjson) {
				delete myjson;
				myjson = 0;
			}
			if (params) {
				delete params;
				params = 0;
			}
			if (answer) {
				delete answer;
				answer = 0;
			}
		}
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

ApiResponse KadnetApiClient::SaveSign(UnicodeString requestId, AnsiString signContent, AnsiString certContent, UnicodeString cpVersion)
{
	try{
		TJSONObject *myjson = 0;
		TStringStream *params = 0;
		TStringStream *answer = 0;

		try{
			myjson = new TJSONObject();
			myjson->AddPair("requestId",requestId);
			myjson->AddPair("signContent",signContent);
			myjson->AddPair("certContent",certContent);
			myjson->AddPair("cpVersion",cpVersion);
			TEncoding *LEncoding = NULL;
			UnicodeString empty = 0;
			TStringStream *params = new TStringStream(myjson->ToString(),LEncoding->UTF8,false);
			TStringStream *answer = new TStringStream(empty,LEncoding->UTF8,false);

			IdHTTPConnect->Post("https://api.kadnet.ru/v1/Requests/SaveSign",params,answer);
			ApiResponse response = ApiResponse(answer->DataString);

			delete LEncoding;
			delete myjson;
			delete params;
			delete answer;

			return response;
		} catch (Exception *ex) {
			if (myjson) {
				delete myjson;
				myjson = 0;
			}
			if (params) {
				delete params;
				params = 0;
			}
			if (answer) {
				delete answer;
				answer = 0;
			}
		}
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

ApiResponse KadnetApiClient::SaveSign(UnicodeString requestId, unsigned char signContentArray, int signContentLenght, unsigned char certContentArray, int certContentLenght, UnicodeString cpVersion)
{
	try{
		TJSONObject *myjson = 0;
		TStringStream *params = 0;
		TStringStream *answer = 0;
		try{
			AnsiString signContent = AnsiString((char*) signContentArray,signContentLenght);
			AnsiString certContent = AnsiString((char*) certContentArray,certContentLenght);
			myjson = new TJSONObject();
			myjson->AddPair("requestId",requestId);
			myjson->AddPair("signContent",signContent);
			myjson->AddPair("certContent",certContent);
			myjson->AddPair("cpVersion",cpVersion);
			TEncoding *LEncoding = NULL;
			UnicodeString empty;
			params = new TStringStream(myjson->ToString(),LEncoding->UTF8,false);
			answer = new TStringStream(empty,LEncoding->UTF8,false);

			IdHTTPConnect->Post("https://api.kadnet.ru/v1/Requests/SaveSign",params,answer);
			ApiResponse response = ApiResponse(answer->DataString);

			delete LEncoding;
			delete myjson;
			delete params;
			delete answer;

			return response;
		} catch (Exception *ex) {
			if (myjson) {
				delete myjson;
				myjson = 0;
			}
			if (params) {
				delete params;
				params = 0;
			}
			if (answer) {
				delete answer;
				answer = 0;
			}
		}
	}
	catch(Exception *ex)
	{}
	ApiResponse response;
	return response;
}

/*******************************************************************************
	�������� token ����������� � �������
*/
UnicodeString KadnetApiClient::GetToken() { return token; }




/******************************************************************************/
/*******************************************************************************
	����� � ������������
*/
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
