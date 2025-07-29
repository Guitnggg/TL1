#pragma once

#include "KamataEngine.h"

#include <map>

class GameScene {
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

public:

    /// <summary>
    /// オブジェクト 1個分のデータ
    /// </summary>
    struct ObjectData {
        std::string type;  // "type"
        std::string name;  // "name"

        //"transform"
        struct Transform {
            KamataEngine::Vector3 translation;  // "translation"
            KamataEngine::Vector3 rotation;     // "rotation"
            KamataEngine::Vector3 scaling;      // "scaling"
        };

        Transform transform;  // メンバの準備

        // "file name"
        std::string file_name;
    };

    /// <summary>
    /// レベルデータ
    /// </summary>
    struct LevelData {
        // "name"
        std::string name;

        // "object"
        std::vector<ObjectData> objects;
    };

private:

    KamataEngine::Camera camera_;
   
    std::map<std::string, KamataEngine::Model*> models;

    std::vector<std::pair<KamataEngine::WorldTransform*, KamataEngine::Model*>> objects_;
};

