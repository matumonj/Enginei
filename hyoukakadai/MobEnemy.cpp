#include "MobEnemy.h"
/// <summary>
/// コンストラクタ
/// </summary>
MobEnemy::MobEnemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
MobEnemy::~MobEnemy()
{
	delete MobObject, MobModel;
}

//初期化処理
void MobEnemy::Initialize()
{
	//モデルの読込
	MobModel = Model::CreateFromOBJ("subenemy");
	//モデル割り当て
	//MobObject = new Object3d();
	MobObject = Object3d::Create();
	MobObject->SetModel(MobModel);

	//パラメータのセット
	Mob_Scl = { 2,2,2 };
	Mob_Rot = { 0,180,0 };
	Mob_Pos = { -10,-2,0 };
}

//更新処理
void MobEnemy::Update()
{
	//パラメータのセット
	//モブ
	MobObject->SetPosition(Mob_Pos);
	MobObject->SetScale({ 1,1,1 });
	MobObject->SetRotation(Mob_Rot);
	
	MobObject->Update({ 1,1,1,1 });
}

//描画処理
void MobEnemy::Draw()
{
	MobObject->PreDraw();
	MobObject->Draw();
	MobObject->PostDraw();
}

//解放処理
void MobEnemy::Finalize()
{
	delete MobObject, MobModel;
}