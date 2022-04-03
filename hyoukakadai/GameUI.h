#pragma once
#include"Sprite.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"DirectXCommon.h"
class GameUI
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	//�e�X�v���C�g�̃p�����[�^�ɂ�static�t���Ƃ��Ă�������
	//playscene�̌Ăяo����GameUI�̃C���X�^���X�����K�v�Ȃ�����
	//���ɂ������UI
	static Sprite* LineLength;
	static Sprite* LineLengthout;
	static XMFLOAT2 lpos,loutpos;//���W
	static XMFLOAT2 lscl,loutscl;//�X�P�[��
	static float tempx;
	static float lsclMax;
public:
	static void UISpriteSet();
	static void UIUpdate(float length,bool flag, bool &boundflag,float movement);
	static void UIDraw(DirectXCommon*dxcomn);
};

