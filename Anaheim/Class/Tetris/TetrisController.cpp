#include "StdAfx.h"
#include "TetrisController.h"
#include "TetrisModel.h"
#include "TetrisView.h"
#include "TetrisRemoting.h"
#include "TetrisSound.h"
#include "TetrisField.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * ƒeƒgƒŠƒXController
 */
TetrisController::TetrisController(Anaheim::Tetris::TetrisModel ^model, Anaheim::Tetris::TetrisView ^view, System::Windows::Forms::Control ^mainCanvas, cli::array<System::Windows::Forms::Control ^,1> ^nextCanvases)
{
	this->model = model;
	this->model->FieldChanged += gcnew EventHandler(this, &TetrisController::ModelFieldChanged);
	this->model->GameOver += gcnew TetrisScoreEventHandler(this, &TetrisController::ModelGameOver);
	this->view = view;
	this->remoting = gcnew TetrisRemoting();
	this->sound = gcnew TetrisSound(mainCanvas);
	this->timer = gcnew Timer();
	this->timer->Interval = 700;
	this->timer->Tick += gcnew EventHandler(this, &TetrisController::TimerTick);
	this->key = gcnew TetrisKey(this->model, this->timer);
	this->isPause = false;
	mainCanvas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &TetrisController::CanvasPaint);
	for each (Control^ canvas in nextCanvases)
	{
		canvas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &TetrisController::CanvasPaint);
	}
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::TimerTick(System::Object ^sender, System::EventArgs ^e)
{
	this->model->MoveDownAutomatic();
	this->view->Draw();
	this->RemoteSend();
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::CanvasPaint(System::Object ^sender, System::Windows::Forms::PaintEventArgs ^e)
{
	if (this->isPause) return;

	this->view->Draw(dynamic_cast<Control^>(sender));
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::ModelFieldChanged(System::Object ^sender, System::EventArgs ^e)
{
	if (!this->model->Field->ExistsCompleteRow())
	{
		this->sound->PlayEndDownSound();
	}
	else
	{
		this->timer->Stop();
		this->sound->PlayRemoveSound();
		this->view->Draw();
		this->RemoteSend();
		System::Threading::Thread::Sleep(300);
		this->timer->Start();
	}
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::ModelGameOver(System::Object ^sender, Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->Stop();
	this->isPause = false;
	this->sound->StopBGM();
	this->sound->PlayGameOverSound();
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::RemoteSend()
{
	this->remoting->Send(this->model->Field, this->model->CurrentMino, gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 50005));
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::SetSoundON(bool isON)
{
	this->sound->ON = isON;
	if (isON && this->timer->Enabled)
	{
		this->sound->PlayBGM();
	}
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::Clear()
{
	this->Stop();
	this->sound->StopBGM();
	this->OnGameOver(gcnew TetrisScoreEventArgs(this->model->Score));
	this->model->Clear();
	this->view->Clear();
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::Initialize()
{
	this->Stop();
	this->view->Clear();
	this->model->Initialize();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::Start()
{
	if (this->timer->Enabled) return false;

	this->view->Draw();
	this->RemoteSend();
	this->sound->PlayBGM();
	this->timer->Start();
	this->isPause = false;
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::Stop()
{
	if (!this->timer->Enabled) return false;

	this->view->Clear();
	this->sound->PauseBGM();
	this->timer->Stop();
	this->isPause = true;
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::ProcessDialogKey(System::Windows::Forms::Keys keyData)
{
	if (!this->timer->Enabled) return false;
	if (!this->key->IsRegisteredKey(keyData)) return false;

	if (this->key->ExecuteKeyAction(keyData))
	{
		this->view->Draw();
		this->RemoteSend();
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::StartRemote()
{
	return this->remoting->Start(gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 50000));
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::StopRemote()
{
	return this->remoting->Stop();
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::OnGameOver(Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->GameOver(this, e);
}
// ----------------------------------------------------------------------------------------------------
