#pragma once

#include "ReportBook.h"
#include "ReportCommand.h"
#include "ReportEventArgs.h"

namespace RX78_2
{
	namespace Report
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace System::Collections::Generic;

		/**
		 * レポート編集クラス
		 */
		ref class ReportEditor
		{
		/**
		 * フィールド
		 */
		private:
			ReportBook^ report;
			List<ReportCommand^>^ commands;
			int currentIndex;

		/**
		 * コンストラクタ
		 */
		public:
			ReportEditor(ReportBook^ report);

		/**
		 * メソッド
		 */
		private:
			bool AddCommand(ReportCommand^ command);

		public:
			/// 編集
			bool Edit(String^ section, Point point, String^ value);
			/// 挿入，追加
			bool Insert(String^ section, Point point, String^ value);
			/// 削除
			bool Remove(String^ section, Point point);
			/// 行挿入，追加
			bool InsertStep(String^ section, int index, ReportItem^ item);
			/// 行削除
			bool RemoveStep(String^ section, int index);
			/// Undoできるか判定
			bool CanUndo();
			/// Redoできるか判定
			bool CanRedo();
			/// Undo
			bool Undo();
			/// Redo
			bool Redo();
			/// クリア
			void Clear();

		/**
		 * イベント
		 */
		private:
			void OnEndAction(ReportEventArgs^ e);

		public:
			/// アクション後発信イベント
			event ReportEventHandler^ EndAction;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
