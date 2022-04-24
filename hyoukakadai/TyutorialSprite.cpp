#include "TyutorialSprite.h"
#include"Fader.h"
#include"Line.h"
void TyutorialSprite::Initialize()
{
	Sprite::LoadTexture(30, L"Resources/lineshot.png");
	Sprite::LoadTexture(31, L"Resources/lineshot.png");
	Sprite::LoadTexture(32, L"Resources/lineshot.png");
	Sprite::LoadTexture(33, L"Resources/lineshot.png");
	Sprite::LoadTexture(34, L"Resources/lineshot.png");
	Sprite::LoadTexture(35, L"Resources/lineshot.png");
	sprite[0] = Sprite::Create(30, { 750,50 });//開始
	sprite[1] = Sprite::Create(31, { 750,50 });//移動
	sprite[2] = Sprite::Create(32, { 750,50 });//糸出し
	sprite[3] = Sprite::Create(33, { 750,50 });//回収とひっつき
	sprite[4] = Sprite::Create(32, { 750,50 });//攻撃
	sprite[5] = Sprite::Create(33, { 750,50 });//終了
	*alpha = 0;
}

void TyutorialSprite::Update()
{
	switch (phase)
	{
	case TyutorialSprite::Phase::None:
		OK_flag = false;
		break;

	case TyutorialSprite::Phase::Start:
	//	if (alpha[0] <= 0.0f) {
			if (Input::GetInstance()->TriggerKey(DIK_O)){
			phase = Phase::Move;
		}
		break;

	case TyutorialSprite::Phase::Move:
		if (Input::GetInstance()->TriggerKey(DIK_O)&&Fader::GetInstance()->GetAlpha()>=0.6f) {
			OK_flag = true;
		}
		if (!OK_flag) {
			alpha[1] = 0.9f;
		}
		else{
			alpha[1] = 0.0f;
		}
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag);
		
		if (OK_flag&&alpha[1] <= 0.0f) {
			if (Input::GetInstance()->Pushkey(DIK_LEFT) || Input::GetInstance()->Pushkey(DIK_RIGHT)) {
				nextphaseflag_move++;
			}
			if (nextphaseflag_move >= 50) {
				phase = Phase::LineShot;
				nextphaseflag_move = 0;
				OK_flag = false;
			}
		}
		break;
	case TyutorialSprite::Phase::LineShot:
		if (Input::GetInstance()->TriggerKey(DIK_O) && Fader::GetInstance()->GetAlpha() >= 0.6f) {
			OK_flag = true;
		}
		if (!OK_flag) {
			alpha[2] = 0.9f;
		} else {
			alpha[2] = 0.0f;
		}
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag);

		if (OK_flag && alpha[2] <= 0.0f) {
			if (Line::GetInstance()->Getelf()==true) {
				phase = Phase::LineOperation;
				OK_flag = false;
			}
		}
		break;
	case TyutorialSprite::Phase::LineOperation:
		//Fader::feedIn(0.7f);
	//if(flag){//aボタン押されたら
//Fader::feedOut(0.0f);
//}
	//if(alpha[3]<=0.0f){
		break;
	case TyutorialSprite::Phase::Attack:
		//Fader::feedIn(0.7f);
	//if(flag){//aボタン押されたら
//Fader::feedOut(0.0f);
//}
	//if(alpha[4]<=0.0f){
		break;
	case TyutorialSprite::Phase::End:
		break;
	default:
		break;
	}
	for (int i = 0; i < Max; i++) {
		sprite[i]->SetSize({ 700,600 });
		sprite[i]->setcolor({ 1,1,1,alpha[i] });
	}
}

void TyutorialSprite::Draw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());
	for (int i = 0; i < Max; i++) {
		sprite[i]->Draw();
	}
	Sprite::PostDraw(dxcomn->GetCmdList());
}