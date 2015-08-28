
#include "C4NetIO.h"

#include <stdio.h>

const uint16_t C4PuncherPort = 11115;

class C4PuncherServer : public C4NetIOUDP, private C4NetIO::CBClass
{
public:
	C4PuncherServer() { C4NetIOUDP::SetCallback(this); }
private:
	// Event handlers
	virtual bool OnConn(const addr_t &AddrPeer, const addr_t &AddrConnect, const addr_t *OwnAddr, C4NetIO *pNetIO)
	{ 
		printf("Punched back at %s:%d...\n", inet_ntoa(AddrPeer.sin_addr), htons(AddrPeer.sin_port));
		return false;
	}
	virtual void OnPacket(const class C4NetIOPacket &rPacket, C4NetIO *pNetIO)
	{
		// Unused
	}
} Puncher;

int main(int argc, char * argv[])
{
	// Log
	printf("Starting puncher...\n");

	// Get port
	uint16_t iPort = C4PuncherPort;
	if(argc)
	{
		iPort = atoi(*argv);
		if(!iPort) iPort = C4PuncherPort;
	}
	
	// Initialize
	if(!Puncher.Init(iPort))
	{
		fprintf(stderr, "Could not initialize puncher: %s", Puncher.GetError());
		return 1;
	}

	// Log
	printf("Listening on port %d...\n", iPort);

	// Execute forever
	Puncher.ExecuteUntil(-1);

	return 0;
}
