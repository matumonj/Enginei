#include "Player.h"
#include"Input.h"
#include"DebugTxt.h"
#include"SphereCollider.h"
#include"Collision.h"
#include"Destroy.h"
using namespace DirectX;

Player* Player::Create(Model* model)
{
	//インスタンスを生成
	Player* instance = new Player();
	if (instance == nullptr) {
		return nullptr;
	}

	//初期化
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
	// コライダーの追加
	float radius = 0.6f;
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	//collider->SetAttribute(COLLISION_ATTR_ALLIES);

	return true;
}
void Player::Update(XMFLOAT4 color)
{
	Input* input = Input::GetInstance();


	//移動ベクトルをy軸周りの角度で回転
	XMVECTOR move = { 0,0,0.1f,0 };
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	move = XMVector3TransformNormal(move, matRot);


	//行列の更新とか
	Object3d::Update({ 1,1,1,1 });
}

void Player::OnCollision(const CollisionInfo& info)
{
	//debugText->Print("Hit", 950, 20, 3.0f);
	//}
	//テキストと表示
	//DebugTxt::GetInstance()->Print("Hit",950,20,3);
}

void Player::Attack(XMFLOAT3 playerpos)
{
	//向いてる方向に移動
	if (Input::GetInstance()->TriggerKey(DIK_RIGHT)) {
		playerRot = State::Right;
	} else if (Input::GetInstance()->TriggerKey(DIK_LEFT)) {
		playerRot = State::Left;
	}

	if (Input::GetInstance()->TriggerKey(DIK_W)) {
		action = Action::Attack;
	}
	if (Input::GetInstance()->TriggerKey(DIK_S)) {
		action = Action::None;
	}


	if (action == Action::Attack) {

		timer++;
		switch (playerRot)
		{
		case State::Left:
			Area_X_s = 5;
			Area_X_e =0;
			break;

		case State::Right:
			Area_X_e = 4;
			Area_X_s = 0;
			break;
		}
		
		if (timer >= 2) {
			action = Action::None;
			timer = 0;
		}
	} 
	HP = max(HP, 0);
	HP = min(HP, 10);
}

void Player::CollisionAttack(std::unique_ptr<Enemy>enemy[], XMFLOAT3 playerpos)
{
	damageArea.Area_s = { position.x- Area_X_s,position.y - 8 };
	damageArea.Area_e = { position.x + Area_X_e ,position.y + 5 };

	//当たり判定

	if (action == Action::Attack) {
	for (int i = 0; i < 4; i++)
	{
		if (enemy[i] != nullptr) {
			if (Collision::Boxcol(damageArea.Area_s, damageArea.Area_e, { enemy[i]->GetPosition().x - 1,enemy[i]->GetPosition().y - 1 }, { enemy[i]->GetPosition().x + 1,enemy[i]->GetPosition().y + 1 }) == true) {
				enemy[i]->SetDead(true);
			}
		}
		}
	}
}



void Player::CollisionAttack(Enemy*enemy, XMFLOAT3 playerpos)
{
	damageArea.Area_s = { position.x - Area_X_s,position.y - 8 };
	damageArea.Area_e = { position.x + Area_X_e ,position.y + 5 };

	//当たり判定

	if (action == Action::Attack) {
		for (int i = 0; i < 4; i++)
		{
			if (enemy != nullptr) {
				if (Collision::Boxcol(damageArea.Area_s, damageArea.Area_e, { enemy->GetPosition().x - 1,enemy->GetPosition().y - 1 }, { enemy->GetPosition().x + 1,enemy->GetPosition().y + 1 }) == true) {
					enemy->SetDead(true);
				}
			}
		}
	}
}

void Player::Finalize()
{
	Destroy(playerobj);
	Destroy(playermodel);
}