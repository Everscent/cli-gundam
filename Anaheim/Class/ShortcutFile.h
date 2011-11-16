#pragma once

namespace Anaheim
{
	using namespace System;

	/**
	 * ショートカットファイル
	 */
	public ref class ShortcutFile
	{
	/**
	 * フィールド
	 */
	private:
		String^ fileName;
		String^ linkPath;
		String^ argument;
		String^ workDirectory;
		String^ comment;

	/**
	 * コンストラクタ
	 */
	public:
		ShortcutFile(String^ fileName, String^ linkPath);

	/**
	 * メソッド
	 */
	public:
		/// ショートカット作成
		void Save();

	/**
	 * プロパティ
	 */
	public:
		/// コマンドパラメータ
		property String^ Argument
		{
			void set(String^ value) { this->argument = value; }
		}
		/// 作業ディレクトリ
		property String^ WorkDirectory
		{
			void set(String^ value) { this->workDirectory = value; }
		}
		/// コメント
		property String^ Comment
		{
			void set(String^ value) { this->comment = value; }
		}
	};
	// ----------------------------------------------------------------------------------------------------
}
