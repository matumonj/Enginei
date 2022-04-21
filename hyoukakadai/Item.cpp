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
	//ÉÇÉfÉãÇÃì«çû
	for (int i = 0; i < itemMax; i++) {
		itemModel= Model::CreateFromOBJ("bossenemy");
		//ÉÇÉfÉãäÑÇËìñÇƒ
		//MobObject = new Object3d();
		itemObj[i] = Object3d::Create();
		itemObj[i]->SetModel(itemModel);
	}
}

void Item::Update(std::unique_ptr<Enemy>enemy[])
{
	for (int i = 0; i < 4; i++) {
		if (enemy[i] != nullptr) {
			positione[i] = enemy[i]->GetPosition();;
		}

		Drop(enemy);

		itemObj[i]->SetPosition(position[i]);
		itemObj[i]->SetScale({ 1,1,1 });
		itemObj[i], Update(enemy);
	}

}

void Item::Draw()
{
	for (int i = 0; itemMax; i++) {
		itemObj[i]->PreDraw();
		itemObj[i]->Draw();
		itemObj[i]->PostDraw();
	}
}
void Item::Drop(std::unique_ptr<Enemy>enemy[])
{
	for (int i = 0; i <4; i++) {
			position[i]= positione[i];
	}
}