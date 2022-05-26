#pragma once
#include"BaseScene.h"
#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"WinApp.h"

#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"DebugTxt.h"
#include"LightGroup.h"
#include"DebugCamera.h"
#include"DirectXCommon.h"
#include"Fader.h"
#include"Player.h"
#include"f_Model.h"
#include"f_Object3d.h"
class TitleScene:public BaseScene
{
private:

public:
	TitleScene(SceneManager* sceneManager);
private:
	Fader* feed;
	float alpha = 1;
	Sprite* titlesprite;
	bool feedflag = false;
	bool feedinflag = false;
	bool feedd = false;
	float distance = 30;
	//DirectXCommon* dxcomn;
	f_Model* playermodel = nullptr;
	f_Object3d* player = nullptr;
	DebugCamera* camera; 
	XMFLOAT3 Player_Pos = { 20,128,0 };// = player->GetPosition();
	XMFLOAT3 Player_Rot = { 0,180,0 };
//	XMFLOAT3 Player_Scl={0.0}
public:
	void Initialize(DirectXCommon* dxCommon)override;
	void Update(DirectXCommon* dxCommon)override;
	void Draw(DirectXCommon* dxcomn)override;
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList);
	void Finalize()override;
};

