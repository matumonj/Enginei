#include "Effects.h"
Effects::~Effects()
{
	delete efk;
}
void Effects::Initialize(DirectXCommon* dxcomn, DebugCamera* camera)
{
	//�G�t�F�N�g�̃C���X�^���X����
	efk = new mEffekseer();
	attackefk = new mEffekseer();
	//efk1 = new mEffekseer();

	//�G�t�F�N�g�̃Z�b�g(3��������)
	attackefk->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/attack - �R�s�[.efk", (const EFK_CHAR*)L"effect/10");
	efk->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/deadef.efk", (const EFK_CHAR*)L"effect/10");
	//efk1->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/SimpleLaser.efk", (const EFK_CHAR*)L"effect/10");
}

void Effects::Update(DirectXCommon*dxcomn,DebugCamera*camera,  std::unique_ptr<Enemy>enemy[],Player*player)
{
	for (int i=0; i < 4; i++) {
		if (enemy[i] != nullptr) {
			if (enemy[i]->GetState_DEAD() == true) {
				df = true;
			}
			if (df == true) {
				efk->SetPosition(enemy[i]->GetPosition().x, enemy[i]->GetPosition().y, enemy[i]->GetPosition().z);
				efk->Load_Effect();
				df = false;
			}
		}
	}
	if (player->GetRot_Left()) {
		attackefk->SetPosition(player->GetPosition().x-2, player->GetPosition().y, player->GetPosition().z);
		attackefk->SetRotation(1, 180, 0);
	}
	else if(player->GetRot_Right()){
		attackefk->SetPosition(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
		attackefk->SetRotation(1, 90, 0);
		//Effect_Rot = { 0,0,0 };
	}
	if (Input::GetInstance()->TriggerKey(DIK_P)) {
		attack = true;
	}
	
	if (attack) {
		attackefk->Load_Effect();
		attack = false;
	}
	//�G�t�F�N�g�̃p�����[�^�Z�b�g
	/*efk->SetPosition(Effect_Pos.x, Effect_Pos.y, Effect_Pos.z);
	efk->SetRotation(0, 0, 0);
	efk->SetScale(1, 1, 1);
	efk1->SetPosition(-10, 0, 190);*/

	//�G�t�F�N�g�̍Đ�
	//if (Input::GetInstance()->Pushkey(DIK_SPACE)) {
	//efk->Load_Effect();
	////}
	//efk1->Load_Effect();

	//�G�t�F�N�g�̃A�j���[�V�����~�߂�
	//if (Input::GetInstance()->Pushkey(DIK_C)) {
	//	efk->Stop_Effect();
	//}

	//view,projection�s����G�t�F�N�g�̃e�N�X�`���ɂ�����
	efk->EffekseerUpdate(dxcomn, camera);
	attackefk->EffekseerUpdate(dxcomn, camera);
	//efk1->EffekseerUpdate(dxcomn, camera);

}

void Effects::Draw(DirectXCommon*dxcomn)
{
	//�G�t�F�N�g�̉摜
	efk->EffekseerDraw(dxcomn->GetCmdList());
	attackefk->EffekseerDraw(dxcomn->GetCmdList());
	//efk1->EffekseerDraw(dxcomn->GetCmdList());
}