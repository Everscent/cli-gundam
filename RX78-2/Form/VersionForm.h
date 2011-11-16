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
	/// VersionForm の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class VersionForm : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Label^  label;
	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::LinkLabel^  linkLabelURL;
	private: System::Windows::Forms::PictureBox^  pictureBox;

	public:
		VersionForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~VersionForm()
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(VersionForm::typeid));
			this->label = (gcnew System::Windows::Forms::Label());
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->linkLabelURL = (gcnew System::Windows::Forms::LinkLabel());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// label
			// 
			this->label->AutoSize = true;
			this->label->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->label->Location = System::Drawing::Point(157, 12);
			this->label->Name = L"label";
			this->label->Size = System::Drawing::Size(122, 16);
			this->label->TabIndex = 0;
			this->label->Text = L"RX78-2 Ver.1.0.0";
			// 
			// buttonOk
			// 
			this->buttonOk->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->buttonOk->Location = System::Drawing::Point(232, 113);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(75, 23);
			this->buttonOk->TabIndex = 1;
			this->buttonOk->Text = L"OK";
			this->buttonOk->UseVisualStyleBackColor = true;
			// 
			// linkLabelURL
			// 
			this->linkLabelURL->AutoSize = true;
			this->linkLabelURL->Location = System::Drawing::Point(158, 44);
			this->linkLabelURL->Name = L"linkLabelURL";
			this->linkLabelURL->Size = System::Drawing::Size(149, 12);
			this->linkLabelURL->TabIndex = 2;
			this->linkLabelURL->TabStop = true;
			this->linkLabelURL->Text = L"http://gtoys.blog48.fc2.com/";
			this->linkLabelURL->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &VersionForm::linkLabelURL_LinkClicked);
			// 
			// pictureBox
			// 
			this->pictureBox->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox.Image")));
			this->pictureBox->Location = System::Drawing::Point(12, 12);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(120, 127);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox->TabIndex = 3;
			this->pictureBox->TabStop = false;
			// 
			// FormVersion
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::GhostWhite;
			this->ClientSize = System::Drawing::Size(319, 148);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->linkLabelURL);
			this->Controls->Add(this->buttonOk);
			this->Controls->Add(this->label);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"FormVersion";
			this->ShowInTaskbar = false;
			this->Text = L"RX78-2 Version";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	/// リンククリック
	private: System::Void linkLabelURL_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e)
			 {
				 System::Diagnostics::Process::Start(this->linkLabelURL->Text);
			 }
			 // ----------------------------------------------------------------------------------------------------
	};
}
