#include "StdAfx.h"
#include "PuzzleDrag.h"

using namespace RX78_2;
using namespace RX78_2::Puzzle;

/**
 * パズルドラッグクラス
 */
PuzzleDrag::PuzzleDrag()
{
	this->Clear();
}
// ----------------------------------------------------------------------------------------------------

void PuzzleDrag::Clear()
{
	this->dragObject = nullptr;
	this->clickPoint = Point(0, 0);
	this->direction = Direction::Up;
	this->startPoint = Point(0, 0);
	this->endPoint = Point(0, 0);
}
// ----------------------------------------------------------------------------------------------------

void PuzzleDrag::Begin(System::Windows::Forms::Control ^dragObject, System::Drawing::Point clickPoint, RX78_2::Puzzle::PuzzleDrag::Direction direction)
{
	this->dragObject = dragObject;
	this->clickPoint = clickPoint;
	this->direction = direction;
	this->startPoint = this->dragObject->Location;
	this->endPoint = this->startPoint;

	switch (this->direction)
	{
		case Direction::Up:
			this->endPoint.Y -= this->dragObject->Height;
			break;
		case Direction::Down:
			this->endPoint.Y += this->dragObject->Height;
			break;
		case Direction::Left:
			this->endPoint.X -= this->dragObject->Width;
			break;
		case Direction::Right:
			this->endPoint.X += this->dragObject->Width;
			break;
		default:
			break;
	}
}
// ----------------------------------------------------------------------------------------------------

void PuzzleDrag::Move(System::Drawing::Point mousePoint)
{
	if (this->dragObject == nullptr) return;

	int distance = 0;
	int max = 0;
	switch (this->direction)
	{
		case Direction::Up:
			distance = this->clickPoint.Y - mousePoint.Y;
			max = this->dragObject->Height;
			break;
		case Direction::Down:
			distance = mousePoint.Y - this->clickPoint.Y;
			max = this->dragObject->Height;
			break;
		case Direction::Left:
			distance = this->clickPoint.X - mousePoint.X;
			max = this->dragObject->Width;
			break;
		case Direction::Right:
			distance = mousePoint.X - this->clickPoint.X;
			max = this->dragObject->Width;
			break;
		default:
			break;
	}

	distance = System::Math::Max(distance, 0);
	distance = System::Math::Min(distance, max);

	switch (this->direction)
	{
		case Direction::Up:
			this->dragObject->Top = this->startPoint.Y - distance;
			break;
		case Direction::Down:
			this->dragObject->Top = this->startPoint.Y + distance;
			break;
		case Direction::Left:
			this->dragObject->Left = this->startPoint.X - distance;
			break;
		case Direction::Right:
			this->dragObject->Left = this->startPoint.X + distance;
			break;
		default:
			break;
	}
}
// ----------------------------------------------------------------------------------------------------

bool PuzzleDrag::End()
{
	if (this->dragObject == nullptr) return false;

	bool isEndPoint = false;
	int middlePoint = 0;

	switch (this->direction)
	{
		case Direction::Up:
			middlePoint = (this->startPoint.Y + this->endPoint.Y) / 2;
			if (this->dragObject->Top < middlePoint)
			{
				isEndPoint = true;
			}
			break;
		case Direction::Down:
			middlePoint = (this->startPoint.Y + this->endPoint.Y) / 2;
			if (middlePoint < this->dragObject->Top)
			{
				isEndPoint = true;
			}
			break;
		case Direction::Left:
			middlePoint = (this->startPoint.X + this->endPoint.X) / 2;
			if (this->dragObject->Left < middlePoint)
			{
				isEndPoint = true;
			}
			break;
		case Direction::Right:
			middlePoint = (this->startPoint.X + this->endPoint.X) / 2;
			if (middlePoint < this->dragObject->Left)
			{
				isEndPoint = true;
			}
			break;
		default:
			break;
	}

	if (isEndPoint)
	{
		this->dragObject->Location = this->endPoint;
	}
	else
	{
		this->dragObject->Location = this->startPoint;
	}

	this->Clear();

	return isEndPoint;
}
// ----------------------------------------------------------------------------------------------------
