/*
 *
 * TODO: other HTTP methods like OPTIONS, POST, ...
 *
 */


#include "StdAfx.h"
#include <iostream>
/*
 * HTTPRequester.cpp
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

#include <vector>
#include <WinSock.h>
#include "ptr.h"
#include "HTTPRequest.h"
#include "HTTPConnector.h"

using namespace AmbientLib::HTTP;

HTTPRequest::HTTPRequest(std::string method, std::string url, std::string host)
{
	request = "";
	// create the http request according to the specified method

	if(method.compare("GET")==0){

		// create the GET request
		
		request.append(method);
		request.append(" ");
		request.append(url);
		request.append(" ");
		request.append(HTTP_VERSION);
		request.append(HTTP_CRLF);
		request.append(HTTP_HOST);
		request.append(" ");
		request.append(host);
		request.append(HTTP_CRLF);
		// now the connection state and which types we accept + user agent
		request.append(HTTP_USER_AGENT);
		request.append(HTTP_CRLF);
		request.append(HTTP_ACCEPT);
		request.append(HTTP_CRLF);
		request.append(HTTP_KEEP_ALIVE);
		request.append(HTTP_CRLF);
		request.append(HTTP_CONNECTION_STATE);
		request.append(HTTP_CRLF);
		request.append(HTTP_CRLF);
	}

}


HTTPRequest::~HTTPRequest(void)
{
	
}

std::string HTTPRequest::getRequest()
{
	return request;
}
