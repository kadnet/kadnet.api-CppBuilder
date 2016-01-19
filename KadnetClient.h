#ifndef mylib_h
#define mylib_h

#include <vcl.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#pragma hdrstop
#pragma argsused

#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdSSLOpenSSL.hpp>          ////Add by Kadnet
#include <DBXJSON.hpp>
class ApiResponse
{
	public:
		ApiResponse();
		ApiResponse(UnicodeString json);

		bool Result();
		UnicodeString Data();
		UnicodeString Date();

		void SetResult(UnicodeString str);
		void SetData(UnicodeString str);
		void SetDate(UnicodeString str);
	private:
		bool __result;
		UnicodeString __data;
		UnicodeString __date;
};

enum ExportFormat {
	Raw,
	Dxf,
	MidMif,
	OmsPoints,
	Pdf
};

class KadnetApiClient
{
   public:
	  KadnetApiClient();
	  KadnetApiClient(TIdHTTP* IdHTTPConnect);
	  KadnetApiClient(UnicodeString url);
	  KadnetApiClient(TIdHTTP* IdHTTPConnect, UnicodeString tokenparam);

	  //установка токена
	  void SetToken (UnicodeString tokenparam);

	  ApiResponse TestConnection();
	  ApiResponse Auth(UnicodeString Login, UnicodeString Password, UnicodeString Software);
	  ApiResponse GetRequestsTypes();
	  ApiResponse GetObjectsTypes();
	  ApiResponse GetRequestsTariffs();

	  //Скачивание файла
	  //TMemoryStream GetRequestContent(UnicodeString reqId); //так должно быть
	  void GetRequestContent(UnicodeString reqId,UnicodeString format); //так чтобы протестить

	  ApiResponse CheckRequests(UnicodeString kadNumbers, UnicodeString comment, UnicodeString requestTypeId, UnicodeString objectTypeId);
	  ApiResponse CreateRequest(bool selfSigned,UnicodeString tariffId, UnicodeString kadNumber, UnicodeString comment, UnicodeString requestTypeId, UnicodeString objectTypeId);

	  ApiResponse GetRequests(UnicodeString limitRequests, UnicodeString skipRequests);
	  ApiResponse GetRequests(UnicodeString requestTypeId, UnicodeString limitRequests, UnicodeString skipRequests);
	  ApiResponse GetRequest(UnicodeString requestId);
	  UnicodeString GetToken();
   private:
	  TIdHTTP* IdHTTPConnect;
	  UnicodeString url;
	  UnicodeString token;
	  void SetConnectionSettings();
};


#endif

