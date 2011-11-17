#include "StdAfx.h"
#include "TetrisDrawing.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * テトリス描画
 */
TetrisDrawing::TetrisDrawing(System::Windows::Forms::Control ^canvas, ITetrisDrawAPI ^api)
{
	this->canvas = canvas;
	this->api = api;
}
// ----------------------------------------------------------------------------------------------------

PointF TetrisDrawing::GetBlockLocation(System::Drawing::Point point, System::Drawing::SizeF blockSize)
{
	float x = blockSize.Width * point.X; 
	float y = blockSize.Height * point.Y;
	return PointF(x, y);
}
// ----------------------------------------------------------------------------------------------------

void TetrisDrawing::DrawBlock(System::Drawing::PointF location, System::Drawing::SizeF size, System::Drawing::Color color)
{
	this->api->FillRectangle(color, location, size);
	this->api->DrawRectangle(this->canvas->BackColor, 2, location, size);
}
// ----------------------------------------------------------------------------------------------------

void TetrisDrawing::Draw(Anaheim::Tetris::TetrisMino ^mino)
{
	this->api->BeginDraw();

	this->DrawCore(mino);

	this->api->EndDraw();
}
// ----------------------------------------------------------------------------------------------------

void TetrisDrawing::Clear()
{
	this->api->Clear();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisDrawing::IsMyCanvas(System::Windows::Forms::Control ^canvas)
{
	return (this->canvas == canvas) ? true : false;
}
// ----------------------------------------------------------------------------------------------------

/**
 * メイン描画
 */
MainTetrisDrawing::MainTetrisDrawing(System::Windows::Forms::Control ^canvas, Anaheim::Tetris::ITetrisDrawAPI ^api, Anaheim::Tetris::TetrisField ^field)
	: TetrisDrawing(canvas, api)
{
	this->field = field;
}
// ----------------------------------------------------------------------------------------------------

void MainTetrisDrawing::DrawMino(Anaheim::Tetris::TetrisMino ^mino)
{
	SizeF size = this->GetBlockSize();

	for each (Point point in mino->Points)
	{
		PointF location = this->GetBlockLocation(point, size);
		this->DrawBlock(location, size, mino->Color);
	}
}
// ----------------------------------------------------------------------------------------------------

SizeF MainTetrisDrawing::GetBlockSize()
{
	const int margin = 6;
	float width = static_cast<float>(this->canvas->Width - margin) / TetrisField::COL_COUNT;
	float height = static_cast<float>(this->canvas->Height - margin) / TetrisField::ROW_COUNT;
	return SizeF(width, height);
}
// ----------------------------------------------------------------------------------------------------

void MainTetrisDrawing::DrawCore(Anaheim::Tetris::TetrisMino ^mino)
{
	SizeF size = this->GetBlockSize();

	int y = 0;
	for each (TetrisFieldRow^ row in this->field->Rows)
	{
		int x = 0;
		for each (Color color in row->Colors)
		{
			if (!color.Equals(Color::Empty))
			{
				PointF location = this->GetBlockLocation(Point(x, y), size);
				this->DrawBlock(location, size, color);
			}
			x++;
		}
		y++;
	}

	TetrisMino^ ghost = mino->CreateGhost();
	this->DrawMino(ghost);
	this->DrawMino(mino);
}
// ----------------------------------------------------------------------------------------------------

/**
 * ネクスト描画
 */
NextTetrisDrawing::NextTetrisDrawing(System::Windows::Forms::Control ^canvas, Anaheim::Tetris::ITetrisDrawAPI ^api)
	: TetrisDrawing(canvas, api)
{
}
// ----------------------------------------------------------------------------------------------------

SizeF NextTetrisDrawing::GetBlockSize()
{
	const int margin = 6;

	float width = (float)(this->canvas->Width - margin) / TetrisMino::HORI_COUNT;
	float height = (float)(this->canvas->Height - margin) / TetrisMino::VERT_COUNT;
	return SizeF(width, height);
}
// ----------------------------------------------------------------------------------------------------

void NextTetrisDrawing::DrawCore(Anaheim::Tetris::TetrisMino ^mino)
{
	SizeF size = this->GetBlockSize();
	for each (Point point in mino->RelativePoints)
	{
		PointF location = this->GetBlockLocation(point, size);
		PointF adjust = mino->AdjustPointForNext(location, size);
		this->DrawBlock(adjust, size, mino->Color);
	}
}
// ----------------------------------------------------------------------------------------------------
