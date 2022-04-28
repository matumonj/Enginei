#include "MobEnemy.h"
#include<math.h>
#include"Line.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
MobEnemy::MobEnemy()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MobEnemy::~MobEnemy()
{
	delete MobObject, MobModel;
}

//����������
void MobEnemy::Initialize()
{
	//���f���̓Ǎ�
	MobModel = Model::CreateFromOBJ("bossenemy");
	//���f�����蓖��
	//MobObject = new Object3d();
	MobObject = Object3d::Create();
	MobObject->SetModel(MobModel);
	//MobObject->Initialize();
	//�p�����[�^�̃Z�b�g
	Mob_Scl = { 2,2,2 };
	Mob_Rot = { 0,180,0 };
	//Mob_Pos = { -10,-2,0 };
	//Position = { 24,10,0 };
	HP = 10;

}

//�X�V����
void MobEnemy::Update(XMFLOAT3 position)
{
	//float lx = Line::GetInstance()->getpos().x;
	//float ly= Line::GetInstance()->getpos().y;
	////�p�����[�^�̃Z�b�g
	//float dis;
	//
	//	dis = sqrtf((lx-Position.x) * (lx - Position.x) +
	//		(ly - Position.y) * (ly - Position.y));

	//	if (dis <= 2 &&Line::GetInstance()->Gettriggerflag()) {
	//		Line::GetInstance()->Setelf(true);
	//	}

	//	if (Line::GetInstance()->Getelf()) {
	//		Line::GetInstance()->Setpos(Position.x,Position.y);
	//	}
	//���u
	//MobObject->SetPosition(Position);
	if (HP < 0) {
		enemyState = State::DEAD;
	} else {
	//	enemyState = State::ALIVE;
	}
	MobObject->SetScale({ 0.5,0.5,0.5 });
	MobObject->SetRotation({ 0,180,0 });

	//Follow(position);
	MobObject->Update({ 1,1,1,1 });
	MobObject->SetPosition(Position);

}

//�`�揈��
void MobEnemy::Draw()
{
	MobObject->PreDraw();
	MobObject->Draw();
	MobObject->PostDraw();
}

//�������
void MobEnemy::Finalize()
{
	delete MobObject, MobModel;
}
void MobEnemy::EnemySearchPlayer(Player* player)
{
	//Follow(player);
}

void MobEnemy::Follow(Player*player)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (player->GetPosition().x - Position.x);
	angleZ = (player->GetPosition().y - Position.y);
	angleR = sqrtf((Position.x - player->GetPosition().x) * (Position.x - player->GetPosition().x)
		+ (Position.y - player->GetPosition().y) * (Position.y - player->GetPosition().y));
	if (angleR>5) {
		Position.x += (angleX / angleR) * centerSpeed;
		Position.y += (angleZ / angleR) * centerSpeed;
	}
	//Position.x =player.x;
	//Position.y =player.y;
	MobObject->SetPosition(Position);
	//MobObject->SetPosition(Position);
	float dis;
	dis = sqrtf((player->GetPosition().x - Position.x) * (player->GetPosition().x - Position.x) +
		(player->GetPosition().y - Position.y) * (player->GetPosition().y - Position.y));
	if (dis <= 2) {
		Attack(player);
	}
}

void MobEnemy::Motion(int timer)
{
	switch (enemyState)
	{
	case State::ALIVE:

		break;

	case State::DEAD:

		break;
	}

}
void MobEnemy::Attack(Player*player)
{
		//player->SetHp(player->getHp() - AttackDamage);
}
void MobEnemy::ColMap(int map[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y)
{
	
}

void MobEnemy::enemyappearance(TyutorialSprite* sprite)
{
	if (sprite->GetPhase_Attack() == true) {
		if (Position.y >= -2) {
			Position.y -= 0.5f;
		}
	}
}