#pragma once

namespace RX78_2
{
	namespace Arrow
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace System::Windows::Forms;

		/**
		 * 虫クラス
		 */
		ref class Insect
		{
		/**
		 * フィールド
		 */
		protected:
			literal int WIDTH = 30;
			literal int HEIGHT = 45;
			literal int LEG_LENGTH = 10;
			literal int LEG_COUNT = 4;
			literal int MOVE_COUNT_MAX = 10;

			PointF location;				///< 位置
			array<PointF>^ legLocations;	///< 足座標	
			double degree;					///< 回転角度（degree）

			int moveCount;					///< ムーブカウント
			PointF moveLocation;			///< 移動先
			int movingLegNo;				///< 動かす足No.
			PointF moveLegLocatin;			///< 足移動先
			double moveDegree;				///< 回転先

			Point targetPoint;				///< 移動先位置（マウス座標）

			int speed;						///< 移動スピードゆらぎ
			int skipMoveCount;				///< 移動スキップ数

			Control^ canvas;				///< キャンバス
			Random^ random;					///< 乱数

		/**
		 * コンストラクタ
		 */
		public:
			Insect(Control^ canvas, Random^ random);

		/**
		 * メソッド
		 */
		protected:
			PointF GetLegPoint(int index);
			PointF GetLegDefaultPoint(int index);
			PointF GetLegPointCore(int index, Point jitter);
			void ChangeMoveCondition();
			void MoveCore();
			virtual void CalcSpeed();
			virtual System::Drawing::Color GetColor();

		public:
			/// 移動
			void Move();
			/// 位置，角度リセット
			void Reset();
			/// ボディー位置取得
			array<PointF>^ GetBodyPoints();
			/// 足位置取得
			array<PointF>^ GetLegPoints();
			/// Arrow位置取得
			array<PointF>^ GetArrowPoints();

		/**
		 * プロパティ
		 */
		public:
			/// 描画色
			property System::Drawing::Color Color
			{
				System::Drawing::Color get() { return this->GetColor(); } 
			}
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * シャア
		 */
		ref class CharInsect : public Insect
		{
		/**
		 * コンストラクタ
		 */
		public:
			CharInsect(Control^ canvas, Random^ random);

		/**
		 * メソッド
		 */
		protected:
			virtual void CalcSpeed() override;
			virtual System::Drawing::Color GetColor() override;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
