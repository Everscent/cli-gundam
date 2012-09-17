#pragma once

namespace RX78_2
{
	namespace Report
	{
		using namespace System;
		using namespace System::IO;
		using namespace System::Collections::Generic;
		using namespace System::Xml;
		using namespace Microsoft::VisualBasic::FileIO;

		/**
		 * レポートアイテム
		 */
		ref class ReportItem
		{
		/**
		 * フィールド
		 */
		private:
			List<String^>^ strings;

		/**
		 * コンストラクタ
		 */
		public:
			ReportItem();
			ReportItem(int count);
			ReportItem(List<String^>^ strigs);
			ReportItem(XmlElement^ xmlElement);

		/**
		 * メソッド
		 */
		public:
			/// 読み込み
			String^ GetValue(int index);
			/// 書き込み
			bool SetValue(int index, String^ value);
			/// 追加
			void Add(String^ value);
			/// 削除
			bool RemoveAt(int index);
			/// 挿入
			bool Insert(int index, String^ value);
			/// クリア
			void Clear();
			/// カンマ区切りの文字列取得
			virtual String^ ToString() override;
			/// 文字列のarray
			array<String^>^ ToStringArray();
			/// XmlElementのarray
			array<XmlElement^>^ ToXmlElement(XmlDocument ^document);

		/**
		 * プロパティ
		 */
		public:
			/// 文字列数
			property int Count
			{
				int get() { return this->strings->Count; }
			}
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * レポートリスト
		 */
		ref class ReportList
		{
		/**
		 * フィールド
		 */
		private:
			String^ section;
			List<ReportItem^>^ items;

		/**
		 * コンストラクタ
		 */
		public:
			ReportList(String^ section, List<ReportItem^>^ items);
			ReportList(XmlElement^ element);

		/**
		 * メソッド
		 */
		private:
			int GetMaxColCount();

		public:
			/// 追加
			void Add(ReportItem^ item);
			/// 削除
			bool Remove(ReportItem^ item);
			/// 挿入
			bool Insert(int index, ReportItem^ item);
			/// クリア
			void Clear();
			/// カンマ区切り文字列取得
			array<String^>^ ToCommaStrings();
			/// XmlElement取得
			XmlElement^ ToXmlElement(XmlDocument ^document);
			
		/**
		 * プロパティ
		 */
		public:
			/// セクション
			property String^ Section
			{
				String^ get() { return this->section; }
			}
			/// ReportItemリスト
			property List<ReportItem^>^ Items
			{
				List<ReportItem^>^ get() { return this->items; }
			}
			/// 最大列数
			property int MaxColCount
			{
				int get() { return this->GetMaxColCount(); }
			}
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * レポートブック
		 */
		ref class ReportBook
		{
		/**
		 * フィールド
		 */
		private:
			String^ fileName;
			List<ReportList^>^ lists;

		/**
		 * コンストラクタ
		 */
		public:
			ReportBook();

		/**
		 * メソッド
		 */
		private:
			bool IsSectionString(array<String^>^ strings);
			bool LoadCsvFile(String^ fileName);
			bool LoadXmlFile(String^ fileName);
			bool SaveCsvFile(String^ fileName);
			bool SaveXmlFile(String^ fileName);

		public:
			/// ファイル読み込み
			bool LoadFile(String^ fileName);
			/// ファイル保存
			bool SaveFile();
			/// ファイル保存（新規ファイル）
			bool SaveFile(String^ fileName);
			/// クリア
			void Clear();
			/// レポートリスト取得（セクション指定）
			ReportList^ Select(String^ section);
			
		/**
		 * プロパティ
		 */
		public:
			/// 全レポートリスト
			property List<ReportList^>^ Lists
			{
				List<ReportList^>^ get() { return this->lists; }
			}
			/// ファイル名
			property String^ FileName
			{
				String^ get() { return this->fileName; }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
