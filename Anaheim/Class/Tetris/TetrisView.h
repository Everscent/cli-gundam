#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Collections::Generic;

		ref class TetrisDrawing;
		ref class TetrisField;
		ref class TetrisMino;

		/**
		 * �e�g���XView
		 */
		ref class TetrisView
		{
		/**
		 * �t�B�[���h
		 */
		private:
			array<TetrisDrawing^>^ drawings;
			TetrisField^ field;
			List<TetrisMino^>^ minos;

		/**
		 * �R���X�g���N�^
		 */
		public:
			TetrisView(Control^ mainCanvas, array<Control^>^ nextCanvases, TetrisField^ field, List<TetrisMino^>^ minos);

		/**
		 * ���\�b�h
		 */
		public:
			/// �N���A
			void Clear();
			/// �`��i�S�`��j
			bool Draw();
			/// �`��i�w��j
			bool Draw(Control^ canvas);
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
