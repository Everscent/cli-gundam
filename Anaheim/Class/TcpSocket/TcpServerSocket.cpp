#include "StdAfx.h"
#include "TcpServerSocket.h"
#include "TcpAcceptWorkerArgs.h"

using namespace Anaheim;
using namespace Anaheim::TcpSocket;

/**
 * TCPƒT[ƒo
 */
TcpServerSocket::TcpServerSocket()
{
	this->server = nullptr;
	this->clients = gcnew List<TcpClientSocket^>;
	this->started = false;
	this->acceptWorker = gcnew BackgroundWorker();
	this->acceptWorker->WorkerReportsProgress = true;
	this->acceptWorker->DoWork += gcnew DoWorkEventHandler(this, &TcpServerSocket::AcceptWorkerDoWork);
	this->acceptWorker->ProgressChanged += gcnew ProgressChangedEventHandler(this, &TcpServerSocket::AcceptWorkerProgressChanged);
	this->encoding = System::Text::Encoding::ASCII;
}
// ----------------------------------------------------------------------------------------------------

void TcpServerSocket::AcceptWorkerDoWork(System::Object ^sender, System::ComponentModel::DoWorkEventArgs ^e)
{
	try
	{
		while (true)
		{
			TcpClient^ client = this->server->AcceptTcpClient();
			TcpEventArgs^ args = gcnew TcpEventArgs(dynamic_cast<IPEndPoint^>(client->Client->RemoteEndPoint), dynamic_cast<IPEndPoint^>(client->Client->LocalEndPoint), nullptr, this->encoding);
			this->acceptWorker->ReportProgress(0, gcnew TcpAcceptWorkerArgs(args, client));
		}
	}
	catch (Exception^)
	{
		return;
	}
}
// ----------------------------------------------------------------------------------------------------

void TcpServerSocket::AcceptWorkerProgressChanged(System::Object ^sender, System::ComponentModel::ProgressChangedEventArgs ^e)
{
	TcpAcceptWorkerArgs^ args = dynamic_cast<TcpAcceptWorkerArgs^>(e->UserState);

	TcpClientSocket^ client = gcnew TcpClientSocket(args->Client);
	client->Encoding = this->encoding;
	client->Received += gcnew TcpEventHandler(this, &TcpServerSocket::ReceivedClient);
	client->DisConnected += gcnew TcpEventHandler(this, &TcpServerSocket::DisConnectedClient);
	this->clients->Add(client);

	this->OnConnected(args->TcpArgs);
}
// ----------------------------------------------------------------------------------------------------

void TcpServerSocket::ReceivedClient(System::Object ^sender, Anaheim::TcpSocket::TcpEventArgs ^e)
{
	this->OnReceived(e);
}
// ----------------------------------------------------------------------------------------------------

void TcpServerSocket::DisConnectedClient(System::Object ^sender, Anaheim::TcpSocket::TcpEventArgs ^e)
{
	for each (TcpClientSocket^ client in this->clients)
	{
		if (System::Object::ReferenceEquals(client, sender))
		{
			this->clients->Remove(client);
			break;
		}
	}
	this->OnDisConnected(e);
}
// ----------------------------------------------------------------------------------------------------

bool TcpServerSocket::IsEnabledEndPoint(System::Net::IPEndPoint ^endPoint)
{
	array<IPAddress^>^ addresses = System::Net::Dns::GetHostAddresses(System::Net::Dns::GetHostName());
	for each (IPAddress^ address in addresses)
	{
		if (address->Equals(endPoint->Address))
		{
			return true;
		}
	}

	if (endPoint->Address->ToString()->Equals("127.0.0.1"))
	{
		return true;
	}

	return false;
}
// ----------------------------------------------------------------------------------------------------

void TcpServerSocket::SetEncoding(System::Text::Encoding ^encoding)
{
	this->encoding = encoding;
	for each (TcpClientSocket^ client in this->clients)
	{
		client->Encoding = this->encoding;
	}
}
// ----------------------------------------------------------------------------------------------------

bool TcpServerSocket::Initialize(System::Net::IPEndPoint ^endPoint)
{
	try
	{
		if (!this->IsEnabledEndPoint(endPoint)) return false;

		this->Stop();
		this->server = gcnew TcpListener(endPoint);
	}
	catch (Exception^)
	{
		return false;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TcpServerSocket::Start()
{
	if (this->server == nullptr || this->started) return false;
	
	this->server->Start();
	this->started = true;
	this->acceptWorker->RunWorkerAsync();

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TcpServerSocket::Stop()
{
	if (this->server == nullptr || !this->started) return false;

	for each (TcpClientSocket^ client in this->clients)
	{
		client->DisConnect();
	}
	this->clients->Clear();

	this->server->Stop();
	this->started = false;

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TcpServerSocket::DisConnect(System::Net::IPEndPoint ^endPoint)
{
	for each (TcpClientSocket^ client in this->clients)
	{
		if (client->RemoteEndPoint->Equals(endPoint))
		{
			client->DisConnect();
			this->clients->Remove(client);
			return true;
		}
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool TcpServerSocket::SendMessage(System::String ^message, System::Net::IPEndPoint ^endPoint)
{
	bool result = false;
	for each (TcpClientSocket^ client in this->clients)
	{
		if (client->RemoteEndPoint->Equals(endPoint))
		{
			result = client->SendMessage(message);
			break;
		}
	}
	return result;
}
// ----------------------------------------------------------------------------------------------------

void TcpServerSocket::OnConnected(Anaheim::TcpSocket::TcpEventArgs ^e)
{
	this->Connected(this, e);
}
// ----------------------------------------------------------------------------------------------------

void TcpServerSocket::OnDisConnected(Anaheim::TcpSocket::TcpEventArgs ^e)
{
	this->DisConnected(this, e);
}
// ----------------------------------------------------------------------------------------------------

void TcpServerSocket::OnReceived(Anaheim::TcpSocket::TcpEventArgs ^e)
{
	this->Received(this, e);
}
// ----------------------------------------------------------------------------------------------------
