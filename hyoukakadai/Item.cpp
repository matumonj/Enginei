#include "Item.h"


Item::Item()
{

}
Item::~Item()
{
	delete* itemObj, itemModel;
}
void Item::Initialize()
{
	itemModel = Model::CreateFromOBJ("bullet");

	//ÉÇÉfÉãÇÃì«çû
	for (int i = 0; i < itemMax; i++) {
		//ÉÇÉfÉãäÑÇËìñÇƒ
	///	itemObj[i] = new Object3d();
		itemObj[i] = Object3d::Create();
	//	itemObj[i]->Initialize();
		itemObj[i]->SetModel(itemModel);
	}

}

void Item::Update(std::unique_ptr<Enemy>enemy[])
{

		Drop(enemy);
		for (int i = 0; i<itemMax; i++) {
		itemObj[i]->SetPosition(position[i]);
		itemObj[i]->SetScale({ 1,1,1 });
		itemObj[i]->Update({1,1,1,1});
	}
}

void Item::Draw()
{
	for (int i = 0; i<itemMax; i++) {
		itemObj[i]->PreDraw();
		itemObj[i]->Draw();
		itemObj[i]->PostDraw();
	}
}
void Item::Drop(std::unique_ptr<Enemy>enemy[])
{
	for (int i = 0; i < 4; i++) {
		if (enemy[i] != nullptr) {
			position[i] = enemy[i]->GetPosition();
		}
	
	}
}

void Item::HealEfficasy(Player*player)
{
	
}