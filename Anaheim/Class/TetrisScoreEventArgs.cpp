#include "StdAfx.h"
#include "TetrisScoreEventArgs.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * テトリスリモートイベントArgs
 */
TetrisScoreEventArgs::TetrisScoreEventArgs(Anaheim::Tetris::PublicTetrisScore ^score)
{
	this->score = score;
}
// ----------------------------------------------------------------------------------------------------
