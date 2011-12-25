#include "StdAfx.h"
#include "TetrisRemoteEventArgs.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * テトリスリモートイベントArgs
 */
TetrisRemoteEventArgs::TetrisRemoteEventArgs(TetrisField ^field, TetrisMino ^mino)
{
	this->field = field;
	this->mino = mino;
}
// ----------------------------------------------------------------------------------------------------
