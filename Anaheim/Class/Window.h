#pragma once

namespace Anaheim
{
	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Windows::Forms;

	/**
	 * ウィンドウ操作
	 */
	public ref class Window abstract sealed
	{
	/**
	 * メソッド
	 */
	private:
		static Process^ GetPreviousProcess();				///< 起動済みプロセス取得
		static void ForegroundWindow(Process^ process);		///< ウィンドウ前面表示

	public:
		/// 起動済みウィンドウを最前面表示
		static void WakeupHasStartedWindow();
	};
	// ----------------------------------------------------------------------------------------------------
}
