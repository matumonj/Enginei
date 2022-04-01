#include "GameUI.h"
//糸にかかわるUI
using namespace DirectX;
Sprite*GameUI::LineLength=nullptr;
Sprite* GameUI::LineLengthout = nullptr;
XMFLOAT2 GameUI::lpos, GameUI::loutpos;//座標
XMFLOAT2 GameUI::lscl, GameUI::loutscl;//スケール
void GameUI::UISpriteSet()
{
	// デバッグテキスト用テクスチャ読み込み
	//外枠
	Sprite::LoadTexture(10, L"Resources/bosshp.png");
	//内枠
	Sprite::LoadTexture(11, L"Resources/gomi.png");
	LineLengthout = Sprite::Create(10, { 0.0f,-200.0f });
	LineLength = Sprite::Create(11, { 0.0f,-200.0f });
	loutpos = { 50,100 };
	loutscl = { 500,50 };
	lpos = { 70,120 };
	lscl = { 480,40 };

}

void GameUI::UIUpdate()
{
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