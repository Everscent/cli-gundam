#include "StdAfx.h"
#include "TetrisField.h"
#include "TetrisMino.h"

using namespace Anaheim;
using namespace Anaheim::Tetris::Model;

/**
 * テトリス フィールド行
 */
TetrisFieldRow::TetrisFieldRow(int count)
{
	this->colors = gcnew array<Color>(count);
	this->Clear();
}
// ----------------------------------------------------------------------------------------------------

void TetrisFieldRow::Clear()
{
	for each (Color% color in this->colors)
	{
		color = Color::Empty;
	}
}
// ----------------------------------------------------------------------------------------------------

bool TetrisFieldRow::IsComplete()
{
	for each (Color color in this->colors)
	{
		if (color.Equals(Color::Empty))
		{
			return false;
		}
	}
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisFieldRow::IsEmpty()
{
	for each (Color color in this->colors)
	{
		if (!color.Equals(Color::Empty))
		{
			return false;
		}
	}
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisFieldRow::IsEmpty(int col)
{
	if (this->colors->Length <= col) return false;

	return (this->colors[col].Equals(Color::Empty)) ? true : false;
}
// ----------------------------------------------------------------------------------------------------

array<Byte>^ TetrisFieldRow::Serialize()
{
	array<Byte>^ bytes = gcnew array<Byte>(this->colors->Length * 3);
	int index = 0;
	for each (Color color in this->colors)
	{
		bytes[index] = color.R;
		index++;
		bytes[index] = color.G;
		index++;
		bytes[index] = color.B;
		index++;
	}
	return bytes;
}
// ----------------------------------------------------------------------------------------------------

void TetrisFieldRow::Deserialize(cli::array<unsigned char,1> ^bytes)
{
	int index = 0;
	for each (Color% color in this->colors)
	{
		Byte r = bytes[index];
		index++;
		Byte g = bytes[index];
		index++;
		Byte b = bytes[index];
		index++;

		if (r == 0 && g == 0 && b == 0)
		{
			color = Color::Empty;
		}
		else
		{
			color = Color::FromArgb(r, g, b);
		}
	}
}
// ----------------------------------------------------------------------------------------------------

/**
 * テトリス フィールド
 */
TetrisField::TetrisField()
{
	this->rows = gcnew List<TetrisFieldRow^>;
	for (int i = 0; i < this->ROW_COUNT; i++)
	{
		this->rows->Add(gcnew TetrisFieldRow(this->COL_COUNT));
	}
}
// ----------------------------------------------------------------------------------------------------

bool TetrisField::IsEmptyRows()
{
	for each (TetrisFieldRow^ row in this->rows)
	{
		if (!row->IsEmpty())
		{
			return false;
		}
	}
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisField::RemoveCompleteRowsMatch(Anaheim::Tetris::Model::TetrisFieldRow ^row)
{
	if (row->IsComplete())
	{
		return true;
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

void TetrisField::Clear()
{
	for each (TetrisFieldRow^ row in this->rows)
	{
		row->Clear();
	}
}
// ----------------------------------------------------------------------------------------------------

void TetrisField::SetMino(Anaheim::Tetris::Model::TetrisMino ^mino)
{
	for each (Point point in mino->Points)
	{
		this->rows[point.Y]->Colors[point.X] = mino->Color;
	}
}
// ----------------------------------------------------------------------------------------------------

bool TetrisField::ExistsCompleteRow()
{
	for each (TetrisFieldRow^ row in this->rows)
	{
		if (row->IsComplete())
		{
			return true;
		}
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

int TetrisField::RemoveCompleteRows()
{
	this->rows->RemoveAll(gcnew Predicate<TetrisFieldRow^>(this, &TetrisField::RemoveCompleteRowsMatch));

	int removeCount = TetrisField::ROW_COUNT - this->rows->Count;

	for (int i = 0; i < removeCount; i++)
	{
		this->rows->Insert(0, gcnew TetrisFieldRow(this->COL_COUNT));
	}

	return removeCount;
}
// ----------------------------------------------------------------------------------------------------

array<Byte>^ TetrisField::Serialize()
{
	int length = this->BYTE_SIZE;
	array<Byte>^ bytes = gcnew array<Byte>(length);
	int index = 0;
	for each (TetrisFieldRow^ row in this->rows)
	{
		array<Byte>^ b = row->Serialize();
		b->CopyTo(bytes, index);
		index += b->Length;
	}
	return bytes;
}
// ----------------------------------------------------------------------------------------------------

void TetrisField::Deserialize(cli::array<unsigned char,1> ^bytes)
{
	array<Byte>^ b = gcnew array<Byte>(this->COL_COUNT * 3);
	int index = 0;
	for each (TetrisFieldRow^ row in this->rows)
	{
		Array::Copy(bytes, index, b, 0, b->Length);
		row->Deserialize(b);
		index += b->Length;
	}
}
// ----------------------------------------------------------------------------------------------------
