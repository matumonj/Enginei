#include "Player.h"
#include"Input.h"
#include"DebugTxt.h"
#include"SphereCollider.h"
#include"Collision.h"
#include"Destroy.h"
#include"Fader.h"
#include"Line.h"
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
	LONG u_r = 32768;
	LONG a = 30000;
	//向いてる方向に移動

	//コントローラー
	if (Input::GetInstance()->TriggerButtonA()||Input::GetInstance()->TriggerKey(DIK_A)) {
		//攻撃処理
		action = Action::Attack;
	}

	if (action == Action::Attack) {

		timer++;
		switch (playerRot)
		{
		case State::Left:
			Area_X_s = 5;
			Area_X_e = 0;
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
	
}
void Player::CollisionAttack(std::unique_ptr<Enemy>enemy[], XMFLOAT3 playerpos)
{
	damageArea.Area_s = { position.x- Area_X_s,position.y - 3 };
	damageArea.Area_e = { position.x + Area_X_e ,position.y + 3 };

	//当たり判定

	if (action == Action::Attack) {
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr) {
			if (Collision::Boxcol(damageArea.Area_s, damageArea.Area_e, { enemy[i]->GetPosition().x,enemy[i]->GetPosition().y - 1 }, { enemy[i]->GetPosition().x ,enemy[i]->GetPosition().y + 1 }) == true) {
				enemy[i]->SetDead(true);
			}
		}
		}
	}
}



void Player::CollisionAttack1(Enemy*enemy, XMFLOAT3 playerpos)
{
	damageArea.Area_s = { position.x - Area_X_s,position.y - 8 };
	damageArea.Area_e = { position.x + Area_X_e ,position.y + 5 };

	//当たり判定

	if (action == Action::Attack) {
		
		if (enemy != nullptr) {
			if (Collision::Boxcol(damageArea.Area_s, damageArea.Area_e,
				{ enemy->GetPosition().x - 3,enemy->GetPosition().y - 3 },
				{ enemy->GetPosition().x + 3,enemy->GetPosition().y + 3}) == true) {
				enemy->SetHP(enemy->GetHP() - 1);
			}
		}
	}
}

void Player::PlayerMoves(XMFLOAT3& move, float moveSpeed, bool& JumpFlag, float& grav, float& time,XMFLOAT3& rot) {
	///////// コントローラー //////////
	// スティックの方向判定
	// 無反応範囲
	LONG u_r = 32768;
	LONG a = 30000;

	//左
	// 方向だけを調べる方法

	
	if (Line::GetInstance()->GetStop() == false) {
		//grav = 0;
		//time = 0;
		JumpFlag = false;
	}
	if (Line::GetInstance()->GetStop() == true) {

		if (Input::GetInstance()->GetCMove().lX < u_r - a)
		{
			//if (Fader::GetInstance()->GetAlpha() <= 0.1f) {
				// 左に傾けた
			if (move.x <= 0) {
				moveSpeed = 0;
			}
			else {
				playerRot = State::Left;
				move.x -= moveSpeed;
				rot.y = 90;
			}
			//}
		}
		else if (Input::GetInstance()->GetCMove().lX > u_r + a)
		{
			//if (Fader::GetInstance()->GetAlpha() <= 0.1f) {
				// 右に傾けた
			playerRot = State::Right;
			move.x += moveSpeed;
			//}
			rot.y = -90;
		}
		if (Input::GetInstance()->TriggerButtonB())
		{
			JumpFlag = true;
			// 左に傾けた
			//Player_Pos.x -= moveSpeed;

		}
	}

	if (JumpFlag == true) {
		move.y += 0.12f;
		time += 0.02f;
	}

	

}


void Player::Finalize()
{
	Destroy(playerobj);
	Destroy(playermodel);
}

void Player::FlyingAttack(Enemy* enemy)
{
	float len;
	
	if (Line::GetInstance()->Getelf() == true ) {
		len = (position.x - enemy->GetPosition().x) * (position.x - enemy->GetPosition().x) +
			(position.y - enemy->GetPosition().y) * (position.y - enemy->GetPosition().y);
		if (len <= 2) {
			flyattack_f = true;
		}
}
	if (flyattack_f) {
		if (enemy != nullptr) {
			enemy->SetDead(true);
			//flyattack_f = false;
		}
		else {
			flyattack_f = false;
		}
	}
}