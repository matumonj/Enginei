#include "MobEnemy.h"
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
	MobModel = Model::CreateFromOBJ("subenemy");
	//���f�����蓖��
	//MobObject = new Object3d();
	MobObject = Object3d::Create();
	MobObject->SetModel(MobModel);

	//�p�����[�^�̃Z�b�g
	Mob_Scl = { 2,2,2 };
	Mob_Rot = { 0,180,0 };
	Mob_Pos = { -10,-2,0 };
}

//�X�V����
void MobEnemy::Update()
{
	//�p�����[�^�̃Z�b�g
	//���u
	MobObject->SetPosition(Mob_Pos);
	MobObject->SetScale({ 1,1,1 });
	MobObject->SetRotation(Mob_Rot);
	
	MobObject->Update({ 1,1,1,1 });
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