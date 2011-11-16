#pragma once

#include "ReportBook.h"

namespace RX78_2
{
	namespace Report
	{
		using namespace System;
		using namespace System::Drawing;

		/**
		 * レポート編集イベントパラメータ
		 */
		ref class ReportEventArgs : public EventArgs
		{
		/**
		 * コンストラクタ
		 */
		public:
			ReportEventArgs();
		/**
		 * プロパティ
		 */
		public:
			/// Undo or Redo
			property bool IsUndo;
			/// 編集のあったセクション名
			property String^ Section;
			/// 編集コマンドフラグ
			property bool IsEdit;
			/// 編集ポイント
			property Point Point;
			/// 変更前文字
			property String^ OldValue;
			/// 変更後文字
			property String^ NewValue;
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * 編集イベント デリゲート
		 */
		delegate void ReportEventHandler(Object^ sender, ReportEventArgs^ e);
		// ----------------------------------------------------------------------------------------------------
	}
}
