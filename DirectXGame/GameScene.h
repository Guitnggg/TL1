#pragma once

#include "KamataEngine.h"

class GameScene{
public:

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameScene();

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw();

private:

    KamataEngine::Camera camera_;
    KamataEngine::Model* model_ = nullptr;
};

