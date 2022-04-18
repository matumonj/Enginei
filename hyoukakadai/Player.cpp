#include "Player.h"
#include"Input.h"
#include"DebugTxt.h"
#include"SphereCollider.h"
#include"Collision.h"
using namespace DirectX;

Player* Player::Create(Model* model)
{
	//�C���X�^���X�𐶐�
	Player* instance = new Player();
	if (instance == nullptr) {
		return nullptr;
	}

	//������
	instance->Initialize();//	delete instance;
	//	assert(0);

	if (model) {
		instance->SetModel(model);
	}
	return instance;
}

bool Player::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//aaaaaaa
	// �R���C�_�[�̒ǉ�
	float radius = 0.6f;
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	//collider->SetAttribute(COLLISION_ATTR_ALLIES);

	return true;
}
void Player::Update(XMFLOAT4 color)
{
	Input* input = Input::GetInstance();


	//�ړ��x�N�g����y������̊p�x�ŉ�]
	XMVECTOR move = { 0,0,0.1f,0 };
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	move = XMVector3TransformNormal(move, matRot);


	//�s��̍X�V�Ƃ�
	Object3d::Update({ 1,1,1,1 });
}

void Player::OnCollision(const CollisionInfo& info)
{
	//debugText->Print("Hit", 950, 20, 3.0f);
	//}
	//�e�L�X�g�ƕ\��
	//DebugTxt::GetInstance()->Print("Hit",950,20,3);
}

void Player::Attack(XMFLOAT3 playerpos)
{
	//�����Ă�����Ɉړ�
	if (Input::GetInstance()->TriggerKey(DIK_RIGHT)) {
		playerRot = State::Right;
	} else if (Input::GetInstance()->TriggerKey(DIK_LEFT)) {
		playerRot = State::Left;
	}

	if (Input::GetInstance()->TriggerKey(DIK_P)) {
		action = Action::Attack;
	}
	if (Input::GetInstance()->TriggerKey(DIK_N)) {
		action = Action::None;
	}


	if (action == Action::Attack) {

		timer++;
		switch (playerRot)
		{
		case State::Left:
			Area_X = 50;
			break;

		case State::Right:
			Area_X = 50;
			break;
		}
		
		if (timer >= 2) {
			action = Action::None;
			timer = 0;
		}
	} 

}

void Player::CollisionAttack(std::unique_ptr<Enemy>enemy[], XMFLOAT3 playerpos)
{
	damageArea.Area_s = { position.x ,position.y - 5 };
	damageArea.Area_e = { position.x + 5 ,position.y + 5 };

	//�����蔻��

	if (action == Action::Attack) {
	for (int i = 0; i < 2; i++)
	{
		if (enemy[i] != nullptr) {
			if (Collision::Boxcol(damageArea.Area_s, damageArea.Area_e, { enemy[i]->GetPosition().x - 1,enemy[i]->GetPosition().y - 1 }, { enemy[i]->GetPosition().x + 1,enemy[i]->GetPosition().y + 1 }) == true) {
				enemy[i]->SetDead(true);
			}
		}
		}
	}
}
