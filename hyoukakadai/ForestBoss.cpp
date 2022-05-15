#include "ForestBoss.h"
#include"Collision.h"
#include"MobEnemy.h"
#include"Helper.h"
#include"mHelper.h"
#include<random>
#define PI 3.14
int ForestBoss::StayCount = 0;
float ForestBoss::startcount = 0;
bool ForestBoss::stayflag;
XMFLOAT3 ForestBoss::startPos;
bool ForestBoss::bossjumpflag = false;
XMFLOAT3 ForestBoss::wpos[max];
int ForestBoss::attacktime = 0;
XMFLOAT3 ForestBoss::Skewers_Scl[max] = { {1,1,1},{1,1,1},{1,1,1} };
bool ForestBoss::woodatkflag = false;
float ForestBoss::woodatkCount = 0;
float ForestBoss::woodatkCount2 = 0;
float ForestBoss::woodatkCount3 = 0;
// Sphere ForestBoss::playersphere;
ForestBoss::ForestBoss()
{
}
ForestBoss* ForestBoss::GetInstance()
{
	static ForestBoss instance;
	return &instance;
}
ForestBoss::~ForestBoss()
{
	delete BossObject, BossModel;
}
void ForestBoss::MoveBlockJump()
{
	//�u���b�N���܂���p�̃W�����v����
	//��莞�ԓ����Ȃ�������W�����v
	time++;
	if (time % 20 == 0) {
		oldx = Position.x;
		//oldy = Position.y;
	}
	if (Collision::GetLenX({ oldx,oldy,0.0f }, Position) <= 0.0f) {
		time2++;
		if (time2 > 10) {
			//bossjumpflag = true;
			time2 = 0;
		}
	}

}
void ForestBoss::EnemySearchPlayer(Player* player)
{

}
void ForestBoss::Attack(Player* player)
{

}
//����������
void ForestBoss::Initialize()
{
	//���f���̓Ǎ�
	BossModel = Model::CreateFromOBJ("zako1");
	//���f�����蓖��
	BossObject = Object3d::Create();
	BossObject->SetModel(BossModel);

	SkewersBossModel= Model::CreateFromOBJ("wood");
	for (int i = 0; i < max; i++) {
		SkewersObject[i] = Object3d::Create();
		SkewersObject[i]->SetModel(SkewersBossModel);
	}
	//�p�����[�^�̃Z�b�g
	Position = { 67,-4,0 };
	Boss_Scl = { 2,2,2 };
	Boss_Rot = { 0,0,0 };
	Rotation = { 30,80,80 };
	//���f���̓Ǎ�
	Rotation.z = 0;
	HP = MaxHP;
	startPos = { 40,-18,0 };
}//

//�X�V����
void ForestBoss::Update(XMFLOAT3 position)
{
	Old_Pos = Position;

	if (bossjumpflag == true) {
		if (bossjumpflag2) {
			Position.y += 0.5f;
		} else {
			Position.y += 0.2f;
		}
		bosstime += 0.02f;
	} else {
		bossjumpflag2 = false;
	}

	if (HP <= 0) {
		enemyState = State::DEAD;
	} else {
		enemyState = State::ALIVE;
	}
	BossObject->Update({ 1,1,1,1 });
	for (int i = 0; i < max; i++) {
		SkewersObject[i]->Update({ 1,1,1,1 });
	}
	GetDamage();
	//���u
	Rotation.x = 0;

	BossObject->SetPosition(Position);
	BossObject->SetScale({ 2,2,2 });
	BossObject->SetRotation(Rotation);
	for (int i = 0; i < max; i++) {
		SkewersObject[i]->SetScale(Skewers_Scl[i]);
		SkewersObject[i]->SetRotation({ 0,0,-90 });
		//BossObject->SetRotation(Boss_Rot);
		SkewersObject[i]->SetPosition(wpos[i]);
	}
}
void ForestBoss::SkewersAttack(int map[130][20], std::unique_ptr<Object3d> tst[130][20])
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j< 130; j++) {
			if (map[j][i] == 3) {
				wpos[0] = { tst[j][i]->GetPosition().x - 5,tst[j][i]->GetPosition().y,tst[j][i]->GetPosition().z };
				if (woodatkflag) {
					map[j][i] = 4;
				}
			}
				if (map[j][i] == 5) {
					wpos[1] = { tst[j][i]->GetPosition().x + 5,tst[j][i]->GetPosition().y,tst[j][i]->GetPosition().z };
					if (woodatkflag) {
						map[j][i] = 4;
					}
				}
				if (map[j][i] == 6) {
					wpos[2] = { tst[j][i]->GetPosition().x + 5,tst[j][i]->GetPosition().y,tst[j][i]->GetPosition().z };
					if (woodatkflag) {
						map[j][i] = 4;
					}
				}
				//break;
			
		}
	}
	if (Input::GetInstance()->TriggerKey(DIK_O)) {
		woodatkflag = true;
	}
	if (woodatkflag) {
		if (Skewers_Scl[0].y <= 8) {
			woodatkCount += 0.05f;
			Skewers_Scl[0].y = Easing::EaseOut(woodatkCount, 0, 8);
		}
		if (Skewers_Scl[1].y >= -8) {
			woodatkCount2 -= 0.05f;
			Skewers_Scl[1].y = Easing::EaseOut(woodatkCount2, 0, -8);
		} 
		if (Skewers_Scl[2].y >= -8) {
			woodatkCount3 -= 0.05f;
			Skewers_Scl[2].y = Easing::EaseOut(woodatkCount3, 0, -8);
		} 
		else {
			woodatkflag = false;
		}
	}
//	wpos ={ 0,0,0 };
	
}
//�`�揈��
void ForestBoss::Draw(DirectXCommon* dxcomn)
{
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
	for (int i = 0; i < max; i++) {
		SkewersObject[i]->PreDraw();
		SkewersObject[i]->Draw();
		SkewersObject[i]->PostDraw();
	}
}

//�������
void ForestBoss::Finalize()
{

}
void ForestBoss::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{}

void ForestBoss::Motion(Player* player)
{
	const float dis = 0.5f;
	switch (bossAction)
	{
	case SetStartPos://�����ʒu�ɖ߂��
		
		break;
	
	case None:
		attacktime++;
		if (Input::GetInstance()->TriggerKey(DIK_S)) {
			bossAction = SetStartPos;
		}
		if (HP < MaxHP / 2) {
			bossAction = SetStartPos;//�̗͂����ȉ��Ȃ����珉���ʒu��
		}
		if (Collision::GetLen_X(Position.x, player->GetPosition().x) > 5) {
			Follow(player->GetPosition());
			//MoveBlockJump();//�{�X�̖��܂���p�ƃu���b�N��щz���Ƃ�

		} else {
			if (attacktime % 50 == 0) {
				bossAction = NormalAttack;//�v���C���[����̕��������瓊��
				attacktime = 0;
			}
		}

		if (HP != MaxHP && HP != BefHP && HP % 4 == 0) {
			bossAction = SetStartPos;
		}

		break;
	case MoveRight://�ːi�E
		if (movement < 10) {
			Position.x += bossmovespeed;
			movement += 0.5f;
		} else if (movement >= 10) {
			movement = 0;
		}
		break;
	case MoveLeft://�ːi��
		if (movement < 10) {
			Position.x -= bossmovespeed;
			movement += 0.5f;
		} else if (movement >= 10) {
			movement = 0;
		}
		break;

	case Stay://�r�[���O�̑ҋ@
		StayCount++;
		if (StayCount > 150) {
			bossAction = None;
			StayCount = 0;
		}
		break;

	case NormalAttack:
		NormalAttacks(player);
		break;
	case StartBattle:
		if (startcount > 2.0f) {
			bossAction = None;
			//	phase = true;
		}
		break;
	default:
		break;
	}

}

void ForestBoss::ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)
{

}
void ForestBoss::Follow(XMFLOAT3 position)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (position.x - Position.x);
	angleZ = (position.y - Position.y);
	angleR = sqrtf((Position.x - position.x) * (Position.x - position.x)
		+ (Position.y - position.y) * (Position.y - position.y));

	Position.x += (angleX / angleR) * (bossmovespeed / 2);

}


void ForestBoss::NormalAttacks(Player* player)
{
	//DamageAreaStart = { Position.x,Position.y + 2 };
	if (Rotation.y == 180) {//�E�����Ă�Ƃ���
		DamageAreaStart = { Position.x,Position.y + 2 };
		DamageArea = { Position.x - 8 ,Position.y - 2 };
		if (Collision::Boxcol({ player->GetPosition().x,player->GetPosition().y },
			{ player->GetPosition().x + 2,player->GetPosition().y + 2 }, DamageArea, DamageAreaStart
		) == true) {
			player->SetHp(player->getHp() - 1);
		}
	} else {
		DamageAreaStart = { Position.x,Position.y - 2 };
		DamageArea = { Position.x + 5,Position.y + 2 };
		if (Collision::Boxcol({ player->GetPosition().x,player->GetPosition().y },
			{ player->GetPosition().x + 2,player->GetPosition().y + 2 }, DamageAreaStart, DamageArea
		) == true) {
			player->SetHp(player->getHp() - 1);
		}
	}

	if (Rotation.z >= -360) {
		bossjumpflag = true;
		Rotation.z -= 20;
	} else {
		bossjumpflag = false;
		bossAction = None;
		Rotation.z = 0;
	}
	//player->SetHp(player->getHp() - 1);

	//bossAction = None;
}

void ForestBoss::appearance(float& camerapos)
{

	if (phase) {
		cameratime += 0.01f;
		camerapos = Easing::EaseOut(cameratime, camerapos, 35.37f);
		//bossAction = None;
	} else {
		startcount += 0.01;
		camerapos = 67.235f;
		bossjumpflag = true;
		if (startcount > 2.0f) {
			bossAction = None;
			phase = true;
		}
	}
}

void ForestBoss::GetDamage()
{

	if (HP == MaxHP) {
		OldHP = HP - 1;
	}
	if (HP == OldHP && !damageRec) {
		damageRec = true;
		OldHP--;
	}
	if (damageRec) {
		r = 1.0f; g = 0.2f; b = 0.0f;
		damageRec = false;
	} else {
		if (r > 0.0f)r -= 0.1f;
		if (g < 1.0f)g += 0.1f;
		if (b < 1.0f)b += 0.1f;
		//BossObject->SetColor({ 1,1.0f,1.0f,1 });
	}
	BossObject->SetColor({ r,g,b,1.0f });
}
void ForestBoss::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position) {

}