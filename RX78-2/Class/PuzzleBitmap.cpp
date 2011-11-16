#include "StdAfx.h"
#include "PuzzleBitmap.h"

using namespace RX78_2;
using namespace RX78_2::Puzzle;

/**
 * ピクチャービットマップ
 */
PuzzleBitmap::PuzzleBitmap()
{
	this->fileBmp = nullptr;
	this->reverseBmp = nullptr;
	this->resizeFileBmp = nullptr;
	this->resizeReverseBmp = nullptr;
	this->size.Width = 0;
	this->size.Height = 0;
}
// ----------------------------------------------------------------------------------------------------

void PuzzleBitmap::CreateReverseBmp()
{
	this->reverseBmp = dynamic_cast<Bitmap^>(this->fileBmp->Clone());
	Color tempColor;
	int width = this->reverseBmp->Width;
	int height = this->reverseBmp->Height;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			tempColor = this->reverseBmp->GetPixel(x, y);
			this->reverseBmp->SetPixel(x, y, Color::FromArgb(255 - tempColor.R, 255 - tempColor.G, 255 - tempColor.B));
		}
	}
	this->resizeReverseBmp = dynamic_cast<Bitmap^>(this->reverseBmp->Clone());
}
// ----------------------------------------------------------------------------------------------------

bool PuzzleBitmap::LoadFile(System::String ^fileName)
{
	try
	{
		this->fileBmp = gcnew Bitmap(fileName);
		this->size.Width = this->fileBmp->Width;
		this->size.Height = this->fileBmp->Height;
		this->resizeFileBmp = dynamic_cast<Bitmap^>(this->fileBmp->Clone());
		this->CreateReverseBmp();

		// SetPixelを実行するとなぜか再読み込みが速くなる（リサイズの時など）
		Color tempColor = this->fileBmp->GetPixel(0, 0);
		this->fileBmp->SetPixel(0, 0, Color::FromArgb(tempColor.R, tempColor.G, tempColor.B));
	}
	catch (Exception^)
	{
		return false;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

void PuzzleBitmap::ChangeSize(System::Drawing::Size size)
{
	this->size = size;
	if (this->resizeFileBmp != nullptr && this->size != this->resizeFileBmp->Size)
	{
		delete this->resizeFileBmp;
		this->resizeFileBmp = gcnew Bitmap(this->fileBmp, this->size.Width, this->size.Height);
	}
	if (this->resizeReverseBmp != nullptr && this->size != this->resizeReverseBmp->Size)
	{
		delete this->resizeReverseBmp;
		this->resizeReverseBmp = gcnew Bitmap(this->reverseBmp, this->size.Width, this->size.Height);
	}
}
// ----------------------------------------------------------------------------------------------------

Bitmap^ PuzzleBitmap::GetBitmap(bool isReverse)
{
	if (isReverse)
	{
		return this->resizeReverseBmp;
	}
	else
	{
		return this->resizeFileBmp;
	}
}
// ----------------------------------------------------------------------------------------------------

Bitmap^ PuzzleBitmap::GetSmallBitmap(System::Drawing::Point point, bool isReverse)
{
	Bitmap^ result = nullptr;

	if (point.X < this->CUT_COUNT_X && point.Y < this->CUT_COUNT_Y)
	{
		Bitmap^ bitmap = this->GetBitmap(isReverse);
		if (bitmap != nullptr)
		{
			int width = this->size.Width;
			int height = this->size.Height;
			System::Drawing::Rectangle rect = System::Drawing::Rectangle((width / this->CUT_COUNT_X) * point.X, (height / this->CUT_COUNT_Y) * point.Y, width / this->CUT_COUNT_X, height / this->CUT_COUNT_Y);
			result = bitmap->Clone(rect, bitmap->PixelFormat);
		}
	}

	return result;
}
// ----------------------------------------------------------------------------------------------------