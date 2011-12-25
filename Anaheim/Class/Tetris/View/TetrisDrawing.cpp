#include "StdAfx.h"
#include "TetrisDrawing.h"
#include "TetrisField.h"
#include "TetrisMino.h"
#include "TetrisDrawAPI.h"

using namespace Anaheim;
using namespace Anaheim::Tetris::View;

/**
 * ƒeƒgƒŠƒX•`‰æ
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
	this->api->FillRectangleGradation(color, Color::FromArgb(color.A, Color::White), location, size);
	this->api->DrawRectangle(this->canvas->BackColor, 2, location, size);
}
// ----------------------------------------------------------------------------------------------------

void TetrisDrawing::Draw(Anaheim::Tetris::Model::TetrisMino ^mino)
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
 * ƒƒCƒ“•`‰æ
 */
MainTetrisDrawing::MainTetrisDrawing(System::Windows::Forms::Control ^canvas, Anaheim::Tetris::View::ITetrisDrawAPI ^api, Anaheim::Tetris::Model::TetrisField ^field)
	: TetrisDrawing(canvas, api)
{
	this->field = field;
}
// ----------------------------------------------------------------------------------------------------

void MainTetrisDrawing::DrawRemoveBlock(System::Drawing::PointF location, System::Drawing::SizeF size)
{
	this->api->FillRectangleGradation(Color::FromArgb(192, Color::White), Color::FromArgb(192, this->canvas->BackColor), location, size);
	this->api->DrawRectangle(this->canvas->BackColor, 2, location, size);
}
// ----------------------------------------------------------------------------------------------------

void MainTetrisDrawing::DrawMino(Anaheim::Tetris::Model::TetrisMino ^mino)
{
	SizeF size = this->GetBlockSize();

	for each (Point point in mino->Points)
	{
		PointF location = this->GetBlockLocation(point, size);
		this->DrawBlock(location, size, mino->Color);
	}
}
// ----------------------------------------------------------------------------------------------------

void MainTetrisDrawing::DrawGhostMino(Anaheim::Tetris::Model::GhostTetrisMino ^mino)
{
	this->DrawMino(mino);

	// ˜gü•`‰æ
	SizeF size = this->GetBlockSize();
	for each (Point point in mino->Points)
	{
		PointF location = this->GetBlockLocation(point, size);
		this->api->DrawLine(mino->DarkBorderColor, 1, PointF(location.X + size.Width, location.Y + size.Height), PointF(location.X, location.Y + size.Height));
		this->api->DrawLine(mino->DarkBorderColor, 1, PointF(location.X, location.Y + size.Height), location);
	}
	for each (Point point in mino->Points)
	{
		PointF location = this->GetBlockLocation(point, size);
		this->api->DrawLine(mino->BrightBorderColor, 1, location, PointF(location.X + size.Width, location.Y));
		this->api->DrawLine(mino->BrightBorderColor, 1, PointF(location.X + size.Width, location.Y), PointF(location.X + size.Width, location.Y + size.Height));
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

void MainTetrisDrawing::DrawCore(Anaheim::Tetris::Model::TetrisMino ^mino)
{
	SizeF size = this->GetBlockSize();

	int y = 0;
	for each (TetrisFieldRow^ row in this->field->Rows)
	{
		if (row->IsComplete())
		{
			for (int x = 0; x < TetrisField::COL_COUNT; x++)
			{
				PointF location = this->GetBlockLocation(Point(x, y), size);
				this->DrawRemoveBlock(location, size);
			}			
		}
		else
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
		}
		y++;
	}

	if (!this->field->ExistsCompleteRow())
	{
		GhostTetrisMino^ ghost = mino->CreateGhost();
		this->DrawGhostMino(ghost);
		this->DrawMino(mino);
	}
}
// ----------------------------------------------------------------------------------------------------

/**
 * ƒlƒNƒXƒg•`‰æ
 */
NextTetrisDrawing::NextTetrisDrawing(System::Windows::Forms::Control ^canvas, Anaheim::Tetris::View::ITetrisDrawAPI ^api)
	: TetrisDrawing(canvas, api)
{
}
// ----------------------------------------------------------------------------------------------------

SizeF NextTetrisDrawing::GetBlockSize()
{
	const int margin = 6;
	float width = static_cast<float>(this->canvas->Width - margin) / TetrisMino::HORI_COUNT;
	float height = static_cast<float>(this->canvas->Height - margin) / TetrisMino::VERT_COUNT;
	return SizeF(width, height);
}
// ----------------------------------------------------------------------------------------------------

void NextTetrisDrawing::DrawCore(Anaheim::Tetris::Model::TetrisMino ^mino)
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
