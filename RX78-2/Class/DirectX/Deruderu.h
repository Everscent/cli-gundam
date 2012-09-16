#pragma once

#include "IMovable.h"
#include "IDrawable.h"

namespace RX78_2
{
	namespace DirectX
	{
		using namespace System;
		using namespace System::IO;
		using namespace System::Drawing;
		using namespace System::Collections::Generic;
		using namespace System::Windows::Forms;
		using namespace Microsoft::DirectX;
		using namespace Microsoft::DirectX::Direct3D;

		/**
		 * ランダム移動キューブ
		 */
		ref class Deruderu : public IMovable, IDrawable
		{
		/**
		 * フィールド
		 */
		private:
			initonly Material shadowMaterial;
			initonly float initHeight;

			Mesh^ mesh;
			array<ExtendedMaterial>^ materials;
			array<Texture^>^ textures;
			Vector3 scale;
			Vector3 location;
			float rotate;
			float heightAngle;
			List<Keys>^ keys;

		/**
		 * コンストラクタ
		 */
		public:
			Deruderu(Device^ device);

		/**
		 * メソッド
		 */
		public:
			/// 初期化
			bool Initialize(Device^ device);
			/// キーダウン入力
			void InputKeyDown(Keys key);
			/// キーアップ入力
			void InputKeyUp(Keys key);
			/// 移動
			virtual void Move(Device^ device);
			/// 描画
			virtual void Draw(Device^ device);
			/// 影描画
			virtual void DrawShadow(Device^ device, Vector3 lightingLocation, Plane plane);

		/**
		 * プロパティ
		 */
		public:
			/// 位置
			property Vector3 Location
			{
				Vector3 get() { return this->location; }
			}
			/// 回転
			property float Rotate
			{
				float get() { return this->rotate; }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
