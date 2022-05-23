#include "GameUI.h"
#include<stdio.h>
#include"Input.h"
#include"DebugCamera.h"
#include"Destroy.h"
#include"Line.h"
#include"BossEnemy.h"
//糸にかかわるUI
using namespace DirectX;
Sprite* GameUI::LineLength = nullptr;
Sprite* GameUI::LineLengthout = nullptr;
Sprite* GameUI::Attention[3] = { nullptr };
Sprite* GameUI::PlayerHP = nullptr;
Sprite* GameUI::BossHP;
nTexture* GameUI::AllowTexure = nullptr;
nTexture* GameUI::TargetTexture = nullptr;

XMFLOAT2 GameUI::lpos, GameUI::loutpos;//座標
XMFLOAT2 GameUI::lscl, GameUI::loutscl;//スケール
XMFLOAT3 GameUI::Alowpos, GameUI::Alowrot, GameUI::Alowscl = { 1,0.5f,10 };
XMFLOAT3 GameUI::Targetpos, GameUI::Targetrot, GameUI::Targetscl = { 0.8f,0.8f,1 };
XMFLOAT2 GameUI::playerHPPos, GameUI::playerHPScl; //座標
XMFLOAT2 GameUI::BossHPpos, GameUI::BossHPscl;

float GameUI::alpha = 0.5, GameUI::walpha = 0, GameUI::Targetalpha = 0;
float GameUI::tempx = 0;
float GameUI::lsclMax;
Sprite* GameUI::NowLoad;
float GameUI::LoadAlpha=0;
GameUI* GameUI::GetInstance()
{
	static GameUI instance;
	return &instance;

}
void GameUI::UISpriteSet()
{
	// デバッグテキスト用テクスチャ読み込み
	//外枠
	Sprite::LoadTexture(10, L"Resources/bosshp.png");
	//内枠
	Sprite::LoadTexture(11, L"Resources/gomi.png");
	//注意
	Sprite::LoadTexture(12, L"Resources/attention.png");

	LineLengthout = Sprite::Create(10, { 0.0f,-200.0f });
	LineLength = Sprite::Create(11, { 0.0f,-200.0f });
	Attention[0] = Sprite::Create(12, { 0.0f,-200.0f });
	AllowTexure = nTexture::Create(12, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	AllowTexure->CreateNormalTexture();
	loutpos = { 50,200 };
	loutscl = { 500,50 };
	lpos = { 70,120 };
	lscl = { 0,40 };
	Attention[0]->SetSize({ 1500,800 });
	Attention[0]->SetPosition({ WinApp::window_width / 2 - 600,WinApp::window_height / 2 });
	BossHP= Sprite::Create(10, { 0.0f,-200.0f });
	BossHPpos = { 200,800 };
}
void GameUI::BossUIUpdate(Enemy* enemy) {
	if (enemy != nullptr) {
		float f = enemy->GetHP() * 10;
		BossHPscl = { f ,70 };
		BossHP->SetPosition(BossHPpos);
		BossHP->SetSize(BossHPscl);
		BossHP->setcolor({ 1,1,1,1 });
	}
	//BossHP->SetSize(BossHPscl);
}
void GameUI::UIUpdate(float length, bool flag, bool& boundflag, float movement)
{
	lsclMax = 300;// loutscl.x - 30;

	if (flag) {//紐伸ばしたら長さを減らす
		//lscl.x -= 10.0f;
	}
	//loutscl.x--;
	//デバッグ用:紐の長さ回復
	if (lscl.x < loutscl.x - 20) {
		lscl.x++;
	}
	if (boundflag) {
		if (loutscl.x >= 0)
			loutscl.x -= 3;//最大値を減らす
		if (tempx - loutscl.x > movement * 2) {//最大値の減る量(減る前と減ったあとの最大値を計算)
			boundflag = false;//!boundflag->colf
		}
		if (lscl.x >= lsclMax) {//最大値が減ったあと紐の長さがそれ超えるようであれば最大値に合わせる
			lscl.x = lsclMax;
		}
	} else {
		//減る前の最大値を保存
		tempx = loutscl.x;
	}
	AttentionUI();
	loutscl.x += 0.1f;
	if (loutscl.x >= 500.0f) {
		loutscl.x = 500.0f;
	}
	LineLength->SetPosition(lpos);
	LineLength->SetSize(lscl);
	LineLengthout->SetPosition(loutpos);
	LineLengthout->SetSize(loutscl);
	Attention[0]->setcolor({ walpha,1,1,1 });
}

void GameUI::UIDraw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());
	//Attention[0]->Draw();
	LineLengthout->Draw();
	//LineLength->Draw();
	BossHP->Draw();
	Sprite::PostDraw(dxcomn->GetCmdList());
}

void GameUI::AllowUISet()
{
	//矢印
	nTexture::LoadTexture(12, L"Resources/angle.png");

	AllowTexure->CreateNormalTexture();
}

void GameUI::AllowUIUpdate(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position, float rotangle, bool flag)
{
	Alowpos.x = position.x;
	Alowpos.y = position.y;
	Alowrot.z = rotangle;

	AllowTexure->SetPosition(Alowpos);
	AllowTexure->SetScale(Alowscl);
	AllowTexure->SetRotation(Alowrot);
	AllowTexure->SetColor({ 1,1,1,alpha });
	if (flag) {
		alpha -= 0.1f;
	}
	if (Input::GetInstance()->TriggerKey(DIK_1)) {
		alpha = 0.8f;
	}
	max(alpha, 0.05f);
	min(alpha, 0.8f);
	AllowTexure->Update(matview, matprojection);
}

void GameUI::AllowUIDraw(DirectXCommon* dxcomn)
{
	nTexture::PreDraw(dxcomn->GetCmdList());
	AllowTexure->Draw();
	nTexture::PostDraw();
}

void GameUI::AttentionUI()
{
	if (loutscl.x <= 0) {
		if (Input::GetInstance()->Pushkey(DIK_SPACE))
		{
			walpha = 0.8f;
		}
	}
	walpha -= 0.02f;
	min(walpha, 0.8f);
	max(walpha, 0);
}

void GameUI::TargetUISet()
{
	//矢印
	nTexture::LoadTexture(13, L"Resources/target.png");
	TargetTexture = nTexture::Create(13, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });

	TargetTexture->CreateNormalTexture();
}
void GameUI::TargetUIUpdate(XMMATRIX matview, XMMATRIX matprojection, bool flag)
{
	if (flag) {
		if (Targetalpha <= 1.0f) {
			Targetalpha += 0.05f;
		}
		if (Targetscl.y >= 0.4) {
			Targetscl.y -= 0.02f;
		}
		if (Targetscl.x >= 0.4) {
			Targetscl.x -= 0.02f;
		}
		Targetpos = Line::GetInstance()->getpos();
		//TargetTexture->SetPosition();
	} else {
		Targetscl = { 1,1,1 };
		if (Targetalpha >= 0) {
			Targetalpha -= 0.1f;
		}
	}
	TargetTexture->SetColor({ 1,1,1,Targetalpha });
	TargetTexture->SetPosition(Targetpos);
	TargetTexture->SetScale(Targetscl);
	TargetTexture->SetRotation(Targetrot);

	TargetTexture->Update(matview, matprojection);
}
void GameUI::TargetUIDraw(DirectXCommon* dxcomn)
{
	nTexture::PreDraw(dxcomn->GetCmdList());
	TargetTexture->Draw();
	nTexture::PostDraw();
}

void GameUI::PlayerUISet()
{
	//playerhp
	Sprite::LoadTexture(13, L"Resources/bosshp.png");
	PlayerHP = Sprite::Create(13, { 0.0f,-200.0f });

	playerHPScl = { 500,50 };
	playerHPPos = { 40,300 };
}

void GameUI::PlayerUIUpdate(Player* player)
{

	playerHPScl.x = (float)(player->getHp() * 5);
	PlayerHP->SetSize(playerHPScl);
	PlayerHP->SetPosition(playerHPPos);
	PlayerHP->setcolor({ 1,1,1,1 });
}

void GameUI::PlayerUIDraw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());
	PlayerHP->Draw();
	Sprite::PostDraw(dxcomn->GetCmdList());
}
void GameUI::AllDraw(DirectXCommon* dxcomn)
{
	//weffect->Draw(dxcomn);
	AllowUIDraw(dxcomn);
	TargetUIDraw(dxcomn);
	UIDraw(dxcomn);
	PlayerUIDraw(dxcomn);
}

void GameUI::Finalize()
{
	//delete LineLength,LineLengthout;
	Destroy(LineLength);
	Destroy(LineLengthout);
	Destroy(PlayerHP);
	Destroy(Attention[0]);
	Destroy(Attention[1]);
	Destroy(Attention[2]);
	Destroy(AllowTexure);
	//delete AllowTexure;
	delete TargetTexture;
	//delete EnemySearchTexure;
}

void GameUI::NowLoadSet()
{
	Sprite::LoadTexture(42, L"Resources/load.png");
	NowLoad = Sprite::Create(42, { 0.0f,-200.0f });

	LoadAlpha = 0;
}

void GameUI::NowLoadUpdate(bool onf)
{
	NowLoad->SetPosition({ 1500,600 });
	NowLoad->SetPosition({ 200,200 });
	if (onf) {
		LoadAlpha = 1.0f;
	}
	else {
		LoadAlpha = 0.0f;
	}
	NowLoad->setcolor({ 1,1,1,LoadAlpha });
	
}
void GameUI::NowLoadDraw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());
	NowLoad->Draw();
	Sprite::PostDraw(dxcomn->GetCmdList());
}