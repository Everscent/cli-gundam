#include "StdAfx.h"
#include "PicturePuzzle.h"

using namespace RX78_2;
using namespace RX78_2::Puzzle;

/**
 * ピクチャーパズル
 */
PicturePuzzle::PicturePuzzle()
{
	this->bitmap = gcnew PuzzleBitmap();
	this->drag = gcnew PuzzleDrag();
	this->correctArray = gcnew array<Control^>(26);
	this->realArray = gcnew array<Control^>(26);
	this->emptyPoint = Point(0, 0);
}
// ----------------------------------------------------------------------------------------------------

Point PicturePuzzle::IndexToPoint(int index)
{
	if (index == 25)
	{
		return Point(4, 5);
	}
	else
	{
		return Point(index % 5, index / 5);
	}
}
// ----------------------------------------------------------------------------------------------------

int PicturePuzzle::PointToIndex(System::Drawing::Point point)
{
	if (point == Point(4, 5))
	{
		return 25;
	}
	else
	{
		return point.X + point.Y * 5;
	}
}
// ----------------------------------------------------------------------------------------------------

void PicturePuzzle::SetPuzzleControl(cli::array<System::Windows::Forms::Control ^,2> ^puzzle)
{
	int count = 0;
	for each (Control^ puzl in puzzle)
	{
		int index = this->PointToIndex(Point(count / 5, count % 5));
		this->correctArray[index] = puzl;
		count++;
	}
	this->correctArray[25] = nullptr;

	this->correctArray->CopyTo(this->realArray, 0);
}
// ----------------------------------------------------------------------------------------------------

void PicturePuzzle::Shuffle()
{
	this->correctArray->CopyTo(this->realArray, 0);

	Random^ random = gcnew Random();
	int n = 24;
	while (1 < n)
	{
		n--;
		int k = random->Next(n + 1);
		Control^ temp = this->realArray[k];
		this->realArray[k] = this->realArray[n];
		this->realArray[n] = temp;
	}

	this->realArray[25] = this->correctArray[24];	// 25枚目
	this->realArray[24] = nullptr;

	this->emptyPoint = Point(4, 4);
}
// ----------------------------------------------------------------------------------------------------

bool PicturePuzzle::MovePuzzle(System::Windows::Forms::Control ^puzzle)
{
	if (this->GetDirectionCanMove(puzzle) == PuzzleDrag::Direction::Non) return false;

	Point temp = this->emptyPoint;
	this->emptyPoint = this->GetRialPoint(puzzle);
	this->realArray[this->PointToIndex(temp)] = puzzle;
	this->realArray[this->PointToIndex(emptyPoint)] = nullptr;

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool PicturePuzzle::IsCorrect(System::Windows::Forms::Control ^puzzle)
{
	int index = 0;
	for each (Control^ puzl in this->realArray)
	{
		if (puzl == puzzle)
		{
			break;
		}
		index++;
	}

	return (this->correctArray[index] == this->realArray[index]) ? true : false;
}
// ----------------------------------------------------------------------------------------------------

Point PicturePuzzle::GetCorrectPoint(System::Windows::Forms::Control ^puzzle)
{
	int index = 0;
	for each (Control^ puzl in this->correctArray)
	{
		if (puzl == puzzle)
		{
			break;
		}
		index++;
	}

	return this->IndexToPoint(index);
}
// ----------------------------------------------------------------------------------------------------

Point PicturePuzzle::GetRialPoint(System::Windows::Forms::Control ^puzzle)
{
	int index = 0;
	for each (Control^ puzl in this->realArray)
	{
		if (puzl == puzzle)
		{
			break;
		}
		index++;
	}

	return this->IndexToPoint(index);
}
// ----------------------------------------------------------------------------------------------------

PuzzleDrag::Direction PicturePuzzle::GetDirectionCanMove(System::Windows::Forms::Control ^puzzle)
{
	Point point = this->GetRialPoint(puzzle);

	if (this->emptyPoint == Point(point.X, point.Y - 1))
	{
		return PuzzleDrag::Direction::Up;
	}
	else if (this->emptyPoint == Point(point.X, point.Y + 1))
	{
		return PuzzleDrag::Direction::Down;
	}
	else if (this->emptyPoint == Point(point.X - 1, point.Y))
	{
		return PuzzleDrag::Direction::Left;
	}
	else if (this->emptyPoint == Point(point.X + 1, point.Y))
	{
		return PuzzleDrag::Direction::Right;
	}

	return PuzzleDrag::Direction::Non;
}
// ----------------------------------------------------------------------------------------------------
