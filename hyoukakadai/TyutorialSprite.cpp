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
	Sprite::LoadTexture(30, L"Resources/lineshot.png");
	Sprite::LoadTexture(31, L"Resources/titletu.png");
	Sprite::LoadTexture(32, L"Resources/lineshot.png");
	Sprite::LoadTexture(33, L"Resources/lineope.png");
	Sprite::LoadTexture(34, L"Resources/attack.png");
	//Sprite::LoadTexture(35, L"Resources/lineshot.png");
	//2
	//Sprite::LoadTexture(36, L"Resources/lineshot.png");//���o��+���̏��
	Sprite::LoadTexture(35, L"Resources/lineshot.png");//���o��+���̏��
	Sprite::LoadTexture(36, L"Resources/taskclear5.png");//�U��+�v���C���[�̗̑�
	//clear

	Sprite::LoadTexture(37, L"Resources/tu.png");//�ړ�
	Sprite::LoadTexture(38, L"Resources/taskclear.png");//�U��+�v���C���[�̗̑�
	Sprite::LoadTexture(39, L"Resources/taskclear2.png");//�U��+�v���C���[�̗̑�
	Sprite::LoadTexture(40, L"Resources/taskclear3.png");//���o��+���̏��
	Sprite::LoadTexture(41, L"Resources/taskclear4.png");//�U��+�v���C���[�̗̑�
	Sprite::LoadTexture(42, L"Resources/taskclear5.png");//�U��+�v���C���[�̗̑�

	//�S�ăN���A
	Sprite::LoadTexture(43, L"Resources/cleartutorial.png");//�U��+�v���C���[�̗̑�
	sprite[0] = Sprite::Create(30, { 500,50 });//�J�n
	sprite[1] = Sprite::Create(31, { 500,50 });//�ړ�
	sprite[2] = Sprite::Create(32, { 500,50 });//���o��
	sprite[3] = Sprite::Create(33, { 500,50 });//����ƂЂ���
	sprite[4] = Sprite::Create(34, { 500,50 });//�U��
	sprite[5] = Sprite::Create(35, { 500,50 });//�I��
	sprite[6] = Sprite::Create(36, { 500,50 });//�I��
	sprite[7] = Sprite::Create(37, { 500,50 });//�I��
	sprite[8] = Sprite::Create(38, { 500,50 });//�I��

	sprite[9] = Sprite::Create(37, { 1450,250 });//�I��
	sprite[10] = Sprite::Create(38, { 1450,250 });//�I��
	sprite[11] = Sprite::Create(39, { 1450,250 });//�I��
	sprite[12] = Sprite::Create(40, { 1450,250 });//�I��
	sprite[13] = Sprite::Create(41, { 1450,250 });//�I��
	sprite[14] = Sprite::Create(42, { 1450,250 });//�I��
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
		if (Input::GetInstance()->TriggerKey(DIK_O)) {
			phase = Phase::Move;
			Destroy(sprite[0]);
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
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag);

		if (OK_flag && alpha[1] <= 0.0f) {
			if (Input::GetInstance()->Pushkey(DIK_LEFT) || Input::GetInstance()->Pushkey(DIK_RIGHT)) {
				nextphaseflag_move++;
			}
			if (nextphaseflag_move >= 100) {//��苗���������玟�̃t�F�[�Y��
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
		if (!OK_flag) {
			alpha[2] = 0.9f;
		} else {
			alpha[2] = 0.0f;
		}
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag);

		if (OK_flag && alpha[2] <= 0.0f) {
			if (Line::GetInstance()->Getelf() == true) {
				phase = Phase::LineOperation;
				OK_flag = false;
				Destroy(sprite[2]);
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
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag);
		if (OK_flag && alpha[3] <= 0.0f) {
			if (Line::GetInstance()->Getboundflag() == true) {
				nextphaseflag_bond = true;
			}
			if (Line::GetInstance()->Getreturnflag() == true) {
				nextphaseflag_return = true;
			}
			if (nextphaseflag_bond) {
				task = Clear::LineBond;
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
		Fader::feedInOut_f(0.7f, 0.0f, OK_flag);
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
		Fader::feedIn(0.7f);
		Destroy(sprite[5]);
		break;
	default:
		break;
	}


	for (int i = 0; i < 9; i++) {
		if (sprite[i] != nullptr) {
			sprite[i]->SetSize({ 700,600 });
			sprite[i]->setcolor({ 1,1,1,alpha[i] });
		}
	}
	for (int i = 9; i < 15; i++) {
		if (sprite[i] != nullptr) {
			sprite[i]->SetSize({ 500,600 });
			sprite[i]->setcolor({ 1,1,1,1 });
		}
	}
}

void TyutorialSprite::Draw(DirectXCommon* dxcomn)
{
	//	for (int i = 0; i < Max; i++) {
	Sprite::PreDraw(dxcomn->GetCmdList());
	switch (phase)
	{
	case Phase::Start:
		break;
	case Phase::Move:
		sprite[1]->Draw();
		break;
	case Phase::LineShot:
		sprite[2]->Draw();
		break;
	case Phase::LineOperation:
		sprite[3]->Draw();
		break;
	case Phase::Attack:
		sprite[4]->Draw();
		break;
	case Phase::End:
		break;

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