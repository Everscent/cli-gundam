#pragma once

#include "ISerializable.h"
#include "TetrisMino.h"

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			using namespace System;
			using namespace System::Drawing;
			using namespace System::Collections::Generic;

			ref class TetrisMino;

			/**
			 * テトリス フィールド行
			 */
			public ref class TetrisFieldRow : public ISerializable
			{
			/**
			 * フィールド
			 */
			private:
				array<Color>^ colors;

			/**
			 * コンストラクタ
			 */
			public:
				TetrisFieldRow(int count);

			/**
			 * メソッド
			 */
			public:
				/// クリア
				void Clear();
				/// 完了チェック
				bool IsComplete();
				/// 空チェック
				bool IsEmpty();
				/// 空チェック（列指定）
				bool IsEmpty(int col);
				/// シリアライズ
				virtual array<Byte>^ Serialize();
				/// デシリアライズ
				virtual void Deserialize(array<Byte>^ bytes);

			/**
			 * プロパティ
			 */
			public:
				/// 色
				property array<Color>^ Colors
				{
					array<Color>^ get() { return this->colors; }
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * テトリス フィールド
			 */
			public ref class TetrisField : public ISerializable
			{
			/**
			 * フィールド
			 */
			private:
				List<TetrisFieldRow^>^ rows;

			public:
				/// 横方向サイズ
				literal int COL_COUNT = 10;
				/// 縦方向サイズ
				literal int ROW_COUNT = 20;
				/// バイトサイズ
				literal int BYTE_SIZE = COL_COUNT * ROW_COUNT * 3;

			/**
			 * コンストラクタ
			 */
			public:
				TetrisField();

			/**
			 * メソッド
			 */
			private:
				bool IsEmptyRows();
				bool RemoveCompleteRowsMatch(TetrisFieldRow^ row);

			public:
				/// クリア
				void Clear();
				/// ミノをcolorsにセット
				void SetMino(TetrisMino^ mino);
				/// 完了行が存在するか判定
				bool ExistsCompleteRow();
				/// 完了行を削除
				int RemoveCompleteRows();
				/// シリアライズ
				virtual array<Byte>^ Serialize();
				/// デシリアライズ
				virtual void Deserialize(array<Byte>^ bytes);

			/**
			 * プロパティ
			 */
			public:
				/// 行コレクション
				property List<TetrisFieldRow^>^ Rows
				{
					List<TetrisFieldRow^>^ get() { return this->rows; }
				}
				/// 空チェック
				property bool IsEmpty
				{
					bool get() { return this->IsEmptyRows(); }
				}
			};
			// ----------------------------------------------------------------------------------------------------
		}
	}
}
