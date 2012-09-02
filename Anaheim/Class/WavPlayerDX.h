#pragma once

namespace Anaheim
{
	using namespace System;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace Microsoft::DirectX;
	using namespace Microsoft::DirectX::DirectSound;

	/**
	 * 音楽プレイヤー（DirectX版）
	 */
	public ref class WavPlayerDX
	{
	/**
	 * フィールド
	 */
	private:
		Device^ device;
		SecondaryBuffer^ buffer;

	/**
	 * コンストラクタ
	 */
	public:
		WavPlayerDX(Control^ owner, Stream^ stream);

	/**
	 * メソッド
	 */
	public:
		/// 再生
		void Play();
		/// 再生（ループ）
		void PlayLoop();
		/// 一時停止
		void Pause();
		/// 停止
		void Stop();
	};
	// ----------------------------------------------------------------------------------------------------
}