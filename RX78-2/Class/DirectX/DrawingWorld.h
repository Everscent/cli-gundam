#pragma once

namespace RX78_2
{
	namespace DirectX
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Drawing;
		using namespace System::ComponentModel;
		using namespace System::Collections::Generic;
		using namespace Microsoft::DirectX;
		using namespace Microsoft::DirectX::Direct3D;

		ref class Lighting;
		ref class Camera;
		ref class Floor;
		ref class RandomMovingCube;
		ref class Deruderu;
		ref class DrawingText;
		ref class XYZAxis;
		interface class IMovable;
		interface class IDrawable;

		/**
		 * 描画世界
		 */
		ref class DrawingWorld
		{
		/**
		 * フィールド
		 */
		private:
			Control^ canvas;
			Device^ device;
			BackgroundWorker^ backWorker;

			Lighting^ lighting;
			Camera^ camera;
			Floor^ floor;
			Deruderu^ deruderu;
			DrawingText^ text;
			XYZAxis^ xyzAxis;

			List<IMovable^>^ movingItems;
			List<IDrawable^>^ drawingItems;

		/**
		 * コンストラクタ
		 */
		public:
			DrawingWorld(Control^ canvas, Control^ keyOwner, Control^ mouseOwner);

		/**
		 * メソッド
		 */
		private:
			bool CreateInstance();
			void DoLoopProcess();
			void Move();
			void Draw();
			void ControlKeyDown(Object^ sender, KeyEventArgs^ e);
			void ControlKeyUp(Object^ sender, KeyEventArgs^ e);
			void ControlMouseMove(Object^ sender, MouseEventArgs^ e);
			void ControlMouseWheel(Object^ sender, MouseEventArgs^ e);
			void BackWorkerDoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
			void SetXYZAxisEnabled(bool enabled);

		public:
			/// 初期化
			bool Initialize();
			/// 開放
			void Release();
			/// スタート
			bool Start();
			/// ストップ
			bool Stop();

		/**
		 * プロパティ
		 */
		public:
			/// XYZ軸有効/無効
			property bool XYZAxisEnabled
			{
				void set(bool value) { this->SetXYZAxisEnabled(value); }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
