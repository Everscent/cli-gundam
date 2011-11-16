#include "StdAfx.h"
#include "UdpEventArgs.h"

using namespace Anaheim;
using namespace Anaheim::UdpSocket;

/**
 * UDP�C�x���gArgs
 */
UdpEventArgs::UdpEventArgs(System::Net::IPEndPoint ^remoteEndPoint, cli::array<unsigned char,1> ^bytes)
{
	this->remoteEndPoint = remoteEndPoint;
	this->bytes = bytes;
}
// ----------------------------------------------------------------------------------------------------
