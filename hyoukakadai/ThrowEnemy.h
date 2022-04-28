#pragma once
#include"mEffekseer.h"
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
class ThrowEnemy :
    public Enemy
{
public:
    ThrowEnemy();
    ~ThrowEnemy();
private:
    Model* EnemyModel = nullptr;
    Object3d* EnemyObj = nullptr;
    
    Model* ThrowModel[10] = { nullptr };
    Object3d* ThrowObj[10] = { nullptr };

    XMFLOAT3 position = {};
    XMFLOAT3 scale = {};
    XMFLOAT3 rotation = {};

    XMFLOAT3 thposition[10] = {};
    XMFLOAT3 thscale[10] = {};
    XMFLOAT3 throtation[10] = {};

    enum class State {
        SearchPlayer,
        Attack,
        Dead,
        None,
    };
    struct ThrowParam {
        float movex, movey;
        float initialvec_x=1;
        float initialvec_y=3;
        float grav=-5.0f/60;
        int time=0;
        bool flag = false;
    };
    ThrowParam throwparam[10];
    int attackf[10] = { false };
    int attackcount = 0;
    State enemyState = State::None;
    int cooltime = 0;
    int Damage = 1;
public:
    void Initialize()override;
    void Update(XMFLOAT3 position)override;
    void Draw()override;
    void EnemySearchPlayer(Player*player)override;
    void Attack(Player* player)override;
    void Motion(int time)override;
    void ProjectileMotion();
    void ColMap(int map[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y)override;
    bool GetStateAttack() { if (enemyState == State::Attack)return true; }
    void enemyappearance(TyutorialSprite* sprite) override{};
   
};

