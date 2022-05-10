#include "FirstBoss.h"
#include"Collision.h"
#include"MobEnemy.h"
#include"Helper.h"
#include"mHelper.h"
#include<random>
#define PI 3.14
float FirstBoss::startcount = 0;
bool FirstBoss::stayflag;
XMFLOAT3 FirstBoss::startPos;
bool FirstBoss::bossjumpflag = false;
int FirstBoss::attacktime = 0;
// Sphere FirstBoss::playersphere;
FirstBoss::FirstBoss()
{
}
FirstBoss* FirstBoss::GetInstance()
{
	static FirstBoss instance;
	return &instance;
}
FirstBoss::~FirstBoss()
{
	delete BossObject, BossModel;
}
void FirstBoss::MoveBlockJump()
{
	//ブロック埋まり回避用のジャンプ処理
	//一定時間動かなかったらジャンプ
	time++;
	if (time % 20 == 0) {
		oldx = Position.x;
		//oldy = Position.y;
	}
	if (Collision::GetLenX({ oldx,oldy,0.0f }, Position) <= 0.0f) {
		time2++;
		if (time2 > 10) {
			//bossjumpflag = true;
			time2 = 0;
		}
	}

}
void FirstBoss::EnemySearchPlayer(Player* player)
{

}
void FirstBoss::Attack(Player* player)
{

}
//初期化処理
void FirstBoss::Initialize()
{
	//モデルの読込
	BossModel = Model::CreateFromOBJ("zako1");
	//モデル割り当て
	BossObject = Object3d::Create();
	BossObject->SetModel(BossModel);

	//パラメータのセット
	Position = { 67,-4,0 };
	Boss_Scl = { 2,2,2 };
	Boss_Rot = { 0,0,0 };
	Rotation = { 30,80,80 };
	//モデルの読込
	Rotation.z = 0;
	HP = MaxHP;
	startPos = { 40,-18,0 };
}

//更新処理
void FirstBoss::Update(XMFLOAT3 position)
{
	Old_Pos = Position;

	if (bossjumpflag == true) {
		if (bossjumpflag2) {
			Position.y += 0.5f;
		} else {
			Position.y += 0.2f;
		}
		bosstime += 0.02f;
	} else {
		bossjumpflag2 = false;
	}

	if (HP <= 0) {
		enemyState = State::DEAD;
	} else {
		enemyState = State::ALIVE;
	}
	BossObject->Update({ 1,1,1,1 });
	//モブ
	//Rotation = { 0,180,0 };

	if (position.x < Position.x) {
		//Rotation = { 0,180,0 };
		if(Rotation.y!=180){
			Rotation.y+=10;
		}
		//rottime += 0.1f;
		//Easing::EaseOut(rottime, Rotation.x, 0);
		// SetRotation({ 0,180,0 });
	} else if (position.x >= Position.x) {
		//	rottime += 0.1f;
		if (Rotation.y != 0) {
			Rotation.y -= 10;
		}
		//Rotation = { 0,0,0 };
		//Easing::EaseOut(rottime, Rotation.x, 180);
		//SetRotation({ 0,-90,0 });
	}
	//Rotation.x = 0;
	Rotation.x = 0;

	BossObject->SetPosition(Position);
	BossObject->SetScale({2,2,2 });
	BossObject->SetRotation(Rotation);
	//BossObject->SetRotation(Boss_Rot);

}

//描画処理
void FirstBoss::Draw()
{
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
}

//解放処理
void FirstBoss::Finalize()
{

}
void FirstBoss::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{
	//grav-grav
//time-time
//movespeed-movespeed
	float height;//
	float width;
	XMFLOAT3 Player_Scl = { 3,3,3 };
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Position.x + Player_Scl.x > mapx[j][i] - (width - bossmovespeed) && Position.x - Player_Scl.x < mapx[j][i] + (width - bossmovespeed))) {
					if (Old_Pos.y > mapy[j][i] && Position.y - Player_Scl.y < mapy[j][i] + height) {
						Position.y = height + mapy[j][i] + Player_Scl.y;
						bossgrav = 0.0f;
						bosstime = 0;
						bossjumpflag = false;
						break;
					} else if (Old_Pos.y <mapy[j][i] && Position.y + Player_Scl.y>mapy[j][i] - height) {
						Position.y = mapy[j][i] - (Player_Scl.y + height);
						break;
					}

				} else {
					bossmovespeed = 0.2f;
					bossgrav = 0.03;
				}

				//プレイヤーの左辺
				if ((Position.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Position.y + Player_Scl.y)) {
					if (Position.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						Position.y = Position.y + 0.001f;
						Position.x = width + mapx[j][i] + Player_Scl.x;
						break;
					}
					//プレイヤーの右辺
					else if (Position.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						Position.x = mapx[j][i] - (Player_Scl.x + width);
						break;
					}
				} else {
					bossmovespeed = 0.2f;
				}
			}
		}
	}

	bosstime += 0.04f;
	Position.y -= bossgrav * bosstime * bosstime;
}

void FirstBoss::Motion(Player* player)
{
	const float dis = 0.5f;
	switch (bossAction)
	{
	case SetStartPos://初期位置に戻るやつ
		if (player->GetPosition().x > Position.x) {
			//Rotation = { 0,90,0 };
			// SetRotation({ 0,180,0 });
		} else {
			//Rotation = { 0,120,0 };
			//SetRotation({ 0,-90,0 });
		}
		if (player->GetPosition().x < Position.x) {
			startPos.x = 67;
		} else {
			startPos.x = 20;
		}

		if (Collision::GetLen(startPos, Position) <= dis + 1) {
			bossAction = RushAttacks;
		} else {
			Helper::Follow(startPos, Position, dis, bossmovespeed);
		}
		break;
	case RushAttacks:

		RushAttackStay(player);
		RushAttack(player);
		break;
	case None:
		//Rotation.x = 0;
		attacktime++;
		if (Input::GetInstance()->TriggerKey(DIK_S)) {
			bossAction = SetStartPos;
		}	
		if (HP < MaxHP / 2) {
			bossAction = SetStartPos;//体力が一定以下なったら初期位置に
		}
		if (Collision::GetLen_X(Position.x, player->GetPosition().x) > 5) {
			Follow(player->GetPosition());
			//MoveBlockJump();//ボスの埋まり回避用とブロック飛び越えとか
		
		} else {
			if (attacktime % 50 == 0) {
				bossAction = NormalAttack;//プレイヤーが上の方逃げたら投擲
				attacktime = 0;
			}
		}
		
		if (HP < 5) {
			bossAction = RushAttacks;
		}
		break;
	case MoveRight://突進右
		if (movement < 10) {
			Position.x += bossmovespeed;
			movement += 0.5f;
		} else if (movement >= 10) {
			movement = 0;
		}
		break;
	case MoveLeft://突進左
		if (movement < 10) {
			Position.x -= bossmovespeed;
			movement += 0.5f;
		} else if (movement >= 10) {
			movement = 0;
		}
		break;

	case Stay://ビーム前の待機
		if (startcount > 1.0f) {
			bossAction = None;
		}
		break;

	case NormalAttack:
		NormalAttacks(player);
		break;
	default:
		break;
	}

}


void FirstBoss::Follow(XMFLOAT3 position)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (position.x - Position.x);
	angleZ = (position.y - Position.y);
	angleR = sqrtf((Position.x - position.x) * (Position.x - position.x)
		+ (Position.y - position.y) * (Position.y - position.y));
	
		Position.x += (angleX / angleR) * (bossmovespeed / 2);
	
}


void FirstBoss::RushAttack(Player* player)
{
	if (Input::GetInstance()->TriggerKey(DIK_R)) {
		rushAttackPrm.rushflag = true;
	}

	if (rushAttackPrm.rushflag) {
		if (Collision::GetLen_X(rushAttackPrm.aftermovex, Position.x) >= 0.5f) {
			rushAttackPrm.count += 0.01f;
			Position.x = Easing::EaseOut(rushAttackPrm.count, Position.x, rushAttackPrm.aftermovex);
		} else {
			rushAttackPrm.count = 0.0f;
			rushAttackPrm.rushflag = false;
			bossjumpflag = true;
			bossAction = None;
		}
	}
	if (Collision::GetLen_X(Position.x, player->GetPosition().x) > 5) {
		player->SetHp(player->getHp() - 1);
	}
}

void FirstBoss::RushAttackStay(Player* player)
{
	if (shaketime != 0) {
		oshake = rand() % 7 - 14;
		oshakex = rand() % 7 - 14;
		oshakey = rand() % 7 - 14;

		shakex = oshakex * 0.01f;
		shakey = oshakey * 0.01f;
		shake = oshake * 0.01f;
		shakex -= shake;
		shakey -= shake;
		shaketime--;
		//}
		//シェイク値を０に
	} else {
		shakex = 0;
		shakey = 0;
		rushAttackPrm.rushflag = true;
		shaketime = 100;
	}
	Position.x += shakex;

	if (!rushAttackPrm.rushflag) {
		if (player->GetPosition().x < Position.x) {
			rushAttackPrm.aftermovex = Position.x - 40;
		} else {
			rushAttackPrm.aftermovex = Position.x + 40;
		}
	}
}

void FirstBoss::NormalAttacks(Player* player)
{
	//DamageAreaStart = { Position.x,Position.y + 2 };
	if (Rotation.y == 180) {//右向いてるときの
		DamageAreaStart = { Position.x,Position.y + 2 };
		DamageArea = { Position.x-8 ,Position.y - 2 };
		if (Collision::Boxcol({ player->GetPosition().x,player->GetPosition().y },
			{ player->GetPosition().x + 2,player->GetPosition().y + 2 }, DamageArea, DamageAreaStart
		) == true) {
			player->SetHp(player->getHp() - 1);
		}
	} else {
		DamageAreaStart = { Position.x,Position.y-2 };
		DamageArea = { Position.x+5,Position.y + 2 };
		if (Collision::Boxcol({ player->GetPosition().x,player->GetPosition().y },
			{ player->GetPosition().x + 2,player->GetPosition().y + 2 }, DamageAreaStart, DamageArea
		) == true) {
			player->SetHp(player->getHp() - 1);
		}
	}
	
	if (Rotation.z <= 360) {
		Rotation.z += 20;
	}
	else {
		
		bossAction = None;
		Rotation.z = 0;
	}
	//player->SetHp(player->getHp() - 1);

	//bossAction = None;
}

void FirstBoss::appearance(float& camerapos)
{
	
	if (phase) {
		cameratime += 0.01f;
		camerapos = Easing::EaseOut(cameratime, camerapos, 35.37f);
		//bossAction = None;
	}
	else {
		startcount+=0.01;
		camerapos = 67.235f;
		bossjumpflag = true;
		if (startcount > 1.0f) {
			
			phase = true;
		}
	}
}
