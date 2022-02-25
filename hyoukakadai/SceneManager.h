#pragma once
#include"BaseScene.h"
class SceneManager
{
public:
	//更新
	void Update(DirectXCommon* dxCommon);
	//描画
	void Draw(DirectXCommon* dxcomn);
	//次のシーンへ移行するためのセッター
	void SetnextScene(BaseScene* nextScene_) { nextScene = nextScene_; }
private:
	BaseScene* Scene;
	BaseScene* nextScene = nullptr;
};

