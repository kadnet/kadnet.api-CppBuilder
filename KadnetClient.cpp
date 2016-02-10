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
KadnetApiClient::KadnetApiClient(TIdHTTP* IdHTTP){ IdHTTPConnect = IdHTTP; SetConnectionSettings();}  //самое полный конструктор, используй его.
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
	//индивидуальный для всех клиентов
	IdHTTPConnect->Request->CustomHeaders->Values["Api-Key"]="MFjpY5JGHzWoCPzdl0RqJJBPcZPTZtUYTGHjW4mbbCW3MWZZZf/RuPtmLrnTqvRgdQVqXCeFzWXD1F92Hxn1R2Zez1nx1MCQfiRdIrHJeDtYPlHAcaAsMaMIYM4yH/AhltvVOokTcKftRQwy2hTv0g==";
	}
	catch (Exception *ex)
	{}
}

/*
	Установка Token-а для KadnetClient
*/
void KadnetApiClient::SetToken (UnicodeString tokenparam)
{
	token = tokenparam;
	IdHTTPConnect->Request->CustomHeaders->Values["Authorization"]=token;
}

/*
	Проверка соединения с сайтом Kadnet
		выполняется подключение без передачи данных
		если удалось подключиться к серверу выдается приветствие
		и время сервера
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
	Авторизация на сайте Kadnet
		передается логин, пароль и версия ПО
		результатом передается JSON
			Result: true;
			Data: [Token];
			Date: [Время сервера]
	ОСТАЛЬНЫЕ ФУНКЦИИ ДОСТУПНЫ ТОЛЬКО ПОСЛЕ ПОЛУЧЕНИЯ TOKEN
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
	Получить данные о типах запросов
	Тут можно получить информацию о запросах, которые можно сделать: Запрос сведений из ЕГРП, Запрос сведений о кад. стоимости и т.п.
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
	Получить данные о типах объектов
	Тут информация об объектах, на которые мы запрашиваем информацию: квартира, помещение, здание, учестов и т.п.
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
	Получить данные о тарифах
	У каждого запроса должен быть тариф, по нему определяется, сколько средств будет списано у пользователя, как будет сделан запрос
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
	Получить данные о регионах
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
	Получить результаты запроса
	результатом придет файл с сервера
*/
//TMemoryStream KadnetApiClient::GetRequestContent(UnicodeString reqId) так должно быть
void  KadnetApiClient::GetRequestContent(UnicodeString reqId, UnicodeString format) //так для тестирования
{
	try{
	// надо делать так
	TMemoryStream* ms = new TMemoryStream;
	IdHTTPConnect->Get("https://api.kadnet.ru/v1/Requests/GetContent/"+reqId+"/"+format,ms);
	ms->Position=0;
	//так можно сохранить данные в файл
	//return ms;
	//пока чтобы протестить делаем так
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
	myjson->AddPair("kadNumber",kadNumber);
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

ApiResponse KadnetApiClient::SaveSign(UnicodeString requestId, UnicodeString signContent, UnicodeString certContent, UnicodeString cpVersion)
{
    try{
	TMemoryStream *result = new TMemoryStream();
	TJSONObject *myjson = new TJSONObject();
	myjson->AddPair("requestId",requestId);
	myjson->AddPair("signContent",signContent);
	myjson->AddPair("certContent",certContent);
	myjson->AddPair("cpVersion",cpVersion);
	TStringStream *params = new TStringStream(myjson->ToString());
	IdHTTPConnect->Post("https://api.kadnet.ru/v1/Requests/SaveSign",params,result);
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


/*	Получить token сохраненный в клиенте*/
UnicodeString KadnetApiClient::GetToken() { return token; }

int Tools::Test()
{
	return 1;
}

UnicodeString Tools::PrintJSON(UnicodeString json)
{
	UnicodeString result;
	TJSONArray* JSON = (TJSONArray*)TJSONObject::ParseJSONValue(json); //преобразуем строку в JSON объект
	int count = JSON->Size();
	result = "JSONCount = " + count;                                          //Смотрим сколько объектов в json-е
	for (int i=0; i < count; i++) {                                    //будем переберать каждый объект
		TJSONValue* oneEntry = JSON->Get(i);                           //выбираем один объект
		TJSONArray*  objProperties =  (TJSONArray*)oneEntry;                 //находим все его своства
	   //	int len = objProperties->Count;                                      //Сейчас будем перебирать все свойства
	   //	for (int k=0; k < len; k++) {
	   //		TJSONValue *oneProperty = objProperties->Get(k);                //получить одно свойство
	   //		result = oneProperty->Value();                             //получить его значение
	   //	}
	}
	return "count="+UnicodeString(count)+"\t"+result;
/*	try{
		TJSONObject *JSON = (TJSONObject*)TJSONObject::ParseJSONValue(json); //преобразуем строку в JSON объект
		int size = JSON->Size(); //получаем количество объектов в JSON
	}
	catch (Exception *ex)
	{}
	return "OK";*/
}
