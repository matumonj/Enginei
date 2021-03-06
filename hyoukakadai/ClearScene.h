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

class ClearScene:public BaseScene
{
private:

public:
	ClearScene(SceneManager* sceneManager);
private:
	Fader* feed;
	float alpha = 1;
	Sprite* clearsprite;
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

