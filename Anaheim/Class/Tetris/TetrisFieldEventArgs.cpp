#include "StdAfx.h"
#include "TetrisFieldEventArgs.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * テトリスフィールドイベントArgs
 */
TetrisFieldEventArgs::TetrisFieldEventArgs(Anaheim::Tetris::Model::TetrisField ^field)
{
	this->field = field;
}
// ----------------------------------------------------------------------------------------------------
