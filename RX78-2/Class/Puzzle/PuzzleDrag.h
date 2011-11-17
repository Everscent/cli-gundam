#pragma once

namespace RX78_2
{
	namespace Puzzle
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace System::Windows::Forms;

		/**
		 * パズルドラッグクラス
		 */
		ref class PuzzleDrag
		{
		/**
		 * enum class
		 */
		public:
			enum class Direction
			{
				Up,
				Down,
				Left,
				Right,
				Non,
			};

		/**
		 * フィールド
		 */
		private:
			Control^ dragObject;
			Point clickPoint;
			Direction direction;

			Point startPoint;
			Point endPoint;

		/**
		 * コンストラクタ
		 */
		public:
			PuzzleDrag();

		/**
		 * メソッド
		 */
		private:
			void Clear();

		public:
			/// ドラッグ開始
			void Begin(Control^ dragObject, Point clickPoint, Direction direction);
			/// ドラッグ
			void Move(Point mousePoint);
			/// ドラッグ終了
			bool End();
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
