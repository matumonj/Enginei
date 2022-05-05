#include "Item.h"
#include"Destroy.h"
#include"Collision.h"
#include"GameUI.h"
Item::Item()
{

}
Item::~Item()
{
	delete* itemObj, itemModel;
}
void Item::Initialize()
{
	itemModel = Model::CreateFromOBJ("item");

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
		for (int i = 0; i < itemMax; i++) {
			if (itemObj[i] != nullptr) {
				itemObj[i]->SetPosition(position[i]);
				itemObj[i]->SetScale({ 1,1,1 });
				itemObj[i]->Update({ 1,1,1,1 });
			}
		}
}

void Item::Draw()
{
	for (int i = 0; i<itemMax; i++) {
		if (itemObj[i] != nullptr) {
			itemObj[i]->PreDraw();
			itemObj[i]->Draw();
			itemObj[i]->PostDraw();
		}
	}
}
void Item::Drop(std::unique_ptr<Enemy>enemy[])
{
	for (int i = 0; i < itemMax; i++) {
		if (enemy[i] != nullptr) {
			position[i] = enemy[i]->GetPosition();
		}
		else {
			GetPossible[i] = true;
		}
	
	}
}

void Item::HealEfficasy(Player*player)
{
	float dis[itemMax];
	for (int i = 0; i < itemMax; i++) {
		if(itemObj[i]!=nullptr){
		dis[i] = sqrtf((position[i].x - player->GetPosition().x) * (position[i].x - player->GetPosition().x) +
			(position[i].y - player->GetPosition().y) * (position[i].y - player->GetPosition().y));
		if (GetPossible[i] == true) {
			if (dis[i] <= 1) {
				GetItem(player);
				Destroy(itemObj[i]);
			}
		}
		}
	}
}

void Item::GetItem(Player* plauer)
{
	
	GameUI::GetInstance()->SetlineOutScl(GameUI::GetInstance()->GetOutX()+20);

}