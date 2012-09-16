#pragma once

#include "IMovable.h"

namespace RX78_2
{
	namespace DirectX
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace System::Windows::Forms;
		using namespace Microsoft::DirectX;
		using namespace Microsoft::DirectX::Direct3D;

		/**
		 * カメラ
		 */
		ref class Camera : public IMovable
		{
		/**
		 * フィールド
		 */
		private:
			float radius;
			float locationTheta;
			float locationPhi;
			float targetY;
			Point oldMouseLocation;

		/**
		 * コンストラクタ
		 */
		public:
			Camera(float radius);

		/**
		 * メソッド
		 */
		public:
			/// マウス移動入力
			void InputMouseMove(Point mouseLocation, MouseButtons button);
			/// マウスホイル入力
			void InputMouseWheel(int delta);
			/// 移動
			virtual void Move(Device^ device);

		/**
		 * プロパティ
		 */
		public:
			/// θ
			property float Theta
			{
				float get() { return this->locationTheta; }
			}
			/// φ
			property float Phi
			{
				float get() { return this->locationPhi; }
			}
			/// R
			property float Radius
			{
				float get() { return this->radius; }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
