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

typedef struct
{
	int socket;
	int state;
	int streamID;
	int arglen;
	int argc;
	uint32_t filetime;	/* time of last download we started */
	struct AVal filename;	/* name of last download */
	char *connect;

} STREAMING_SERVER;

STREAMING_SERVER *rtmpServer = 0;	// server structure pointer

typedef struct
{
	char *hostname;
	int rtmpport;
	int protocol;
	int bLiveStream;		// is it a live stream? then we can't seek/resume

	long int timeout;		// timeout connection afte 300 seconds
	uint32_t bufferTime;

	char *rtmpurl;
	AVal playpath;
	AVal swfUrl;
	AVal tcUrl;
	AVal pageUrl;
	AVal app;
	AVal auth;
	AVal swfHash;
	AVal flashVer;
	AVal subscribepath;
	uint32_t swfSize;

	uint32_t dStartOffset;
	uint32_t dStopOffset;
	uint32_t nTimeStamp;
} RTMP_REQUEST;

#define STR2AVAL(av,str)	av.av_val = str; av.av_len = strlen(av.av_val)

/* this request is formed from the parameters and used to initialize a new request,
* thus it is a default settings list. All settings can be overriden by specifying the
* parameters in the GET request. */
RTMP_REQUEST defaultRTMPRequest;

#ifdef _DEBUG
uint32_t debugTS = 0;

int pnum = 0;

FILE *netstackdump = NULL;
FILE *netstackdump_read = NULL;
#endif

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
