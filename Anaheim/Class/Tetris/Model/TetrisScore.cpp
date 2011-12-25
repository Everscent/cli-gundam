#include "StdAfx.h"
#include "TetrisScore.h"

using namespace Anaheim;
using namespace Anaheim::Tetris::Model;

/**
 * テトリス スコア（公開用）
 */
PublicTetrisScore::PublicTetrisScore()
{
}
// ----------------------------------------------------------------------------------------------------

/**
 * テトリス スコア
 */
TetrisScore::TetrisScore()
{
	this->Clear();
}
// ----------------------------------------------------------------------------------------------------

void TetrisScore::Clear()
{
	this->score = 0;
	this->singleCount = 0;
	this->doubleCount = 0;
	this->tripleCount = 0;
	this->tetrisCount = 0;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisScore::UpdateScore(int removeCount, bool isPerfect)
{
	int score = 0;
	switch (removeCount)
	{
		case 1:
			this->singleCount++;
			score = static_cast<int>(System::Math::Pow(2, 0)) * 100;
			break;
		case 2:
			this->doubleCount++;
			score = static_cast<int>(System::Math::Pow(2, 1)) * 100;
			break;
		case 3:
			this->tripleCount++;
			score = static_cast<int>(System::Math::Pow(2, 2)) * 100;
			break;
		case 4:
			this->tetrisCount++;
			score = static_cast<int>(System::Math::Pow(2, 3)) * 100;
			break;
		default:
			return false;
	}

	if (isPerfect)
	{
		score *= 10;
	}
	this->score += score;

	return true;
}
// ----------------------------------------------------------------------------------------------------
