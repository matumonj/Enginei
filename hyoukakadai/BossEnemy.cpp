#include "BossEnemy.h"

BossEnemy::BossEnemy()
{
}

BossEnemy::~BossEnemy()
{
	delete BossObject, BossModel;
}

void BossEnemy::EnemySearchPlayer(Player* player)
{

}
//����������
void BossEnemy::Initialize()
{
	//���f���̓Ǎ�
	BossModel = Model::CreateFromOBJ("bossenemy");
	//���f�����蓖��
	//BossObject = new Object3d();
	BossObject = Object3d::Create();
	BossObject->SetModel(BossModel);

	//�p�����[�^�̃Z�b�g
	Boss_Scl = { 2,2,2 };
	Boss_Rot = { 0,180,0 };
	Boss_Pos = { 10,-2,0 };
}

//�X�V����
void BossEnemy::Update(XMFLOAT3 position)
{
	//�p�����[�^�̃Z�b�g
	//���u
	BossObject->SetPosition(Boss_Pos);
	BossObject->SetScale({ 1,1,1 });
	BossObject->SetRotation(Boss_Rot);
	BossObject->Update({ 1,1,1,1 });
}

//�`�揈��
void BossEnemy::Draw()
{
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
}

//�������
void BossEnemy::Finalize()
{
	delete BossObject, BossModel;
}
void BossEnemy::ColMap(int map[15][100], float mapx[15][100], float mapy[15][100], const int X, const int Y)
{
	
}