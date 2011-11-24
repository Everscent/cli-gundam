// RX77-2.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"
#include "MainForm.h"

using namespace RX77_2;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// 二重起動チェック
	System::Threading::Mutex^ mutex = gcnew System::Threading::Mutex(true, "RX77-2");
    if (!mutex->WaitOne(0, false))
	{
		Anaheim::Window::WakeupHasStartedWindow();
        return 1;
    }

	// コントロールが作成される前に、Windows XP ビジュアル効果を有効にします
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// メイン ウィンドウを作成して、実行します
	Application::Run(gcnew MainForm());

	// ミューテックス解放
	mutex->ReleaseMutex();

	return 0;
}
