#include "Line.h"
#include"Input.h"
#include"GameUI.h"
#define PI 3.14159
using namespace DirectX;
Texture* Line::Twine = nullptr;
float Line::FollowangleX, Line::FollowangleZ, Line::FollowangleR;
 float Line::FollowSpeed = 1.0f;
 bool Line::trigger = false;
 int Line::f;
 bool Line::boundflag = false;
 bool Line::returnflag = false;
 float Line::tempx, Line::tempy;
 float Line::linex, Line::linex2, Line::liney, Line::liney2;
 float Line::lineangle = 0;
 float Line::subradius = 0;
 float Line::Startsubradius = 2.0f;
 float Line::olddistance = 0;
 const float Line::LengThenSpeed = 1.0f;
 const float Line::MaxLen = 30.0f;
 const float Line::MinLen = 0.0f;
 float Line::LimitGauge;
 bool Line::lengthserchf = false;
 bool Line::colf = false;
 float Line::grav = 0.05f;
 float Line::MoveSpeed = 0;
 Object3d* Line::NeedleObj=nullptr;
 Model* Line::NeedleModel=nullptr;
 int Line::L_Cflag = 0;
 XMFLOAT3 Line::po = { 0,0,0 },Line::needlepos;
 bool Line::elf = false;
 float Line::oldlinex, Line::oldliney;
 int Line::index = -1;
 Line* Line::GetInstance()
 {
	 static Line instance;
	 return &instance;
}

void Line::Initialize()
{
	Texture::LoadTexture(13, L"Resources/gomi.png");
	Twine = Texture::Create(13, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	
	NeedleModel= Model::CreateFromOBJ("sphere");
	NeedleObj = Object3d::Create();
	NeedleObj->SetModel(NeedleModel);
	
}

void Line::Update(XMMATRIX matview,XMMATRIX matprojection,std::unique_ptr<Object3d>player[],XMFLOAT3& Player_Pos,bool& mapcolf)
{
	float sdistance;
	sdistance = sqrtf(((player[0]->GetPosition().x - linex2) * (player[0]->GetPosition().x - linex2)) +
		((player[0]->GetPosition().y - liney2) * (player[0]->GetPosition().y - liney2))
	);
	//UI部分の外枠ゲージが０なったら紐出せなくなる
	LimitGauge = GameUI::GetInstance()->Getsclx();
	if (LimitGauge < 0) {
		trigger = false;//紐出せないように
		subradius = 0;//伸ばせる紐の長さを０に強制
		//boundflag = false;
		//returnflag = false;
	}

	//やけくそコード,汚いよ
	linex = player[0]->GetPosition().x;//線の始点をプレイヤー位置に
	liney = player[0]->GetPosition().y;
	if (Input::GetInstance()->Pushkey(DIK_1) && (!returnflag && !boundflag)) {
		lineangle += 13.0f;//移動方向の指定
		subradius = Startsubradius;//飛ぶ方向の矢印みたいなの長さの初期値設定(後で置き換え.どうせ別のオブジェするでしょ)
	}
	if (!elf) {
		linex2 = tempx + cosf((lineangle)*PI / 180) * subradius;
		liney2 = tempy + sinf((lineangle)*PI / 180) * subradius;
	}
	//////////中心点//////飛ばす角度///////////////////半径(距離)

	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && (!returnflag && !boundflag)) {
		trigger = true;//線を伸ばすフラグね
		elf = false;
	}

	if (trigger) {//trigger:線伸ばすフラグ
		subradius += LengThenSpeed;//線を伸ばす
		if (subradius > MaxLen||elf) {//一定以上行ったら+ブロックに針あたったら
			trigger = false;
			lengthserchf = true;
		}
		if (subradius > MaxLen && !elf) {//一定以上行って何も当たらなかったら
			trigger = false;
			lengthserchf = true;
			returnflag = true;
		}
		
	} else if (!trigger && subradius > 0) {//フラグ切られて線の長さがまだある時
		if (Input::GetInstance()->TriggerKey(DIK_F)&&elf) {//線が伸び切って何もあたっていないとき
			boundflag = true;//線の終点へ吸い付くフラグ
		} else if (Input::GetInstance()->TriggerKey(DIK_G)) {
			returnflag = true;//線がプレイヤーの方へ戻ってくるフラグ,紐の長さがmaxlen超えて針がブロックとあたっていなかったらこれtrueに
		}
		//線の終点とプレイヤーとの距離求める
		float distance;
		distance = sqrtf(((player[0]->GetPosition().x - linex2) * (player[0]->GetPosition().x - linex2)) +
			((player[0]->GetPosition().y - liney2) * (player[0]->GetPosition().y - liney2))
		);
		//プレイヤーと紐の距離が一定以内に縮まったら
		if (distance <= 1.0f) {
			colf = true;//UIゲージ減らす処理gameui.cppの方
			//elf = false;
			boundflag = false;
			subradius = 0;//線の長さを0に
		}
	}
	//先の長さが最大超えた、またはブロックあたったらその時点のプレイヤーと線の距離を求める（その距離分ゲージ減らす）
	if (lengthserchf) {
		olddistance = sdistance;//ui.scaleX-sdistance*4
		lengthserchf = false;
	}

	//吸い付く処理
	if (boundflag) {
		FollowangleX = (linex2 - player[0]->GetPosition().x);
		FollowangleZ = (liney2 - player[0]->GetPosition().y);//これZじゃなくてYです
		FollowangleR = sqrtf((player[0]->GetPosition().x - linex2) * (player[0]->GetPosition().x - linex2)
			+ (player[0]->GetPosition().y - liney2) * (player[0]->GetPosition().y - liney2));

		Player_Pos.x += (FollowangleX / FollowangleR) * FollowSpeed;
		Player_Pos.y += (FollowangleZ / FollowangleR) * FollowSpeed;
	} else {
		//吸い付くフラグがFALSEんときだけ中心点をプレイヤーの方に
		/*メモ:ずっと中心点を現時点のプレイヤーの座標に設定してるとプレイヤーが動いた分だけ
　　　　　線の終点も動いてしまうから(subradiusの部分が中心点依存)*/
		tempx = Player_Pos.x;
		tempy = Player_Pos.y;
	}
	//線が戻ってくる処理
	if (returnflag) {
		subradius -= 1.5f;
		if (subradius <= 0) {//先の長さが０なったら切る
			returnflag = false;
			//mapcolf = false;
			colf = true;
		}
	}

	max(subradius, MinLen);
	min(subradius, MaxLen);
	Twine->CreateLineTexture(linex, linex2, liney, liney2);
	Twine->SetPosition(po);
	Twine->Update(matview, matprojection);
	
	
	NeedleObj->SetPosition({linex2,liney2,Player_Pos.z});
	needlepos = NeedleObj->GetPosition();
	NeedleObj->SetScale({ 0.8,0.4,0.5 });
	NeedleObj->Update({ 1,1,1,1 });
}

void Line::Draw(DirectXCommon* dxcomn)
{
	Texture::PreDraw(dxcomn->GetCmdList());
	Twine->Draw();
	Texture::PostDraw();
	
	Object3d::PreDraw();
	//NeedleObj->Draw();
	Object3d::PostDraw();
}


void Line::CollisionEnemy(std::unique_ptr<Enemy>position[])
{
	//int in = -1;
	float dis[2];
	for (int i = 0; i < 2; i++) {
		if (position[i] != nullptr) {
			dis[i] = sqrtf((position[i]->GetPosition().x - needlepos.x) * (position[i]->GetPosition().x - needlepos.x) +
				(position[i]->GetPosition().y - needlepos.y) * (position[i]->GetPosition().y - needlepos.y));

			if (dis[i] <= 2 && trigger && !elf) {
				elf = true;
				index = i;//あたった敵の要素番号を割り当て
			}
		}
		if (elf) {
			linex2 = position[index]->GetPosition().x;
			liney2 = position[index]->GetPosition().y;	
		}
	
		if (returnflag || colf) {
			elf = false;
		}
	}
}
//フラグ説明
/*
boundflag:紐の終点へプレイヤーが吸い付くフラグ
returnflag:紐の終点(subradius)がプレイヤーの方へ
colf:紐の残量が減るフラグ
elf:紐とマップブロック&&敵の当たり判定
lenserchf:紐ゲージの減る量を決めるフラグ
*/