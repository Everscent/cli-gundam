#include "StdAfx.h"
#include "TetrisManager.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * ƒeƒgƒŠƒX
 */
TetrisManager::TetrisManager(System::Windows::Forms::Control ^mainCanvas, cli::array<System::Windows::Forms::Control ^,1> ^nextCanvases)
{
	this->field = gcnew TetrisField();
	this->minos = gcnew List<TetrisMino^>;
	this->drawings = gcnew array<TetrisDrawing^>(nextCanvases->Length + 1);
	this->drawings[0] = gcnew MainTetrisDrawing(mainCanvas, gcnew GraphicsTetrisDrawAPI(mainCanvas), this->field);
	int count = 0;
	for each (Control^ canvas in nextCanvases)
	{
		this->drawings[count + 1] = gcnew NextTetrisDrawing(canvas, gcnew GraphicsTetrisDrawAPI(canvas));
		count++;
	}
	this->score = gcnew TetrisScore();
	this->remote = gcnew TetrisRemoteControl();
}
// ----------------------------------------------------------------------------------------------------

void TetrisManager::AddNextMinos()
{
	array<TetrisMino^>^ shuffleMino =
	{
		gcnew ITetrisMino(Point(3, 0), this->field),
		gcnew JTetrisMino(Point(3, 0), this->field),
		gcnew LTetrisMino(Point(3, 0), this->field),
		gcnew STetrisMino(Point(3, 0), this->field),
		gcnew ZTetrisMino(Point(3, 0), this->field),
		gcnew TTetrisMino(Point(3, 0), this->field),
		gcnew OTetrisMino(Point(3, 0), this->field)
	};

	Random^ random = gcnew Random();
	int n = shuffleMino->Length;
	while (1 < n)
	{
		n--;
		int k = random->Next(n + 1);
		TetrisMino^ temp = shuffleMino[k];
		shuffleMino[k] = shuffleMino[n];
		shuffleMino[n] = temp;
	}
	
	for each (TetrisMino^ mino in shuffleMino)
	{
		this->minos->Add(mino);
	}
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::SetNewMino()
{
	this->minos->Remove(this->CurrentMino);

	while (this->minos->Count < this->drawings->Length)
	{
		this->AddNextMinos();
	}

	return (this->CurrentMino->IsIllegalLocation()) ? false : true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::EndDown()
{
	this->field->SetMino(this->CurrentMino);
	int count = this->field->RemoveCompleteRows();
	bool isPerfect = this->field->IsEmpty;
	if (this->score->UpdateScore(count, isPerfect))
	{
		this->OnChangedScore(gcnew TetrisScoreEventArgs(this->score));
	}

	return this->SetNewMino();
}
// ----------------------------------------------------------------------------------------------------

void TetrisManager::Clear()
{
	this->field->Clear();
	this->minos->Clear();
	this->score->Clear();

	for each (TetrisDrawing^ drawing in this->drawings)
	{
		drawing->Clear();
	}
}
// ----------------------------------------------------------------------------------------------------

void TetrisManager::Initialize()
{
	this->Clear();
	this->SetNewMino();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::Draw()
{
	if (this->CurrentMino == nullptr) return false;

	int count = 0;
	for each (TetrisDrawing^ drawing in this->drawings)
	{
		drawing->Draw(this->minos[count]);
		count++;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::Draw(System::Windows::Forms::Control ^canvas)
{
	if (this->CurrentMino == nullptr) return false;

	int count = 0;
	for each (TetrisDrawing^ drawing in this->drawings)
	{
		if (drawing->IsMyCanvas(canvas))
		{
			drawing->Draw(this->minos[count]);
			return true;
		}
		count++;
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::RotateRight()
{
	return this->CurrentMino->RotateRight();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::RotateLeft()
{
	return this->CurrentMino->RotateLeft();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::MoveRight()
{
	return this->CurrentMino->MoveRight();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::MoveLeft()
{
	return this->CurrentMino->MoveLeft();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::MoveDown()
{
	return this->CurrentMino->MoveDown();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::MoveDownAutomatic()
{
	if (!this->MoveDown())
	{
		bool result = this->EndDown();
		if (!result)
		{
			this->OnGameOver(gcnew EventArgs());
		}
		this->OnTurnEnd(gcnew EventArgs());

		return result;
	}

	this->remote->Send(this->field, this->CurrentMino, gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 50005));

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::Teleport()
{
	TetrisMino^ ghost = this->CurrentMino->CreateGhost();
	this->CurrentMino->MoveTo(ghost);
	return this->CurrentMino->IsIllegalLocation();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::StartRemote()
{
	return this->remote->Start(gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 50000));
}
// ----------------------------------------------------------------------------------------------------

bool TetrisManager::StopRemote()
{
	return this->remote->Stop();
}
// ----------------------------------------------------------------------------------------------------

void TetrisManager::OnTurnEnd(System::EventArgs ^e)
{
	this->TurnEnd(this, e);
}
// ----------------------------------------------------------------------------------------------------

void TetrisManager::OnChangedScore(TetrisScoreEventArgs ^e)
{
	this->ChangedScore(this, e);
}
// ----------------------------------------------------------------------------------------------------

void TetrisManager::OnGameOver(System::EventArgs ^e)
{
	this->GameOver(this, e);
}
// ----------------------------------------------------------------------------------------------------
