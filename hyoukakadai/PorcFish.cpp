#include "PorcFish.h"
#include<math.h>
#include"Line.h"
/// <summary>
/// コンストラクタ
/// </summary>
PorcFish::PorcFish()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PorcFish::~PorcFish()
{
	delete ThronObject, ThronModel;
}

//初期化処理
void PorcFish::Initialize()
{
	//モデルの読込
	ThronModel = Model::CreateFromOBJ("enemy_harisenbon");
	//モデル割り当て
	//ThronObject = new Object3d();
	ThronObject = Object3d::Create();
	ThronObject->SetModel(ThronModel);
	//ThronObject->Initialize();
	//パラメータのセット
	HP = 10;

}

//更新処理
void PorcFish::Update(XMFLOAT3 position)
{

	if (jumpflag == true) {
		Position.y += 0.5f;
		time += 0.02f;
	}
	//float lx = Line::GetInstance()->getpos().x;
	//float ly= Line::GetInstance()->getpos().y;
	////パラメータのセット
	//float dis;
	//
	//	dis = sqrtf((lx-Position.x) * (lx - Position.x) +
	//		(ly - Position.y) * (ly - Position.y));

	//	if (dis <= 2 &&Line::GetInstance()->Gettriggerflag()) {
	//		Line::GetInstance()->Setelf(true);
	//	}

	//	if (Line::GetInstance()->Getelf()) {
	//		Line::GetInstance()->Setpos(Position.x,Position.y);
	//	}
	//モブ
	//ThronObject->SetPosition(Position);
	if (HP < 0) {
		enemyState = State::DEAD;
	} else {
		//	enemyState = State::ALIVE;
	}
	ThronObject->SetScale({ 0.5,0.5,0.5 });
	ThronObject->SetRotation({ 0,180,0 });


	ThronObject->Update({ 1,1,1,1 });
	ThronObject->SetPosition(Position);

}

//描画処理
void PorcFish::Draw(DirectXCommon* dxcomn)
{
	ThronObject->PreDraw();
	ThronObject->Draw();
	ThronObject->PostDraw();
}

//解放処理
void PorcFish::Finalize()
{
	delete ThronObject, ThronModel;
}
void PorcFish::EnemySearchPlayer(Player* player)
{
	//Follow(player);
}

void PorcFish::Follow(Player* player)
{

}

void PorcFish::Motion(Player* player)
{
	countUpDownMove++;
	float PI = 3.14;
	const float moveCycle = 120.0f;
	//if (!NuclearDeayh) {
		Position.y = Position.y + sin(PI * 2 / moveCycle * countUpDownMove) * 1.2;
		//Rotation.y = BarrelRotFollow * 60 + 180;

	//}
	//if (NuclearHP == 1) {

		//NuclearDeayh = true;
	//}
	//DeathMotion();
//	if (NuclearDeayh && Position.y < position.y - 20) {
		//SetHP(0);
		//SetDead(true);
		//enemyState = State::DEAD;
	//}
		float dis;
		dis = sqrtf((player->GetPosition().x - Position.x) * (player->GetPosition().x - Position.x) +
			(player->GetPosition().y - Position.y) * (player->GetPosition().y - Position.y));
		if (dis <= 2) {
			//servDamage = true;
			if (servDamage) {
				player->SetHp(player->getHp() - 10);
				servDamage = false;
				stayflg = true;
				//Attack(player);
			}
		}
		if (stayflg) {
			redamageCount++;
			if (redamageCount > 30) {
				servDamage = true;
				redamageCount = 0;
				stayflg = false;
			}
		}
}
void PorcFish::Attack(Player* player)
{
	//player->SetHp(player->getHp() - AttackDamage);
}
void PorcFish::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{

}

void PorcFish::enemyappearance(TyutorialSprite* sprite)
{

}
void PorcFish::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)
{
}
void PorcFish::ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)
{}