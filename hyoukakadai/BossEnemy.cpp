#include "BossEnemy.h"
#include"Collision.h"
#include"MobEnemy.h"
#include"Helper.h"
#define PI 3.14
bool BossEnemy::altAttackflag = false, BossEnemy::altattacklag = false;
Ray BossEnemy::laserRay;
int BossEnemy::counter = 0;
bool BossEnemy::stayflag;
// Sphere BossEnemy::playersphere;
BossEnemy::BossEnemy()
{
}
BossEnemy* BossEnemy::GetInstance()
{
	static BossEnemy instance;
	return &instance;
}
BossEnemy::~BossEnemy()
{
	delete BossObject, BossModel;
	delete* ThrowObj, ThrowModel;
	for (int i = 0; i < SummonMax; i++) {
		enemy[i].reset();
	}
	//delete BossObject, BossModel;
}
void BossEnemy::MoveBlockJump()
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
			bossjumpflag = true;
			time2 = 0;
		}
	}

}
void BossEnemy::EnemySearchPlayer(Player* player)
{

}
void BossEnemy::Attack(Player* player)
{
	//�����C�L���X�g���������ɓ���Ă���܂���
	playersphere.center = { player->GetPosition().x, player->GetPosition().y, player->GetPosition().z };
	playersphere.radius = 1.0f;
	laserRay.start = { Position.x,Position.y + 0.5f,Position.z };
	laserRay.dir = { -1,0,0 };

	if (bossjumpflag == true) {
		if (bossjumpflag2) {
			Position.y += 0.5f;
		}
		else {
			Position.y += 0.2f;
		}
		bosstime += 0.02f;
	}
	else {
		bossjumpflag2 = false;
	}
}
//����������
void BossEnemy::Initialize()
{
	//���f���̓Ǎ�
	BossModel = Model::CreateFromOBJ("sphere");
	//���f�����蓖��
	BossObject = Object3d::Create();
	BossObject->SetModel(BossModel);
	for (int i = 0; i < SummonMax; i++) {
		enemy[i] = std::make_unique<MobEnemy>();
		enemy[i]->Initialize();
	}
	//�p�����[�^�̃Z�b�g
	Position = { 40,-4,0 };
	Boss_Scl = { 0.5,0.5,0.5 };
	Boss_Rot = { 0,180,0 };
	//���f���̓Ǎ�
	ThrowModel = Model::CreateFromOBJ("sphere");
	for (int i = 0; i < ThrowObjMax; i++) {
		//���f�����蓖��
		//MobObject = new Object3d();
		ThrowObj[i] = Object3d::Create();
		ThrowObj[i]->SetModel(ThrowModel);
		thposition[i] = Position;
	}
	HP = MaxHP;
	startPos = { 40,-18,0 };
}

//�X�V����
void BossEnemy::Update(XMFLOAT3 position)
{
	Old_Pos = Position;

	if (HP <= 0) {
		enemyState = State::DEAD;
	} else {
		enemyState = State::ALIVE;
	}
	for (int i = 0; i < ThrowObjMax; i++) {
		ThrowObj[i]->SetPosition(thposition[i]);
		ThrowObj[i]->Update({ 1,1,1,1 });
	}
	//SetHP(HP);
	for (int i = 0; i < SummonMax; i++)
	{
		summonEnemy[i].SOld_Pos = enemy[i]->GetPosition();
		enemy[i]->Setposition(SummonEnemyPos[i]);
		enemy[i]->Update(position);
	}
	BossObject->Update({ 1,1,1,1 });
	//���u
	BossObject->SetPosition(Position);
	BossObject->SetScale({ 1,1,1 });
	BossObject->SetRotation(Boss_Rot);

}

//�`�揈��
void BossEnemy::Draw()
{
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
	
	for (int i = 0; i < ThrowObjMax; i++) {
		ThrowObj[i]->PreDraw();
		ThrowObj[i]->Draw();
		ThrowObj[i]->PostDraw();
	}
	for (int i = 0; i < SummonMax; i++) {
		enemy[i]->Draw();
	}
}

//�������
void BossEnemy::Finalize()
{
	
}
void BossEnemy::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{
	//grav-grav
//time-time
//movespeed-movespeed
	float height;//
	float width;
	XMFLOAT3 Player_Scl = {1,1,1 };
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Position.x + Player_Scl.x > mapx[j][i] - (width - bossmovespeed) && Position.x - Player_Scl.x < mapx[j][i] + (width - bossmovespeed))) {
					if (Old_Pos.y > mapy[j][i] && Position.y - Player_Scl.y < mapy[j][i] + height) {
						Position.y = height + mapy[j][i] + Player_Scl.y;
						//moveSpeed = 0;
						bossgrav = 0.0f;
						bosstime = 0;
						bossjumpflag = false;
						//	Line::GetInstance()->SetBondflag(false);
						break;
					} else if (Old_Pos.y <mapy[j][i] && Position.y + Player_Scl.y>mapy[j][i] - height) {
						Position.y = mapy[j][i] - (Player_Scl.y + height);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}

				} else {
					bossmovespeed = 0.2f;
					bossgrav = 0.03;
				}

				//�v���C���[�̍���
				if ((Position.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Position.y + Player_Scl.y)) {
					if (Position.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						//bossjumpflag = true;
						Position.y = Position.y + 0.001f;
						Position.x = width + mapx[j][i] + Player_Scl.x;
						hitf = true;
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
					//�v���C���[�̉E��
					else if (Position.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						//bossjumpflag = true;
						hitf = true;
						Position.x = mapx[j][i] - (Player_Scl.x + width);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
				} else {
					hitf = false;
					bossmovespeed = 0.2f;
				}
			}
		}
	}

	bosstime += 0.04f;
	Position.y -= bossgrav * bosstime * bosstime;
	//
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			for (int k = 0; k < ThrowObjMax; k++) {
				if (map[j][i] == 1) {
					if ((thposition[k].x + 0.5f > mapx[j][i] - 0.5f && thposition[k].x - 0.5f < mapx[j][i] + 0.5f) &&
						thposition[k].y + 0.5f > mapy[j][i] && thposition[k].y - 0.5f < mapy[j][i] + 0.5f) {
						throwparam[k].flag = false;
					}
					if (throwparam[k].time > 200) {
						throwparam[k].flag = false;
					}
				}
			}
		}
	}


}

void BossEnemy::Motion(Player*player)
{

	switch (bossAction)
	{
	case SetStartPos://�����ʒu�ɖ߂���
		Helper::Follow(startPos, Position, 0.1f, bossmovespeed);
		if (Collision::GetLen(Position, startPos) <= 1.0f) {
			bossAction = Stay;//�����ʒu�ɖ߂�����r�[���̏���(�ҋ@)
		}
		MoveBlockJump();//�����ł��߂�r���u���b�N�Ƃ���������W�����v
		break;
	case None://�f�t�H�̓���
		//���ɂȂ���Βǂ������Ă���
		Follow(player->GetPosition());

		if (HP<MaxHP/2) {
			bossAction = SetStartPos;//�̗͂����ȉ��Ȃ����珉���ʒu��
		}
		if (Collision::GetLenX(Position, player->GetPosition()) > 5) {
			MoveBlockJump();//�{�X�̖��܂���p�ƃu���b�N��щz���Ƃ�
		} else {
			if (Collision::GetLenY(Position, player->GetPosition()) > 10) {
				bossAction = NormalAttack;//�v���C���[����̕��������瓊��
			}
		}
		if (Input::GetInstance()->TriggerKey(DIK_S)) {
			bossAction = SummonEnemyAttack;
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
	case Jump:

		break;
	case Stay://�r�[���O�̑ҋ@
		counter++;
		if (counter > 300) {
			bossAction = AltAttack;
		}
		stayflag = true;//�G�t�F�N�g�p�̑ҋ@�t���O

		break;
	case SummonEnemyAttack:
		SummonEnemy(player->GetPosition());
		break;
	case AltAttack://�r�[��
		stayflag = false;
		Attackcount++;
		if (Attackcount > 10) {
			altattacklag = true;//�u���b�N�̔j��ƃr�[���̃^�C�~���O���킹
		}
		if (Attackcount > 100) {//��莞�Ԍo�߂�����U���I��
			altAttackflag = false;//����Ȃ��
			Attackcount = 0;
			altattacklag = false;//�Q����񂾁H
			bossAction = NormalAttack;
		} else {
			altAttackflag = true;
		}
		//�{�X�r�[���̃��C�ƃv���C��[�̓����蔻��
		if (Collision::CheckRay2Sphere(laserRay, playersphere)==true){
			player->SetHp(player->getHp() - AltDamage);
		}
		break;
	case NormalAttack:
		ThrowAttack(player);
		break;
	default:
		break;
	}
	
}


void BossEnemy::ThrowAttack(Player* player)
{
	for (int i = 0; i < ThrowObjMax; i++) {
		if (throwparam[i].flag == true) {
			throwparam[i].time++;
			throwparam[i].movex = (throwparam[i].initialvec_x * throwparam[i].time) / 600 / (i + 1);
			throwparam[i].movey = (throwparam[i].initialvec_y * throwparam[i].time +
				0.5f * throwparam[i].grav * throwparam[i].time * throwparam[i].time) / 600 / (i + 1);
			thposition[i].x += pm[i] * (throwparam[i].movex * 2);

			thposition[i].y += throwparam[i].movey * 2;
			thposition[i].y += throwparam[i].movey * 2;
		}
		if (attackcount % 20 == 0) {
			if (throwparam[i].flag == false) {
				throwparam[i].flag = true;
				thposition[i] = Position;
				throwparam[i].time = 0;
				throwparam[i].movex = 0;
				throwparam[i].movey = 0;
				ThrowObj[i]->SetScale({ 1,1,1 });
				if (player->GetPosition().x <= Position.x) {
					pm[i] = -1;
				} else {
					pm[i] = 1;
				}
				break;
			}

		}

	}
	attackcount++;
	for (int i = 0; i < ThrowObjMax; i++) {
		if (Collision::GetLen(player->GetPosition(), thposition[i]) <= 2 && throwparam[i].flag == true&& !throwparam[i].smflag) {
			player->SetHp(player->getHp() - ThrowDamage);
			throwparam[i].smflag = true;
		}
		
		if (throwparam[i].smflag) {
			if (ThrowObj[i]->GetScale().x >= 0) {
				ThrowObj[i]->SetScale({ ThrowObj[i]->GetScale().x - 0.25f ,ThrowObj[i]->GetScale().y - 0.25f,1 });
			}
			else {
				throwparam[i].smflag = false;
				throwparam[i].flag = false;
			}
		}
	}
	
}

void BossEnemy::Follow(XMFLOAT3 position)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (position.x - Position.x);
	angleZ = (position.y - Position.y);
	angleR = sqrtf((Position.x - position.x) * (Position.x - position.x)
		+ (Position.y - position.y) * (Position.y - position.y));
	if (angleR > 5) {
		Position.x += (angleX / angleR) * (bossmovespeed / 2);
	}
}

void BossEnemy::SummonEnemy(XMFLOAT3 position)
{
	for (int i = 0; i < SummonMax; i++) {
	if (!bossjumpflag2&&!summonattackflag) {
		bossjumpflag2 = true;
		bossjumpflag = true;
	}
	else {
		if(Position.y>-2){
				if (summonEnemy[i].flag == false) {
					summonEnemy[i].flag = true;
					summonattackflag = true;
				}
			}
		}
	}
	for (int i = 0; i < SummonMax; i++) {
		switch (i)
		{
		case 0:
			summonEnemy[0].initialvec_x = -1.0f;
			break;
		case 1:
			summonEnemy[1].initialvec_x = -0.5f;
			break;
		case 2:
			summonEnemy[2].initialvec_x = 0.0f;
			break;
		case 3:
			summonEnemy[3].initialvec_x = 0.5f;
			break;
		case 4:
			summonEnemy[4].initialvec_x = 1.0f;
			break;
		default:
			break;
		}
	
		if (summonEnemy[i].flag == true) {
				summonEnemy[i].time++;
				summonEnemy[i].movex = (summonEnemy[i].initialvec_x * summonEnemy[i].time) / 1500;
				summonEnemy[i].movey = (summonEnemy[i].initialvec_y * summonEnemy[i].time +
					0.5f * summonEnemy[i].grav * summonEnemy[i].time * summonEnemy[i].time) / 1500;
				SummonEnemyPos[i].x += (summonEnemy[i].movex * 2);

				SummonEnemyPos[i].y += summonEnemy[i].movey * 2;
				SummonEnemyPos[i].z = -1;
				if (SummonEnemyPos[i].y < -30) {
					summonEnemy[i].flag = false;
					bossjumpflag2 = false;
					bossjumpflag = false;
					bossAction = None;
				}
		}

			if (summonEnemy[i].flag == false) {
				SummonEnemyPos[i] = Position;
				summonEnemy[i].time = 0;
				summonEnemy[i].movex = 0;
				summonEnemy[i].movey = 0;
				enemy[i]->SetScale({ 1,1,1 });
		}
		}
}