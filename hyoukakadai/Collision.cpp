#include "Collision.h"//collision
#include"Line.h"
bool Collision::hit = false;
Collision* Collision::GetInstance()
{
	static Collision instance;
	return &instance;

}
void Collision::ColMap1(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y, float& grav, float& time, float& movespeed, bool& jumpf, XMFLOAT3& Player_Pos, XMFLOAT3& Old_Pos)
{
	//grav-grav
	//time-time
	//movespeed-movespeed
	float height;//
	float width;
	XMFLOAT3 Player_Scl = { 1,1,1 };
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Line::GetInstance()->getpos().x + 1.0f > mapx[j][i] - (width) && Line::GetInstance()->getpos().x - 1.0f < mapx[j][i] + (width)) && Line::GetInstance()->getpos().y + 1.0f > mapy[j][i] - height && Line::GetInstance()->getpos().y - 1.0f < mapy[j][i] + height) {
					if ( Line::GetInstance()->Gettriggerflag() == true) {
						Line::GetInstance()->Setmapcol(true);
						Line::GetInstance()->Setelf(true);
					}
				}
			
				if (Line::GetInstance()->Getboundflag() == false) {
				
					if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
						if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
							Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
							//moveSpeed = 0;
							grav = 0.0f;
							time = 0;
							jumpf = false;
							//Line::GetInstance()->SetBondflag(false);
							break;
						} else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
							Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
							//Line::GetInstance()->SetBondflag(false);
							break;
						}

					} else {
						movespeed = 0.2f;
						grav = 0.03f;
					}

					//プレイヤーの左辺
					if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
						if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {

							Player_Pos.y = Player_Pos.y + 0.001f;
							Player_Pos.x = mapx[j][i] + (width + Player_Scl.x);
							//Line::GetInstance()->SetBondflag(false);
							break;
						}
						//プレイヤーの右辺
						else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {

							Player_Pos.x = mapx[j][i] - (Player_Scl.x + width);
							//Line::GetInstance()->SetBondflag(false);
							//movespeed = 0;
							break;
						}
					} else {
						movespeed = 0.2f;
					}
				}
			}
		}
	}

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1 && Line::GetInstance()->Getboundflag() == true) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
					if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
						//Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
						Line::GetInstance()->Setpos(Player_Pos.x, Player_Pos.y);
						//Line::GetInstance()->SetSubradius(0);
						//Line::GetInstance()->Setmapcol(false);
						//Line::GetInstance()->Setelf(false);

						Line::GetInstance()->SetBondflag(false);
						Line::GetInstance()->SetSubradius(0);

						break;
					} else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
						// Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
						Line::GetInstance()->Setpos(Player_Pos.x, Player_Pos.y);

						//Line::GetInstance()->SetBondflag(false);
					//	Line::GetInstance()->SetSubradius(0);
						Line::GetInstance()->Setmapcol(false);
						Line::GetInstance()->Setelf(false);

						Line::GetInstance()->SetBondflag(false);
						Line::GetInstance()->SetSubradius(0);

						break;
					}

				} else {
					movespeed = 0.2f;
					grav = 0.03f;
				}

				//プレイヤーの左辺
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
					if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						Line::GetInstance()->Setpos(Player_Pos.x, Player_Pos.y);
						//Line::GetInstance()->SetBondflag(false);
						//Line::GetInstance()->SetSubradius(0);
						Line::GetInstance()->Setmapcol(false);
						Line::GetInstance()->Setelf(false);

						Line::GetInstance()->SetBondflag(false);
						Line::GetInstance()->SetSubradius(0);

						break;
					}
					//プレイヤーの右辺
					else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						Line::GetInstance()->Setpos(Player_Pos.x, Player_Pos.y);

						//Line::GetInstance()->SetBondflag(false);
						//Line::GetInstance()->SetSubradius(0);
						Line::GetInstance()->Setmapcol(false);
						Line::GetInstance()->Setelf(false);

						Line::GetInstance()->SetBondflag(false);
						Line::GetInstance()->SetSubradius(0);

						break;
					}
				} else {
					movespeed = 0.2f;
				}
			}
		}
	}
	//
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 2 && Line::GetInstance()->Getboundflag() == false && Line::GetInstance()->getcolfsub() == false) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
					if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
						Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
						//moveSpeed = 0;
						grav = 0.0f;
						time = 0;
						jumpf = false;
						//Line::GetInstance()->SetBondflag(false);
						break;
					} else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
						Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}

				} else {
					movespeed = 0.2f;
					grav = 0.03f;
				}

				//プレイヤーの左辺
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
					if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {

						Player_Pos.y = Player_Pos.y + 0.001f;
						Player_Pos.x = width + mapx[j][i] + Player_Scl.x;
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
					//プレイヤーの右辺
					else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {

						Player_Pos.x = mapx[j][i] - (Player_Scl.x + width);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
				} else {
					movespeed = 0.2f;
				}
			}
		}
	}

	/// <summary>
	/// 
	/// 
	/// </summary>
	/// <param name="dxCommon"></param>

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {

			if (map[j][i] == 2 && Line::GetInstance()->Getboundflag() == true && Line::GetInstance()->getcolfsub() == true) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y + 0.2f;
				width = tst[j][i]->GetScale().x + 0.2f;

				if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
					if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
						map[j][i] = 0;
						Line::GetInstance()->setcolfsub(false);
						break;
					} else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
						map[j][i] = 0;
						Line::GetInstance()->setcolfsub(false);
						break;
					}

				}
				//プレイヤーの左辺
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
					if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						map[j][i] = 0;
						Line::GetInstance()->setcolfsub(false);
						break;
					}
					//プレイヤーの右辺
					else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						map[j][i] = 0;
						Line::GetInstance()->setcolfsub(false);
						break;
					}
				}
			}
		}
	}


	time += 0.04f;
	Player_Pos.y -= grav * time * time;

}

void Collision::CollisionMap(int map[20][200], std::unique_ptr<Object3d> tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y, float& grav, float& time, float& movespeed, bool& jumpf, XMFLOAT3& Player_Pos,XMFLOAT3 Player_Scl, XMFLOAT3& Old_Pos, int MAP_NUMBER)
{
	float height;//
	float width;
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == MAP_NUMBER ) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;
				if ((Line::GetInstance()->getpos().x + 1.0f > mapx[j][i] - (width) && Line::GetInstance()->getpos().x - 1.0f < mapx[j][i] + (width)) && Line::GetInstance()->getpos().y + 1.0f > mapy[j][i] - height && Line::GetInstance()->getpos().y - 1.0f < mapy[j][i] + height) {
					if (Line::GetInstance()->Gettriggerflag() == true) {
						Line::GetInstance()->Setmapcol(true);
						Line::GetInstance()->Setelf(true);
					}
				}

				if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
					if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
						Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
						hit = true;
						//moveSpeed = 0;
						grav = 0.0f;
						time = 0;
						jumpf = false;
						break;
					}
					else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
						Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
						break;
					}

				}
				else {
					movespeed = 0.2f;
					grav = 0.03f;
				}

				//プレイヤーの左辺
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
					if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						hit = true;
						Player_Pos.y = Player_Pos.y + 0.001f;
						Player_Pos.x = width + mapx[j][i] + Player_Scl.x;
						//grav = 0.0f;
						//time = 0;
						break;
					}
					//プレイヤーの右辺
					else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						Player_Pos.x = mapx[j][i] - (Player_Scl.x + width);
						//grav = 0.0f;
						//time = 0;
						//moveSpeed = 0;
						break;
					}
				}
				else {
					movespeed = 0.2f;
				}
			}
		}
	}
}

void Collision::ColMap2(int map[130][20], std::unique_ptr<Object3d> tst[130][20], float mapx[130][20],  float mapy[130][20], const int X, const int Y, float& grav, float& time, float& movespeed, bool& jumpf, XMFLOAT3& Player_Pos, XMFLOAT3& Old_Pos)
{
	//grav-grav
//time-time
//movespeed-movespeed
	float height;//
	float width;
	XMFLOAT3 Player_Scl = { 1,1,1 };
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1|| map[j][i] == 2) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Line::GetInstance()->getpos().x + 1.0f > mapx[j][i] - (width) && Line::GetInstance()->getpos().x - 1.0f < mapx[j][i] + (width)) && Line::GetInstance()->getpos().y + 1.0f > mapy[j][i] - height && Line::GetInstance()->getpos().y - 1.0f < mapy[j][i] + height) {
					if (Line::GetInstance()->Gettriggerflag() == true) {
						Line::GetInstance()->Setmapcol(true);
						Line::GetInstance()->Setelf(true);
					}
				}

				if (Line::GetInstance()->Getboundflag() == false) {

					if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
						if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
							Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
							//moveSpeed = 0;
							grav = 0.0f;
							time = 0;
							jumpf = false;
							//Line::GetInstance()->SetBondflag(false);
							break;
						}
						else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
							Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
							//Line::GetInstance()->SetBondflag(false);
							break;
						}

					}
					else {
						movespeed = 0.2f;
						grav = 0.03f;
					}

					//プレイヤーの左辺
					if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
						if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {

							Player_Pos.y = Player_Pos.y + 0.001f;
							Player_Pos.x = mapx[j][i] + (width + Player_Scl.x);
							//Line::GetInstance()->SetBondflag(false);
							break;
						}
						//プレイヤーの右辺
						else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {

							Player_Pos.x = mapx[j][i] - (Player_Scl.x + width);
							//Line::GetInstance()->SetBondflag(false);
							//movespeed = 0;
							break;
						}
					}
					else {
						movespeed = 0.2f;
					}
				}
			}
		}
	}

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1|| map[j][i] == 2 && Line::GetInstance()->Getboundflag() == true) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
					if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
						//Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
						Line::GetInstance()->Setpos(Player_Pos.x, Player_Pos.y);
						//Line::GetInstance()->SetSubradius(0);
						//Line::GetInstance()->Setmapcol(false);
						//Line::GetInstance()->Setelf(false);

						Line::GetInstance()->SetBondflag(false);
						Line::GetInstance()->SetSubradius(0);

						break;
					}
					else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
						// Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
						Line::GetInstance()->Setpos(Player_Pos.x, Player_Pos.y);

						//Line::GetInstance()->SetBondflag(false);
					//	Line::GetInstance()->SetSubradius(0);
						Line::GetInstance()->Setmapcol(false);
						Line::GetInstance()->Setelf(false);

						Line::GetInstance()->SetBondflag(false);
						Line::GetInstance()->SetSubradius(0);

						break;
					}

				}
				else {
					movespeed = 0.2f;
					grav = 0.03f;
				}

				//プレイヤーの左辺
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
					if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						Line::GetInstance()->Setpos(Player_Pos.x, Player_Pos.y);
						//Line::GetInstance()->SetBondflag(false);
						//Line::GetInstance()->SetSubradius(0);
						Line::GetInstance()->Setmapcol(false);
						Line::GetInstance()->Setelf(false);

						Line::GetInstance()->SetBondflag(false);
						Line::GetInstance()->SetSubradius(0);

						break;
					}
					//プレイヤーの右辺
					else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						Line::GetInstance()->Setpos(Player_Pos.x, Player_Pos.y);

						//Line::GetInstance()->SetBondflag(false);
						//Line::GetInstance()->SetSubradius(0);
						Line::GetInstance()->Setmapcol(false);
						Line::GetInstance()->Setelf(false);

						Line::GetInstance()->SetBondflag(false);
						Line::GetInstance()->SetSubradius(0);

						break;
					}
				}
				else {
					movespeed = 0.2f;
				}
			}
		}
	}


	time += 0.04f;
	Player_Pos.y -= grav ;

}



float Collision::GetLen(XMFLOAT3 position, XMFLOAT3 position2)
{
	float len;
	len = sqrt((position.x - position2.x) * (position.x - position2.x) + (position.y - position2.y) * (position.y - position2.y));
	return len;
}

float Collision::GetLen_X(float position,float position2)
{
	float len;
	len = sqrt((position - position2) * (position - position2));
	return len;
}
float Collision::GetLenX(XMFLOAT3 position, XMFLOAT3 position2)
{
	float len;
	len = sqrt((position.x - position2.x) * (position.x - position2.x) );
	return len;
}
float Collision::GetLenY(XMFLOAT3 position, XMFLOAT3 position2)
{
	float len;
	len = sqrt((position.y - position2.y) * (position.y - position2.y));
	return len;
}
//
void Collision::ColMapb1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y, float& grav, float& time, float& movespeed, bool& jumpf, XMFLOAT3& Player_Pos, XMFLOAT3& Old_Pos)
{
	//grav-grav
	//time-time
	//movespeed-movespeed
	float height;//
	float width;
	XMFLOAT3 Player_Scl = { 1,1,1 };
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1|| map[j][i] == 2|| map[j][i] == 4) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;
				if ((Line::GetInstance()->getpos().x + 1.0f > mapx[j][i] - (width) && Line::GetInstance()->getpos().x - 1.0f < mapx[j][i] + (width)) && Line::GetInstance()->getpos().y + 1.0f > mapy[j][i] - height && Line::GetInstance()->getpos().y - 1.0f < mapy[j][i] + height) {
					if (Line::GetInstance()->Gettriggerflag() == true) {
						Line::GetInstance()->Setmapcol(true);
						Line::GetInstance()->Setelf(true);
					}
				}

				if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
					if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
						Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
						//moveSpeed = 0;
						grav = 0.0f;
						time = 0;
						//jumpf = false;
						break;
					} else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
						Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
						break;
					}

				} else {
					movespeed = 0.2f;
					grav = 0.03f;
				}

				//プレイヤーの左辺
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
					if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						Player_Pos.y = Player_Pos.y + 0.001f;
						Player_Pos.x = width + mapx[j][i] + Player_Scl.x;
						//grav = 0.0f;
						//time = 0;
						break;
					}
					//プレイヤーの右辺
					else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						Player_Pos.x = mapx[j][i] - (Player_Scl.x + width);
						//grav = 0.0f;
						//time = 0;
						//moveSpeed = 0;
						break;
					}
				} else {
					movespeed = 0.2f;
				}
			}
			
		}
	}
	time += 0.04f;
	float gravtime= grav * time * time;

	Player_Pos.y -=gravtime;

	gravtime = max(0.0f, gravtime);
	//enemy->Setposition(Player_Pos);

}

/// <summary>
/// 
/// 
/// </summary>
/// <param name="dxCommon"></param>

void Collision::ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point, const Triangle& triangle, DirectX::XMVECTOR* closest)
{
	// pointがp0の外側の頂点領域の中にあるかどうかチェック
	XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
	XMVECTOR p0_p2 = triangle.p2 - triangle.p0;
	XMVECTOR p0_pt = point - triangle.p0;

	float d1 = XMVector3Dot(p0_p1, p0_pt).m128_f32[0];
	float d2 = XMVector3Dot(p0_p2, p0_pt).m128_f32[0];

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0が最近傍
		*closest = triangle.p0;
		return;
	}

	// pointがp1の外側の頂点領域の中にあるかどうかチェック
	XMVECTOR p1_pt = point - triangle.p1;

	float d3 = XMVector3Dot(p0_p1, p1_pt).m128_f32[0];
	float d4 = XMVector3Dot(p0_p2, p1_pt).m128_f32[0];

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1が最近傍
		*closest = triangle.p1;
		return;
	}

	// pointがp0_p1の辺領域の中にあるかどうかチェックし、あればpointのp0_p1上に対する射影を返す
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// pointがp2の外側の頂点領域の中にあるかどうかチェック
	XMVECTOR p2_pt = point - triangle.p2;

	float d5 = XMVector3Dot(p0_p1, p2_pt).m128_f32[0];
	float d6 = XMVector3Dot(p0_p2, p2_pt).m128_f32[0];
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// pointがp0_p2の辺領域の中にあるかどうかチェックし、あればpointのp0_p2上に対する射影を返す
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// pointがp1_p2の辺領域の中にあるかどうかチェックし、あればpointのp1_p2上に対する射影を返す
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	// pointは面領域の中にある。closestを重心座標を用いて計算する
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}
bool Collision::CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::XMVECTOR* inter, DirectX::XMVECTOR* reject)
{
	// 中心点の距離の２乗 <= 半径の和の２乗　なら交差
	float dist = XMVector3LengthSq(sphereA.center - sphereB.center).m128_f32[0];

	float radius2 = sphereA.radius + sphereB.radius;
	radius2 *= radius2;

	if (dist <= radius2) {
		if (inter) {
			// Aの半径が0の時座標はBの中心　Bの半径が0の時座標はAの中心　となるよう補完
			float t = sphereB.radius / (sphereA.radius + sphereB.radius);
			*inter = XMVectorLerp(sphereA.center, sphereB.center, t);
		}
		// 押し出すベクトルを計算
		if (reject) {
			float rejectLen = sphereA.radius + sphereB.radius - sqrtf(dist);
			*reject = XMVector3Normalize(sphereA.center - sphereB.center);
			*reject *= rejectLen;
		}
		return true;
	}

	return false;
}

bool Collision::CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter, DirectX::XMVECTOR* reject)
{
	XMVECTOR p;
	// 球の中心に対する最近接点である三角形上にある点pを見つける
	ClosestPtPoint2Triangle(sphere.center, triangle, &p);
	// 点pと球の中心の差分ベクトル
	XMVECTOR v = p - sphere.center;
	// 距離の二乗を求める
	//（同じベクトル同士の内積は三平方の定理のルート内部の式と一致する）
	float distanceSquare = XMVector3Dot(v, v).m128_f32[0];
	// 球と三角形の距離が半径以下なら当たっていない
	if (distanceSquare > sphere.radius * sphere.radius)	return false;
	// 擬似交点を計算
	if (inter) {
		// 三角形上の最近接点pを疑似交点とする
		*inter = p;
	}
	// 押し出すベクトルを計算
	if (reject) {
		float ds = XMVector3Dot(sphere.center, triangle.normal).m128_f32[0];
		float dt = XMVector3Dot(triangle.p0, triangle.normal).m128_f32[0];
		float rejectLen = dt - ds + sphere.radius;
		*reject = triangle.normal * rejectLen;
	}
	return true;
}

bool Collision::Boxcol(XMFLOAT2 a1, XMFLOAT2 a2, XMFLOAT2 b1, XMFLOAT2 b2)
{
	if (b1.x > a2.x) { return false; }
	if (a1.x > b2.x) { return false; }
	if (b1.y > a2.y) { return false; }
	if (a1.y > b2.y) { return false; }
	return true;
}
bool Collision::CheckBox2Box(XMFLOAT3 object1, XMFLOAT3& object2, XMFLOAT3 r, XMFLOAT3 r2)
{
	BoxVertex Object1;
	BoxVertex Object2;

	//object1の右頂点
	Object1.Right = object1.x + r.x * 2;
	//object1の左頂点
	Object1.Left = object1.x;
	//object1の上頂点
	Object1.Up = object1.y + r.y;
	//object1の下頂点
	Object1.Down = object1.y - r.y;

	//object1の右頂点
	Object2.Right = object2.x + r.x * 2;
	//object1の左頂点
	Object2.Left = Object2.Right;
	//object1の下頂点
	Object2.Down = object2.y - r2.y;
	//object1の上頂点
	Object2.Up = object2.y + r2.y;

	//→１と左２　→２と左１　上１と下２　上２と下１
	return Object1.Right >= Object2.Left && Object2.Right >= Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;

}
bool Collision::CheckRay2Plane(const Ray& lay, const Plane& plane, float* distance, DirectX::XMVECTOR* inter)
{
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値

	float d1 = XMVector3Dot(plane.normal, lay.dir).m128_f32[0];
	// 裏面には当たらない
	if (d1 > -epsilon) {
		return false;
	}

	float d2 = XMVector3Dot(plane.normal, lay.start).m128_f32[0];
	float t = (plane.distance - d2) / d1;

	if (t < 0) return false;

	// 距離を書き込む
	if (distance) {
		*distance = t;
	}

	// 交点を計算
	if (inter) {
		*inter = lay.start + t * lay.dir;
	}

	return true;
}

bool Collision::CheckRay2Triangle(const Ray& lay, const Triangle& triangle, float* distance, DirectX::XMVECTOR* inter)
{
	// 三角形が乗っている平面を算出
	Plane plane;
	XMVECTOR interPlane;
	plane.normal = triangle.normal;
	plane.distance = XMVector3Dot(triangle.normal, triangle.p0).m128_f32[0];
	// レイと平面が当たっていなければ、当たっていない	
	if (!CheckRay2Plane(lay, plane, distance, &interPlane)) {
		return false;
	}
	// レイと平面が当たっていたので、距離と交点が書き込まれた

	// レイと平面の交点が三角形の内側にあるか判定
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値
	XMVECTOR m;
	// 辺p0_p1について
	XMVECTOR pt_p0 = triangle.p0 - interPlane;
	XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
	m = XMVector3Cross(pt_p0, p0_p1);
	// 辺の外側
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) {
		return false;
	}

	// 辺p1_p2について
	XMVECTOR pt_p1 = triangle.p1 - interPlane;
	XMVECTOR p1_p2 = triangle.p2 - triangle.p1;
	m = XMVector3Cross(pt_p1, p1_p2);
	// 辺の外側
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) {
		return false;
	}

	// 辺p2_p0について
	XMVECTOR pt_p2 = triangle.p2 - interPlane;
	XMVECTOR p2_p0 = triangle.p0 - triangle.p2;
	m = XMVector3Cross(pt_p2, p2_p0);
	// 辺の外側
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) {
		return false;
	}

	if (inter) {
		*inter = interPlane;
	}

	// 内側なので、当たっている
	return true;
}

bool Collision::CheckRay2Sphere(const Ray& lay, const Sphere& sphere, float* distance, DirectX::XMVECTOR* inter)
{
	XMVECTOR m = lay.start - sphere.center;
	float b = XMVector3Dot(m, lay.dir).m128_f32[0];
	float c = XMVector3Dot(m, m).m128_f32[0] - sphere.radius * sphere.radius;
	// layの始点がsphereの外側にあり(c > 0)、layがsphereから離れていく方向を
	// 差している場合(b > 0)、当たらない
	if (c > 0.0f && b > 0.0f) {
		return false;
	}

	float discr = b * b - c;
	// 負の判別式はレイが球を外れていることに一致
	if (discr < 0.0f) {
		return false;
	}

	// レイは球と交差している。
	// 交差する最小の値tを計算
	float t = -b - sqrtf(discr);
	// tが負である場合、レイは球の内側から開始しているのでtをゼロにクランプ
	if (t < 0) t = 0.0f;

	if (distance) {
		*distance = t;
	}

	if (inter) {
		*inter = lay.start + t * lay.dir;
	}

	return true;
}

float Collision::LinetoBoxCollision(const int Map_X, const int Map_Y, Object3d** map[], Player* player, float radius)
{
	BoxVertex** MapObject;
	BoxVertex PlayerObject;

	PlayerObject.Left = player->GetPosition().x - 1;
	PlayerObject.Right = player->GetPosition().x + 1;
	PlayerObject.Up = player->GetPosition().y + 1;
	PlayerObject.Down = player->GetPosition().y - 1;

	for (int i = 0; i < Map_Y; i++) {
		for (int j = 0; j < Map_X; j++) {
			MapObject[i][j].Right = map[i][j]->GetPosition().x + 1;
			MapObject[i][j].Left = map[i][j]->GetPosition().x - 1;
			MapObject[i][j].Up = map[i][j]->GetPosition().y + 1;
			MapObject[i][j].Down = map[i][j]->GetPosition().y - 1;

		}
	}
	for (int i = 0; i < Map_Y; i++) {
		for (int j = 0; j < Map_X; j++) {
			return MapObject[i][j].Right >= PlayerObject.Left && PlayerObject.Right >= MapObject[i][j].Left && MapObject[i][j].Up >= PlayerObject.Down && PlayerObject.Up >= MapObject[i][j].Down;
		}
	}

}

bool Collision::BoxCollision_Down(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1の右頂点
	Object1.Right = object1.x + radius1.x;
	//object1の左頂点
	Object1.Left = object1.x - radius1.x;
	//object1の上頂点
	Object1.Up = object1.y + radius1.y;
	//object1の下頂点
	Object1.Down = object1.y - radius1.y;

	//object1の左頂点
	Object2.Left = object2.x - radius2.x;
	//object1の右頂点
	Object2.Right = object2.x + radius2.x;
	//object1の下頂点
	Object2.Down = object2.y - radius2.y;
	//object1の上頂点
	Object2.Up = Object2.Down + 2;
	//→１と左２　→２と左１　上１と下２　上２と下１
	return Object1.Right > Object2.Left && Object2.Right > Object1.Left && Object1.Up > Object2.Down && Object2.Up > Object1.Down;
}

bool Collision::BoxCollision_Up(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1の右頂点
	Object1.Right = object1.x + radius1.x;
	//object1の左頂点
	Object1.Left = object1.x - radius1.x;
	//object1の上頂点
	Object1.Up = object1.y + radius1.y;
	//object1の下頂点
	Object1.Down = object1.y - radius1.y;

	//object1の左頂点
	Object2.Left = object2.x - radius2.x;
	//object1の右頂点
	Object2.Right = object2.x + radius2.x;
	//object1の下頂点
	Object2.Down = object2.y - radius2.y;
	//object1の上頂点
	Object2.Up = Object2.Down - 2;
	//→１と左２　→２と左１　上１と下２　上２と下１
	return Object1.Right > Object2.Left && Object2.Right > Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;
}


bool Collision::BoxCollision_Left(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1の右頂点
	Object1.Right = object1.x + radius1.x;
	//object1の左頂点
	Object1.Left = object1.x;
	//object1の上頂点
	Object1.Up = object1.y + radius1.y;
	//object1の下頂点
	Object1.Down = object1.y - radius1.y;

	//object1の左頂点
	Object2.Left = object2.x - radius2.x;
	//object1の右頂点
	Object2.Right = Object2.Left + 2;
	//object1の下頂点
	Object2.Down = object2.y - radius2.y;
	//object1の上頂点
	Object2.Up = object2.y + radius2.y;
	//→１と左２　→２と左１　上１と下２　上２と下１
	return Object1.Right >= Object2.Left && Object2.Right >= Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;
}

bool Collision::BoxCollision_Right(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1の右頂点
	Object1.Right = object1.x + radius1.x;
	//object1の左頂点
	Object1.Left = object1.x;
	//object1の上頂点
	Object1.Up = object1.y + radius1.y;
	//object1の下頂点
	Object1.Down = object1.y - radius1.y;

	//object1の右頂点
	Object2.Right = object2.x + radius2.x;
	//object1の左頂点
	Object2.Left = Object2.Right - 2;
	//object1の下頂点
	Object2.Down = object2.y - radius2.y;
	//object1の上頂点
	Object2.Up = object2.y + radius2.y;
	//→１と左２　→２と左１　上１と下２　上２と下１
	return Object1.Right >= Object2.Left && Object2.Right >= Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;
}