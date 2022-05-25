#include "MyGame.h"
#include"SceneManager.h"
void MyGame::Initialize(DirectXCommon* dxCommon)
{
	Framework::Initialize(dxCommon);
	Sprite::StaticInitialize(dxcomn->GetDev(), WinApp::window_width, WinApp::window_height);
	LightGroup::StaticInitialize(dxcomn->GetDev());
	FbxLoader::GetInstance()->Initialize(dxcomn->GetDev());
	Texture::StaticInitialize(dxcomn->GetDev(), WinApp::window_width, WinApp::window_height);
	nTexture::StaticInitialize(dxcomn->GetDev(), WinApp::window_width, WinApp::window_height);

	//Scene = new TitleScene();
	//初期シーン

<<<<<<< HEAD
	BaseScene*scene_ = new BossScene3(sceneManger);
=======

	BaseScene*scene_ = new Tutorial(sceneManger);
>>>>>>> 30ac9d6d2f379f5c9a963990f2a160cec833276d


	sceneManger->SetnextScene(scene_);

	//Scene->Initialize();
}

void MyGame::Update(DirectXCommon* dxCommon)
{
	Framework::Update(dxCommon);
}


void MyGame::Draw(DirectXCommon* dxcomn)
{
	Framework::Draw(dxcomn);
}


//背景スプライト描画　少しめんどくさいやり方 clearDepthBuffer()よみこむため
void MyGame::backGround()
{
	//->BackGround(dxcomn->GetCmdList());
	//dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	//Scene->SpritePost(dxcomn->GetCmdList());
}
void MyGame::Finalize()
{
	Framework::Finalize();
}

