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
	stayflag = false;
	beamf = false;
	Scale = { 1,1,1};
	bossAction = None;
	nTexture::LoadTexture(8, L"Resources/targetcircle.png");

	damagearea[0] = nTexture::Create(8, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	damagearea[0]->CreateNormalTexture();

	damagearea[1] = nTexture::Create(8, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	damagearea[1]->CreateNormalTexture();

	damagearea2[0] = nTexture::Create(8, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	damagearea2[0]->CreateNormalTexture();

	damagearea2[1] = nTexture::Create(8, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	damagearea2[1]->CreateNormalTexture();

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
	BossArmObject2[0] = Object3d::Create();
	BossArmObject2[0]->SetModel(BossArmModel);
	BossArmObject2[0]->Initialize();
	//syurikenm = Model::CreateFromOBJ("syuriken");
	BossArmObject2[1] = Object3d::Create();
	BossArmObject2[1]->SetModel(BossArmModel);
	BossArmObject2[1]->Initialize();
	//モデルの読込
	ShotModel = Model::CreateFromOBJ("sphere");

	for (int i = 0; i < 3; i++) {
		ShotObj[i] = Object3d::Create();
		ShotObj[i]->SetModel(ShotModel);
		Shot_Pos[i] = { Position };

	}
	//Rotation.z = 0;
	Position.y = -18;
	HP = MaxHP;

}//

//更新処理
void LastBoss::Update(XMFLOAT3 position)
{
	gametimer++;
	beamatck = beamf;
	staybeam = beamf2;
	texpos[0] = damagearea[0]->GetPosition();
	
	Old_Pos = Position;


	if (HP <= 0) {
		enemyState = State::DEAD;
	} else {
		enemyState = State::ALIVE;
	}


	//Arm_Rot[1].z = rotfollow  ;//60=角度調整用 180=反転
	GetDamage();
	//モブ
	//Rotation.x = 60;
	//Position.y = -18;
	Position.z = 0;
	UpDownMove(position);

	//Scale.x -= 0.001f;
	BossObject->SetPosition(Position);
	BossObject->SetScale(Scale);
	BossObject->Update({ r,g,b,1 });
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
		BossArmObject2[i]->SetPosition({ damagearea2[i]->GetPosition().x,damagearea2[i]->GetPosition().y,damagearea2[i]->GetPosition().z + 10 });
		BossArmObject2[i]->SetRotation({ 90,0,0 });
		BossArmObject2[i]->SetScale({ 4, konbouscl2, 4 });

		BossArmObject2[i]->Update({ 1,1,1,1 });
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
	if (zattack) {
		BossArmObject[0]->PreDraw();
		BossArmObject[0]->Draw();
		BossArmObject[0]->PostDraw();
		BossArmObject[1]->PreDraw();
		BossArmObject[1]->Draw();
		BossArmObject[1]->PostDraw();
	}
	if (zattack2) {
		BossArmObject2[0]->PreDraw();
		BossArmObject2[0]->Draw();
		BossArmObject2[0]->PostDraw();
		BossArmObject2[1]->PreDraw();
		BossArmObject2[1]->Draw();
		BossArmObject2[1]->PostDraw();
	}
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
	nTexture::PreDraw(dxcomn->GetCmdList());
	damagearea[0]->Draw();
	damagearea[1]->Draw();
	damagearea2[0]->Draw();
	damagearea2[1]->Draw();
	nTexture::PostDraw();

	for (int i = 0; i < 3; i++) {
		if (ShotObj[i] != nullptr) {
			ShotObj[i]->PreDraw();
			ShotObj[i]->Draw();
			ShotObj[i]->PostDraw();
		}
	}
	//ImGui::Begin("scl");
	//ImGui::SliderFloat("scly", &syurikenscl[0].y, 20.0f, 20.0f);
	//ImGui::SliderFloat("scly", &lene, 20.0f, 20.0f);
	//ImGui::End();
}

//解放処理
void LastBoss::Finalize()
{

}
void LastBoss::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{

	//
	
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			for (int k = 0; k < 3; k++) {
				if (map[j][i] == 1 || map[j][i] == 2) {
					if (Collision::GetLen(tst[j][i]->GetPosition(), Shot_Pos[k]) < 2) {
						shotf[k] = false;
						//hitcol[k] = true;
						break;
					}

				}
			}
		}
	}
	GetDamageMove(map, tst);
}

void LastBoss::Motion(Player* player)
{
	if (zattack) {
		if (Collision::GetLen(damagearea[0]->GetPosition(), player->GetPosition()) < 5) {
			player->SetHp(player->getHp() - 1);
		}
		if (Collision::GetLen(damagearea[1]->GetPosition(), player->GetPosition()) < 5) {
			player->SetHp(player->getHp() - 1);
		}
	}
	if (zattack2) {
		if (Collision::GetLen(damagearea2[0]->GetPosition(), player->GetPosition()) < 5) {
			player->SetHp(player->getHp() - 1);
		}
		if (Collision::GetLen(damagearea2[1]->GetPosition(), player->GetPosition()) < 5) {
			player->SetHp(player->getHp() - 1);
		}
	}
	RotationDamageblock();
	atcf = zattack;
	NormalAttacks(player);
	colsyuri(player);
	ZAttack(player);
	ZAttack2(player);
	GetDamage();
	if (Input::GetInstance()->TriggerKey(DIK_L)) {
		bossAction = Stay;
	}
	switch (bossAction)
	{
	case syurikenattack:
		syurikenack = true;
		rotack[0] = true;
		rotack[1] = true;
		
		//bossAction = None;
		break;

	case Zattackp:

		break;

	case KeepPos:

		break;
	case SetStartPos://初期位置に戻るや

		break;

	case None:
	
		if (Collision::GetLen_X(Position.x, player->GetPosition().x) > 5) {
			Follow(player->GetPosition());
			//MoveBlockJump();//ボスの埋まり回避用とブロック飛び越えとか

		}
		if (HP!=MaxHP&&HP %10==0) {
			bossAction = syurikenattack;
		}
		if (HP == MaxHP / 2-1) {
			bossAction = Stay;
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

	case Stay://ビーム前の待機]
		Scale = { 1,1,1 };
		stayflag = true;
		StayCount++;
		if (StayCount > 200) {
			beamatck = true;
			beamf = true;
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
		Scale = { 1,1,1 };
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
	angleR = sqrtf((Position.x - position.x) * (Position.x - position.x)+ (Position.y - position.y) * (Position.y - position.y));

	Position.x += (angleX / angleR) * (bossmovespeed / 2);
	Position.y += (angleZ / angleR) * (bossmovespeed / 2);

}


void LastBoss::appearance(float& camerapos, float position)
{



}


void LastBoss::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position) {

	for (int i = 0; i < 2; i++) {
		damagearea[i]->SetScale({texscl});
		damagearea[i]->SetColor({ 1,1,1,zalpha });

		damagearea[i]->Update(matview, matprojection);

		damagearea2[i]->SetScale({ texscl2 });
		damagearea2[i]->SetColor({ 1,1,1,zalpha2 });

		damagearea2[i]->Update(matview, matprojection);
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
				if (!beamf&&!stayflag) {
					shotf[i] = true;
					BarrelRec = true;
				} //else {
				
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
		
	}
	if (syurikenscl[0].y >= 1.9f) {
		syurikentimer++;
		if (syurikentimer > 260) {
			//bossAction = None;
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
			bossAction = None;
			//syurikentimer++;
		}
	}
	if (rotack[1]) {
		sclplus[1] += 0.01f;
		syurikenscl[1].x = Easing::EaseOut(sclplus[1], 0, 2);
		syurikenscl[1].y = Easing::EaseOut(sclplus[1], 0, 2);
		if (syurikenscl[1].y >= 1.9f) {
			HP=HP - 1;
			rotack[1] = false;
			bossAction = None;
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
	if (gametimer % 300 == 0 && (!syurikenack&& !stayflag&&!beamf)) {
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
				bossAction = None;
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
	//私レイキャストをこっちに入れておりません
	playersphere.center = { player->GetPosition().x, player->GetPosition().y, player->GetPosition().z };
	playersphere.radius = 5.0f;
	laserRay.start = { Position.x,Position.y + 0.5f,Position.z };
	laserRay.dir = { -1,0,0 };

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
		GetDamageSclx = true;
		GetDamageScly = true;
		damageRec = false;
	} else {
		if (r > 0.0f)r -= 0.05f;
		if (g < 1.0f)g += 0.05f;
		if (b < 1.0f)b += 0.05f;
		//BossObject->SetColor({ 1,1.0f,1.0f,1 });
	}
	BossObject->SetColor({ r,g,b,1.0f });

	if (HP == 1) {
		BossObject->SetColor({ 1,0,0,1.0f });

		dtime++;
		if (Rotation.z > -180) {
			Rotation.z - 5 * dtime;
		} else {
			SetHP(0);
			dtime = 0;
		}
	}
	
}

void LastBoss::GetDamageMove(int map[20][200], std::unique_ptr<Object3d>  tst[20][200])
{
	if (damageRec) {

	}
	if (GetDamageSclx) {
		if (Scale.x >= 0) {
			Scale.x -= 0.1f;
		} else {
			//movearea = true;
			//Scale.x = 1;
			GetDamageSclx = false;
		}
	}
	if (GetDamageScly) {

		if (Scale.y <= 3) {
			Scale.y += 0.1f;
		} else {
			movearea = true;
			//Scale.y = 1;
			GetDamageScly = false;
		}
	}
	
	if (movearea&&(!beamf&&!stayflag)) {
		for (int i = 0; i < 200; i++) {
			for (int j = 0; j < 20; j++) {
				if (map[j][i] == mapnum) {
					Position = tst[j][i]->GetPosition();
					Scale.x = 1;
					Scale.y = 1;
				}
			}
		}
		mapnum++;
		if (mapnum > 54) {
			mapnum = 50;
		}
		movearea = false;
	}
	if (stayflag || beamf) {
		for (int i = 0; i < 200; i++) {
			for (int j = 0; j < 20; j++) {
				if (map[j][i] == 54) {
					Position = tst[j][i]->GetPosition();
					Scale.x = 1;
					Scale.y = 1;
				}
			}
		}
	}
}
void LastBoss::ZAttack2(Player*player)
{
	if (HP<MaxHP/2&& gametimer % 350 == 0 && (!syurikenack && !stayflag && !beamf)) {
		zattack2 = true;
		zatackEndTimer2 = 0;

	}
	if (!zattack2) {
		if (texscl2.x >= 0) {
			texscl2.x -= 0.5f;
			texscl2.y -= 0.5f;
		}
		oldplayerpos2 = player->GetPosition();
		oldplayerpos2.z = player->GetPosition().z + 20;
		zalpha2 = 0;
		konbouscl2 = 0;
	} else {
		if (texscl2.x <= 2 && !rearm2) {
			texscl2.x += 0.1f;
			texscl2.y += 0.1f;
		} else {
			zatackStartTimer2++;
		}
		if (zatackStartTimer2 > 105) {
			if (konbouscl2 < 5 && zatackEndTimer2 == 0 && !rearm2) {
				konbouscl2 += 0.5;
			} else {
				zatackEndTimer2++;
				if (zatackEndTimer2 > 45) {
					rearm2 = true;
				}
			}
		}
		if (rearm2) {
			if (konbouscl2 > 0) {
				konbouscl2 -= 0.5f;
				//zatackEndTimer = 0;
				zatackStartTimer2 = 0;
				//zattack = false;
			} else {
				//rearm = false;
			}
			if (texscl2.x > 0) {
				texscl2.x -= 0.1f;
				texscl2.y -= 0.1f;
			} else {
				rearm2 = false;
				zattack2 = false;
				bossAction = None;
			}
		}
		
		//	if (HP < 20) {
		damagearea2[0]->SetPosition({ oldplayerpos2.x - 15,oldplayerpos2.y,oldplayerpos2.z });;
		damagearea2[1]->SetPosition({ oldplayerpos2.x + 35,oldplayerpos2.y,oldplayerpos2.z });

		//	}
		zalpha2 = 1;
	}
	konbouscl2 = max(konbouscl2, 0);
	konbouscl2 = min(konbouscl2, 5);

}