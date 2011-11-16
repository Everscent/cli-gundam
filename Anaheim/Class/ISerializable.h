#pragma once

namespace Anaheim
{
	using namespace System;

	/**
	 * シリアライズ インターフェイス
	 */
	interface class ISerializable
	{
	/**
	 * メソッド
	 */
	public:
		/// シリアライズ
		virtual array<Byte>^ Serialize();
		/// デシリアライズ
		virtual void Deserialize(array<Byte>^ bytes);
	};
	// ----------------------------------------------------------------------------------------------------
}
