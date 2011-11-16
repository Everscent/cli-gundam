#include "StdAfx.h"
#include "TcpEventArgs.h"

using namespace Anaheim;
using namespace Anaheim::TcpSocket;

/**
 * TCPƒCƒxƒ“ƒgArgs
 */
TcpEventArgs::TcpEventArgs(System::Net::IPEndPoint ^remoteEndPoint, System::Net::IPEndPoint ^localEndPoint, System::String ^message)
{
	this->remoteEndPoint = remoteEndPoint;
	this->localEndPoint = localEndPoint;
	this->message = message;
}
// ----------------------------------------------------------------------------------------------------
