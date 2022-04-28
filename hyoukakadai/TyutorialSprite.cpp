#include "TyutorialSprite.h"
#include"Fader.h"
#include"Line.h"
#include"Destroy.h"
TyutorialSprite::~TyutorialSprite()
{
	Destroy(sprite[0]);
	Destroy(sprite[1]);
	Destroy(sprite[2]);
	Destroy(sprite[3]);
	Destroy(sprite[4]);
	Destroy(sprite[5]);
	Destroy(sprite[6]);
	Destroy(sprite[7]);
	Destroy(sprite[8]);
	Destroy(sprite[9]);
}

void TyutorialSprite::Initialize()
{
	Sprite::LoadTexture(30, L"Resources/tutorial.png");
	Sprite::LoadTexture(31, L"Resources/move.png");
	Sprite::LoadTexture(32, L"Resources/lineshot.png");
	Sprite::LoadTexture(33, L"Resources/lineope.png");
	Sprite::LoadTexture(34, L"Resources/attack.png");
	//Sprite::LoadTexture(35, L"Resources/lineshot.png");
	//2
	//Sprite::LoadTexture(36, L"Resources/lineshot.png");//糸出し+糸の上限
	Sprite::LoadTexture(35, L"Resources/lineshot.png");//糸出し+糸の上限
	Sprite::LoadTexture(36, L"Resources/task.png");//攻撃+プレイヤーの体力
	//clear

	Sprite::LoadTexture(37, L"Resources/tut.png");//移動
	Sprite::LoadTexture(38, L"Resources/task.png");//攻撃+プレイヤーの体力
	Sprite::LoadTexture(39, L"Resources/task.png");//攻撃+プレイヤーの体力
	Sprite::LoadTexture(40, L"Resources/task.png");//糸出し+糸の上限
	Sprite::LoadTexture(41, L"Resources/task.png");//攻撃+プレイヤーの体力
	Sprite::LoadTexture(42, L"Resources/task.png");//攻撃+プレイヤーの体力

	//全てクリア
	Sprite::LoadTexture(43, L"Resources/cleartutorial.png");//攻撃+プレイヤーの体力
	sprite[0] = Sprite::Create(30, { 200,50 });//開始
	sprite[1] = Sprite::Create(31, { 500,50 });//移動
	sprite[2] = Sprite::Create(32, { 500,50 });//糸出し
	sprite[3] = Sprite::Create(33, { 500,50 });//回収とひっつき
	sprite[4] = Sprite::Create(34, { 500,50 });//攻撃
	sprite[5] = Sprite::Create(43, { 500,50 });//終了
	sprite[6] = Sprite::Create(36, { 500,50 });//終了
	sprite[7] = Sprite::Create(37, { 500,50 });//終了
	sprite[8] = Sprite::Create(38, { 500,50 });//終了

	sprite[9] = Sprite::Create(37, { 1450,250 });//終了
	sprite[10] = Sprite::Create(38, { 1450,250 });//終了
	sprite[11] = Sprite::Create(39, { 1450,250 });//終了
	sprite[12] = Sprite::Create(40, { 1450,250 });//終了
	sprite[13] = Sprite::Create(41, { 1450,250 });//終了
	sprite[14] = Sprite::Create(42, { 1450,250 });//終了
	sprite[15] = Sprite::Create(43, { 0,0 });//終了
	for (int i = 9; i < 15; i++) {
		alpha[i] = 1;
	}

}

void TyutorialSprite::Update(Enemy* enemy)
{
	switch (phase)
	{
	case TyutorialSprite::Phase::None:
		OK_flag = false;
		break;

	case TyutorialSprite::Phase::Start:
		
		//	if (alpha[0] <= 0.0f) {
		
		Fader::feedInOutf_a(alpha[0], 1.8f,-0.1f,inoutspeed);
		if (alpha[0]<0.0f) {
			Fader::feedOut(-0.1f,NormalfeedSpeed);
		}
		else {
			Fader::feedIn(0.8f, NormalfeedSpeed);
		}
		if (Fader::GetInstance()->GetAlpha() < 0.0f) {
			phase = Phase::Move;
		///	Destroy(sprite[0]);
		}
		break;

	case TyutorialSprite::Phase::Move:
		if (Input::GetInstance()->TriggerKey(DIK_O) && Fader::GetInstance()->GetAlpha() >= 0.6f) {
			OK_flag = true;
		}
		if (!OK_flag) {
			alpha[1] = 0.9f;
		} else {
			alpha[1] = 0.0f;
		}
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag, NormalinoutSpeed);

		if (OK_flag && alpha[1] <= 0.0f) {
			if (Input::GetInstance()->Pushkey(DIK_LEFT) || Input::GetInstance()->Pushkey(DIK_RIGHT)) {
				nextphaseflag_move++;
			}
			if (nextphaseflag_move >= 100) {//一定距離歩いたら次のフェーズへ
				phase = Phase::LineShot;
				nextphaseflag_move = 0;
				OK_flag = false;
				Destroy(sprite[1]);
				task = Clear::Move;
			}
		}
		break;
	case TyutorialSprite::Phase::LineShot:
		if (Input::GetInstance()->TriggerKey(DIK_O) && Fader::GetInstance()->GetAlpha() >= 0.6f) {
			OK_flag = true;
		}
		if (OK_flag&&Input::GetInstance()->TriggerKey(DIK_O) &&alpha[5]>=0.8f) {
			OK_flag_2nd = true;
		}
		if (!OK_flag) {
			alpha[2] = 0.9f;
		} else {
			alpha[2] = 0.0f;
			Fader::feedIn_a(alpha[5], 0.9f, NormalfeedSpeed);
		}
		if (OK_flag_2nd) {
			alpha[5]=0;
		}
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag_2nd, NormalinoutSpeed);

		if (OK_flag_2nd && alpha[5] <= 0.0f) {
			if (Line::GetInstance()->Getelf() == true) {
				phase = Phase::LineOperation;
				OK_flag = false;
				Destroy(sprite[2]);
				Destroy(sprite[5]);
				task = Clear::LineShot;
			}
		}
		break;
	case TyutorialSprite::Phase::LineOperation:
		if (Input::GetInstance()->TriggerKey(DIK_O) && Fader::GetInstance()->GetAlpha() >= 0.6f) {
			OK_flag = true;
		}
		if (!OK_flag) {
			alpha[3] = 0.9f;
		} else {
			alpha[3] = 0.0f;
		}
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag, NormalinoutSpeed);
		if (OK_flag && alpha[3] <= 0.0f) {
			if (Line::GetInstance()->Getboundflag() == true) {
				nextphaseflag_bond = true;
			}
			if (Line::GetInstance()->Getreturnflag() == true) {
				nextphaseflag_return = true;
			}
			if (nextphaseflag_bond) {
				task = Clear::LineBond;
				//Line::GetInstance()->SetReturnflag(false);
			}

			if (nextphaseflag_bond && nextphaseflag_return) {
				phase = Phase::Attack;
				OK_flag = false;
				Destroy(sprite[3]);
			}
		}
		break;
	case TyutorialSprite::Phase::Attack:
		if (Input::GetInstance()->TriggerKey(DIK_O) && Fader::GetInstance()->GetAlpha() >= 0.6f) {
			OK_flag = true;
		}
		if (!OK_flag) {
			alpha[4] = 0.9f;
		} else {
			alpha[4] = 0.0f;
		}
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag, NormalinoutSpeed);
		if (OK_flag && alpha[4] <= 0.0f) {
			if (enemy == nullptr) {
				nextphaseflag_attack = true;
			}
			if (nextphaseflag_attack) {
				phase = Phase::End;
				OK_flag = false;
				Destroy(sprite[4]);
				task = Clear::Attack;
			}
		}
		break;
	case TyutorialSprite::Phase::End:
		if (Input::GetInstance()->TriggerKey(DIK_O) && Fader::GetInstance()->GetAlpha() >= 0.6f) {
			OK_flag = true;
		}
		Fader::feedIn(0.7f, NormalfeedSpeed);
		Fader::feedInOutf_f_a(alpha[15], 0.8f, 0.0f, OK_flag, NormalinoutSpeed);
		//alpha[15] = 1.0f;
		for (int i = 9; i < 15; i++) {
			alpha[i] = 0;
		}
		Destroy(sprite[5]);
		break;
	default:
		break;
	}

	sprite[0]->SetSize({ 1700,600 });
	sprite[0]->setcolor({ 1,1,1,alpha[0] });
	for (int i = 1; i < 9; i++) {
		if (sprite[i] != nullptr) {
			sprite[i]->SetSize({ 700,600 });
			sprite[i]->setcolor({ 1,1,1,alpha[i] });
		}
	}
	for (int i = 9; i < 15; i++) {
		if (sprite[i] != nullptr) {
			sprite[i]->SetSize({ 500,600 });
			sprite[i]->setcolor({ 1,1,1,alpha[i] });
		}
	}
	sprite[15]->SetSize({1920, 1080
});
	sprite[15]->setcolor({ 1,1,1,alpha[15] });
}

void TyutorialSprite::Draw(DirectXCommon* dxcomn)
{
	//	for (int i = 0; i < Max; i++) {
	Sprite::PreDraw(dxcomn->GetCmdList());
	switch (phase)
	{
	case Phase::Start:
		sprite[0]->Draw();
		break;
	case Phase::Move:
		sprite[1]->Draw();
		break;
	case Phase::LineShot:
		sprite[2]->Draw();
		sprite[5]->Draw();
		break;
	case Phase::LineOperation:
		sprite[3]->Draw();
		break;
	case Phase::Attack:
		sprite[4]->Draw();
		break;
	case Phase::End:
		sprite[15]->Draw();

	default:
		break;
	}

	switch (task)
	{
	case TyutorialSprite::Clear::None:
		sprite[9]->Draw();
		break;
	case TyutorialSprite::Clear::Move:
		sprite[10]->Draw();
		Destroy(sprite[9]);
		break;
	case TyutorialSprite::Clear::LineShot:
		sprite[11]->Draw();
		Destroy(sprite[10]);
		break;
	case TyutorialSprite::Clear::LineBond:
		sprite[12]->Draw();
		if (nextphaseflag_return) {
			task = Clear::LineCol;
		}
		Destroy(sprite[11]);
		break;
	case TyutorialSprite::Clear::LineCol:
		sprite[13]->Draw();
		Destroy(sprite[12]);
		break;
	case TyutorialSprite::Clear::Attack:
		sprite[14]->Draw();
		Destroy(sprite[13]);
		break;
	default:
		break;
	}

	Sprite::PostDraw(dxcomn->GetCmdList());
	//}
}

void TyutorialSprite::Finalize()
{
	Destroy(sprite[0]);
	Destroy(sprite[1]);
	Destroy(sprite[2]);
	Destroy(sprite[3]);
	Destroy(sprite[4]);
	Destroy(sprite[5]);
	Destroy(sprite[6]);
	Destroy(sprite[7]);
	Destroy(sprite[8]);
	Destroy(sprite[9]);
	Destroy(sprite[14]);
}