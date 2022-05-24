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
#include"StageSelect.h"
#pragma once
class GamOver:public BaseScene
{
private:

public:
	GamOver(SceneManager* sceneManager);
private:
	Fader* feed;
	float alpha = 1;
	Sprite* titlesprite;
	bool feedflag = false;
	bool feedinflag = false;
	bool feedd = false;
	//DirectXCommon* dxcomn;
public:
	void Initialize(DirectXCommon* dxCommon)override;
	void Update(DirectXCommon* dxCommon)override;
	void Draw(DirectXCommon* dxcomn)override;
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList);
	void Finalize()override;
};

