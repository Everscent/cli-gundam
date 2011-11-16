#include "StdAfx.h"
#include "Window.h"
#include <windows.h>

using namespace Anaheim;

/**
 * ウィンドウ操作
 */
Process^ Window::GetPreviousProcess()
{
	Process^ myProcess = Process::GetCurrentProcess();
	array<Process^>^ processes = Process::GetProcessesByName(myProcess->ProcessName);

	for each (Process^ pro in processes)
	{
		if (pro->Id != myProcess->Id)	// 自分自身ではないプロセスを取得
		{
			return pro;
		}
	}

	return nullptr;
}
// ----------------------------------------------------------------------------------------------------

void Window::ForegroundWindow(Process ^process)
{
	HWND hWnd = (HWND)((void*)process->MainWindowHandle);
	if (hWnd == NULL)
	{
		System::Windows::Forms::MessageBox::Show("すでに起動しています！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else
	{
		if (::IsIconic(hWnd) == TRUE)
		{
			::ShowWindowAsync(hWnd, SW_RESTORE);
		}
		::SetForegroundWindow(hWnd);
	}
}
// ----------------------------------------------------------------------------------------------------

void Window::WakeupHasStartedWindow()
{
	Process^ process = Window::GetPreviousProcess();
	if (process != nullptr)
	{
		Window::ForegroundWindow(process);		
	}
}
// ----------------------------------------------------------------------------------------------------
