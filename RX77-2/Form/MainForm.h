#pragma once

#include "ConfigFile.h"

namespace RX77_2
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Anaheim::Tetris;

	/// <summary>
	/// MainForm の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{

#pragma region フィールド

	private: ConfigFile^ config;			///< コンフィグファイル
	private: TetrisRemotePackage^ tetris;	///< テトリス

	private: System::Windows::Forms::Panel^  panelCanvas;

#pragma endregion

	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
			this->Initialize();
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->panelCanvas = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// panelCanvas
			// 
			this->panelCanvas->BackColor = System::Drawing::Color::Black;
			this->panelCanvas->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelCanvas->Location = System::Drawing::Point(0, 0);
			this->panelCanvas->Name = L"panelCanvas";
			this->panelCanvas->Size = System::Drawing::Size(300, 600);
			this->panelCanvas->TabIndex = 0;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::GhostWhite;
			this->ClientSize = System::Drawing::Size(300, 600);
			this->Controls->Add(this->panelCanvas);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(316, 638);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"RX77-2";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			this->ResumeLayout(false);

		}
#pragma endregion

	/// 初期化
	private: void Initialize()
			 {
				 String^ filename = System::IO::Path::ChangeExtension(System::Windows::Forms::Application::ExecutablePath, ".ini");
				 this->config = gcnew ConfigFile(filename);
				 this->config->LoadFormSizeAndLocation(this);

				 this->tetris = gcnew TetrisRemotePackage(this->panelCanvas);
				 this->tetris->StartRemote();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// クローズ後処理
	private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
			 {
				 this->tetris->StopRemote();
				 this->config->SaveFormSizeAndLocation(this);
			 }
			 // ----------------------------------------------------------------------------------------------------

	};
}

