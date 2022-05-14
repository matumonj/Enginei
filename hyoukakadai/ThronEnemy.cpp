#include "ThronEnemy.h"
#include<math.h>
#include"Line.h"
/// <summary>
/// コンストラクタ
/// </summary>
ThronEnemy::ThronEnemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ThronEnemy::~ThronEnemy()
{
	delete ThronObject, ThronModel;
}

//初期化処理
void ThronEnemy::Initialize()
{
	//モデルの読込
	ThronModel = Model::CreateFromOBJ("bossenemy");
	//モデル割り当て
	//ThronObject = new Object3d();
	ThronObject = Object3d::Create();
	ThronObject->SetModel(ThronModel);
	//ThronObject->Initialize();
	//パラメータのセット
	HP = 10;
	
}

//更新処理
void ThronEnemy::Update(XMFLOAT3 position)
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

	//Follow(position);
	ThronObject->Update({ 1,1,1,1 });
	ThronObject->SetPosition(Position);

}

//描画処理
void ThronEnemy::Draw(DirectXCommon* dxcomn)
{
	ThronObject->PreDraw();
	ThronObject->Draw();
	ThronObject->PostDraw();
}

//解放処理
void ThronEnemy::Finalize()
{
	delete ThronObject, ThronModel;
}
void ThronEnemy::EnemySearchPlayer(Player* player)
{
	//Follow(player);
}

void ThronEnemy::Follow(Player* player)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (player->GetPosition().x - Position.x);
	//angleZ = (player->GetPosition().y - Position.y);
	angleR = sqrtf((Position.x - player->GetPosition().x) * (Position.x - player->GetPosition().x));
	if (angleR < 2) {
		
		followf =true;
		//Position.x += (angleX / angleR) * movespeed;
		//Position.y += (angleZ / angleR) * centerSpeed;
	}
	if (followf) {
		Position.x += (angleX / angleR) * movespeed;
	}
	//Position.x =player.x;
	//Position.y =player.y;
	//ThronObject->SetPosition(Position);
	//ThronObject->SetPosition(Position);
	float dis;
	dis = sqrtf((player->GetPosition().x - Position.x) * (player->GetPosition().x - Position.x) +
		(player->GetPosition().y - Position.y) * (player->GetPosition().y - Position.y));
	if (dis <= 2) {
		//Attack(player);
	}
}

void ThronEnemy::Motion(Player* player)
{
	if (!followf) {
		jumpcount++;
		if (jumpcount % 50 == 0) {
			//jumpflag = true;
			jumpcount = 0;
		}
	}
}
void ThronEnemy::Attack(Player* player)
{
	//player->SetHp(player->getHp() - AttackDamage);
}
void ThronEnemy::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{
	//grav-grav
	Old_Pos = Position;
	//time-time
	//movespeed-movespeed
	float height;//
	float width;
	XMFLOAT3 Player_Scl = { 1,1,1 };
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Position.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Position.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
					if (Old_Pos.y > mapy[j][i] && Position.y - Player_Scl.y < mapy[j][i] + height) {
						Position.y = height + mapy[j][i] + Player_Scl.y;
						//moveSpeed = 0;
						grav = 0.0f;
						time = 0;
						jumpflag = false;
						//	Line::GetInstance()->SetBondflag(false);
						break;
					} else if (Old_Pos.y <mapy[j][i] && Position.y + Player_Scl.y>mapy[j][i] - height) {
						Position.y = mapy[j][i] - (Player_Scl.y + height);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}

				} else {
					movespeed = 0.1f;
					grav = 0.03;
				}

				//プレイヤーの左辺
				if ((Position.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Position.y + Player_Scl.y)) {
					if (Position.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						//jumpflag = true;
						Position.y = Position.y + 0.001f;
						Position.x = width + mapx[j][i] + Player_Scl.x;

						//Line::GetInstance()->SetBondflag(false);
						break;
					}
					//プレイヤーの右辺
					else if (Position.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						//jumpflag = true;

						Position.x = mapx[j][i] - (Player_Scl.x + width);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
				} else {
					movespeed = 0.1f;
				}
			}
		}
	}

	time += 0.04f;
	Position.y -= grav * time * time;
}

void ThronEnemy::enemyappearance(TyutorialSprite* sprite)
{
	
}
void ThronEnemy::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)
{
}
