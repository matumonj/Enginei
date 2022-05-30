#include "LastBoss.h"
#include "LastBoss.h"
#include "LastBoss.h"
#include"Collision.h"
#include"MobEnemy.h"
#include"Helper.h"
#include"mHelper.h"
#include<random>
#define PI 3.14
#include"imgui.h"
bool LastBoss::atcf;
XMFLOAT3 LastBoss::texpos[2];
bool LastBoss::staybeam;
bool LastBoss::beamatck;
bool LastBoss::stayflag;
Ray LastBoss::laserRay;
// Sphere LastBoss::playersphere;
LastBoss::LastBoss()
{
}
LastBoss* LastBoss::GetInstance()
{
	static LastBoss instance;
	return &instance;
}
LastBoss::~LastBoss()
{
	delete BossObject, BossModel;
}
void LastBoss::MoveBlockJump()
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
void LastBoss::EnemySearchPlayer(Player* player)
{

}
void LastBoss::Attack(Player* player)
{

}
//初期化処理
void LastBoss::Initialize()
{
	nTexture::LoadTexture(8, L"Resources/targetcircle.png");

	damagearea[0] = nTexture::Create(8, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	damagearea[0]->CreateNormalTexture();

	damagearea[1] = nTexture::Create(8, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	damagearea[1]->CreateNormalTexture();

	syurikenm = Model::CreateFromOBJ("syuriken");
	syuriken[0] = Object3d::Create();
	syuriken[0]->SetModel(syurikenm);
	syuriken[0]->Initialize();
	//syurikenm = Model::CreateFromOBJ("syuriken");
	syuriken[1] = Object3d::Create();
	syuriken[1]->SetModel(syurikenm);
	syuriken[1]->Initialize();
	//モデルの読込
	BossModel = Model::CreateFromOBJ("boss1");
	//モデル割り当て
	BossObject = Object3d::Create();
	BossObject->SetModel(BossModel);
	BossObject->Initialize();
	
	Position = { 67,-4,0 };
	Boss_Scl = { 2,2,2 };
	Boss_Rot = { 0,-180,0 };
	Rotation = { 0,0,0 };

	BossArmModel = Model::CreateFromOBJ("konbou");
	BossArmObject[0] = Object3d::Create();
	BossArmObject[0]->SetModel(BossArmModel);
	BossArmObject[0]->Initialize();
	//syurikenm = Model::CreateFromOBJ("syuriken");
	BossArmObject[1] = Object3d::Create();
	BossArmObject[1]->SetModel(BossArmModel);
	BossArmObject[1]->Initialize();
	//モデルの読込
	ShotModel = Model::CreateFromOBJ("sphere");

	for (int i = 0; i < 3; i++) {
		ShotObj[i] = Object3d::Create();
		ShotObj[i]->SetModel(ShotModel);
		Shot_Pos[i] = { Position };

	}
	//Rotation.z = 0;
	HP = MaxHP;

}//

//更新処理
void LastBoss::Update(XMFLOAT3 position)
{

	beamatck = beamf;
	staybeam = beamf2;
	texpos[0] = damagearea[0]->GetPosition();
	RotationDamageblock();
	Old_Pos = Position;


	if (HP <= 0) {
		enemyState = State::DEAD;
	} else {
		enemyState = State::ALIVE;
	}


	//Arm_Rot[1].z = rotfollow  ;//60=角度調整用 180=反転
	GetDamage();
	//モブ
	Rotation.x = 60;
	Position.y = -18;
	Position.z = 0;
	UpDownMove(position);
	BossObject->SetPosition(Position);
	//BossObject->SetScale({ 2,2,2 });
	BossObject->Update({ 1,1,1,1 });
	BossObject->SetRotation(Rotation);
	for (int i = 0; i < 2; i++) {
		syuriken[i]->SetPosition(syurikenpos[i]);
		syuriken[i]->SetRotation(syurikenrot[i]);
		syuriken[i]->SetScale(syurikenscl[i]);
		syuriken[i]->Update({ 1,1,1,1 });

		BossArmObject[i]->SetPosition({ damagearea[i]->GetPosition().x,damagearea[i]->GetPosition().y,damagearea[i]->GetPosition().z+10});
		BossArmObject[i]->SetRotation({ 90,0,0 });
		BossArmObject[i]->SetScale({4, konbouscl, 4});

		BossArmObject[i]->Update({ 1,1,1,1 });
	}
	for (int i = 0; i < 3; i++) {
		if (ShotObj[i] != nullptr) {
			ShotObj[i]->SetPosition(Shot_Pos[i]);
			ShotObj[i]->SetRotation({ 0,0,0 });
			ShotObj[i]->SetScale({ 1,1,1 });
			ShotObj[i]->Update({ 1,1,1,1 });
		}
	}
}

//描画処理
void LastBoss::Draw(DirectXCommon* dxcomn)
{
	
	syuriken[0]->PreDraw();
	syuriken[0]->Draw();
	syuriken[0]->PostDraw();
	syuriken[1]->PreDraw();
	syuriken[1]->Draw();
	syuriken[1]->PostDraw();
	if (zatackStartTimer != 0) {
		BossArmObject[0]->PreDraw();
		BossArmObject[0]->Draw();
		BossArmObject[0]->PostDraw();
		BossArmObject[1]->PreDraw();
		BossArmObject[1]->Draw();
		BossArmObject[1]->PostDraw();
	}
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
	nTexture::PreDraw(dxcomn->GetCmdList());
	damagearea[0]->Draw();
	damagearea[1]->Draw();
	nTexture::PostDraw();

	for (int i = 0; i < 3; i++) {
		if (ShotObj[i] != nullptr) {
			ShotObj[i]->PreDraw();
			ShotObj[i]->Draw();
			ShotObj[i]->PostDraw();
		}
	}
	ImGui::Begin("scl");
	//ImGui::SliderFloat("scly", &syurikenscl[0].y, 20.0f, 20.0f);
	//ImGui::SliderFloat("scly", &lene, 20.0f, 20.0f);
	ImGui::End();
}

//解放処理
void LastBoss::Finalize()
{

}
void LastBoss::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{}

void LastBoss::Motion(Player* player)
{
	atcf = zattack;
	NormalAttacks(player);
	colsyuri(player);
	ZAttack(player);
	if (Input::GetInstance()->TriggerKey(DIK_L)) {
		bossAction = Stay;
	}
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
		stayflag = true;
		StayCount++;
		if (StayCount > 200) {
			beamatck = true;
			bossAction = altattackk;
			StayCount = 0;
		}
		break;

	case NormalAttack:
		NormalAttacks(player);

		break;
	case StartBattle:

		break;
	case altattackk:
		beamAtack(player);
		break;
	default:
		break;
	}

}

void LastBoss::ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)
{

}
void LastBoss::Follow(XMFLOAT3 position)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (position.x - Position.x);
	angleZ = (position.y - Position.y);
	angleR = sqrtf((Position.x - position.x) * (Position.x - position.x));

	Position.x += (angleX / angleR) * (bossmovespeed / 2);

}


void LastBoss::appearance(float& camerapos, float position)
{



}

void LastBoss::GetDamage()
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
void LastBoss::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position) {

	for (int i = 0; i < 2; i++) {
		damagearea[i]->SetScale({texscl});
		damagearea[i]->SetColor({ 1,1,1,zalpha });

		damagearea[i]->Update(matview, matprojection);
	}
}


void LastBoss::NormalAttacks(Player* player)
{
	float x[3];
	float y[3];
	for (int i = 0; i < 3; i++) {
		if (attackcount % 400 == 0) {
			BarrelFolflag = false;
			if (!shotf[i]) {
				//shotf[i] = true;
				//if (Input::GetInstance()->TriggerKey(DIK_S)) {
				if (!ChangeAttack) {
					shotf[i] = true;
					BarrelRec = true;
				} else {
					delete ShotObj[i];
					ShotObj[i] = nullptr;
				}
				//}

				Shot_Pos[i] = { Position };
				x[i] = player->GetPosition().x - Shot_Pos[i].x;
				y[i] = player->GetPosition().y - Shot_Pos[i].y;

				BulAngle[i] = sqrtf(x[i] * x[i] + y[i] * y[i]);
				rt[i] += 0.05f;
				Xspeed[i] = ((0.1f) * x[i] / BulAngle[i]);
				Yspeed[i] = ((0.1f) * y[i] / BulAngle[i]);
				break;
			}

		}

		if (shotf[i] && ShotObj[i] != nullptr) {
			Shot_Pos[i].x += Xspeed[i];
			Shot_Pos[i].y += Yspeed[i];
			if (Collision::GetLen(Shot_Pos[i], player->GetPosition()) < 1) {
				player->SetHp(player->getHp() - 1);
				shotf[i] = false;
				break;
			}
			if (Collision::GetLen(Shot_Pos[i], Position) > 100) {
				shotf[i] = false;
				break;
			}

		}
	}
}

void LastBoss::UpDownMove(XMFLOAT3 position)
{

}

void LastBoss::DeathMotion()
{

}

void LastBoss::RotationDamageblock()
{

	if (Input::GetInstance()->TriggerKey(DIK_T)) {
		syurikenack = true;
		rotack[0] = true;
		rotack[1] = true;
	}
	if (syurikenscl[0].y >= 1.9f) {
		syurikentimer++;
		if (syurikentimer > 260) {
			syurikenack = false;
			syurikentimer = 0;
		}
	}
	if(syurikenack){
		
	}
	else {
		if (syurikenscl[0].y >= 0) {
			syurikenscl[0].y -= 0.01f;
			syurikenscl[0].x -= 0.01f;

			syurikenscl[1].y -= 0.01f;
			syurikenscl[1].x -= 0.01f;
		}
		sclplus[0] = 0;
		sclplus[1] = 0;
	}
	if (rotack[0]) {
		sclplus[0] += 0.01f;
		syurikenscl[0].x=Easing::EaseOut(sclplus[0], 0, 2);
		syurikenscl[0].y = Easing::EaseOut(sclplus[0], 0, 2);
		if (syurikenscl[0].y >= 1.9f) {
			//sclplus[0] = 0;
			rotack[0] = false;
			//syurikentimer++;
		}
	}
	if (rotack[1]) {
		sclplus[1] += 0.01f;
		syurikenscl[1].x = Easing::EaseOut(sclplus[1], 0, 2);
		syurikenscl[1].y = Easing::EaseOut(sclplus[1], 0, 2);
		if (syurikenscl[1].y >= 1.9f) {
			rotack[1] = false;
		}
	}
	syurikenrot[0].z++;
	syurikenrot[1].z++;
}

void LastBoss::colsyuri(Player*player)
{
	pobb.m_NormaDirect[0] = { player->GetMatrot().r[0].m128_f32[0],player->GetMatrot().r[0].m128_f32[1],player->GetMatrot().r[0].m128_f32[2] };
	pobb.m_NormaDirect[1] = { player->GetMatrot().r[1].m128_f32[0],player->GetMatrot().r[1].m128_f32[1],player->GetMatrot().r[1].m128_f32[2] };
	pobb.m_NormaDirect[2] = { player->GetMatrot().r[2].m128_f32[0],player->GetMatrot().r[2].m128_f32[1],player->GetMatrot().r[2].m128_f32[2] };
	pobb.m_fLength[0] = 1;//x方向の長さ
	pobb.m_fLength[1] = 1;//y方向の長さ
	pobb.m_fLength[2] = 1;//z方向の長さ
	//敵のOBB 回転ベクトル
	syuriken0.m_NormaDirect[0] = { syuriken[0]->GetMatrot().r[0].m128_f32[0],syuriken[0]->GetMatrot().r[0].m128_f32[1],syuriken[0]->GetMatrot().r[0].m128_f32[2] };
	syuriken0.m_NormaDirect[1] = { syuriken[0]->GetMatrot().r[1].m128_f32[0], syuriken[0]->GetMatrot().r[1].m128_f32[1], syuriken[0]->GetMatrot().r[1].m128_f32[2] };
	syuriken0.m_NormaDirect[2] = { syuriken[0]->GetMatrot().r[2].m128_f32[0], syuriken[0]->GetMatrot().r[2].m128_f32[1], syuriken[0]->GetMatrot().r[2].m128_f32[2] };
	syuriken0.m_fLength[0] = syurikenscl[0].x*0.5;//x方向の長さ
	syuriken0.m_fLength[1] = syurikenscl[0].y * 5.5;//y方向の長さ
	syuriken0.m_fLength[2] = syurikenscl[0].z;//z方向の長さ
	//OBBの設定位置
	pobb.m_Pos = { player->GetPosition().x,player->GetPosition().y,player->GetPosition().z };
	syuriken0.m_Pos = { syuriken[0]->GetPosition().x,  syuriken[0]->GetPosition().y, syuriken[0]->GetPosition().z };

	if (ps0->ColOBBs(pobb, syuriken0)) {
		player->SetHp(player->getHp() - 1);
	} else {
		//obbf = 0;
	}

	//敵のOBB 回転ベクトル
	syuriken1.m_NormaDirect[0] = { syuriken[1]->GetMatrot().r[0].m128_f32[0],syuriken[1]->GetMatrot().r[0].m128_f32[1],syuriken[1]->GetMatrot().r[0].m128_f32[2] };
	syuriken1.m_NormaDirect[1] = { syuriken[1]->GetMatrot().r[1].m128_f32[0], syuriken[1]->GetMatrot().r[1].m128_f32[1], syuriken[1]->GetMatrot().r[1].m128_f32[2] };
	syuriken1.m_NormaDirect[2] = { syuriken[1]->GetMatrot().r[2].m128_f32[0], syuriken[1]->GetMatrot().r[2].m128_f32[1], syuriken[1]->GetMatrot().r[2].m128_f32[2] };
	syuriken1.m_fLength[0] = syurikenscl[1].x*0.5;//x方向の長さ
	syuriken1.m_fLength[1] = syurikenscl[1].y * 5.5;//y方向の長さ
	syuriken1.m_fLength[2] = syurikenscl[1].z;//z方向の長さ
	//OBBの設定位置
	pobb.m_Pos = { player->GetPosition().x,player->GetPosition().y,player->GetPosition().z };
	syuriken1.m_Pos = { syuriken[1]->GetPosition().x,  syuriken[1]->GetPosition().y, syuriken[1]->GetPosition().z };

	if (ps1->ColOBBs(pobb, syuriken1)) {
		player->SetHp(player->getHp() - 1);
	} else {
		//obbf = 0;
	}
	//敵のOBB 回転ベクトル
	syuriken2.m_NormaDirect[0] = { syuriken[0]->GetMatrot().r[0].m128_f32[0],syuriken[0]->GetMatrot().r[0].m128_f32[1],syuriken[0]->GetMatrot().r[0].m128_f32[2] };
	syuriken2.m_NormaDirect[1] = { syuriken[0]->GetMatrot().r[1].m128_f32[0], syuriken[0]->GetMatrot().r[1].m128_f32[1], syuriken[0]->GetMatrot().r[1].m128_f32[2] };
	syuriken2.m_NormaDirect[2] = { syuriken[0]->GetMatrot().r[2].m128_f32[0], syuriken[0]->GetMatrot().r[2].m128_f32[1], syuriken[0]->GetMatrot().r[2].m128_f32[2] };
	syuriken2.m_fLength[0] = syurikenscl[0].x*5.5;//x方向の長さ
	syuriken2.m_fLength[1] = syurikenscl[0].y*0.5 ;//y方向の長さ
	syuriken2.m_fLength[2] = syurikenscl[0].z;//z方向の長さ
	//OBBの設定位置
	pobb.m_Pos = { player->GetPosition().x,player->GetPosition().y,player->GetPosition().z };
	syuriken2.m_Pos = { syuriken[0]->GetPosition().x,  syuriken[0]->GetPosition().y, syuriken[0]->GetPosition().z };

	if (ps2->ColOBBs(pobb, syuriken2)) {
		player->SetHp(player->getHp() - 1);
	} else {
		//obbf = 0;
	}

	//敵のOBB 回転ベクトル
	syuriken3.m_NormaDirect[0] = { syuriken[1]->GetMatrot().r[0].m128_f32[0],syuriken[1]->GetMatrot().r[0].m128_f32[1],syuriken[1]->GetMatrot().r[0].m128_f32[2] };
	syuriken3.m_NormaDirect[1] = { syuriken[1]->GetMatrot().r[1].m128_f32[0], syuriken[1]->GetMatrot().r[1].m128_f32[1], syuriken[1]->GetMatrot().r[1].m128_f32[2] };
	syuriken3.m_NormaDirect[2] = { syuriken[1]->GetMatrot().r[2].m128_f32[0], syuriken[1]->GetMatrot().r[2].m128_f32[1], syuriken[1]->GetMatrot().r[2].m128_f32[2] };
	syuriken3.m_fLength[0] = syurikenscl[1].x*5.5;//x方向の長さ
	syuriken3.m_fLength[1] = syurikenscl[1].y*0.5;//y方向の長さ
	syuriken3.m_fLength[2] = syurikenscl[1].z;//z方向の長さ
	//OBBの設定位置
	pobb.m_Pos = { player->GetPosition().x,player->GetPosition().y,player->GetPosition().z };
	syuriken3.m_Pos = { syuriken[1]->GetPosition().x,  syuriken[1]->GetPosition().y, syuriken[1]->GetPosition().z };

	if (ps3->ColOBBs(pobb, syuriken3)) {
		player->SetHp(player->getHp() - 1);
	} else {
		//obbf = 0;
	}
}

void LastBoss::ZAttackTex(XMMATRIX matview, XMMATRIX matprojection, Player* player)
{
	
}

void LastBoss::Drawtex(DirectXCommon* dcomn)
{

}

void LastBoss::ZAttack(Player*player)
{
	if (Input::GetInstance()->TriggerKey(DIK_Z)) {
		zattack = true;
		zatackEndTimer = 0;

	}
	if (!zattack) {
		if (texscl.x >= 0) {
			texscl.x -= 0.5f;
			texscl.y -= 0.5f;
		}
		oldplayerpos = player->GetPosition();
		oldplayerpos.z = player->GetPosition().z + 20;
		zalpha = 0;
		konbouscl = 0;
	} else {
			if (texscl.x <= 2 && !rearm) {
				texscl.x += 0.1f;
				texscl.y += 0.1f;
			} else {
				zatackStartTimer++;
			}
			if (zatackStartTimer > 105) {
				if (konbouscl < 5 && zatackEndTimer == 0 && !rearm) {
					konbouscl += 0.5;
				} else {
					zatackEndTimer++;
					if (zatackEndTimer > 45) {
						rearm = true;
					}
				}
			}
		if (rearm) {
			if (konbouscl > 0) {
				konbouscl -= 0.5f;
				//zatackEndTimer = 0;
				zatackStartTimer = 0;
				//zattack = false;
			}
			else {
				//rearm = false;
			}
			if (texscl.x > 0) {
				texscl.x -= 0.1f;
				texscl.y -= 0.1f;
			}
			else {
				rearm = false;
				zattack = false;
			}
		}
		damagearea[0]->SetPosition(oldplayerpos);
		damagearea[1]->SetPosition({ oldplayerpos.x + 20,oldplayerpos.y,oldplayerpos.z
			});
		zalpha = 1;
	}
	konbouscl = max(konbouscl, 0);
	konbouscl = min(konbouscl, 5);

}

void LastBoss::beamAtack(Player*player)
{
	stayflag = false;
	Attackcount++;
	if (Attackcount > 50) {
		beamf = true;//ブロックの破壊とビームのタイミング合わせ
	}
	if (Attackcount > 100) {//一定時間経過したら攻撃終了
		beamf2 = false;//これなんで
		Attackcount = 0;
		beamf = false;//２つあるんだ？
		bossAction = NormalAttack;
	} else {
		beamf2 = true;
	}
	//ボスビームのレイとプレイやーの当たり判定
	if (Collision::CheckRay2Sphere(laserRay, playersphere) == true) {
		player->SetHp(player->getHp() - 1);
	}
}