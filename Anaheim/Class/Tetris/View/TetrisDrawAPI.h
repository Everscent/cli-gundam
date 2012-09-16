#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		namespace View
		{
			using namespace System;
			using namespace System::Drawing;
			using namespace System::Drawing::Drawing2D;
			using namespace System::Windows::Forms;

			/**
			 * テトリス描画APIインターフェイス
			 */
			interface class ITetrisDrawAPI
			{
			/**
			 * メソッド
			 */
			public:
				/// 描画開始
				virtual void BeginDraw() abstract;
				/// 直線描画
				virtual void DrawLine(Color color, float width, PointF point1, PointF point2) abstract;
				/// 四角形描画
				virtual void DrawRectangle(Color color, float width, PointF point, SizeF size) abstract;
				/// 四角形塗りつぶし
				virtual void FillRectangle(Color color, PointF point, SizeF size) abstract;
				/// 四角形塗りつぶし（グラデーション）
				virtual void FillRectangleGradation(Color color1, Color color2, PointF point, SizeF size) abstract;
				/// 描画終了
				virtual void EndDraw() abstract;
				/// クリア
				virtual void Clear() abstract;
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * テトリス描画API
			 */
			ref class GraphicsTetrisDrawAPI : public ITetrisDrawAPI
			{
			/**
			 * フィールド
			 */
			private:
				Control^ canvas;
				Bitmap^ bitmap;		// ダブルバッファリング
				Graphics^ graphics;

			/**
			 * コンストラクタ
			 */
			public:
				GraphicsTetrisDrawAPI(Control^ canvas);

			/**
			 * メソッド
			 */
			private:
				void CanvasResize(System::Object^ sender, System::EventArgs^ e);
				void Clear(Graphics^ graphics);

			public:
				/// 描画開始
				virtual void BeginDraw();
				/// 直線描画
				virtual void DrawLine(Color color, float width, PointF point1, PointF point2);
				/// 四角形描画
				virtual void DrawRectangle(Color color, float width, PointF point, SizeF size);
				/// 四角形塗りつぶし
				virtual void FillRectangle(Color color, PointF point, SizeF size);
				/// 四角形塗りつぶし（グラデーション）
				virtual void FillRectangleGradation(Color color1, Color color2, PointF point, SizeF size);
				/// 描画終了
				virtual void EndDraw();
				/// クリア
				virtual void Clear();
			};
			// ----------------------------------------------------------------------------------------------------
		}
	}
}
