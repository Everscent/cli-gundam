#pragma once

namespace Anaheim
{
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;

	/**
	 * メニューバー，ツールバー，コンテキストメニューの関連付け
	 */
	ref class MenuPair
	{
	/**
	 * フィールド
	 */
	private:
		ToolStripMenuItem^ mainMenu;		///< メニューバー
		ToolStripMenuItem^ contextMenu;		///< コンテキストメニュー
		ToolStripButton^ toolButton;		///< ツールボタン

	/**
	 * コンストラクタ
	 */
	public:
		MenuPair(ToolStripMenuItem^ mainMenu, ToolStripMenuItem^ contextMenu, ToolStripButton^ toolButton);

	/**
	 * メソッド
	 */
	public:
		/// ペアのメインメニュー実行
		bool ExecuteMainMenu();
		/// ペアのコンテキスト，ツールバーのEnabled変更
		bool ChangeEnabled(bool enabled);

	/**
	 * プロパティ
	 */
	public:
		/// メインメニュー
		property ToolStripMenuItem^ MainMenu
		{
			ToolStripMenuItem^ get() { return this->mainMenu; }
		}
		/// コンテキストメニュー
		property ToolStripMenuItem^ ContextMenue
		{
			ToolStripMenuItem^ get() { return this->contextMenu; }
		}
		/// ツールボタン
		property ToolStripButton^ ToolButton
		{
			ToolStripButton^ get() { return this->toolButton; }
		}
	};
	// ----------------------------------------------------------------------------------------------------

	/**
	 * メニュー関連付けリスト
	 */
	public ref class MenuPairList
	{
	/**
	 * フィールド
	 */
	private:
		List<MenuPair^>^ items;

	/**
	 * コンストラクタ
	 */
	public:
		MenuPairList();

	/**
	 * メソッド
	 */
	public:
		/// 登録（メインメニュー，コンテキストメニュー）
		void SetPair(ToolStripMenuItem^ mainMenu, ToolStripMenuItem^ contextMenu);
		/// 登録（メインメニュー，ツールボタン
		void SetPair(ToolStripMenuItem^ mainMenu, ToolStripButton^ toolButton);
		/// 登録（メインメニュー，コンテキストメニュー，ツールボタン）
		void SetPair(ToolStripMenuItem^ mainMenu, ToolStripMenuItem^ contextMenu, ToolStripButton^ toolButton);
		/// ペアのコンテキストメニュー実行
		bool ExecuteContext(Object^ contextMenu);
		/// ペアのツールボタン実行
		bool ExecuteToolButtont(Object^ toolButton);
		/// ペアのEnabled更新
		bool UpdateEnabled(Object^ mainMenu);
	};
	// ----------------------------------------------------------------------------------------------------
}
