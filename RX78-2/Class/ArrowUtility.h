#pragma once

namespace RX78_2
{
	namespace Arrow
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace System::Windows::Forms;

		/**
		 * Arrowユーティリティ
		 */
		ref class ArrowUtility abstract sealed
		{
		/**
		 * メソッド
		 */
		public:
			/// マウスカーソル位置取得（キャンバスの座標系）
			static Point GetMousePoint(Control^ canvas);
			/// 0～360°に変換
			static double ConvertDegree(double degree);
			/// ポイント間の角度
			static double GetAngle(PointF point1, PointF point2);
			/// 中間角度取得
			static double GetHalfAngle(double degree1, double degree2);
			/// 座標回転
			static PointF RotatePoint(PointF point, PointF center, double degree);
			/// 座標移動
			static PointF MovePoint(PointF point, int distance, double degree);
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
