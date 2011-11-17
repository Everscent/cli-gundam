#pragma once

namespace RX78_2
{
	namespace Puzzle
	{
		using namespace System;
		using namespace System::Drawing;

		/**
		 * パズルビットマップ
		 */
		ref class PuzzleBitmap
		{
		/**
		 * フィールド
		 */
		private:
			literal int CUT_COUNT_X = 5;
			literal int CUT_COUNT_Y = 5;

			Bitmap^ fileBmp;
			Bitmap^ reverseBmp;
			Bitmap^ resizeFileBmp;
			Bitmap^ resizeReverseBmp;
			Size size;

		/**
		 * コンストラクタ
		 */
		public:
			PuzzleBitmap();

		/**
		 * メソッド
		 */
		private:
			void CreateReverseBmp();

		public:
			/// ファイル読み込み
			bool LoadFile(String^ fileName);
			/// サイズ変更
			void ChangeSize(Size size);
			/// ビットマップ取得（裏/表）
			Bitmap^ GetBitmap(bool isReverse);
			/// ビットマップ（小）取得（裏/表）
			Bitmap^ GetSmallBitmap(Point point, bool isReverse);
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
