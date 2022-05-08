#pragma once
#include "Enemy.h"
#pragma once
#include"mEffekseer.h"
#include"Object3d.h"
#include"Model.h"
#include"TyutorialSprite.h"
class ThronEnemy :
    public Enemy
{
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ThronEnemy();

        /// <summary>
        /// デストラクタ
        /// </summary> 
        ~ThronEnemy();

    private:
        //オブジェクトのインスタンス
        Object3d* ThronObject = nullptr;
        //モデルのインスタンス
        Model* ThronModel = nullptr;
        //
        mEffekseer* effect_dead;
    private:
       
    public:
        void EnemySearchPlayer(Player* player)override;

        /// <summary>
        /// 初期化
        /// </summary>
        void Initialize()override;

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update(XMFLOAT3 position)override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw()override;

        /// <summary>
        /// 解放処理
        /// </summary>
        void Finalize()override;
        void Follow(Player* player);
        void Motion(Player* player)override;
        void Attack(Player* player)override;
        float angleXs, angleZs, angleRs;
        float centerSpeed = 0.1f;
        const int AttackDamage = 2;
    public:
        /// <summary>
        /// アクセッサ
        /// </summary>
        /// <returns></returns>
        void ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[15][200], const int X, const int Y);
        void enemyappearance(TyutorialSprite* sprite);
 
};

