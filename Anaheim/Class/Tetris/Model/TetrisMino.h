#pragma once

#include "ISerializable.h"

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			using namespace System;
			using namespace System::Drawing;

			ref class TetrisField;
			ref class GhostTetrisMino;

			/**
			 * テトリスミノ
			 */
			public ref class TetrisMino abstract : public ISerializable
			{
			/**
			 * enum class
			 */
			protected:
				enum class Rotation : Byte
				{
					R1st,
					R2nd,
					R3rd,
					R4th
				};

			/**
			 * フィールド
			 */
			protected:
				Point location;
				Rotation rotation;
				array<Point>^ points;

				TetrisField^ field;

			public:
				/// ブロック数
				literal int BLOCK_COUNT = 4;
				/// 横方向サイズ
				literal int HORI_COUNT = 4;
				/// 縦方向サイズ
				literal int VERT_COUNT = 2;
				/// バイトサイズ
				literal int BYTE_SIZE = 12;

			/**
			 * コンストラクタ
			 */
			public:
				TetrisMino(Point location, TetrisField^ field);

			/**
			 * メソッド
			 */
			protected:
				virtual void RefreshPoints() abstract;
				virtual array<Point>^ GetPoints();
				bool RotateCore(Rotation oldRotation);
				bool MoveCore(Point oldPoint);

			public:
				/// 不正位置チェック
				bool IsIllegalLocation();
				/// 右回転
				virtual bool RotateRight();
				/// 左回転
				virtual bool RotateLeft();
				/// 右移動
				virtual bool MoveRight();
				/// 左移動
				virtual bool MoveLeft();
				/// 下移動
				virtual bool MoveDown();
				/// 他ミノの位置へ移動
				bool MoveTo(TetrisMino^ mino);
				/// ゴースト作成
				GhostTetrisMino^ CreateGhost();
				/// Next表示用ブロック位置調整
				virtual PointF AdjustPointForNext(PointF location, SizeF size) abstract;
				/// シリアライズ
				virtual array<Byte>^ Serialize();
				/// デシリアライズ
				virtual void Deserialize(array<Byte>^ bytes);

			/**
			 * プロパティ
			 */
			public:
				/// ミノ位置取得
				property array<Point>^ Points
				{
					array<Point>^ get() { return this->GetPoints(); }
				}
				/// 相対ミノ位置取得
				property array<Point>^ RelativePoints
				{
					array<Point>^ get() { return this->points; }
				}
				/// テレポート位置
				property Point TeleportPoint
				{
					Point get() { return this->location; }
				}
				/// 色
				property System::Drawing::Color Color
				{
					virtual System::Drawing::Color get() abstract;
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * Iテトリスミノ
			 */
			ref class ITetrisMino : public TetrisMino
			{
			/**
			 * フィールド
			 */
			public:
				static initonly System::Drawing::Color COLOR = System::Drawing::Color::Aqua;

			/**
			 * コンストラクタ
			 */
			public:
				ITetrisMino(Point location, TetrisField^ field);

			/**
			 * メソッド
			 */
			protected:
				virtual void RefreshPoints() override;

			public:
				/// Next表示用ブロック位置調整
				virtual PointF AdjustPointForNext(PointF location, SizeF size) override;

			/**
			 * プロパティ
			 */
			public:
				/// 色
				property System::Drawing::Color Color
				{
					virtual System::Drawing::Color get() override { return this->COLOR; }
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * Jテトリスミノ
			 */
			ref class JTetrisMino : public TetrisMino
			{
			/**
			 * フィールド
			 */
			public:
				static initonly System::Drawing::Color COLOR = System::Drawing::Color::Blue;

			/**
			 * コンストラクタ
			 */
			public:
				JTetrisMino(Point location, TetrisField^ field);

			/**
			 * メソッド
			 */
			protected:
				virtual void RefreshPoints() override;

			public:
				/// Next表示用ブロック位置調整
				virtual PointF AdjustPointForNext(PointF location, SizeF size) override;

			/**
			 * プロパティ
			 */
			public:
				/// 色
				property System::Drawing::Color Color
				{
					virtual System::Drawing::Color get() override { return this->COLOR; }
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * Lテトリスミノ
			 */
			ref class LTetrisMino : public TetrisMino
			{
			/**
			 * フィールド
			 */
			public:
				static initonly System::Drawing::Color COLOR = System::Drawing::Color::Orange;

			/**
			 * コンストラクタ
			 */
			public:
				LTetrisMino(Point location, TetrisField^ field);

			/**
			 * メソッド
			 */
			protected:
				virtual void RefreshPoints() override;

			public:
				/// Next表示用ブロック位置調整
				virtual PointF AdjustPointForNext(PointF location, SizeF size) override;

			/**
			 * プロパティ
			 */
			public:
				/// 色
				property System::Drawing::Color Color
				{
					virtual System::Drawing::Color get() override { return this->COLOR; }
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * Sテトリスミノ
			 */
			ref class STetrisMino : public TetrisMino
			{
			/**
			 * フィールド
			 */
			public:
				static initonly System::Drawing::Color COLOR = System::Drawing::Color::Lime;

			/**
			 * コンストラクタ
			 */
			public:
				STetrisMino(Point location, TetrisField^ field);

			/**
			 * メソッド
			 */
			protected:
				virtual void RefreshPoints() override;

			public:
				/// Next表示用ブロック位置調整
				virtual PointF AdjustPointForNext(PointF location, SizeF size) override;

			/**
			 * プロパティ
			 */
			public:
				/// 色
				property System::Drawing::Color Color
				{
					virtual System::Drawing::Color get() override { return this->COLOR; }
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * Zテトリスミノ
			 */
			ref class ZTetrisMino : public TetrisMino
			{
			/**
			 * フィールド
			 */
			public:
				static initonly System::Drawing::Color COLOR = System::Drawing::Color::Red;

			/**
			 * コンストラクタ
			 */
			public:
				ZTetrisMino(Point location, TetrisField^ field);

			/**
			 * メソッド
			 */
			protected:
				virtual void RefreshPoints() override;

			public:
				/// Next表示用ブロック位置調整
				virtual PointF AdjustPointForNext(PointF location, SizeF size) override;

			/**
			 * プロパティ
			 */
			public:
				/// 色
				property System::Drawing::Color Color
				{
					virtual System::Drawing::Color get() override { return this->COLOR; }
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * Tテトリスミノ
			 */
			ref class TTetrisMino : public TetrisMino
			{
			/**
			 * フィールド
			 */
			public:
				static initonly System::Drawing::Color COLOR = System::Drawing::Color::Fuchsia;

			/**
			 * コンストラクタ
			 */
			public:
				TTetrisMino(Point location, TetrisField^ field);

			/**
			 * メソッド
			 */
			protected:
				virtual void RefreshPoints() override;

			public:
				/// Next表示用ブロック位置調整
				virtual PointF AdjustPointForNext(PointF location, SizeF size) override;

			/**
			 * プロパティ
			 */
			public:
				/// 色
				property System::Drawing::Color Color
				{
					virtual System::Drawing::Color get() override { return this->COLOR; }
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * Oテトリスミノ
			 */
			ref class OTetrisMino : public TetrisMino
			{
			/**
			 * フィールド
			 */
			public:
				static initonly System::Drawing::Color COLOR = System::Drawing::Color::Yellow;

			/**
			 * コンストラクタ
			 */
			public:
				OTetrisMino(Point location, TetrisField^ field);

			/**
			 * メソッド
			 */
			protected:
				virtual void RefreshPoints() override;

			public:
				/// Next表示用ブロック位置調整
				virtual PointF AdjustPointForNext(PointF location, SizeF size) override;

			/**
			 * プロパティ
			 */
			public:
				/// 色
				property System::Drawing::Color Color
				{
					virtual System::Drawing::Color get() override { return this->COLOR; }
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * ゴーストテトリスミノ
			 */
			ref class GhostTetrisMino : public TetrisMino
			{
			/**
			 * フィールド
			 */
			private:
				TetrisMino^ master;

			/**
			 * コンストラクタ
			 */
			public:
				GhostTetrisMino(Point location, TetrisField^ field, TetrisMino^ master);

			/**
			 * メソッド
			 */
			protected:
				virtual void RefreshPoints() override;
				System::Drawing::Color GetColor();
				System::Drawing::Color GetBrightBorderColor();
				System::Drawing::Color GetDarkBorderColor();

			public:
				/// 右回転
				virtual bool RotateRight() override;
				/// 左回転
				virtual bool RotateLeft() override;
				/// 右移動
				virtual bool MoveRight() override;
				/// 左移動
				virtual bool MoveLeft() override;
				/// Next表示用ブロック位置調整
				virtual PointF AdjustPointForNext(PointF location, SizeF size) override;

			/**
			 * プロパティ
			 */
			public:
				/// 色
				property System::Drawing::Color Color
				{
					virtual System::Drawing::Color get() override { return this->GetColor(); }
				}
				/// 明るい枠線の色
				property System::Drawing::Color BrightBorderColor
				{
					System::Drawing::Color get() { return this->GetBrightBorderColor(); }
				}
				/// 暗い枠線の色
				property System::Drawing::Color DarkBorderColor
				{
					System::Drawing::Color get() { return this->GetDarkBorderColor(); }
				}
			};
			// ----------------------------------------------------------------------------------------------------
		}
	}
}
