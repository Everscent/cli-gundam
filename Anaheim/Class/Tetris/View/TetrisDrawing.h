#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			ref class TetrisField;
			ref class TetrisMino;
			ref class GhostTetrisMino;
		}

		namespace View
		{
			using namespace System;
			using namespace System::Drawing;
			using namespace System::Windows::Forms;
			using namespace System::Collections::Generic;
			using namespace Model;

			interface class ITetrisDrawAPI;

			/**
			 * テトリス描画
			 */
			ref class TetrisDrawing abstract
			{
			/**
			 * フィールド
			 */
			protected:
				Control^ canvas;
				ITetrisDrawAPI^ api;

			/**
			 * コンストラクタ
			 */
			public:
				TetrisDrawing(Control^ canvas, ITetrisDrawAPI^ api);

			/**
			 * メソッド
			 */
			protected:
				/// ブロックサイズ取得
				virtual SizeF GetBlockSize() abstract;
				/// 描画
				virtual void DrawCore(TetrisMino^ mino) abstract;

				PointF GetBlockLocation(Point point, SizeF blockSize);
				void DrawBlock(PointF location, SizeF size, Color color);

			public:
				///　描画
				void Draw(TetrisMino^ mino);
				/// クリア
				void Clear();
				/// キャンバスコントロールの一致判定
				bool IsMyCanvas(Control^ canvas);
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * メイン描画
			 */
			ref class MainTetrisDrawing : public TetrisDrawing
			{
			/**
			 * フィールド
			 */
			private:
				TetrisField^ field;

			/**
			 * コンストラクタ
			 */
			public:
				MainTetrisDrawing(Control^ canvas, ITetrisDrawAPI^ api, TetrisField^ field);

			/**
			 * メソッド
			 */
			private:
				void DrawRemoveBlock(PointF location, SizeF size);
				void DrawMino(TetrisMino^ mino);
				void DrawGhostMino(GhostTetrisMino^ mino);

			protected:
				/// ブロックサイズ取得
				virtual SizeF GetBlockSize() override;
				///　描画
				virtual void DrawCore(TetrisMino^ mino) override;

			/**
			 * プロパティ
			 */
			public:
				/// フィールド
				property TetrisField^ Field
				{
					void set(TetrisField^ value) { this->field = value; }
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * ネクスト描画
			 */
			ref class NextTetrisDrawing : public TetrisDrawing
			{
			/**
			 * コンストラクタ
			 */
			public:
				NextTetrisDrawing(Control^ canvas, ITetrisDrawAPI^ api);

			/**
			 * メソッド
			 */
			protected:
				/// ブロックサイズ取得
				virtual SizeF GetBlockSize() override;
				///　描画
				virtual void DrawCore(TetrisMino^ mino) override;
			};
			// ----------------------------------------------------------------------------------------------------
		}
	}
}
