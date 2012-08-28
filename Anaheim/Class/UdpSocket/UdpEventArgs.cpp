#include "StdAfx.h"
#include "UdpEventArgs.h"

using namespace Anaheim;
using namespace Anaheim::UdpSocket;

/**
 * UDPƒCƒxƒ“ƒgArgs
 */
UdpEventArgs::UdpEventArgs(System::Net::IPEndPoint ^remoteEndPoint, cli::array<unsigned char,1> ^bytes, Encoding ^encoding)
{
	this->remoteEndPoint = remoteEndPoint;
	this->bytes = bytes;
	this->message = (this->bytes == nullptr || encoding == nullptr) ? String::Empty : encoding->GetString(bytes);
}
// ----------------------------------------------------------------------------------------------------
