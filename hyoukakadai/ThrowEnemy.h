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
    
    Model* ThrowModel = nullptr;
    Object3d* ThrowObj = nullptr;

    XMFLOAT3 position = {};
    XMFLOAT3 scale = {};
    XMFLOAT3 rotation = {};

    XMFLOAT3 thposition = {};
    XMFLOAT3 thscale = {};
    XMFLOAT3 throtation = {};

    enum class State {
        SearchPlayer,
        Attack,
        Dead,
        None,
    };
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
};

