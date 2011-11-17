#include "StdAfx.h"
#include "Insect.h"
#include "ArrowUtility.h"

using namespace RX78_2;
using namespace RX78_2::Arrow;

/**
 * 虫クラス
 */
Insect::Insect(System::Windows::Forms::Control ^canvas, System::Random ^random)
{
	this->legLocations = gcnew array<PointF>(this->LEG_COUNT);
	this->canvas = canvas;
	this->random = random;
	this->targetPoint = ArrowUtility::GetMousePoint(this->canvas);
	this->Reset();
}
// ----------------------------------------------------------------------------------------------------

PointF Insect::GetLegPoint(int index)
{
	int jitterX = static_cast<int>(this->speed * this->random->Next(2, 4));
	int jitterY = this->random->Next(10);
	return this->GetLegPointCore(index, Point(jitterX, jitterY));
}
// ----------------------------------------------------------------------------------------------------

PointF Insect::GetLegDefaultPoint(int index)
{
	int jitterX = this->random->Next(10);
	int jitterY = this->random->Next(10);
	return this->GetLegPointCore(index, Point(jitterX, jitterY));
}
// ----------------------------------------------------------------------------------------------------

PointF Insect::GetLegPointCore(int index, System::Drawing::Point jitter)
{
	PointF point;
	switch (index)
	{
		case 0:
			point = PointF(this->location.X + this->HEIGHT / 2 + this->LEG_LENGTH + jitter.X, this->location.Y + this->WIDTH / 2 + jitter.Y);
			break;
		case 1:
			point = PointF(this->location.X + this->HEIGHT / 2 + this->LEG_LENGTH + jitter.X, this->location.Y - this->WIDTH / 2 - jitter.Y);
			break;
		case 2:
			point = PointF(this->location.X - this->HEIGHT / 2 - this->LEG_LENGTH + jitter.X, this->location.Y - this->WIDTH / 2 - jitter.Y);
			break;
		case 3:
			point = PointF(this->location.X - this->HEIGHT / 2 - this->LEG_LENGTH + jitter.X, this->location.Y + this->WIDTH / 2 + jitter.Y);
			break;
		default:
			break;
	}
	return ArrowUtility::RotatePoint(point, this->location, this->degree);
}
// ----------------------------------------------------------------------------------------------------

void Insect::ChangeMoveCondition()
{
	if (this->moveCount != 0) return;

	// 回転先
	Point point = ArrowUtility::GetMousePoint(this->canvas);
	if (point == this->targetPoint)
	{
		this->moveDegree = ArrowUtility::GetAngle(this->targetPoint, this->location);
	}
	else
	{
		double target = ArrowUtility::GetAngle(this->targetPoint, this->location);
		this->moveDegree = ArrowUtility::GetHalfAngle(this->degree, target);
	}
	this->targetPoint = point;

	// 移動ポイント
	this->moveLocation = ArrowUtility::MovePoint(this->location, this->speed, this->degree);

	// 足変更
	switch (this->movingLegNo)
	{
		case 0:
			this->movingLegNo = 2;
			break;
		case 1:
			this->movingLegNo = 3;
			break;
		case 2:
			this->movingLegNo = 1;
			break;
		case 3:
			this->movingLegNo = 0;
			break;
		default:
			this->movingLegNo = 0;
			break;
	}

	// 足移動ポイント
	this->moveLegLocatin = this->GetLegPoint(this->movingLegNo);
}
// ----------------------------------------------------------------------------------------------------

void Insect::MoveCore()
{
	// 回転
	bool isRightRotate = (this->degree < this->moveDegree) ? true : false;
	double deltaDegree = System::Math::Abs(this->moveDegree - this->degree);
	if (180 < deltaDegree)
	{
		deltaDegree = 360 - deltaDegree;
		isRightRotate = (isRightRotate) ? false : true;
	}
	deltaDegree = deltaDegree / (this->MOVE_COUNT_MAX - this->moveCount);
	if (isRightRotate)
	{
		this->degree += deltaDegree;
	}
	else
	{
		this->degree -= deltaDegree;
	}
	this->degree = ArrowUtility::ConvertDegree(this->degree);

	// 移動
	float deltaX = static_cast<float>((this->moveLocation.X - this->location.X)) / (this->MOVE_COUNT_MAX - this->moveCount);
	float deltaY = static_cast<float>((this->moveLocation.Y - this->location.Y)) / (this->MOVE_COUNT_MAX - this->moveCount);
	this->location = PointF(this->location.X + deltaX, this->location.Y + deltaY);

	// 足移動
	float deltaLegX = (this->moveLegLocatin.X - this->legLocations[this->movingLegNo].X) / (this->MOVE_COUNT_MAX - this->moveCount);
	float deltaLegY = (this->moveLegLocatin.Y - this->legLocations[this->movingLegNo].Y) / (this->MOVE_COUNT_MAX - this->moveCount);
	this->legLocations[this->movingLegNo] = PointF(this->legLocations[this->movingLegNo].X + deltaLegX, this->legLocations[this->movingLegNo].Y + deltaLegY);
}
// ----------------------------------------------------------------------------------------------------

void Insect::CalcSpeed()
{
	this->speed = this->random->Next(5, 40);
}
// ----------------------------------------------------------------------------------------------------

System::Drawing::Color Insect::GetColor()
{
	return System::Drawing::Color::DarkBlue;
}
// ----------------------------------------------------------------------------------------------------

void Insect::Move()
{
	if (this->skipMove)
	{
		this->skipMove = false;
		return;
	}

	this->ChangeMoveCondition();

	this->MoveCore();

	if (this->moveCount == this->MOVE_COUNT_MAX - 1)
	{
		this->moveCount = 0;
		this->skipMove = true;
	}
	else
	{
		this->moveCount++;
	}
}
// ----------------------------------------------------------------------------------------------------

void Insect::Reset()
{
	Rectangle rect = System::Windows::Forms::Screen::PrimaryScreen->Bounds;
	int x = this->random->Next(rect.Width);
	int y = this->random->Next(rect.Height);
	this->location = Point(x, y);

	this->degree = this->random->Next(360);

	int count = 0;
	for each (PointF% point in this->legLocations)
	{
		point = this->GetLegDefaultPoint(count);
		count++;
	}

	this->moveCount = this->random->Next(this->MOVE_COUNT_MAX);
	this->moveLocation = this->location;
	this->movingLegNo = this->random->Next(this->LEG_COUNT);
	this->moveLegLocatin = this->legLocations[this->movingLegNo];
	this->moveDegree = this->degree;

	this->skipMove = false;

	this->CalcSpeed();
}
// ----------------------------------------------------------------------------------------------------

array<PointF>^ Insect::GetBodyPoints()
{
	array<PointF>^ corners =
	{
		PointF(this->location.X + this->HEIGHT / 2, this->location.Y + this->WIDTH / 2),
		PointF(this->location.X + this->HEIGHT / 2, this->location.Y - this->WIDTH / 2),
		PointF(this->location.X - this->HEIGHT / 2, this->location.Y - this->WIDTH / 2),
		PointF(this->location.X - this->HEIGHT / 2, this->location.Y + this->WIDTH / 2)
	};

	array<PointF>^ bodys =
	{
		ArrowUtility::RotatePoint(corners[0], this->location, this->degree),
		ArrowUtility::RotatePoint(corners[1], this->location, this->degree),
		ArrowUtility::RotatePoint(corners[2], this->location, this->degree),
		ArrowUtility::RotatePoint(corners[3], this->location, this->degree)
	};

	return bodys;
}
// ----------------------------------------------------------------------------------------------------

array<PointF>^ Insect::GetLegPoints()
{
	return this->legLocations;
}
// ----------------------------------------------------------------------------------------------------

array<PointF>^ Insect::GetArrowPoints()
{
	array<PointF>^ temp =
	{
		PointF(this->location.X - this->HEIGHT / 2 + 13, this->location.Y),
		PointF(this->location.X - this->HEIGHT / 2 + 33, this->location.Y),
		PointF(this->location.X - this->HEIGHT / 2 + 25, this->location.Y + 6),
		PointF(this->location.X - this->HEIGHT / 2 + 25, this->location.Y - 6),
	};

	array<PointF>^ arrow =
	{
		ArrowUtility::RotatePoint(temp[0], this->location, this->degree),
		ArrowUtility::RotatePoint(temp[1], this->location, this->degree),
		ArrowUtility::RotatePoint(temp[2], this->location, this->degree),
		ArrowUtility::RotatePoint(temp[3], this->location, this->degree)
	};

	return arrow;
}
// ----------------------------------------------------------------------------------------------------

/**
 * シャア
 */
CharInsect::CharInsect(System::Windows::Forms::Control ^canvas, System::Random ^random)
	: Insect(canvas, random)
{
}
// ----------------------------------------------------------------------------------------------------

void CharInsect::CalcSpeed()
{
	this->speed = this->random->Next(40, 50);
}
// ----------------------------------------------------------------------------------------------------

System::Drawing::Color CharInsect::GetColor()
{
	return System::Drawing::Color::Crimson;
}
// ----------------------------------------------------------------------------------------------------
