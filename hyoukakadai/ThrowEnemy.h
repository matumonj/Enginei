#pragma once
#include"mEffekseer.h"
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
#include"nTexture.h"
#include"DirectXCommon.h"
class ThrowEnemy :
    public Enemy
{
public:
    ThrowEnemy();
    ~ThrowEnemy();
private:
    nTexture* searchTexture;
    int searchCount = 0;
    bool searchFlag;
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
    int pm[3];
    int pmmove;
    bool movereturn;
    ThrowParam throwparam[3];
    int attackf[3] = { false };
    int attackcount = 0;
    State enemyState = State::None;
    int cooltime = 0;
    int Damage = 1;
    bool followf;
    float movespeed = 0.2f;
    float grav = 0.03f;
    float time = 0;
    int Attackcount = 0;
    XMFLOAT3 Old_Pos;
    bool movexrand;
    float movement = 0;
    int jumpcount = 0;
    bool jumpflag = false;
public:
    void SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)override;
    void Initialize()override;
    void Update(XMFLOAT3 position)override;
    void Draw(DirectXCommon* dxcomn)override;
    void EnemySearchPlayer(Player*player)override;
    void Attack(Player* player)override;
    void Motion(Player* player)override;
    void ProjectileMotion(XMFLOAT3 position);
    void ColMap(int map[20][200] , std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)override;
    bool GetStateAttack() { if (enemyState == State::Attack)return true; }
    void enemyappearance(TyutorialSprite* sprite) override{};
    void ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)override;

};

