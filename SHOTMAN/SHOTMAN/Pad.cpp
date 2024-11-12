#include "Pad.h"
#include "DxLib.h"

namespace
{
	int padInput = 0;	//���݂̃t���[���̃p�b�h����
	int lastInput = 0;  //�ЂƂO�̃t���[���̃p�b�h����
}

namespace Pad
{
	void Update()
	{
		//�O�̃t���[���ɉ�����Ă����{�^���̏����o���Ă���
		lastInput = padInput;
		//���̃t���[���ɉ�����Ă���{�^���̏����擾����
		padInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

	//Press����̎擾
	//�߂�l:������Ă�����true,������Ă��Ȃ�������false
	//����:������s�������{�^��
	bool IsPress(int button)
	{
		if (padInput & button)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//Trigger����̎擾
	bool IsTrigger(int button)
	{
		//�����������݂̃t���[���Ƀ{�^����������Ă��Ȃ�
		if (!(padInput & button))
		{
			return false;
		}

		//�����܂ŏ����������Ƃ������Ƃ�
		//���̃t���[���Ƀ{�^����������Ă͂���

		//�O�̃t���[���Ƀ{�^����������Ă��Ȃ����Trigger�Ɣ���ł���
		if (lastInput & button)
		{
			return false;
		}
		else
		{
			//�O�̃t���[���ɉ�����Ă��Ȃ���
			//���݂̃t���[���ɉ�����Ă���Ƃ������Ƃ�
			//�̃t���[���������ꂽ�u��
			return true;
		}
		
		return false;
	}
}