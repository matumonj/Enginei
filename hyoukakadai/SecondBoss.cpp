#include "SecondBoss.h"
#include"Collision.h"
#include"MobEnemy.h"
#include"Helper.h"
#define PI 3.14

// Sphere SecondBoss::playersphere;
SecondBoss::SecondBoss()
{
}
SecondBoss* SecondBoss::GetInstance()
{
	static SecondBoss instance;
	return &instance;
}
SecondBoss::~SecondBoss()
{
	delete BossObject, BossModel;
}
void SecondBoss::MoveBlockJump()
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
void SecondBoss::EnemySearchPlayer(Player* player)
{

}
void SecondBoss::Attack(Player* player)
{

}
//����������
void SecondBoss::Initialize()
{
	//���f���̓Ǎ�
	BossModel = Model::CreateFromOBJ("sphere");
	//���f�����蓖��
	BossObject = Object3d::Create();
	BossObject->SetModel(BossModel);

	//�p�����[�^�̃Z�b�g
	Position = { 40,-4,0 };
	Boss_Scl = { 0.5,0.5,0.5 };
	Boss_Rot = { 0,180,0 };
	//���f���̓Ǎ�
	HP = MaxHP;
	startPos = { 40,-18,0 };
}
void SecondBoss::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)
{

}

//�X�V����
void SecondBoss::Update(XMFLOAT3 position)
{
	Old_Pos = Position;

	if (HP <= 0) {
		enemyState = State::DEAD;
	} else {
		enemyState = State::ALIVE;
	}
	BossObject->Update({ 1,1,1,1 });
	//���u
	BossObject->SetPosition(Position);
	BossObject->SetScale({ 1,1,1 });
	BossObject->SetRotation(Boss_Rot);

}

//�`�揈��
void SecondBoss::Draw(DirectXCommon*dxcomn)
{
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
}

//�������
void SecondBoss::Finalize()
{

}
void SecondBoss::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{
	//grav-grav
//time-time
//movespeed-movespeed
	float height;//
	float width;
	XMFLOAT3 Player_Scl = { 1,1,1 };
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
						bossgrav = 0.0f;
						bosstime = 0;
						bossjumpflag = false;
						break;
					} else if (Old_Pos.y <mapy[j][i] && Position.y + Player_Scl.y>mapy[j][i] - height) {
						Position.y = mapy[j][i] - (Player_Scl.y + height);
						break;
					}

				} else {
					bossmovespeed = 0.2f;
					bossgrav = 0.03;
				}

				//�v���C���[�̍���
				if ((Position.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Position.y + Player_Scl.y)) {
					if (Position.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						Position.y = Position.y + 0.001f;
						Position.x = width + mapx[j][i] + Player_Scl.x;
						break;
					}
					//�v���C���[�̉E��
					else if (Position.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						Position.x = mapx[j][i] - (Player_Scl.x + width);
						break;
					}
				} else {
					bossmovespeed = 0.2f;
				}
			}
		}
	}

	bosstime += 0.04f;
	Position.y -= bossgrav * bosstime * bosstime;
}

void SecondBoss::Motion(Player* player)
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
	case None:
		Follow(player->GetPosition());

		if (HP < MaxHP / 2) {
			bossAction = SetStartPos;//�̗͂����ȉ��Ȃ����珉���ʒu��
		}
		if (Collision::GetLenX(Position, player->GetPosition()) > 5) {
			MoveBlockJump();//�{�X�̖��܂���p�ƃu���b�N��щz���Ƃ�
		} else {
			if (Collision::GetLenY(Position, player->GetPosition()) > 10) {
				bossAction = NormalAttack;//�v���C���[����̕��������瓊��
			}
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

		break;

	case NormalAttack:

		break;
	default:
		break;
	}

}


void SecondBoss::Follow(XMFLOAT3 position)
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
