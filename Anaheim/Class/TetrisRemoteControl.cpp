#include "StdAfx.h"
#include "TetrisRemoteControl.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * テトリスリモート操作
 */
TetrisRemoteControl::TetrisRemoteControl()
{
	this->udpSocket = gcnew UdpClientSocket();
	this->udpSocket->Received += gcnew UdpEventHandler(this, &TetrisRemoteControl::UdpClientSocketReceived);
	this->isBusy = false;
}
// ----------------------------------------------------------------------------------------------------

TetrisMino^ TetrisRemoteControl::CreateMino(cli::array<unsigned char,1> ^bytes, Anaheim::Tetris::TetrisField ^field)
{
	Color color = Color::FromArgb(bytes[0], bytes[1], bytes[2]);

	if (color.ToArgb() == ITetrisMino::COLOR.ToArgb())
	{
		return gcnew ITetrisMino(Point(), field);
	}
	else if (color.ToArgb() == JTetrisMino::COLOR.ToArgb())
	{
		return gcnew JTetrisMino(Point(), field);
	}
	else if (color.ToArgb()== LTetrisMino::COLOR.ToArgb())
	{
		return gcnew LTetrisMino(Point(), field);
	}
	else if (color.ToArgb() == STetrisMino::COLOR.ToArgb())
	{
		return gcnew STetrisMino(Point(), field);
	}
	else if (color.ToArgb() == ZTetrisMino::COLOR.ToArgb())
	{
		return gcnew ZTetrisMino(Point(), field);
	}
	else if (color.ToArgb() == TTetrisMino::COLOR.ToArgb())
	{
		return gcnew TTetrisMino(Point(), field);
	}
	else if (color.ToArgb() == OTetrisMino::COLOR.ToArgb())
	{
		return gcnew OTetrisMino(Point(), field);
	}

	return nullptr;
}
// ----------------------------------------------------------------------------------------------------

void TetrisRemoteControl::UdpClientSocketReceived(System::Object ^sender, Anaheim::UdpSocket::UdpEventArgs ^e)
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

bool TetrisRemoteControl::Start(IPEndPoint ^endPoint)
{
	if (this->isBusy) return false;
	return this->udpSocket->Start(endPoint);
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemoteControl::Stop()
{
	if (!this->isBusy) return false;
	return this->udpSocket->Stop();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemoteControl::Send(Anaheim::Tetris::TetrisField ^field, Anaheim::Tetris::TetrisMino ^mino, IPEndPoint ^endPoint)
{
	if (this->isBusy) return false;

	array<Byte>^ fieldBytes = field->Serialize();
	array<Byte>^ minoBytes = mino->Serialize();
	array<Byte>^ bytes = gcnew array<Byte>(fieldBytes->Length + minoBytes->Length);
	fieldBytes->CopyTo(bytes, 0);
	minoBytes->CopyTo(bytes, fieldBytes->Length);

	return this->udpSocket->SendData(bytes, endPoint);
}
// ----------------------------------------------------------------------------------------------------

void TetrisRemoteControl::OnReceived(Anaheim::Tetris::TetrisRemoteEventArgs ^e)
{
	this->Received(this, e);
}
// ----------------------------------------------------------------------------------------------------
