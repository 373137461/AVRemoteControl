#pragma once
extern "C"
{
#include "librtmp/rtmp_sys.h"
#include "librtmp/amf.h"
#include "librtmp/log.h"
}

#ifdef linux
#include <linux/netfilter_ipv4.h>
#endif

#ifndef WIN32
#include <sys/types.h>
#include <sys/wait.h>
#endif

#define RD_SUCCESS		0
#define RD_FAILED		1
#define RD_INCOMPLETE		2

#define PACKET_SIZE 1024*1024

#ifdef WIN32
#define InitSockets()	{\
	WORD version;			\
	WSADATA wsaData;		\
					\
	version = MAKEWORD(1,1);	\
	WSAStartup(version, &wsaData);	}

#define	CleanupSockets()	WSACleanup()
#else
#define InitSockets()
#define	CleanupSockets()
#endif

#define DUPTIME	5000	/* interval we disallow duplicate requests, in msec */

enum
{
	STREAMING_ACCEPTING,
	STREAMING_IN_PROGRESS,
	STREAMING_STOPPING,
	STREAMING_STOPPED
};
struct STREAMING_SERVER;
struct RTMP_REQUEST;

#define SAVC(x) const AVal av_##x = AVC(#x)

SAVC(app);
SAVC(connect);
SAVC(flashVer);
SAVC(swfUrl);
SAVC(pageUrl);
SAVC(tcUrl);
SAVC(fpad);
SAVC(capabilities);
SAVC(audioCodecs);
SAVC(videoCodecs);
SAVC(videoFunction);
SAVC(objectEncoding);
SAVC(_result);
SAVC(createStream);
SAVC(getStreamLength);
SAVC(play);
SAVC(fmsVer);
SAVC(mode);
SAVC(level);
SAVC(code);
SAVC(description);
SAVC(secureToken);


int SendConnectResult(RTMP* r, double txn);
int SendResultNumber(RTMP* r, double txn, double ID);
int SendPlayStart(RTMP* r);
int SendPlayStop(RTMP* r);
void spawn_dumper(int argc, AVal* av, char* cmd);
int countAMF(AMFObject* obj, int* argc);
char* dumpAMF(AMFObject* obj, char* ptr, AVal* argv, int* argc);
int ServeInvoke(STREAMING_SERVER* server, RTMP* r, RTMPPacket* packet, unsigned int offset);
int ServePacket(STREAMING_SERVER* server, RTMP* r, RTMPPacket* packet);
void controlServerThread();
void doServe(STREAMING_SERVER* server, int sockfd);
void serverThread(void* arg);
STREAMING_SERVER* startStreaming(const char* address, int port);
void stopStreaming(STREAMING_SERVER* server);
void sigIntHandler(int sig);
int start_sample_rtmp_server(int argc, char** argv);
