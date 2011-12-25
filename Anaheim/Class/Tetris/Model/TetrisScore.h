#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			using namespace System;
			using namespace System::Drawing;

			/**
			 * テトリス スコア（公開用）
			 */
			public ref class PublicTetrisScore abstract
			{
			/**
			 * コンストラクタ
			 */
			public:
				PublicTetrisScore();

			/**
			 * プロパティ
			 */
			public:
				/// スコア
				property int Score
				{
					virtual int get() abstract;
				}
				/// Singleカウント
				property int SingleCount
				{
					virtual int get() abstract;
				}
				/// Doubleカウント
				property int DoubleCount
				{
					virtual int get() abstract;
				}
				/// Tripleカウント
				property int TripleCount
				{
					virtual int get() abstract;
				}
				/// TETRiSカウント
				property int TetrisCount
				{
					virtual int get() abstract;
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * テトリス スコア
			 */
			ref class TetrisScore : public PublicTetrisScore
			{
			/**
			 * フィールド
			 */
			private:
				int score;
				int singleCount;
				int doubleCount;
				int tripleCount;
				int tetrisCount;

			/**
			 * コンストラクタ
			 */
			public:
				TetrisScore();

			/**
			 * メソッド
			 */
			public:
				/// クリア
				void Clear();

				/// 更新
				bool UpdateScore(int removeCount, bool isPerfect);

			/**
			 * プロパティ
			 */
			public:
				/// スコア
				property int Score
				{
					virtual int get() override { return this->score; }
				}
				/// Singleカウント
				property int SingleCount
				{
					virtual int get() override { return this->singleCount; }
				}
				/// Doubleカウント
				property int DoubleCount
				{
					virtual int get() override { return this->doubleCount; }
				}
				/// Tripleカウント
				property int TripleCount
				{
					virtual int get() override { return this->tripleCount; }
				}
				/// TETRiSカウント
				property int TetrisCount
				{
					virtual int get() override { return this->tetrisCount; }
				}
			};
			// ----------------------------------------------------------------------------------------------------
		}
	}
}
