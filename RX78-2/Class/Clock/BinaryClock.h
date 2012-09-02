#pragma once

namespace RX78_2
{
	namespace Clock
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace System::Windows::Forms;

		/**
		 * バイナリクロック
		 */
		ref class BinaryClock
		{
		/**
		 * フィールド
		 */
		private:
			array<Control^, 2>^ panelsSec;
			array<Control^, 2>^ panelsMin;
			array<Control^, 2>^ panelsHour;
			Color onColor;
			Color offColor;

			DateTime endTime;

		/**
		 * コンストラクタ
		 */
		public:
			BinaryClock(array<Control^, 2>^ sec, array<Control^, 2>^ min, array<Control^, 2>^ hour);

		/**
		 * メソッド
		 */
		public:
			/// 表示
			String^ Display();
			/// タイマー残り時間取得
			TimeSpan GetTimerSpan();

		/**
		 * プロパティ
		 */
		public:
			/// ONカラー
			property Color OnColor
			{
				Color get() { return this->onColor; }
				void set(Color value) { this->onColor = value; }
			}
			/// OFFカラー
			property Color OffColor
			{
				Color get() { return this->offColor; }
				void set(Color value) { this->offColor = value; }
			}
			/// 終了時刻
			property DateTime EndTime
			{
				DateTime get() { return this->endTime; }
				void set(DateTime value) { this->endTime = value; }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
