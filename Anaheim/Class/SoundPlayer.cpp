#include "StdAfx.h"
#include "SoundPlayer.h"
#include <windows.h>
#include <Mmsystem.h>

using namespace Anaheim;

/**
 * 音楽プレイヤー
 */
SoundPlayer::SoundPlayer()
{
	this->waveBuffer = nullptr;
}
// ----------------------------------------------------------------------------------------------------

void SoundPlayer::DoWork(System::Object ^data)
{
	Stream^ stream = dynamic_cast<Stream^>(data);
	System::Media::SoundPlayer^ player = gcnew System::Media::SoundPlayer(stream);
	player->PlaySync();
}
// ----------------------------------------------------------------------------------------------------

bool SoundPlayer::Play(System::IO::Stream ^stream)
{
	if (this->waveBuffer != nullptr) return false;

	this->waveBuffer = gcnew array<Byte>(static_cast<int>(stream->Length));
	stream->Read(this->waveBuffer, 0, this->waveBuffer->Length);

    // GCによって移動されないようにする
	this->gcHandle = System::Runtime::InteropServices::GCHandle::Alloc(this->waveBuffer, System::Runtime::InteropServices::GCHandleType::Pinned);

    // 非同期再生する
	::PlaySound(static_cast<LPCWSTR>(this->gcHandle.AddrOfPinnedObject().ToPointer()), NULL, SND_MEMORY | SND_ASYNC);
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool SoundPlayer::PlayLoop(System::IO::Stream ^stream)
{
	if (this->waveBuffer != nullptr) return false;

	this->waveBuffer = gcnew array<Byte>(static_cast<int>(stream->Length));
	stream->Read(this->waveBuffer, 0, this->waveBuffer->Length);

    // GCによって移動されないようにする
	this->gcHandle = System::Runtime::InteropServices::GCHandle::Alloc(this->waveBuffer, System::Runtime::InteropServices::GCHandleType::Pinned);

    // 非同期ループ再生する
	::PlaySound(static_cast<LPCWSTR>(this->gcHandle.AddrOfPinnedObject().ToPointer()), NULL, SND_MEMORY | SND_ASYNC | SND_LOOP);
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool SoundPlayer::Stop()
{
	if (this->waveBuffer == nullptr) return false;

	// 再生しているWAVEを停止する
	::PlaySound(NULL, NULL, SND_PURGE);

    // 開放する
    this->gcHandle.Free();
    this->waveBuffer = nullptr;

	return true;
}
// ----------------------------------------------------------------------------------------------------

void SoundPlayer::PlaySimple(System::IO::Stream ^stream)
{
	Thread^ thread = gcnew Thread(gcnew ParameterizedThreadStart(&SoundPlayer::DoWork));
	thread->Start(stream);
}
// ----------------------------------------------------------------------------------------------------
