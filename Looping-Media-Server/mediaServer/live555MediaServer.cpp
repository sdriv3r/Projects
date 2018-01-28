/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// Copyright (c) 1996-2015, Live Networks, Inc.  All rights reserved
// LIVE555 Media Server
// main program

#include <BasicUsageEnvironment.hh>
#include "DynamicRTSPServer.hh"
#include "version.hh"

int main(int argc, char** argv) 
{
	// Begin by setting up our usage environment:
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);

	UserAuthenticationDatabase* authDB = NULL;

	// Create the RTSP server.  Try first with the default port number (554),
	// and then with the alternative port number (8554):
	RTSPServer* rtspServer;
	portNumBits rtspServerPortNum = 554;
	rtspServer = DynamicRTSPServer::createNew(*env, rtspServerPortNum, authDB);
	if (rtspServer == NULL) {
		rtspServerPortNum = 8554;
		rtspServer = DynamicRTSPServer::createNew(*env, rtspServerPortNum, authDB);
	}
	if (rtspServer == NULL) {
		*env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
		exit(1);
	}

	*env << "    __          __                   _                               \n";
	*env << "   / /   __  __/ /______ __________ ( )_____                         \n";
	*env << "  / /   / / / / //_/ __ `/ ___/_  / |// ___/                         \n";
	*env << " / /___/ /_/ / ,< / /_/ (__  ) / /_  (__  )                          \n";
	*env << "/_____/\\__,_/_/|_|\\__,_/____/ /___/ /____/                         \n";
	*env << "    __  ___         ___          _____                               \n";
	*env << "   /  |/  /__  ____/ (_)___ _   / ___/___  ______   _____  _____     \n";
	*env << "  / /|_/ / _ \\/ __  / / __ `/   \\__ \\/ _ \\/ ___/ | / / _ \\/ ___/\n";
	*env << " / /  / /  __/ /_/ / / /_/ /   ___/ /  __/ /   | |/ /  __/ /         \n";
	*env << "/_/  /_/\\___/\\__,_/_/\\__,_/   /____/\\___/_/    |___/\\___/_/     \n";
	*env << "                                                                     \n";

	*env << "\tversion " << MEDIA_SERVER_VERSION_STRING
		<< " (LIVE555 Streaming Media library version "
		<< LIVEMEDIA_LIBRARY_VERSION_STRING << ").\n\n";

	char* urlPrefix = rtspServer->rtspURLPrefix();
	*env << "Play streams from this server using the URL\n\t"
		<< urlPrefix << "<filename>\nwhere <filename> is a MKV file present in the current directory.\n\n";

	env->taskScheduler().doEventLoop(); // does not return

	return 0; // only to prevent compiler warning
}
