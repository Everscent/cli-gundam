#pragma once

namespace Anaheim
{
	using namespace System;
	using namespace System::IO;
	using namespace System::Threading;

	/**
	 * 音楽プレイヤー
	 */
	public ref class WavPlayer
	{
	/**
	 * フィールド
	 */
	private:
		array<Byte>^ waveBuffer;
		System::Runtime::InteropServices::GCHandle gcHandle;

	/**
	 * コンストラクタ
	 */
	public:
		WavPlayer();

	/**
	 * メソッド
	 */
	private:
		static void DoWork(Object^ data);

	public:
		/// 再生
		bool Play(Stream^ stream);
		/// 再生（ループ）
		bool PlayLoop(Stream^ stream);
		/// 停止
		bool Stop();
		/// 再生（簡易版）
		static void PlaySimple(Stream^ stream);
	};
	// ----------------------------------------------------------------------------------------------------
}
