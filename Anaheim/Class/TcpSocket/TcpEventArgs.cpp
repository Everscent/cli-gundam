#include "StdAfx.h"
#include "TcpEventArgs.h"

using namespace Anaheim;
using namespace Anaheim::TcpSocket;

/**
 * TCPƒCƒxƒ“ƒgArgs
 */
TcpEventArgs::TcpEventArgs(System::Net::IPEndPoint ^remoteEndPoint, System::Net::IPEndPoint ^localEndPoint, cli::array<unsigned char,1> ^bytes, Encoding ^encoding)
{
	this->remoteEndPoint = remoteEndPoint;
	this->localEndPoint = localEndPoint;
	this->bytes = bytes;
	this->message = (this->bytes == nullptr || encoding == nullptr) ? String::Empty : encoding->GetString(bytes);
}
// ----------------------------------------------------------------------------------------------------
