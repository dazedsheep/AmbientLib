/*
 * HTTPResponse.cpp
 *****************************************************************************
 * Copyright (C) 2011 - 2013 Alpen-Adria-Universität Klagenfurt
 *
 * Created on: April 9, 2011
 * Authors: Benjamin Rainer <benjamin.rainer@itec.aau.at>
 *
 * This file is part of ambientLib.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include "StdAfx.h"
#include <iostream>
#include <vector>
#include <WinSock.h>
#include "ptr.h"
#include "HTTPResponse.h"
#include "HTTPConnector.h"


using namespace AmbientLib::HTTP;

using namespace std;

HTTPResponse::HTTPResponse(void)
{

}

HTTPResponse::HTTPResponse(std::string response)
{


	
	// parse the response, for instance check the first line ...
	// seperate the data from the header, if there is data
	

	std::string status = response.substr(strlen(HTTP_VERSION)+1,3);

	statusCode = atoi(status.c_str());

	// check if the request was valid
	if(statusCode == HTTP_OK){

		// extract the data
		unsigned int dataLength = atoi(getFieldValue(HTTP_CONTENT_LENGTH, response).c_str());

		header = response.substr(0,response.length() - dataLength);
		payload = response.substr(response.length() - dataLength,response.length());

	}


	// TODO... EXTEND
	

}

HTTPResponse::~HTTPResponse(void)
{

}

std::string HTTPResponse::getHeader(){

	return header;
}

std::string HTTPResponse::getPayload(){

	return payload;
}

unsigned int  HTTPResponse::getStatusCode(){

	return statusCode;
}

std::string HTTPResponse::getFieldValue(const char* HTTPFIELD, std::string str){
	size_t pos = str.find(HTTPFIELD);
	std::string n = str.substr(pos+strlen(HTTPFIELD),str.length());
	pos = n.find(HTTP_CRLF);
	std::string field = n.substr(0,pos);
	return field;
}