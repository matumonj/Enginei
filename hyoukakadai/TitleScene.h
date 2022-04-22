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
#include"Helper.h"
class TitleScene:public BaseScene
{
private:

public:
	TitleScene(SceneManager* sceneManager);
private:
	float alpha = 1;
	Sprite* titlesprite;
	bool feedflag = false;
	//DirectXCommon* dxcomn;
public:
	void Initialize(DirectXCommon* dxCommon)override;
	void Update(DirectXCommon* dxCommon)override;
	void Draw(DirectXCommon* dxcomn)override;
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList);
	void Finalize()override;
};

