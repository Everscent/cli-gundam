#include "StdAfx.h"
#include "WavPlayerDX.h"

using namespace Anaheim;

/**
 * 音楽プレイヤー（DirectX版）
 */
WavPlayerDX::WavPlayerDX(System::Windows::Forms::Control ^owner, System::IO::Stream ^stream)
{
	this->device = gcnew Device();
	this->device->SetCooperativeLevel(owner, CooperativeLevel::Priority);
	this->buffer = gcnew SecondaryBuffer(stream, this->device);
}
// ----------------------------------------------------------------------------------------------------

void WavPlayerDX::Play()
{
	this->buffer->Play(0, BufferPlayFlags::Default);
}
// ----------------------------------------------------------------------------------------------------

void WavPlayerDX::PlayLoop()
{
	this->buffer->Play(0, BufferPlayFlags::Looping);
}
// ----------------------------------------------------------------------------------------------------

void WavPlayerDX::Pause()
{
	this->buffer->Stop();
}
// ----------------------------------------------------------------------------------------------------

void WavPlayerDX::Stop()
{
	this->buffer->Stop();
	this->buffer->SetCurrentPosition(0);
}
// ----------------------------------------------------------------------------------------------------
