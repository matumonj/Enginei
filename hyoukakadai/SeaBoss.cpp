#include "SeaBoss.h"
#include "SeaBoss.h"
#include"Collision.h"
#include"MobEnemy.h"
#include"Helper.h"
#include"mHelper.h"
#include<random>
#define PI 3.14
#include"imgui.h"

// Sphere SeaBoss::playersphere;
SeaBoss::SeaBoss()
{
}
SeaBoss* SeaBoss::GetInstance()
{
	static SeaBoss instance;
	return &instance;
}
SeaBoss::~SeaBoss()
{
	delete BossObject, BossModel;
}
void SeaBoss::MoveBlockJump()
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
void SeaBoss::EnemySearchPlayer(Player* player)
{
	
}
void SeaBoss::Attack(Player* player)
{

}
//初期化処理
void SeaBoss::Initialize()
{
	//Position = { 67,-4,0 };
	Boss_Scl = { 2,2,2 };
	Boss_Rot = { 0,-180,0 };
	Rotation = { 0,0,0 };
	//モデルの読込
	//Rotation.z = 0;
	HP = MaxHP;
	
}//

//更新処理
void SeaBoss::Update(XMFLOAT3 position)
{
	
	Old_Pos = Position;

	
	if (HP <= 0) {
		enemyState = State::DEAD;
	} else {
		enemyState = State::ALIVE;
	}
	Position.y= position.y;
	
	//Arm_Rot[1].z = rotfollow  ;//60=角度調整用 180=反転
	GetDamage();
	//モブ
	//Rotation.x = 30;
	//Position.x = 20;
	Position.z = 0;
	if (Rotation.z < -90) {
		RotMove = 1;
	} else if (Rotation.z > 0) {
		RotMove = -1;
	}


	Rotation.y = -90;
	Rotation.z +=  1;
	UpDownMove(position);
	//BossObject->SetPosition(Position);
	//BossObject->SetScale({ 2,2,2 });
	//BossObject->SetRotation(Rotation);
	
}

//描画処理
void SeaBoss::Draw(DirectXCommon* dxcomn)
{
	ImGui::Begin("scl");
	//ImGui::SliderFloat("scly", &Arm_Scl[0].y, 20.0f, 20.0f);
	//ImGui::SliderFloat("scly", &lene, 20.0f, 20.0f);
	ImGui::End();
}

//解放処理
void SeaBoss::Finalize()
{

}
void SeaBoss::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 200; j++) {
			if (map[i][j] == 1) {
				if (Collision::GetLen(Position, tst[i][j]->GetPosition()) < 13) {
					map[i][j] = 0;
				}
			}
		}
	}
}

void SeaBoss::EatEnemy(std::unique_ptr<Enemy>enemy[])
{
	//for (int i = 1; i < 10; i++) {
		if (enemy[3] != nullptr) {
			if (Collision::GetLen(Position, enemy[3]->GetPosition()) < 13) {
			//	enemy[3]->SetDead(true);
			}
		}
	//}
}
void SeaBoss::Motion(Player* player)
{
	NormalAttacks(player);
	
	
	switch (bossAction)
	{
	case KeepPos:

		break;
	case SetStartPos://初期位置に戻るや

		break;

	case None:
		if (Input::GetInstance()->TriggerKey(DIK_S)) {
			bossAction = SetStartPos;
		}
		if (HP < MaxHP / 2) {
			bossAction = SetStartPos;//体力が一定以下なったら初期位置に
		}
		if (Collision::GetLen_X(Position.x, player->GetPosition().x) > 5) {
			Follow(player->GetPosition());
			//MoveBlockJump();//ボスの埋まり回避用とブロック飛び越えとか

		} 
		if (HP != MaxHP && HP != BefHP && HP % 4 == 0) {
			bossAction = SetStartPos;
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
		StayCount++;
		if (StayCount > 150) {
			bossAction = None;
			StayCount = 0;
		}
		break;

	case NormalAttack:
		NormalAttacks(player);
		
		break;
	case StartBattle:
		
		break;
	
	default:
		break;
	}

	Follow(player->GetPosition());

}

void SeaBoss::ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)
{

}
void SeaBoss::Follow(XMFLOAT3 position)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (position.x - Position.x);
	//angleZ = (position.y - Position.y);
	angleR = sqrtf((Position.x - position.x) * (Position.x - position.x));

	Position.x += (angleX / angleR) * (bossmovespeed/2 );

}


void SeaBoss::appearance(float& camerapos, float position)
{
	float oldpos = -48;
	if (phase && !returnCamera) {
		cameratime += 0.002f;
		if (camerapos >= 178) {
			cameratime = 0;
			returnCamera = true;
			phase = false;
		} else {
			camerapos = Easing::EaseOut(cameratime, oldpos, 178);
		}
	} else {
		oldpos = camerapos;
		//startcount += 0.01;
	}

	if (returnCamera) {
		returnCameraTime += 0.01f;
		if (camerapos <= -40) {
			returnCameraTime = 0;
			returnCamera = false;
			phase = false;
		} else {
			camerapos = Easing::EaseOut(returnCameraTime, 177, -48);
		}

	}
	if (Input::GetInstance()->TriggerKey(DIK_J)) {
		//bossAction = None;
		phase = true;
	}

	if (!returnCamera && !phase) {
		camerapos = position;
	}
}

void SeaBoss::GetDamage()
{

	if (HP == MaxHP) {
		OldHP = HP - 1;
	}
	if (HP == OldHP && !damageRec) {
		damageRec = true;
		OldHP--;
	}
	if (damageRec) {
		r = 1.0f; g = 0.2f; b = 0.0f;
		damageRec = false;
	} else {
		if (r > 0.0f)r -= 0.1f;
		if (g < 1.0f)g += 0.1f;
		if (b < 1.0f)b += 0.1f;
		//BossObject->SetColor({ 1,1.0f,1.0f,1 });
	}
	//BossObject->SetColor({ r,g,b,1.0f });
}
void SeaBoss::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position) {

}


void SeaBoss::NormalAttacks(Player* player)
{
	
}

void SeaBoss::UpDownMove(XMFLOAT3 position)
{

}

void SeaBoss::DeathMotion()
{

}