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
//初期化処理
void BossEnemy::Initialize()
{
	//モデルの読込
	BossModel = Model::CreateFromOBJ("bossenemy");
	//モデル割り当て
	//BossObject = new Object3d();
	BossObject = Object3d::Create();
	BossObject->SetModel(BossModel);

	//パラメータのセット
	Boss_Scl = { 2,2,2 };
	Boss_Rot = { 0,180,0 };
	Boss_Pos = { 10,-2,0 };
}

//更新処理
void BossEnemy::Update(XMFLOAT3 position)
{
	//パラメータのセット
	//モブ
	BossObject->SetPosition(Boss_Pos);
	BossObject->SetScale({ 1,1,1 });
	BossObject->SetRotation(Boss_Rot);
	BossObject->Update({ 1,1,1,1 });
}

//描画処理
void BossEnemy::Draw()
{
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
}

//解放処理
void BossEnemy::Finalize()
{
	delete BossObject, BossModel;
}
void BossEnemy::ColMap(int map[15][100], float mapx[15][100], float mapy[15][100], const int X, const int Y)
{
	
}