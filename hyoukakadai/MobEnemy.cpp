#include "MobEnemy.h"
#include<math.h>
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
	Mob_Pos = { -10,-2,0 };
	Position = { 20,0,0 };
}

//�X�V����
void MobEnemy::Update(XMFLOAT3 position)
{
	//�p�����[�^�̃Z�b�g
	//���u
	//MobObject->SetPosition(Position);
	MobObject->SetScale({ 1,1,1 });
	MobObject->SetRotation({0,180,0});
	
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
void MobEnemy::EnemySearchPlayer(XMFLOAT3 player)
{
	Follow(player);
}

void MobEnemy::Follow(XMFLOAT3 player)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (player.x - Position.x);
	angleZ = (player.y - Position.y);
	angleR = sqrtf((Position.x - player.x) * (Position.x - player.x)
		+ (Position.y - player.y) * (Position.y - player.y));
	Position.x += (angleX / angleR) * centerSpeed;
	Position.y += (angleZ / angleR) * centerSpeed;
	//Position.x =player.x;
	//Position.y =player.y;
	//MobObject->SetPosition(Position);
	//MobObject->SetPosition(Position);
}