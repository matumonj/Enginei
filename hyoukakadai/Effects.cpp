#include "Effects.h"
#include"imgui.h"
#include"GameUI.h"
Effects::~Effects()
{
	delete efk,attackefk;
}
void Effects::Initialize(DirectXCommon* dxcomn, DebugCamera* camera)
{
	//�G�t�F�N�g�̃C���X�^���X����
	efk = new mEffekseer();
	Healefk = new mEffekseer();
	attackefk = new mEffekseer();
	bossattackefk = new mEffekseer();
	//efk1 = new mEffekseer();

	//�G�t�F�N�g�̃Z�b�g(3��������)
	attackefk->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/attack - �R�s�[.efk", (const EFK_CHAR*)L"effect/10");
	efk->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/deadef.efk", (const EFK_CHAR*)L"effect/10");
	bossattackefk->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/laser.efk", (const EFK_CHAR*)L"effect/10");
	Healefk->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/Heal.efk", (const EFK_CHAR*)L"effect/10");

	//b_Effect_Rot = { -25.08,90,0 };
	//efk1->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/SimpleLaser.efk", (const EFK_CHAR*)L"effect/10");
}
void Effects::HealEffect(bool heal,bool healfs)
{
	GameUI::GetInstance()->GetOutX();

	if (heal||healfs) {
		healf = true;
		//healf = true;
	}
	if (healf) {
		Healefk->Load_Effect();
		healf = false;
	}
}
void Effects::HealEffects(bool heal)
{
	GameUI::GetInstance()->GetOutX();

	if (heal ) {
		healf = true;
		//healf = true;
	}
	if (healf) {
		Healefk->Load_Effect();
		healf = false;
	}
}
void Effects::Update2(DirectXCommon* dxcomn, DebugCamera* camera, std::unique_ptr<Enemy>enemy[], Player* player)
{
	Healefk->SetPosition(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);

	for (int i = 0; i < 10; i++) {
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
		attackefk->SetPosition(player->GetPosition().x - 2, player->GetPosition().y, player->GetPosition().z);
		attackefk->SetRotation(1, 180, 0);
	} else if (player->GetRot_Right()) {
		attackefk->SetPosition(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
		attackefk->SetRotation(1, 90, 0);
		//Effect_Rot = { 0,0,0 };
	}
	if (Input::GetInstance()->TriggerKey(DIK_A)) {
		attack = true;
	}

	//�R���g���[���[
	if (Input::GetInstance()->TriggerButtonA()) {
		//�U������
		attack = true;
	}
	if (player->GetFlyAttack() == true) {
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
	bossattackefk->EffekseerUpdate(dxcomn, camera);
	Healefk->EffekseerUpdate(dxcomn, camera);
	//efk1->EffekseerUpdate(dxcomn, camera);

}
void Effects::Update(DirectXCommon*dxcomn,DebugCamera*camera,  std::unique_ptr<Enemy>enemy[],Player*player)
{
	Healefk->SetPosition(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
	
	for (int i=0; i < 10; i++) {
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
	if (Input::GetInstance()->TriggerKey(DIK_A)) {
		attack = true;
	}
	
	//�R���g���[���[
	if (Input::GetInstance()->TriggerButtonA()) {
		//�U������
		attack = true;
	}
	if (player->GetFlyAttack()==true) {
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
	bossattackefk->EffekseerUpdate(dxcomn, camera);
	Healefk->EffekseerUpdate(dxcomn, camera);
	//efk1->EffekseerUpdate(dxcomn, camera);

}
void Effects::ImGuiDraw()
{
	ImGui::Begin("1");
	ImGui::SetWindowPos(ImVec2(200, 0));
	ImGui::SetWindowSize(ImVec2(500, 300));
	if (ImGui::TreeNode("cameraposition")) {
		float cy;
		ImGui::SliderFloat("cy", &b_Effect_Rot.y, 200, -200);
		ImGui::TreePop();
	}
	ImGui::End();
}
void Effects::Updateo(DirectXCommon* dxcomn, DebugCamera* camera,Enemy*enemy, Player* player)
{
	//for (int i = 0; i < 4; i++) {
		if (enemy != nullptr) {
			if (enemy->GetHP()==0) {
				deathf = true;
			}
			if (deathf == true) {
				efk->SetPosition(enemy->GetPosition().x, enemy->GetPosition().y, enemy->GetPosition().z);
				efk->Load_Effect();
				efk->SetScale( 3,3,3 );
				efk->SetColor(1, 0, 0.2);
				deathf = false;
			}
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
	//attackefk->EffekseerUpdate(dxcomn, camera);
	//bossattackefk->EffekseerUpdate(dxcomn, camera);

	//efk1->EffekseerUpdate(dxcomn, camera);

}
void Effects::BossAttackEffect(DirectXCommon* dxcomn, DebugCamera* camera, bool stay,bool altAttack, XMFLOAT3 bpos)
{
	b_Effect_Pos =bpos;
	if (stay == true) {
		b_Effect_SCl = { 0.5,0.5,0.01 };
	}
	else {
		b_Effect_SCl = { 1,2.5,10 };
	}

	if (altAttack||stay) {
		b_attack = true;
	}
	else {
		b_attack = false;
	}
	if (b_attack) {
		bossattackefk->Load_Effect();
		//b_attack = false;
		
	}
	bossattackefk->SetPosition(b_Effect_Pos.x, b_Effect_Pos.y, b_Effect_Pos.z);
	bossattackefk->SetRotation(b_Effect_Rot.x, b_Effect_Rot.y, b_Effect_Rot.z);
	bossattackefk->SetScale(b_Effect_SCl.x, b_Effect_SCl.y, b_Effect_SCl.z);
	//bossattackefk->SetColor(0, 1, 0);


}
void Effects::Draw(DirectXCommon*dxcomn)
{
	//�G�t�F�N�g�̉摜

	Healefk->EffekseerDraw(dxcomn->GetCmdList());
	efk->EffekseerDraw(dxcomn->GetCmdList());
	attackefk->EffekseerDraw(dxcomn->GetCmdList());
	bossattackefk->EffekseerDraw(dxcomn->GetCmdList());
	//efk1->EffekseerDraw(dxcomn->GetCmdList());
}

void Effects::BossDeath(XMFLOAT3 position, bool f)
{
	if (f) {
		deathf = true;
	}
	if (deathf) {
		efk->SetPosition(position.x, position.y+10, position.z);
		efk->Load_Effect();
		deathf = false;
		//f = false;
	}
}