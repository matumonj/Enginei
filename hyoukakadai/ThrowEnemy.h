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
    
    Model* ThrowModel[3] = { nullptr };
    Object3d* ThrowObj[3] = { nullptr };

    XMFLOAT3 position = {};
    XMFLOAT3 scale = {};
    XMFLOAT3 rotation = {};

    XMFLOAT3 thposition[3] = {};
    XMFLOAT3 thscale[3] = {};
    XMFLOAT3 throtation[3] = {};

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
    ThrowParam throwparam[3];
    int attackf[3] = { false };
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
    void ColMap(int map[15][100], float mapx[15][100], float mapy[15][100], const int X, const int Y)override;
    bool GetStateAttack() { if (enemyState == State::Attack)return true; }
};

