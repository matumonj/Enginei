#include "SceneManager.h"
#include"Destroy.h"
/// <summary>
/// 更新
/// </summary>
void SceneManager::Update(DirectXCommon* dxCommon)
{
	if (nextScene) {
		if (Scene) {//前のシーンを破棄
			Scene->Finalize();
			Destroy(Scene);
		}
		//次のシーンへ移行
		Scene = nextScene;
		nextScene = nullptr;

		Scene->Initialize(dxCommon);//移行したら初期化
	}
	//更新
	Scene->Update(dxCommon);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="cmdList"></param>
void SceneManager::Draw(DirectXCommon* dxcomn)
{
	Scene->Draw(dxcomn);
}