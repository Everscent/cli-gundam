#include "StdAfx.h"
#include "TetrisRemoting.h"
#include "TetrisField.h"
#include "TetrisMino.h"
#include "UdpClientSocket.h"

using namespace Anaheim;
using namespace Anaheim::Tetris::Model;
using namespace Anaheim::UdpSocket;

/**
 * テトリスリモート操作
 */
TetrisRemoting::TetrisRemoting()
{
	this->udpSocket = gcnew UdpClientSocket();
	this->udpSocket->Received += gcnew UdpEventHandler(this, &TetrisRemoting::UdpClientSocketReceived);
	this->isRunning = false;
}
// ----------------------------------------------------------------------------------------------------

TetrisMino^ TetrisRemoting::CreateMino(cli::array<unsigned char,1> ^bytes, Anaheim::Tetris::Model::TetrisField ^field)
{
	Color color = Color::FromArgb(bytes[0], bytes[1], bytes[2]);
	Color icolor = ITetrisMino::COLOR;
	Color jcolor = JTetrisMino::COLOR;
	Color lcolor = LTetrisMino::COLOR;
	Color scolor = STetrisMino::COLOR;
	Color zcolor = ZTetrisMino::COLOR;
	Color tcolor = TTetrisMino::COLOR;
	Color ocolor = OTetrisMino::COLOR;

	if (color.ToArgb() == icolor.ToArgb())
	{
		return gcnew ITetrisMino(Point(), field);
	}
	else if (color.ToArgb() == jcolor.ToArgb())
	{
		return gcnew JTetrisMino(Point(), field);
	}
	else if (color.ToArgb()== lcolor.ToArgb())
	{
		return gcnew LTetrisMino(Point(), field);
	}
	else if (color.ToArgb() == scolor.ToArgb())
	{
		return gcnew STetrisMino(Point(), field);
	}
	else if (color.ToArgb() == zcolor.ToArgb())
	{
		return gcnew ZTetrisMino(Point(), field);
	}
	else if (color.ToArgb() == tcolor.ToArgb())
	{
		return gcnew TTetrisMino(Point(), field);
	}
	else if (color.ToArgb() == ocolor.ToArgb())
	{
		return gcnew OTetrisMino(Point(), field);
	}

	return nullptr;
}
// ----------------------------------------------------------------------------------------------------

void TetrisRemoting::UdpClientSocketReceived(System::Object ^sender, Anaheim::UdpSocket::UdpEventArgs ^e)
{
	TetrisField^ field = gcnew TetrisField();
	array<Byte>^ fieldBytes = gcnew array<Byte>(TetrisField::BYTE_SIZE);
	Array::Copy(e->Bytes, 0, fieldBytes, 0, fieldBytes->Length);
	field->Deserialize(fieldBytes);

	array<Byte>^ minoBytes = gcnew array<Byte>(TetrisMino::BYTE_SIZE);
	Array::Copy(e->Bytes, fieldBytes->Length, minoBytes, 0, minoBytes->Length);
	TetrisMino^ mino = this->CreateMino(minoBytes, field);
	mino->Deserialize(minoBytes);

	this->OnReceived(gcnew TetrisRemoteEventArgs(field, mino));
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemoting::Start(IPEndPoint ^endPoint)
{
	if (this->isRunning) return false;
	this->isRunning = true;
	return this->udpSocket->Start(endPoint);
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemoting::Stop()
{
	if (!this->isRunning) return false;
	this->isRunning = false;
	return this->udpSocket->Stop();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemoting::Send(Anaheim::Tetris::Model::TetrisField ^field, Anaheim::Tetris::TetrisMino ^mino, IPEndPoint ^endPoint)
{
	if (!this->isRunning) return false;

	array<Byte>^ fieldBytes = field->Serialize();
	array<Byte>^ minoBytes = mino->Serialize();
	array<Byte>^ bytes = gcnew array<Byte>(fieldBytes->Length + minoBytes->Length);
	fieldBytes->CopyTo(bytes, 0);
	minoBytes->CopyTo(bytes, fieldBytes->Length);

	return this->udpSocket->SendData(bytes, endPoint);
}
// ----------------------------------------------------------------------------------------------------

void TetrisRemoting::OnReceived(Anaheim::Tetris::TetrisRemoteEventArgs ^e)
{
	this->Received(this, e);
}
// ----------------------------------------------------------------------------------------------------
