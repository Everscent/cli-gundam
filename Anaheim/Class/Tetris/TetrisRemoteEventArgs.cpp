#include "StdAfx.h"
#include "TetrisRemoteEventArgs.h"
#include "TetrisField.h"
#include "TetrisMino.h"

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
