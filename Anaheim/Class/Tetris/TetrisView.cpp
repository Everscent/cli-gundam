#include "StdAfx.h"
#include "TetrisView.h"
#include "TetrisDrawing.h"
#include "TetrisDrawAPI.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * ƒeƒgƒŠƒXView
 */
TetrisView::TetrisView(System::Windows::Forms::Control ^mainCanvas, cli::array<System::Windows::Forms::Control ^,1> ^nextCanvases, Anaheim::Tetris::TetrisField ^field, System::Collections::Generic::List<TetrisMino^> ^minos)
{
	this->drawings = gcnew array<TetrisDrawing^>(nextCanvases->Length + 1);
	this->drawings[0] = gcnew MainTetrisDrawing(mainCanvas, gcnew GraphicsTetrisDrawAPI(mainCanvas), field);
	int count = 0;
	for each (Control^ canvas in nextCanvases)
	{
		this->drawings[count + 1] = gcnew NextTetrisDrawing(canvas, gcnew GraphicsTetrisDrawAPI(canvas));
		count++;
	}
	this->field = field;
	this->minos = minos;
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
