#include "StdAfx.h"
#include "TetrisRemotePackage.h"
#include "TetrisRemoteController.h"
#include "TetrisDrawing.h"
#include "TetrisDrawAPI.h"
#include "TetrisMino.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

TetrisRemotePackage::TetrisRemotePackage(System::Windows::Forms::Control ^canvas)
{
	this->canvas = canvas;
	this->canvas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &TetrisRemotePackage::CanvasPaint);
	this->canvas->Resize += gcnew System::EventHandler(this, &TetrisRemotePackage::CanvasResize);
	this->remote = gcnew TetrisRemoteController();
	this->remote->Received += gcnew TetrisRemoteEventHandler(this, &TetrisRemotePackage::RemoteReceived);
	this->drawing = nullptr;
	this->mino = nullptr;
}
// ----------------------------------------------------------------------------------------------------

void TetrisRemotePackage::RemoteReceived(System::Object ^sender, Anaheim::Tetris::TetrisRemoteEventArgs ^e)
{
	this->drawing = gcnew MainTetrisDrawing(this->canvas, gcnew GraphicsTetrisDrawAPI(this->canvas), e->Field);
	this->mino = e->Mino;
	this->Draw();
}
// ----------------------------------------------------------------------------------------------------

void TetrisRemotePackage::CanvasPaint(System::Object ^sender, System::Windows::Forms::PaintEventArgs ^e)
{
	this->Draw();
}
// ----------------------------------------------------------------------------------------------------

void TetrisRemotePackage::CanvasResize(System::Object ^sender, System::EventArgs ^e)
{
	this->Draw();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemotePackage::StartRemote()
{
	return this->remote->Start(gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 50005));
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemotePackage::StopRemote()
{
	return this->remote->Stop();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisRemotePackage::Draw()
{
	if (this->drawing == nullptr) return false;

	this->drawing->Draw(this->mino);
	return true;
}
// ----------------------------------------------------------------------------------------------------
