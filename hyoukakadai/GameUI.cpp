#include "GameUI.h"
#include<stdio.h>
//���ɂ������UI
using namespace DirectX;
Sprite*GameUI::LineLength=nullptr;
Sprite* GameUI::LineLengthout = nullptr;
XMFLOAT2 GameUI::lpos, GameUI::loutpos;//���W
XMFLOAT2 GameUI::lscl, GameUI::loutscl;//�X�P�[��
float GameUI::tempx = 0;
float GameUI::lsclMax;
void GameUI::UISpriteSet()
{
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	//�O�g
	Sprite::LoadTexture(10, L"Resources/bosshp.png");
	//���g
	Sprite::LoadTexture(11, L"Resources/gomi.png");
	LineLengthout = Sprite::Create(10, { 0.0f,-200.0f });
	LineLength = Sprite::Create(11, { 0.0f,-200.0f });
	loutpos = { 50,100 };
	loutscl = { 500,50 };
	lpos = { 70,120 };
	lscl = { 0,40 };

}

void GameUI::UIUpdate(float length,bool flag,bool&boundflag,float movement)
{
	lsclMax = loutscl.x - 30;

	if (flag) {//�R�L�΂����璷�������炷
		lscl.x -= 10.0f;
	}
	//loutscl.x--;
	//�f�o�b�O�p:�R�̒�����
	if (lscl.x < loutscl.x - 20) {
		lscl.x++;
	}
	if (boundflag) {
		loutscl.x -= 10;//�ő�l�����炷
		if (tempx - loutscl.x > movement*2) {//�ő�l�̌����(����O�ƌ��������Ƃ̍ő�l���v�Z)
			boundflag = false;//!boundflag->colf
		}
		if (lscl.x >= lsclMax) {//�ő�l�����������ƕR�̒��������꒴����悤�ł���΍ő�l�ɍ��킹��
			lscl.x = lsclMax;
		}
	}
	else {
		//����O�̍ő�l��ۑ�
		tempx = loutscl.x;
	}
	
	LineLength->SetPosition(lpos);
	LineLength->SetSize(lscl);
	LineLengthout->SetPosition(loutpos);
	LineLengthout->SetSize(loutscl);
}

void GameUI::UIDraw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());
	LineLengthout->Draw();
	LineLength->Draw();
	Sprite::PostDraw(dxcomn->GetCmdList());
}