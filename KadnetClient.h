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
#include <IdURI.hpp>
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
	  ApiResponse GetObjectsTypesGkn();
	  ApiResponse GetObjectsTypesEgrp();
	  ApiResponse GetRequestsTariffs(UnicodeString tariffId);
	  ApiResponse GetRegions();

	  //Получение результата
	  TMemoryStream* GetRequestContent(UnicodeString reqId,UnicodeString format);

	  //Получить Xml-запроса на подпись
	  AnsiString GetRequestBody(UnicodeString reqId); //Получение xml запроса
	  ApiResponse GetRequestBodyBase64(UnicodeString reqId); //Получение xml запроса

	  //Проверка и создание запроса
	  ApiResponse CheckRequests(UnicodeString kadNumbers, UnicodeString comment, UnicodeString requestTypeId, UnicodeString objectTypeId);
	  ApiResponse CreateRequest(bool selfSigned,UnicodeString tariffCode, UnicodeString kadNumber, UnicodeString comment, UnicodeString requestTypeId, UnicodeString objectTypeId);

	  ApiResponse GetRequests(UnicodeString limitRequests, UnicodeString skipRequests);
	  ApiResponse GetRequestsByType(UnicodeString requestType, UnicodeString limitRequests, UnicodeString skipRequests);
	  ApiResponse GetRequest(UnicodeString requestId);
	  ApiResponse GetRequestHistory(UnicodeString requestId);
	  ApiResponse DeleteRequest(UnicodeString requestId);

	  //Работа с подписью
	  ApiResponse GetRequestsToSign();
	  ApiResponse SaveSign(UnicodeString requestId, UnicodeString signContent, UnicodeString certContent, UnicodeString cpVersion);
	  ApiResponse SaveSign(UnicodeString requestId, AnsiString signContent, AnsiString certContent, UnicodeString cpVersion);
	  ApiResponse SaveSign(UnicodeString requestId, unsigned char signContent, int signContentLenght, unsigned char certContent, int certContentLenght, UnicodeString cpVersion);

	  UnicodeString GetToken();
   private:
	  TIdHTTP* IdHTTPConnect;
	  UnicodeString url;
	  UnicodeString token;
	  void SetConnectionSettings();
};

class Tools
{
	public:
		static int Test();
		static UnicodeString PrintJSON(UnicodeString json);
};

#endif

