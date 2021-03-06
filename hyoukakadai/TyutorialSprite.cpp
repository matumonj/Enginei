#include "TyutorialSprite.h"
#include"Fader.h"
#include"Line.h"
#include"Destroy.h"
#include"Input.h"
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
	Sprite::LoadTexture(90, L"Resources/move2.png");
	Sprite::LoadTexture(32, L"Resources/lineshot1.png");
	Sprite::LoadTexture(33, L"Resources/gaugelimit1.png");
	Sprite::LoadTexture(34, L"Resources/attack1.png");
	//Sprite::LoadTexture(35, L"Resources/lineshot.png");
	//2
	//Sprite::LoadTexture(36, L"Resources/lineshot.png");//???o??+???̏???
	Sprite::LoadTexture(35, L"Resources/gaugelimit.png");//???o??+???̏???
	Sprite::LoadTexture(36, L"Resources/task.png");//?U??+?v???C???[?̗̑?
	//clear

	Sprite::LoadTexture(37, L"Resources/tuask.png");//?ړ?
	Sprite::LoadTexture(38, L"Resources/taskclear.png");//?U??+?v???C???[?̗̑?
	Sprite::LoadTexture(39, L"Resources/taskclear2.png");//?U??+?v???C???[?̗̑?
	Sprite::LoadTexture(40, L"Resources/taskclear3.png");//???o??+???̏???
	Sprite::LoadTexture(41, L"Resources/taskclear4.png");//?U??+?v???C???[?̗̑?
	Sprite::LoadTexture(42, L"Resources/taskclear5.png");//?U??+?v???C???[?̗̑?

	//?S?ăN???A
	Sprite::LoadTexture(43, L"Resources/cleartutorial.png");//?U??+?v???C???[?̗̑?
	sprite[0] = Sprite::Create(30, { 200,50 });//?J?n
	sprite[1] = Sprite::Create(90, { 500,50 });//?ړ?
	sprite[2] = Sprite::Create(32, { 500,50 });//???o??
	sprite[3] = Sprite::Create(33, { 500,50 });//?????ƂЂ???
	sprite[4] = Sprite::Create(34, { 500,50 });//?U??
	sprite[5] = Sprite::Create(35, { 500,70 });//?I??
	sprite[6] = Sprite::Create(36, { 500,50 });//?I??
	sprite[7] = Sprite::Create(37, { 500,50 });//?I??
	sprite[8] = Sprite::Create(38, { 500,50 });//?I??

	sprite[9] = Sprite::Create(37, { startposition,250 });//?I??
	sprite[10] = Sprite::Create(38, { startposition,250 });//?I??
	sprite[11] = Sprite::Create(39, { startposition,250 });//?I??
	sprite[12] = Sprite::Create(40, { startposition,250 });//?I??
	sprite[13] = Sprite::Create(41, { startposition,250 });//?I??
	sprite[14] = Sprite::Create(42, { startposition,250 });//?I??
	sprite[15] = Sprite::Create(43, { 0,0 });//?I??
	for (int i = 9; i < 15; i++) {
		alpha[i] = 1;
	}

}

void TyutorialSprite::Update(Enemy* enemy)
{
	LONG u_r = 32768;
	LONG a = 30000;

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
		if (startposition > 1450) {
			startposition -= 20;
		}
		Line::GetInstance()->SetTrigger(false);
		if (Input::GetInstance()->TriggerButtonB()|| Input::GetInstance()->TriggerKey(DIK_SPACE)&& Fader::GetInstance()->GetAlpha() >= 0.6f) {
			OK_flag = true;
		}
		if (!OK_flag) {
			alpha[1] = 0.9f;
		} else {
			alpha[1] = 0.0f;
		}
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag, NormalinoutSpeed);

		if (OK_flag && alpha[1] <= 0.0f) {
			
			//??
			// ?????????𒲂ׂ????@
			if (Input::GetInstance()->GetCMove().lX < u_r - a || Input::GetInstance()->GetCMove().lX > u_r + a) {
				//if (Input::GetInstance()->Pushkey(DIK_LEFT) || Input::GetInstance()->Pushkey(DIK_RIGHT)) {
					//Input::GetInstance()->TriggerKey(DIK_SPACE)
					nextphaseflag_move++;
				}
			//}
			if (nextphaseflag_move >= 100) {//???苗?????????玟?̃t?F?[?Y??
				phase = Phase::LineShot;
				nextphaseflag_move = 0;
				OK_flag = false;
				Destroy(sprite[1]);
				task = Clear::Move;
			}
		}
		break;
	case TyutorialSprite::Phase::LineShot:
		if (Input::GetInstance()->TriggerButtonB() || Input::GetInstance()->TriggerKey(DIK_SPACE) && Fader::GetInstance()->GetAlpha() >= 0.6f) {
			OK_flag = true;
		}
		if (Input::GetInstance()->TriggerButtonB() || Input::GetInstance()->TriggerKey(DIK_SPACE) &&alpha[5]>=0.8f) {
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
				phase = Phase::Attack;
				OK_flag = false;
				Destroy(sprite[2]);
				Destroy(sprite[5]);
				task = Clear::LineShot;
			}
		}
		break;

	case TyutorialSprite::Phase::Attack:
		if (Input::GetInstance()->TriggerButtonB() || Input::GetInstance()->TriggerKey(DIK_SPACE) && Fader::GetInstance()->GetAlpha() >= 0.6f) {
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
				//task = Clear::Attack;
			}
		}
		break;
	case TyutorialSprite::Phase::End:
		if (Input::GetInstance()->TriggerButtonB() || Input::GetInstance()->TriggerKey(DIK_SPACE) && Fader::GetInstance()->GetAlpha() >= 0.6f) {
			OK_flag = true;
		}
		if (OK_flag) {
			Fader::feedOut(0.0f, NormalfeedSpeed);
		}
		else {
			Fader::feedIn(0.7f, NormalfeedSpeed);
		}
		Fader::feedInOutf_f_a(alpha[15], 0.8f, 0.0f, OK_flag, NormalinoutSpeed);
		//alpha[15] = 1.0f;
		for (int i = 9; i < 15; i++) {
			alpha[i] = 0;
		}
		Destroy(sprite[5]);
		for (int i = 9; i < 15; i++) {
			Destroy(sprite[i]);
		}
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
			sprite[i]->SetPosition({ startposition,250 });
			sprite[i]->setcolor({ 1,1,1,alpha[i] });
		}
	}
	sprite[15]->SetSize({1920, 1080
});
	Fader::FeedSpriteUpdate();
	sprite[15]->setcolor({ 1,1,1,alpha[15] });
}

void TyutorialSprite::Draw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());
	Fader::FeedSpriteDraw();
	Sprite::PostDraw(dxcomn->GetCmdList());


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
	case Phase::Attack:
		sprite[4]->Draw();
		break;
	case Phase::End:
		sprite[15]->Draw();

	default:
		break;
	}
	if (phase != Phase::End) {
	
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