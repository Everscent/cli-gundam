#include "StdAfx.h"
#include "TetrisRemoteManager.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

TetrisRemoteManager::TetrisRemoteManager(System::Windows::Forms::Control ^canvas)
{
	this->canvas = canvas;
	this->remote = gcnew TetrisRemoteControl();
	this->remote->Received += gcnew TetrisRemoteEventHandler(this, &TetrisRemoteManager::RemoteReceived);
	this->drawing = nullptr;
	this->mino = nullptr;
}
// ----------------------------------------------------------------------------------------------------

void TetrisRemoteManager::RemoteReceived(System::Object ^sender, Anaheim::Tetris::TetrisRemoteEventArgs ^e)
{
	this->drawing = gcnew MainTetrisDrawing(this->canvas, gcnew GraphicsTetrisDrawAPI(this->canvas), e->Field);
	this->drawing->Draw(e->Mino);
	this->mino = e->Mino;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemoteManager::StartRemote()
{
	return this->remote->Start(gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 50005));
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemoteManager::StopRemote()
{
	return this->remote->Stop();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemoteManager::Draw()
{
	if (this->drawing == nullptr) return false;

	this->drawing->Draw(this->mino);
	return true;
}
// ----------------------------------------------------------------------------------------------------
