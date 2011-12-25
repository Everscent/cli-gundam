#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		namespace View
		{
			using namespace System;
			using namespace System::Drawing;
			using namespace System::Drawing::Drawing2D;
			using namespace System::Windows::Forms;

			/**
			 * �e�g���X�`��API�C���^�[�t�F�C�X
			 */
			interface class ITetrisDrawAPI
			{
			/**
			 * ���\�b�h
			 */
			public:
				/// �`��J�n
				virtual void BeginDraw();
				/// �����`��
				virtual void DrawLine(Color color, float width, PointF point1, PointF point2);
				/// �l�p�`�`��
				virtual void DrawRectangle(Color color, float width, PointF point, SizeF size);
				/// �l�p�`�h��Ԃ�
				virtual void FillRectangle(Color color, PointF point, SizeF size);
				/// �l�p�`�h��Ԃ��i�O���f�[�V�����j
				virtual void FillRectangleGradation(Color color1, Color color2, PointF point, SizeF size);
				/// �`��I��
				virtual void EndDraw();
				/// �N���A
				virtual void Clear();
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * �e�g���X�`��API
			 */
			ref class GraphicsTetrisDrawAPI : public ITetrisDrawAPI
			{
			/**
			 * �t�B�[���h
			 */
			private:
				Control^ canvas;
				Bitmap^ bitmap;		// �_�u���o�b�t�@�����O
				Graphics^ graphics;

			/**
			 * �R���X�g���N�^
			 */
			public:
				GraphicsTetrisDrawAPI(Control^ canvas);

			/**
			 * ���\�b�h
			 */
			private:
				void CanvasResize(System::Object^ sender, System::EventArgs^ e);
				void Clear(Graphics^ graphics);

			public:
				/// �`��J�n
				virtual void BeginDraw();
				/// �����`��
				virtual void DrawLine(Color color, float width, PointF point1, PointF point2);
				/// �l�p�`�`��
				virtual void DrawRectangle(Color color, float width, PointF point, SizeF size);
				/// �l�p�`�h��Ԃ�
				virtual void FillRectangle(Color color, PointF point, SizeF size);
				/// �l�p�`�h��Ԃ��i�O���f�[�V�����j
				virtual void FillRectangleGradation(Color color1, Color color2, PointF point, SizeF size);
				/// �`��I��
				virtual void EndDraw();
				/// �N���A
				virtual void Clear();
			};
			// ----------------------------------------------------------------------------------------------------
		}
	}
}