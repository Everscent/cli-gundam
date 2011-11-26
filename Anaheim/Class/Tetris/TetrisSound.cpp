#include "StdAfx.h"
#include "TetrisSound.h"
#include "SoundPlayer.h"

using namespace Anaheim;
using namespace Anaheim::Tetris;

/**
 * テトリス音楽
 */
TetrisSound::TetrisSound()
{
	this->player = gcnew SoundPlayer();
	this->isON = false;
}
// ----------------------------------------------------------------------------------------------------

void TetrisSound::SetSoundON(bool isON)
{
	if (!isON)
	{
		this->StopMainSound();
	}
	this->isON = isON;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisSound::PlayMainSound()
{
	if(!this->isON) return false;

	System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
	System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager("Anaheim.Anaheim", assembly);
	Stream^ stream = safe_cast<System::IO::Stream^>(resources->GetObject(L"TetrisMain"));
	return this->player->PlayLoop(stream);
}
// ----------------------------------------------------------------------------------------------------

bool TetrisSound::StopMainSound()
{
	return this->player->Stop();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisSound::PlayGameOverSound()
{
	if(!this->isON) return false;

	System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
	System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager("Anaheim.Anaheim", assembly);
	Stream^ stream = safe_cast<System::IO::Stream^>(resources->GetObject(L"TetrisGameOver"));
	SoundPlayer::PlaySimple(stream);
	return true;
}
// ----------------------------------------------------------------------------------------------------
