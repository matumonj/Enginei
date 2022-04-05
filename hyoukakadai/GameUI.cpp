#include "GameUI.h"
#include<stdio.h>
#include"Input.h"
#include"DebugCamera.h"
//���ɂ������UI
using namespace DirectX;
Sprite*GameUI::LineLength=nullptr;
Sprite* GameUI::LineLengthout = nullptr;
nTexture* GameUI::AllowTexure = nullptr;
XMFLOAT2 GameUI::lpos, GameUI::loutpos;//���W
XMFLOAT2 GameUI::lscl, GameUI::loutscl;//�X�P�[��
XMFLOAT3 GameUI::Alowpos, GameUI::Alowrot, GameUI::Alowscl={ 1,0.5,10 };
float GameUI::alpha = 0.5;
float GameUI::tempx = 0;
float GameUI::lsclMax;
GameUI*GameUI::GetInstance()
{
	static GameUI instance;
	return &instance;

}
void GameUI::UISpriteSet()
{
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	//�O�g
	Sprite::LoadTexture(10, L"Resources/bosshp.png");
	//���g
	Sprite::LoadTexture(11, L"Resources/gomi.png");
	
	LineLengthout = Sprite::Create(10, { 0.0f,-200.0f });
	LineLength = Sprite::Create(11, { 0.0f,-200.0f });
	AllowTexure = nTexture::Create(12, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	AllowTexure->CreateNormalTexture();
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
		if(loutscl.x>=0)
		loutscl.x -= 10;//�ő�l�����炷
		if (tempx - loutscl.x > movement*4) {//�ő�l�̌����(����O�ƌ��������Ƃ̍ő�l���v�Z)
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

void GameUI::AllowUISet()
{
	//���
	nTexture::LoadTexture(12, L"Resources/angle.png");

	AllowTexure->CreateNormalTexture();
}

void GameUI::AllowUIUpdate(XMMATRIX matview, XMMATRIX matprojection,XMFLOAT3 position,float rotangle,bool flag)
{
	Alowpos.x = position.x;
	Alowpos.y = position.y;
	Alowrot.z=rotangle;

	AllowTexure->SetPosition(Alowpos);
	AllowTexure->SetScale(Alowscl);
	AllowTexure->SetRotation(Alowrot);
	AllowTexure->SetColor({ 1,1,1,alpha });
	if (flag) {
		alpha -= 0.1f;
	}
	if (Input::GetInstance()->TriggerKey(DIK_1)) {
		alpha =0.8f;
	}
	max(alpha, 0.05f);
	min(alpha, 0.8f);
	AllowTexure->Update(matview,matprojection);
}

void GameUI::AllowUIDraw(DirectXCommon*dxcomn)
{
	nTexture::PreDraw(dxcomn->GetCmdList());
	AllowTexure->Draw();
	nTexture::PostDraw();
}