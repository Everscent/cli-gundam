#pragma once

namespace Anaheim
{
	using namespace System;

	/**
	 * �V���A���C�Y �C���^�[�t�F�C�X
	 */
	interface class ISerializable
	{
	/**
	 * ���\�b�h
	 */
	public:
		/// �V���A���C�Y
		virtual array<Byte>^ Serialize();
		/// �f�V���A���C�Y
		virtual void Deserialize(array<Byte>^ bytes);
	};
	// ----------------------------------------------------------------------------------------------------
}
