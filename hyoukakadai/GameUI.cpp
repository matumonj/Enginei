#include "GameUI.h"
#include<stdio.h>
//糸にかかわるUI
using namespace DirectX;
Sprite*GameUI::LineLength=nullptr;
Sprite* GameUI::LineLengthout = nullptr;
XMFLOAT2 GameUI::lpos, GameUI::loutpos;//座標
XMFLOAT2 GameUI::lscl, GameUI::loutscl;//スケール
float GameUI::tempx = 0;
float GameUI::lsclMax;
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
	lscl = { 0,40 };

}

void GameUI::UIUpdate(float length,bool flag,bool&boundflag,float movement)
{
	lsclMax = loutscl.x - 30;

	if (flag) {//紐伸ばしたら長さを減らす
		lscl.x -= 10.0f;
	}
	//loutscl.x--;
	//デバッグ用:紐の長さ回復
	if (lscl.x < loutscl.x - 20) {
		lscl.x++;
	}
	if (boundflag) {
		loutscl.x -= 10;//最大値を減らす
		if (tempx - loutscl.x > movement*2) {//最大値の減る量(減る前と減ったあとの最大値を計算)
			boundflag = false;//!boundflag->colf
		}
		if (lscl.x >= lsclMax) {//最大値が減ったあと紐の長さがそれ超えるようであれば最大値に合わせる
			lscl.x = lsclMax;
		}
	}
	else {
		//減る前の最大値を保存
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