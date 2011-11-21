#include "StdAfx.h"
#include "TetrisController.h"
#include "TetrisModel.h"
#include "TetrisView.h"
#include "TetrisRemoteController.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * �e�g���XController
 */
TetrisController::TetrisController(Anaheim::Tetris::TetrisModel ^model, Anaheim::Tetris::TetrisView ^view, System::Windows::Forms::Control ^mainCanvas, cli::array<System::Windows::Forms::Control ^,1> ^nextCanvases)
{
	this->model = model;
	this->model->GameOver += gcnew TetrisScoreEventHandler(this, &TetrisController::ModelGameOver);
	this->view = view;
	this->remote = gcnew TetrisRemoteController();
	this->timer = gcnew Timer();
	this->timer->Interval = 700;
	this->timer->Tick += gcnew EventHandler(this, &TetrisController::TimerTick);
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
	this->view->Draw(dynamic_cast<Control^>(sender));
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::ModelGameOver(System::Object ^sender, Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->timer->Stop();
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::RemoteSend()
{
	this->remote->Send(this->model->Field, this->model->CurrentMino, gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 50005));
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::Clear()
{
	this->timer->Stop();
	this->OnGameOver(gcnew TetrisScoreEventArgs(this->model->Score));
	this->model->Clear();
	this->view->Clear();
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::Initialize()
{
	this->view->Clear();
	this->model->Initialize();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::Start()
{
	if (this->timer->Enabled) return false;

	this->timer->Start();
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::Stop()
{
	if (!this->timer->Enabled) return false;

	this->timer->Stop();
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::ProcessDialogKey(System::Windows::Forms::Keys keyData)
{
	if (!this->timer->Enabled) return false;

	bool hasMoved = false;
	switch (keyData)
	{
		case Keys::NumPad2:
		case Keys::Down:
			hasMoved = this->model->MoveDown();
			break;
		case Keys::NumPad4:
		case Keys::Left:
			hasMoved = this->model->MoveLeft();
			break;
		case Keys::NumPad6:
		case Keys::Right:
			hasMoved = this->model->MoveRight();
			break;
		case Keys::NumPad7:
			hasMoved = this->model->RotateLeft();
			break;
		case Keys::NumPad9:
		case Keys::Up:
			hasMoved = this->model->RotateRight();
			break;
		case Keys::Space:
			this->model->Teleport();
			hasMoved = true;
			break;
		default:
			break;
	}

	if (hasMoved)
	{
		this->view->Draw();
		this->RemoteSend();
	}

	return hasMoved;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::StartRemote()
{
	return this->remote->Start(gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 50000));
}
// ----------------------------------------------------------------------------------------------------

bool TetrisController::StopRemote()
{
	return this->remote->Stop();
}
// ----------------------------------------------------------------------------------------------------

void TetrisController::OnGameOver(Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->GameOver(this, e);
}
// ----------------------------------------------------------------------------------------------------