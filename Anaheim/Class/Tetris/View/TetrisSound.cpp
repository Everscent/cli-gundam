#include "StdAfx.h"
#include "TetrisSound.h"
#include "WavPlayerDX.h"

using namespace Anaheim;
using namespace Anaheim::Tetris::View;

/**
 * テトリス音楽
 */
TetrisSound::TetrisSound(System::Windows::Forms::Control ^owner)
{
	System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
	System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager("Anaheim.Anaheim", assembly);
	
	Stream^ bgmStream = safe_cast<System::IO::Stream^>(resources->GetObject(L"TetrisBGM"));
	this->bgmPlayer = gcnew WavPlayerDX(owner, bgmStream);

	Stream^ gameoverStream = safe_cast<System::IO::Stream^>(resources->GetObject(L"TetrisGameOver"));
	this->gameoverPlayer = gcnew WavPlayerDX(owner, gameoverStream);

	Stream^ removeStream = safe_cast<System::IO::Stream^>(resources->GetObject(L"TetrisRemove"));
	this->removePlayer = gcnew WavPlayerDX(owner, removeStream);

	Stream^ enddownStream = safe_cast<System::IO::Stream^>(resources->GetObject(L"TetrisEndDown"));
	this->enddownPlayer = gcnew WavPlayerDX(owner, enddownStream);

	this->isON = false;
}
// ----------------------------------------------------------------------------------------------------

void TetrisSound::SetSoundON(bool isON)
{
	if (!isON)
	{
		this->StopBGM();
	}
	this->isON = isON;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisSound::PlayBGM()
{
	if (!this->isON) return false;

	this->bgmPlayer->PlayLoop();
	return true;
}
// ----------------------------------------------------------------------------------------------------

void TetrisSound::PauseBGM()
{
	this->bgmPlayer->Pause();
}
// ----------------------------------------------------------------------------------------------------

void TetrisSound::StopBGM()
{
	this->bgmPlayer->Stop();
}
// ----------------------------------------------------------------------------------------------------

bool TetrisSound::PlayGameOverSound()
{
	if (!this->isON) return false;

	this->gameoverPlayer->Stop();
	this->gameoverPlayer->Play();
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisSound::PlayRemoveSound()
{
	if (!this->isON) return false;

	this->removePlayer->Stop();
	this->removePlayer->Play();
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool TetrisSound::PlayEndDownSound()
{
	if (!this->isON) return false;

	this->enddownPlayer->Stop();
	this->enddownPlayer->Play();
	return true;
}
// ----------------------------------------------------------------------------------------------------
