#pragma once
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
class MobEnemy :
    public Enemy
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MobEnemy();

    /// <summary>
    /// デストラクタ
    /// </summary> 
    ~MobEnemy();

private:
    //オブジェクトのインスタンス
    Object3d* MobObject=nullptr;
    //モデルのインスタンス
    Model* MobModel=nullptr;

private:
    XMFLOAT3 Mob_Pos;
    XMFLOAT3 Mob_Rot;
    XMFLOAT3 Mob_Scl;
public:
    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize()override;
    
    /// <summary>
    /// 更新処理
    /// </summary>
    void Update()override;
    
    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// 解放処理
    /// </summary>
    void Finalize()override;
public:
    /// <summary>
    /// アクセッサ
    /// </summary>
    /// <returns></returns>
    XMFLOAT3 GetPosition() { return Mob_Pos; }
    XMFLOAT3 GetRotation() { return Mob_Rot; }
    XMFLOAT3 GetScale() { return Mob_Scl; }

};

