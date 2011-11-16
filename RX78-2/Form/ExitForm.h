#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace RX78_2
{
	/// <summary>
	/// ExitForm の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class ExitForm : public System::Windows::Forms::Form
	{
	private: DateTime finishTime;	///< 終了時刻

	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::Label^  label;
	private: System::Windows::Forms::PictureBox^  pictureBox;
	private: System::Windows::Forms::Timer^  timer;
	
	public:
		ExitForm(void)
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
		~ExitForm()
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
		private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ExitForm::typeid));
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->label = (gcnew System::Windows::Forms::Label());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// buttonOk
			// 
			this->buttonOk->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->buttonOk->Location = System::Drawing::Point(48, 88);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(75, 23);
			this->buttonOk->TabIndex = 0;
			this->buttonOk->Text = L"OK (5)";
			this->buttonOk->UseVisualStyleBackColor = true;
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Location = System::Drawing::Point(172, 88);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 1;
			this->buttonCancel->Text = L"キャンセル";
			this->buttonCancel->UseVisualStyleBackColor = true;
			// 
			// label
			// 
			this->label->AutoSize = true;
			this->label->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->label->Location = System::Drawing::Point(100, 36);
			this->label->Name = L"label";
			this->label->Size = System::Drawing::Size(141, 13);
			this->label->TabIndex = 2;
			this->label->Text = L"RX78-2を終了しますか？";
			// 
			// pictureBox
			// 
			this->pictureBox->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox.Image")));
			this->pictureBox->Location = System::Drawing::Point(12, 12);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(60, 60);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox->TabIndex = 3;
			this->pictureBox->TabStop = false;
			// 
			// timer
			// 
			this->timer->Tick += gcnew System::EventHandler(this, &ExitForm::timer_Tick);
			// 
			// ExitForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::GhostWhite;
			this->ClientSize = System::Drawing::Size(294, 123);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->label);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonOk);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"ExitForm";
			this->ShowInTaskbar = false;
			this->Text = L"RX78-2";
			this->Shown += gcnew System::EventHandler(this, &ExitForm::FormClose_Shown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	/// 初期化
	private: void Initialize()
			 {
				 this->finishTime = DateTime::Now.AddSeconds(5.0);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// Shown
	private: System::Void FormClose_Shown(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->timer->Enabled = true;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// タイマー処理
	private: System::Void timer_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 TimeSpan span = this->finishTime.Subtract(DateTime::Now.AddSeconds(-1.0));
				 if (span.Ticks < 0)
				 {
					 this->buttonOk->PerformClick();
				 }
				 else
				 {
					 this->buttonOk->Text = String::Format("OK ({0})", span.Seconds);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------
	};
}
