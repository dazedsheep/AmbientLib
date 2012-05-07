/*
 * httpConnector.cpp
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

#include "ptr.h"	// smart pointer

#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "httpConnector.h"

using namespace AmbientLib::HTTP;
using namespace std;

HTTPConnector::HTTPConnector(){

	connected = false;
}

/*
 * This constructor takes a full url incluse http://host/...
 */
HTTPConnector::HTTPConnector(string url)
{
	
	// parse the url to identify host and port
	// if "http" is at the beginning delete it :)
	// split up the url into resource, for instance "pub/test"
	// and host for instance "www.foo.org"

	
	size_t found;

	found = url.find("http://");		// this should be at the beginning of the url

	if (found != string::npos){
		// delete the http://
		url = url.substr(strlen("http://"),url.length());
	}else{

		// check for https
		found = url.find("https://");
		if (found != string::npos)
		{
			url = url.substr(strlen("https://"),url.length());
		}else{
			// uhm ERROR ?!
			throw;
		}

	}

	// find the first occurence of /, and extract the host

	found = url.find("/");	// the first occoruence, right after the host

	std::string f_url;
	f_url = url.substr(found);
	std::string host;
	host = url.substr(0,found); // only the host

	// the host part may include a port, check if it is there
	found = host.find(":");

	if(found!=string::npos){

		// we have found ":", so we may say there is a port specified, extract it
		
		string port;
		port = host.substr(found+1, host.length());
		// delte :PORT from the host string
		host = host.substr(0,found);
		cout << port.c_str()<<endl;
		_port = atoi(port.c_str());

	}else{
		// we use the standard port 80
		
		_port = 80;

	}
	_host = host;
	_url = f_url;
	// now we should have all things we need
	errorMessage = "NO ERROR";
	debugMessage = "host: ";
	debugMessage.append(_host);
	debugMessage.append(" url: ");
	debugMessage.append(_url);
	connected = false;

}

HTTPConnector::HTTPConnector(std::string host, std::string url, unsigned short port){

	_host = host;
	_url = url;
	_port = port;
	errorMessage = "NO ERROR";
	connected = false;
}


HTTPConnector::~HTTPConnector(void)
{
	if(connected){
		closesocket(mySocket);
		WSACleanup();
	}
	
}

std::string HTTPConnector::getLastErrorMessage()
{
	return errorMessage;
}

std::string HTTPConnector::getLastDebugMessage()
{
	return debugMessage;
}

bool HTTPConnector::HTTPConnect(){

	// initialize our socket

	SOCKADDR_IN addr;
	HOSTENT *hent;
	int rc;
	WSADATA myWSADATA;

	rc = WSAStartup(MAKEWORD(2,2),&myWSADATA);

	if(rc != 0){
		errorMessage = "Error at initializing Winsock 2.0!";
		return false;

	}

	mySocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
/*	BOOL optval = FALSE;
	int optLen = sizeof(BOOL);
	// set the socket option, disable nagle's algorithm
	setsockopt(mySocket,IPPROTO_TCP,TCP_NODELAY,(char *)&optval,optLen);
	*/

	
	if(mySocket == INVALID_SOCKET){

		errorMessage = "Couldn't create socket.";
		closesocket(mySocket);
		WSACleanup();
		return false;
	}

	hent = gethostbyname(_host.c_str());

	memset(&addr,0,sizeof(SOCKADDR_IN));
	memcpy(&addr.sin_addr, hent->h_addr_list[0],hent->h_length);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

	rc = connect(mySocket,(SOCKADDR *)&addr,sizeof(SOCKADDR));

	if(rc == SOCKET_ERROR){

		errorMessage = "Error at connecting to host: ";
		errorMessage.append(_host);
		closesocket(mySocket);
		WSACleanup();
		return false;
	}

	// set the socket non blocking so we can poll it
	unsigned int timeout=30;
	setsockopt(mySocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(unsigned int));
	debugMessage = "Connected to host: ";
	debugMessage.append(_host);
	connected = true;
	return true;

}

bool HTTPConnector::HTTPDisconnect()
{
	if(connected){
		closesocket(mySocket);
		WSACleanup();
		connected = false;
	}
	return true;

}

int HTTPConnector::HTTPSend(std::string request){
	
	// sending over sockets is a bit tricky, it may happen that not all bytes make their way down the network stack so just force them to go through ...


	int length = request.length();
	int total = 0;
	int bytesgot = 0;
	char *buffer = (char *) request.c_str();
	int left = length;
	while(total < length){

		bytesgot = send(mySocket, buffer+total, left, 0);
		if(bytesgot == SOCKET_ERROR){
		
			// okay okay ...
			errorMessage="Error at sending...";
			return 0;
		}else{

			total += bytesgot;
			left -= bytesgot;

		}


	};
	
	return total;

}


/*
 * TODO: partially parse the received HTTP message
 */
std::string HTTPConnector::HTTPRecv(int len){

	char *buffer = (char *)malloc(len+1);
	std::string response("");
	// okay that's going a bit tricky, because we don't know how big our data is, we will try to get data until we get an error, ...

	// len gives us the start length

	int got = 0;
	int left = len;
	int total = 0;
	

	while(true){
			
		got = recv(mySocket,buffer,left,0);
		if(got==0){
		
			debugMessage = "All data was read from socket.";
			break;
		}
		if (got == SOCKET_ERROR ){
		
			// oops, we got an error ?
			errorMessage = "Error at reading data from socket ... ";
			
			break;

		}else{

			buffer[got] = '\0';
			response.append(buffer);
			got = 0;
			left = len;
		}
	};

	
	free(buffer);
	return response;
}

std::string HTTPConnector::HTTPReceiveResponse(){
#ifdef TIMING_DEBUG
	unsigned int ams,ems;
#endif
	// get the response, parse the first few lines and check how many additional bytes we have to wait for

	// HTTPrecv will read until there is no data left, we get back the full response incl. header ...
#ifdef TIMING_DEBUG
	ams = timeGetTime();
#endif
	std::string resp = HTTPRecv(MAX_HTTP_PACKET_SIZE);
#ifdef TIMING_DEBUG
	ems = timeGetTime();
	std::cout << "receive time: " << ems-ams << std::endl;
#endif
	// parse the header and check if everything is ok
	scoped_ptr<HTTPResponse> response;
	response = new HTTPResponse(resp);		// this will give us all the things we need

	if(response->getStatusCode() != HTTP_OK){

		errorMessage = "ERROR: Server returned error.";
		
	}else{

		resp = response->getPayload();
	
	}
	
	return resp;
	
}

std::string HTTPConnector::HTTPGet(std::string file){

	// create a http request where we may retrieve the whole directory listing or a single file
	_url.append(file);
	scoped_ptr<HTTPRequest> request;
	request = new HTTPRequest("GET",_url,_host);
	debugMessage = request->getRequest();
	
	HTTPSend(request->getRequest());

	// now the request is on his way

	// get the response from the server :)
	

	return HTTPReceiveResponse();

}
