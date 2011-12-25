#include "StdAfx.h"
#include "TetrisController.h"
#include "TetrisModel.h"
#include "TetrisView.h"
#include "TetrisRemoting.h"
#include "TetrisSound.h"
#include "TetrisField.h"

using namespace Anaheim;
using namespace Anaheim::Tetris::Controller;

/**
 * テトリスController（公開用）
 */
PublicTetrisController::PublicTetrisController()
{
}
// ----------------------------------------------------------------------------------------------------

/**
 * テトリスController
 */
TetrisController::TetrisController(Anaheim::Tetris::Model::TetrisModel ^model, Anaheim::Tetris::View::TetrisView ^view, System::Windows::Forms::Control ^mainCanvas, cli::array<System::Windows::Forms::Control ^,1> ^nextCanvases)
{
	this->model = model;
	this->model->FieldChanged += gcnew TetrisFieldEventHandler(this, &TetrisController::ModelFieldChanged);
	this->model->GameOver += gcnew TetrisScoreEventHandler(this, &TetrisController::ModelGameOver);
	this->view = view;
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
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::CanvasPaint(System::Object ^sender, System::Windows::Forms::PaintEventArgs ^e)
{
	if (this->isPause) return;

	this->view->Draw(dynamic_cast<Control^>(sender));
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::ModelFieldChanged(System::Object ^sender, Anaheim::Tetris::TetrisFieldEventArgs ^e)
{
	if (e->Field->ExistsCompleteRow())
	{
		this->timer->Stop();
		System::Threading::Thread::Sleep(300);
		this->timer->Start();
	}
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::ModelGameOver(System::Object ^sender, Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->view->PauseBGM();
	this->timer->Stop();
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::SetSoundON(bool isON)
{
	this->view->SoundON = isON;
	if (isON && this->timer->Enabled)
	{
		this->view->PlayBGM();
	}
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::Clear()
{
	this->Pause();
	this->OnGameOver(gcnew TetrisScoreEventArgs(this->model->Score));
	this->model->Clear();
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::Initialize()
{
	this->Pause();
	this->model->Initialize();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::Start()
{
	if (this->timer->Enabled) return false;

	this->view->Draw();
	this->view->PlayBGM();
	this->timer->Start();
	this->isPause = false;
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::Pause()
{
	if (!this->timer->Enabled) return false;

	this->view->Clear();
	this->view->PauseBGM();
	this->timer->Stop();
	this->isPause = true;
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::StartRemote()
{
	return this->model->StartRemote();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::StopRemote()
{
	return this->model->StopRemote();
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::OnGameOver(Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->GameOver(this, e);
}
// ----------------------------------------------------------------------------------------------------
