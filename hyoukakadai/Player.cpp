#include "Player.h"
#include"Input.h"
#include"DebugTxt.h"
#include"SphereCollider.h"

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

	if (input->Pushkey(DIK_A)) {
		rotation.y -= 2.0f;
	} else if (input->Pushkey(DIK_D)) {
		rotation.y += 2.0f;
	}

	//移動ベクトルをy軸周りの角度で回転
	XMVECTOR move = { 0,0,0.1f,0 };
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	move = XMVector3TransformNormal(move, matRot);

	//向いてる方向に移動
	if (input->Pushkey(DIK_S)) {
		position.x -= move.m128_f32[0];
		position.y -= move.m128_f32[1];
		position.z -= move.m128_f32[2];
	} else if (input->Pushkey(DIK_W)) {
		position.x += move.m128_f32[0];
		position.y += move.m128_f32[1];
		position.z += move.m128_f32[2];
	}
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