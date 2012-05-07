/*
 * httpConnector.h
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


#ifndef HTTP_CONNECTOR_H_
#define HTTP_CONNECTOR_H_

namespace AmbientLib{
	namespace HTTP{

#define HTTP_CRLF				"\r\n"
#define HTTP_VERSION			"HTTP/1.1"
#define HTTP_HOST				"Host:"
#define HTTP_USER_AGENT			"User-Agent: Ambient Lib - AAU"
#define HTTP_ACCEPT				"Accept: text/plain"
#define HTTP_KEEP_ALIVE			"Keep-Alive: 115"
#define HTTP_CONNECTION_STATE	"Connection: keep-alive"
#define HTTP_CONTENT_LENGTH		"Content-Length: "




#define MAX_HTTP_PACKET_SIZE	65000

class HTTPConnector
{

private:

	std::string _host,_url;
	unsigned short _port; 
	SOCKET mySocket;
	std::string errorMessage;
	std::string debugMessage;
	bool connected;

public:
	
	HTTPConnector();
	HTTPConnector(std::string url);
	HTTPConnector(std::string host,std::string url,unsigned short port);
	std::string HTTPGet(std::string file);
	bool HTTPConnect();
	int HTTPSend(std::string request);
	std::string HTTPRecv(int len);

	std::string HTTPReceiveResponse();
	bool HTTPDisconnect();
	~HTTPConnector(void);
	std::string getLastErrorMessage();
	std::string getLastDebugMessage();
	
};
	}
}
#endif