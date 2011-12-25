#include "StdAfx.h"
#include "TetrisKey.h"
#include "TetrisModel.h"

using namespace Anaheim;
using namespace Anaheim::Tetris::Controller;

/**
 * テトリスキー（公開用）
 */
PublicTetrisKey::PublicTetrisKey()
{
}
// ----------------------------------------------------------------------------------------------------

/**
 * テトリスキー
 */
TetrisKey::TetrisKey(Anaheim::Tetris::TetrisModel ^model, System::Windows::Forms::Timer ^timer)
{
	this->keysArray = gcnew array<array<Keys>^>(static_cast<int>(ActionType::Max));
	this->model = model;
	this->timer = timer;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisKey::ExecuteCore(Anaheim::Tetris::Controller::TetrisKey::ActionType type)
{
	switch (type)
	{
		case ActionType::MoveDown:
			return this->model->MoveDown();
		case ActionType::MoveLeft:
			return this->model->MoveLeft();
		case ActionType::MoveRight:
			return this->model->MoveRight();
		case ActionType::RotateLeft:
			return this->model->RotateLeft();
		case ActionType::RotateRight:
			return this->model->RotateRight();
		case ActionType::HardDrop:
			this->timer->Stop();
			if (this->model->HardDrop())
			{
				this->timer->Start();
				return true;
			}
			return false;
		default:
			break;
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisKey::IsRegisteredKey(System::Windows::Forms::Keys key)
{
	for each (array<Keys>^ keys in this->keysArray)
	{
		for each (Keys k in keys)
		{
			if (k == key) return true;
		}
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisKey::Execute(System::Windows::Forms::Keys key)
{
	if (!this->timer->Enabled) return false;

	int count = 0;
	for each (array<Keys>^ keys in this->keysArray)
	{
		for each (Keys k in keys)
		{
			if (k == key)
			{
				return this->ExecuteCore(static_cast<ActionType>(count));
			}
		}
		count++;
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------
