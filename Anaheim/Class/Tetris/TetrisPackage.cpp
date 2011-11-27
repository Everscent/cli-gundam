#include "StdAfx.h"
#include "TetrisPackage.h"
#include "TetrisController.h"
#include "TetrisModel.h"
#include "TetrisView.h"
#include "TetrisField.h"
#include "TetrisMino.h"
#include "TetrisScore.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * テトリスパッケージ
 */
TetrisPackage::TetrisPackage(System::Windows::Forms::Control ^mainCanvas, cli::array<System::Windows::Forms::Control ^,1> ^nextCanvases)
{
	TetrisField^ field = gcnew TetrisField();
	List<TetrisMino^>^ minos = gcnew List<TetrisMino^>;
	this->view = gcnew TetrisView(mainCanvas, nextCanvases, field, minos);
	this->model = gcnew TetrisModel(field, minos, gcnew TetrisScore(), nextCanvases->Length);
	this->controller = gcnew TetrisController(this->model, this->view, mainCanvas, nextCanvases);
	this->model->TurnEnd += gcnew EventHandler(this, &TetrisPackage::ModelTurnEnd);
	this->model->ScoreChanged += gcnew TetrisScoreEventHandler(this, &TetrisPackage::ModelScoreChanged);
	this->model->GameOver += gcnew TetrisScoreEventHandler(this, &TetrisPackage::ModelGameOver);
	this->controller->GameOver += gcnew TetrisScoreEventHandler(this, &TetrisPackage::ControllerGameOver);
}
// ----------------------------------------------------------------------------------------------------

void TetrisPackage::ModelTurnEnd(System::Object ^sender, System::EventArgs ^e)
{
	this->OnTurnEnd(e);
}
// ----------------------------------------------------------------------------------------------------

void TetrisPackage::ModelScoreChanged(System::Object ^sender, Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->OnScoreChanged(e);
}
// ----------------------------------------------------------------------------------------------------

void TetrisPackage::ModelGameOver(System::Object ^sender, Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->OnGameOver(e);
}
// ----------------------------------------------------------------------------------------------------

void TetrisPackage::ControllerGameOver(System::Object ^sender, Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->OnGameOver(e);
}
// ----------------------------------------------------------------------------------------------------

void TetrisPackage::OnTurnEnd(System::EventArgs ^e)
{
	this->TurnEnd(this, e);
}
// ----------------------------------------------------------------------------------------------------

void TetrisPackage::OnScoreChanged(Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->ScoreChanged(this, e);
}
// ----------------------------------------------------------------------------------------------------

void TetrisPackage::OnGameOver(Anaheim::Tetris::TetrisScoreEventArgs ^e)
{
	this->GameOver(this, e);
}
// ----------------------------------------------------------------------------------------------------
