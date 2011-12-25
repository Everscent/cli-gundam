#include "StdAfx.h"
#include "TetrisView.h"
#include "TetrisDrawing.h"
#include "TetrisDrawAPI.h"
#include "TetrisModel.h"
#include "TetrisField.h"

using namespace Anaheim;
using namespace Anaheim::Tetris::View;

/**
 * テトリスView
 */
TetrisView::TetrisView(System::Windows::Forms::Control ^mainCanvas, cli::array<System::Windows::Forms::Control ^,1> ^nextCanvases, Anaheim::Tetris::Model::TetrisModel ^model, Anaheim::Tetris::Model::TetrisField ^field, System::Collections::Generic::List<TetrisMino^> ^minos)
{
	this->drawings = gcnew array<TetrisDrawing^>(nextCanvases->Length + 1);
	this->drawings[0] = gcnew MainTetrisDrawing(mainCanvas, gcnew GraphicsTetrisDrawAPI(mainCanvas), field);
	int count = 0;
	for each (Control^ canvas in nextCanvases)
	{
		this->drawings[count + 1] = gcnew NextTetrisDrawing(canvas, gcnew GraphicsTetrisDrawAPI(canvas));
		count++;
	}
	this->sound = gcnew TetrisSound(mainCanvas);
	this->field = field;
	this->minos = minos;

	model->MinoMoved += gcnew EventHandler(this, &TetrisView::ModelMinoMoved);
	model->FieldChanged += gcnew TetrisFieldEventHandler(this, &TetrisView::ModelFieldChanged);
	model->TurnEnd += gcnew EventHandler(this, &TetrisView::ModelTurnEnd);
	model->GameOver += gcnew TetrisScoreEventHandler(this, &TetrisView::ModelGameOver);
	model->Cleared += gcnew EventHandler(this, &TetrisView::ModelCleared);
}
// ----------------------------------------------------------------------------------------------------

void TetrisView::ModelMinoMoved(System::Object ^sender, System::EventArgs ^e)
{
	this->drawings[0]->Draw(this->minos[0]);
}
// ----------------------------------------------------------------------------------------------------

void TetrisView::ModelFieldChanged(System::Object ^sender, Anaheim::Tetris::TetrisFieldEventArgs ^e)
{
	if (e->Field->ExistsCompleteRow())
	{
		this->sound->PlayRemoveSound();
		this->drawings[0]->Draw(this->minos[0]);	// 削除行の描画
	}
	else
	{
		this->sound->PlayEndDownSound();
	}
}
// ----------------------------------------------------------------------------------------------------

void  TetrisView::ModelTurnEnd(System::Object ^sender, System::EventArgs ^e)
{
	this->Draw();
}
// ----------------------------------------------------------------------------------------------------

void TetrisView::ModelGameOver(System::Object ^sender, Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->sound->StopBGM();
	this->sound->PlayGameOverSound();
}
// ----------------------------------------------------------------------------------------------------

void TetrisView::ModelCleared(System::Object ^sender, System::EventArgs ^e)
{
	this->Clear();
	this->sound->StopBGM();
}
// ----------------------------------------------------------------------------------------------------

void TetrisView::Clear()
{
	for each (TetrisDrawing^ drawing in this->drawings)
	{
		drawing->Clear();
	}
}
// ----------------------------------------------------------------------------------------------------

bool TetrisView::Draw()
{
	if (this->minos->Count == 0) return false;

	int count = 0;
	for each (TetrisDrawing^ drawing in this->drawings)
	{
		drawing->Draw(this->minos[count]);
		count++;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisView::Draw(System::Windows::Forms::Control ^canvas)
{
	if (this->minos->Count == 0) return false;

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

bool TetrisView::PlayBGM()
{
	return this->sound->PlayBGM();
}
// ----------------------------------------------------------------------------------------------------

void TetrisView::PauseBGM()
{
	this->sound->PauseBGM();
}
// ----------------------------------------------------------------------------------------------------

void TetrisView::StopBGM()
{
	this->sound->StopBGM();
}
// ----------------------------------------------------------------------------------------------------
