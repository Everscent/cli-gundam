#include "StdAfx.h"
#include "TetrisMino.h"
#include "TetrisField.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * テトリスミノ
 */
TetrisMino::TetrisMino(System::Drawing::Point location, Anaheim::Tetris::TetrisField ^field)
{
	this->location = location;
	this->rotation = Rotation::R1st;
	this->points = gcnew array<Point>(this->BLOCK_COUNT);
	this->field = field;
}
// ----------------------------------------------------------------------------------------------------

array<Point>^ TetrisMino::GetPoints()
{
	array<Point>^ result = gcnew array<Point>(this->BLOCK_COUNT);
	int i = 0;
	for each (Point% p in result)
	{
		p.X = this->location.X + this->points[i].X;
		p.Y = this->location.Y + this->points[i].Y;
		i++;
	}
	return result;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisMino::RotateCore(Anaheim::Tetris::TetrisMino::Rotation oldRotation)
{
	if (this->IsIllegalLocation())
	{
		this->rotation = oldRotation;
		this->RefreshPoints();
		return false;
	}
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisMino::MoveCore(System::Drawing::Point oldPoint)
{
	if (this->IsIllegalLocation())
	{
		this->location = oldPoint;
		return false;
	}
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisMino::IsIllegalLocation()
{
	for each (Point point in this->Points)
	{
		if (point.X < 0 || TetrisField::COL_COUNT <= point.X) return true;
		if (point.Y < 0 || TetrisField::ROW_COUNT <= point.Y) return true;

		if (!this->field->Rows[point.Y]->IsEmpty(point.X))
		{
			return true;
		}
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisMino::RotateRight()
{
	Rotation old = this->rotation;
	switch (this->rotation)
	{
		case Rotation::R1st:
			this->rotation = Rotation::R2nd;
			break;
		case Rotation::R2nd:
			this->rotation = Rotation::R3rd;
			break;
		case Rotation::R3rd:
			this->rotation = Rotation::R4th;
			break;
		case Rotation::R4th:
			this->rotation = Rotation::R1st;
			break;
		default:
			break;
	}
	this->RefreshPoints();

	return this->RotateCore(old);
}
// ----------------------------------------------------------------------------------------------------

bool TetrisMino::RotateLeft()
{
	Rotation old = this->rotation;
	switch (this->rotation)
	{
		case Rotation::R1st:
			this->rotation = Rotation::R4th;
			break;
		case Rotation::R2nd:
			this->rotation = Rotation::R1st;
			break;
		case Rotation::R3rd:
			this->rotation = Rotation::R2nd;
			break;
		case Rotation::R4th:
			this->rotation = Rotation::R3rd;
			break;
		default:
			break;
	}
	this->RefreshPoints();

	return this->RotateCore(old);
}
// ----------------------------------------------------------------------------------------------------

bool TetrisMino::MoveRight()
{
	Point old = this->location;
	this->location.X++;

	return this->MoveCore(old);
}
// ----------------------------------------------------------------------------------------------------

bool TetrisMino::MoveLeft()
{
	Point old = this->location;
	this->location.X--;

	return this->MoveCore(old);
}
// ----------------------------------------------------------------------------------------------------

bool TetrisMino::MoveDown()
{
	Point old = this->location;
	this->location.Y++;

	return this->MoveCore(old);
}
// ----------------------------------------------------------------------------------------------------

bool TetrisMino::MoveTo(Anaheim::Tetris::TetrisMino ^mino)
{
	Point old = this->location;
	this->location = mino->TeleportPoint;

	return this->MoveCore(old);
}
// ----------------------------------------------------------------------------------------------------

TetrisMino^ TetrisMino::CreateGhost()
{
	TetrisMino^ ghost = gcnew GhostTetrisMino(this->location, this->field, this);
	while (ghost->MoveDown());
	return ghost;
}
// ----------------------------------------------------------------------------------------------------

array<Byte>^ TetrisMino::Serialize()
{
	array<Byte>^ bytes = gcnew array<Byte>(this->BYTE_SIZE);
	bytes[0] = this->Color.R;
	bytes[1] = this->Color.G;
	bytes[2] = this->Color.B;
	bytes[3] = static_cast<Byte>(this->rotation);

	System::BitConverter::GetBytes(this->location.X)->CopyTo(bytes, 4);
	System::BitConverter::GetBytes(this->location.Y)->CopyTo(bytes, 8);

	return bytes;
}
// ----------------------------------------------------------------------------------------------------

void TetrisMino::Deserialize(cli::array<unsigned char,1> ^bytes)
{
	this->rotation = static_cast<TetrisMino::Rotation>(bytes[3]);
	this->location.X = System::BitConverter::ToInt32(bytes, 4);
	this->location.Y = System::BitConverter::ToInt32(bytes, 8);
	this->RefreshPoints();
}
// ----------------------------------------------------------------------------------------------------

/**
 * Iテトリスミノ
 */
ITetrisMino::ITetrisMino(System::Drawing::Point location, Anaheim::Tetris::TetrisField ^field)
	: TetrisMino(location, field)
{
	this->RefreshPoints();
}
// ----------------------------------------------------------------------------------------------------

void ITetrisMino::RefreshPoints()
{
	switch (this->rotation)
	{
		case Rotation::R1st:
			this->points[0] = Point(0, 1);
			this->points[1] = Point(1, 1);
			this->points[2] = Point(2, 1);
			this->points[3] = Point(3, 1);
			break;
		case Rotation::R2nd:
			this->points[0] = Point(2, 0);
			this->points[1] = Point(2, 1);
			this->points[2] = Point(2, 2);
			this->points[3] = Point(2, 3);
			break;
		case Rotation::R3rd:
			this->points[0] = Point(0, 2);
			this->points[1] = Point(1, 2);
			this->points[2] = Point(2, 2);
			this->points[3] = Point(3, 2);
			break;
		case Rotation::R4th:
			this->points[0] = Point(1, 0);
			this->points[1] = Point(1, 1);
			this->points[2] = Point(1, 2);
			this->points[3] = Point(1, 3);
			break;
		default:
			break;
	}
}
// ----------------------------------------------------------------------------------------------------

PointF ITetrisMino::AdjustPointForNext(System::Drawing::PointF location, System::Drawing::SizeF size)
{
	return PointF(location.X, location.Y - size.Height / 2);
}
// ----------------------------------------------------------------------------------------------------

/**
 * Jテトリスミノ
 */
JTetrisMino::JTetrisMino(System::Drawing::Point location, Anaheim::Tetris::TetrisField ^field)
	: TetrisMino(location, field)
{
	this->RefreshPoints();
}
// ----------------------------------------------------------------------------------------------------

void JTetrisMino::RefreshPoints()
{
	switch (this->rotation)
	{
		case Rotation::R1st:
			this->points[0] = Point(0, 0);
			this->points[1] = Point(0, 1);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(2, 1);
			break;
		case Rotation::R2nd:
			this->points[0] = Point(2, 0);
			this->points[1] = Point(1, 0);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(1, 2);
			break;
		case Rotation::R3rd:
			this->points[0] = Point(2, 2);
			this->points[1] = Point(2, 1);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(0, 1);
			break;
		case Rotation::R4th:
			this->points[0] = Point(0, 2);
			this->points[1] = Point(1, 2);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(1, 0);
			break;
		default:
			break;
	}
}
// ----------------------------------------------------------------------------------------------------

PointF JTetrisMino::AdjustPointForNext(System::Drawing::PointF location, System::Drawing::SizeF size)
{
	return PointF(location.X + size.Width / 2, location.Y);
}
// ----------------------------------------------------------------------------------------------------

/**
 * Lテトリスミノ
 */
LTetrisMino::LTetrisMino(System::Drawing::Point location, Anaheim::Tetris::TetrisField ^field)
	: TetrisMino(location, field)
{
	this->RefreshPoints();
}
// ----------------------------------------------------------------------------------------------------

void LTetrisMino::RefreshPoints()
{
	switch (this->rotation)
	{
		case Rotation::R1st:
			this->points[0] = Point(2, 0);
			this->points[1] = Point(2, 1);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(0, 1);
			break;
		case Rotation::R2nd:
			this->points[0] = Point(2, 2);
			this->points[1] = Point(1, 2);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(1, 0);
			break;
		case Rotation::R3rd:
			this->points[0] = Point(0, 2);
			this->points[1] = Point(0, 1);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(2, 1);
			break;
		case Rotation::R4th:
			this->points[0] = Point(0, 0);
			this->points[1] = Point(1, 0);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(1, 2);
			break;
		default:
			break;
	}
}
// ----------------------------------------------------------------------------------------------------

PointF LTetrisMino::AdjustPointForNext(System::Drawing::PointF location, System::Drawing::SizeF size)
{
	return PointF(location.X + size.Width / 2, location.Y);
}
// ----------------------------------------------------------------------------------------------------

/**
 * Sテトリスミノ
 */
STetrisMino::STetrisMino(System::Drawing::Point location, Anaheim::Tetris::TetrisField ^field)
	: TetrisMino(location, field)
{
	this->RefreshPoints();
}
// ----------------------------------------------------------------------------------------------------

void STetrisMino::RefreshPoints()
{
	switch (this->rotation)
	{
		case Rotation::R1st:
			this->points[0] = Point(2, 0);
			this->points[1] = Point(1, 0);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(0, 1);
			break;
		case Rotation::R2nd:
			this->points[0] = Point(2, 2);
			this->points[1] = Point(2, 1);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(1, 0);
			break;
		case Rotation::R3rd:
			this->points[0] = Point(0, 2);
			this->points[1] = Point(1, 2);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(2, 1);
			break;
		case Rotation::R4th:
			this->points[0] = Point(0, 0);
			this->points[1] = Point(0, 1);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(1, 2);
			break;
		default:
			break;
	}
}
// ----------------------------------------------------------------------------------------------------

PointF STetrisMino::AdjustPointForNext(System::Drawing::PointF location, System::Drawing::SizeF size)
{
	return PointF(location.X + size.Width / 2, location.Y);
}
// ----------------------------------------------------------------------------------------------------

/**
 * Zテトリスミノ
 */
ZTetrisMino::ZTetrisMino(System::Drawing::Point location, Anaheim::Tetris::TetrisField ^field)
	: TetrisMino(location, field)
{
	this->RefreshPoints();
}
// ----------------------------------------------------------------------------------------------------

void ZTetrisMino::RefreshPoints()
{
	switch (this->rotation)
	{
		case Rotation::R1st:
			this->points[0] = Point(0, 0);
			this->points[1] = Point(1, 0);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(2, 1);
			break;
		case Rotation::R2nd:
			this->points[0] = Point(2, 0);
			this->points[1] = Point(2, 1);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(1, 2);
			break;
		case Rotation::R3rd:
			this->points[0] = Point(2, 2);
			this->points[1] = Point(1, 2);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(0, 1);
			break;
		case Rotation::R4th:
			this->points[0] = Point(0, 2);
			this->points[1] = Point(0, 1);
			this->points[2] = Point(1, 1);
			this->points[3] = Point(1, 0);
			break;
		default:
			break;
	}
}
// ----------------------------------------------------------------------------------------------------

PointF ZTetrisMino::AdjustPointForNext(System::Drawing::PointF location, System::Drawing::SizeF size)
{
	return PointF(location.X + size.Width / 2, location.Y);
}
// ----------------------------------------------------------------------------------------------------

/**
 * Tテトリスミノ
 */
TTetrisMino::TTetrisMino(System::Drawing::Point location, Anaheim::Tetris::TetrisField ^field)
	: TetrisMino(location, field)
{
	this->RefreshPoints();
}
// ----------------------------------------------------------------------------------------------------

void TTetrisMino::RefreshPoints()
{
	switch (this->rotation)
	{
		case Rotation::R1st:
			this->points[0] = Point(0, 1);
			this->points[1] = Point(1, 1);
			this->points[2] = Point(2, 1);
			this->points[3] = Point(1, 0);
			break;
		case Rotation::R2nd:
			this->points[0] = Point(1, 0);
			this->points[1] = Point(1, 1);
			this->points[2] = Point(1, 2);
			this->points[3] = Point(2, 1);
			break;
		case Rotation::R3rd:
			this->points[0] = Point(2, 1);
			this->points[1] = Point(1, 1);
			this->points[2] = Point(0, 1);
			this->points[3] = Point(1, 2);
			break;
		case Rotation::R4th:
			this->points[0] = Point(1, 2);
			this->points[1] = Point(1, 1);
			this->points[2] = Point(1, 0);
			this->points[3] = Point(0, 1);
			break;
		default:
			break;
	}
}
// ----------------------------------------------------------------------------------------------------

PointF TTetrisMino::AdjustPointForNext(System::Drawing::PointF location, System::Drawing::SizeF size)
{
	return PointF(location.X + size.Width / 2, location.Y);
}
// ----------------------------------------------------------------------------------------------------

/**
 * Oテトリスミノ
 */
OTetrisMino::OTetrisMino(System::Drawing::Point location, Anaheim::Tetris::TetrisField ^field)
	: TetrisMino(location, field)
{
	this->RefreshPoints();
}
// ----------------------------------------------------------------------------------------------------

void OTetrisMino::RefreshPoints()
{
	this->points[0] = Point(1, 0);
	this->points[1] = Point(1, 1);
	this->points[2] = Point(2, 0);
	this->points[3] = Point(2, 1);
}
// ----------------------------------------------------------------------------------------------------

PointF OTetrisMino::AdjustPointForNext(System::Drawing::PointF location, System::Drawing::SizeF size)
{
	return location;
}
// ----------------------------------------------------------------------------------------------------

/**
 * ゴーストテトリスミノ
 */
GhostTetrisMino::GhostTetrisMino(System::Drawing::Point location, Anaheim::Tetris::TetrisField ^field, Anaheim::Tetris::TetrisMino ^master)
	: TetrisMino(location, field)
{
	this->master = master;
	this->RefreshPoints();
}
// ----------------------------------------------------------------------------------------------------

void GhostTetrisMino::RefreshPoints()
{
	this->master->RelativePoints->CopyTo(this->points, 0);
}
// ----------------------------------------------------------------------------------------------------

System::Drawing::Color GhostTetrisMino::GetColor()
{
	System::Drawing::Color color = this->master->Color;
	int alpha = (color == JTetrisMino::COLOR) ? 98 : 64;
	return System::Drawing::Color::FromArgb(alpha, color);
}
// ----------------------------------------------------------------------------------------------------

bool GhostTetrisMino::RotateRight()
{
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool GhostTetrisMino::RotateLeft()
{
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool GhostTetrisMino::MoveRight()
{
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool GhostTetrisMino::MoveLeft()
{
	return false;
}
// ----------------------------------------------------------------------------------------------------

PointF GhostTetrisMino::AdjustPointForNext(System::Drawing::PointF location, System::Drawing::SizeF size)
{
	return this->master->AdjustPointForNext(location, size);
}
// ----------------------------------------------------------------------------------------------------
