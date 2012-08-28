#include "StdAfx.h"
#include "TcpClientSocket.h"

using namespace Anaheim;
using namespace Anaheim::TcpSocket;

/**
 * TCPクライアント
 */
TcpClientSocket::TcpClientSocket()
{
	this->client = gcnew TcpClient();
	this->receiveWorker = gcnew BackgroundWorker();
	this->receiveWorker->WorkerReportsProgress = true;
	this->receiveWorker->DoWork += gcnew DoWorkEventHandler(this, &TcpClientSocket::ReceiveWorkerDoWork);
	this->receiveWorker->ProgressChanged += gcnew ProgressChangedEventHandler(this, &TcpClientSocket::ReceiveWorkerProgressChanged);
	this->encoding = System::Text::Encoding::Default;
}
// ----------------------------------------------------------------------------------------------------

TcpClientSocket::TcpClientSocket(System::Net::Sockets::TcpClient ^client)
{
	this->client = client;
	this->receiveWorker = gcnew BackgroundWorker();
	this->receiveWorker->WorkerReportsProgress = true;
	this->receiveWorker->DoWork += gcnew DoWorkEventHandler(this, &TcpClientSocket::ReceiveWorkerDoWork);
	this->receiveWorker->ProgressChanged += gcnew ProgressChangedEventHandler(this, &TcpClientSocket::ReceiveWorkerProgressChanged);
	if (this->client->Connected)
	{
		this->receiveWorker->RunWorkerAsync();
	}
}
// ----------------------------------------------------------------------------------------------------

void TcpClientSocket::ReceiveWorkerDoWork(System::Object ^sender, System::ComponentModel::DoWorkEventArgs ^e)
{
	try
	{
		array<Byte>^ buffer = gcnew array<Byte>(1024);
		NetworkStream^ stream = this->client->GetStream();
		while (true)
		{
			int size = stream->Read(buffer, 0, buffer->Length);
			if (size == 0)	// 切断
			{
				TcpEventArgs^ args = gcnew TcpEventArgs(dynamic_cast<IPEndPoint^>(client->Client->RemoteEndPoint), dynamic_cast<IPEndPoint^>(client->Client->LocalEndPoint), nullptr, this->encoding);
				this->receiveWorker->ReportProgress(0, args);
				stream->Close();
				this->client->Close();
				break;
			}
			else
			{
				array<Byte>^ bytes = gcnew array<Byte>(size);
				Array::Copy(buffer, bytes, bytes->Length);
				TcpEventArgs^ args = gcnew TcpEventArgs(dynamic_cast<IPEndPoint^>(client->Client->RemoteEndPoint), dynamic_cast<IPEndPoint^>(client->Client->LocalEndPoint), bytes, this->encoding);
				this->receiveWorker->ReportProgress(0, args);
			}
		}
	}
	catch (Exception^)
	{
		return;
	}
}
// ----------------------------------------------------------------------------------------------------

void TcpClientSocket::ReceiveWorkerProgressChanged(System::Object ^sender, System::ComponentModel::ProgressChangedEventArgs ^e)
{
	TcpEventArgs^ args = dynamic_cast<TcpEventArgs^>(e->UserState);
	if (args->Message->Equals(String::Empty))
	{
		this->OnDisConnected(args);
	}
	else
	{
		this->OnReceived(args);
	}
}
// ----------------------------------------------------------------------------------------------------

bool TcpClientSocket::Connect(System::Net::IPEndPoint ^endPoint)
{
	this->client = gcnew TcpClient();
	
	try
	{
		this->client->Connect(endPoint);
		this->receiveWorker->RunWorkerAsync();
	}
	catch (Exception^)
	{
		return false;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TcpClientSocket::DisConnect()
{
	if (!this->client->Connected) return false;

	this->client->GetStream()->Close();
	this->client->Close();

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TcpClientSocket::SendData(cli::array<unsigned char,1> ^bytes)
{
	try
	{
		NetworkStream^ stream = this->client->GetStream();
		stream->Write(bytes, 0, bytes->Length);
	}
	catch (Exception^)
	{
		return false;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TcpClientSocket::SendMessage(System::String ^message)
{
	array<Byte>^ buffer = this->encoding->GetBytes(message);
	return this->SendData(buffer);
}
// ----------------------------------------------------------------------------------------------------

void TcpClientSocket::OnReceived(Anaheim::TcpSocket::TcpEventArgs ^e)
{
	this->Received(this, e);
}
// ----------------------------------------------------------------------------------------------------

void TcpClientSocket::OnDisConnected(Anaheim::TcpSocket::TcpEventArgs ^e)
{
	this->DisConnected(this, e);
}
// ----------------------------------------------------------------------------------------------------
