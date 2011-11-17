#pragma once

#include "ReportBook.h"
#include "ReportEventArgs.h"

namespace RX78_2
{
	namespace Report
	{
		using namespace System;
		using namespace System::Drawing;

		/**
		 * レポート編集コマンド（抽象クラス）
		 */
		ref class ReportCommand abstract
		{
		/**
		 * フィールド
		 */
		protected:
			ReportList^ report;

		/**
		 * コンストラクタ
		 */
		public:
			ReportCommand(ReportList^ report);

		/**
		 * メソッド
		 */
		public:
			/// 実行（Redo）
			virtual bool Execute() abstract;
			/// Undo
			virtual bool Undo() abstract;
			/// イベント用パラメータ取得
			virtual ReportEventArgs^ GetEventArgs();

		/**
		 * プロパティ
		 */
		public:
			/// セクション
			property String^ Section
			{
				String^ get() { return this->report->Section; }
			}
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * レポート編集コマンド（編集）
		 */
		ref class ReportEdit : public ReportCommand
		{
		/**
		 * フィールド
		 */
		private:
			Point point;
			String^ oldValue;
			String^ newValue;

		/**
		 * コンストラクタ
		 */
		public:
			ReportEdit(ReportList^ report, Point point, String^ value);

		/**
		 * メソッド
		 */
		public:
			/// 実行（Redo）
			virtual bool Execute() override;
			/// Undo
			virtual bool Undo() override;
			/// イベント用パラメータ取得
			virtual ReportEventArgs^ GetEventArgs() override;
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * レポート編集コマンド（挿入）
		 */
		ref class ReportInsert : public ReportCommand
		{
		/**
		 * フィールド
		 */
		private:
			Point point;
			String^ value;

		/**
		 * コンストラクタ
		 */
		public:
			ReportInsert(ReportList^ report, Point point, String^ value);

		/**
		 * メソッド
		 */
		public:
			/// 実行（Redo）
			virtual bool Execute() override;
			/// Undo
			virtual bool Undo() override;
			/// イベント用パラメータ取得
			virtual ReportEventArgs^ GetEventArgs() override;
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * レポート編集コマンド（削除）
		 */
		ref class ReportRemove : public ReportCommand
		{
		/**
		 * フィールド
		 */
		private:
			Point point;
			String^ value;

		/**
		 * コンストラクタ
		 */
		public:
			ReportRemove(ReportList^ report, Point point);

		/**
		 * メソッド
		 */
		public:
			/// 実行（Redo）
			virtual bool Execute() override;
			/// Undo
			virtual bool Undo() override;
			/// イベント用パラメータ取得
			virtual ReportEventArgs^ GetEventArgs() override;
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * レポート編集コマンド（ステップ挿入）
		 */
		ref class ReportInsertStep : public ReportCommand
		{
		/**
		 * フィールド
		 */
		private:
			int index;
			ReportItem^ item;

		/**
		 * コンストラクタ
		 */
		public:
			ReportInsertStep(ReportList^ report, int index, ReportItem^ item);

		/**
		 * メソッド
		 */
		public:
			/// 実行（Redo）
			virtual bool Execute() override;
			/// Undo
			virtual bool Undo() override;
			/// イベント用パラメータ取得
			virtual ReportEventArgs^ GetEventArgs() override;
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * レポート編集コマンド（ステップ削除）
		 */
		ref class ReportRemoveStep : public ReportCommand
		{
		/**
		 * フィールド
		 */
		private:
			int index;
			ReportItem^ item;

		/**
		 * コンストラクタ
		 */
		public:
			ReportRemoveStep(ReportList^ report, int index);

		/**
		 * メソッド
		 */
		public:
			/// 実行（Redo）
			virtual bool Execute() override;
			/// Undo
			virtual bool Undo() override;
			/// イベント用パラメータ取得
			virtual ReportEventArgs^ GetEventArgs() override;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
