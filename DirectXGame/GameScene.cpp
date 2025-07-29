#include "GameScene.h"

#include <string>
#include <json.hpp>
#include <fstream>
#include <cassert>
#include <vector>

using namespace KamataEngine;

GameScene::~GameScene() {
    for (auto& [wt, model] : objects_) {
        delete wt;
    }
    objects_.clear();

}

void GameScene::Initialize() {
    //==================================================
    // jsonファイルのデシリアライズ化
    //==================================================

    // 連結してフルパスを得る
    const std::string fullpath = std::string("Resources/levels/") + "scene.json";

    // ファイルストリーム
    std::ifstream file;

    // ファイルを開く
    file.open(fullpath);
    // ファイルオープン失敗をチェック
    if (file.fail()) {
        assert(0);
    }

    // JSON文字列から回答したデータ
    nlohmann::json deserialized;  // deserialized : 逆シリアライズ化 → 1つの文字列をメモリ中のデータ構造化すること

    // 解凍
    file >> deserialized;

    // 正しいレベルデータファイルかチェック
    assert(deserialized.is_object());          // object か json形式にはさまざまな型がある　object型はその中でも「キーと値のペアを持つ構造」
    assert(deserialized.contains("name"));     // "name"が含まれているか
    assert(deserialized["name"].is_string());  // ["name"]は文字列か？

    //==================================================
    // レベルデータを構造体に格納していく
    //==================================================

    LevelData* levelData = new LevelData();

    // "name"を文字列として取得
    levelData->name = deserialized["name"].get < std::string>();
    assert(levelData->name == "scene");  // それは"scene"なのか

    // "objects"の全オブジェクトの走査
    for (nlohmann::json& object : deserialized["objects"]) {
        // オブジェクト１つ分の妥当性のチェック
        assert(object.contains("type"));  // "type"が含まれているか

        if (object["type"].get<std::string>() == "MESH") {
            // １個分の要素の準備
            levelData->objects.emplace_back(ObjectData{});
            ObjectData& objectData = levelData->objects.back();  // 追加要素の参照を用意し可読性もよくなる

            objectData.type = object["type"].get<std::string>();  // "type"
            objectData.name = object["name"].get<std::string>();  // "name"

            // トランスフォームのパラメーター読み込み
            nlohmann::json& transform = object["transform"];

            // 平行移動"transform"
            objectData.transform.translation.x = (float)transform["translation"][0];
            objectData.transform.translation.y = (float)transform["translation"][2];
            objectData.transform.translation.z = (float)transform["translation"][1];

            // 回転角"rotation"
            objectData.transform.rotation.x = -(float)transform["rotation"][0];
            objectData.transform.rotation.y = -(float)transform["rotation"][2];
            objectData.transform.rotation.z = -(float)transform["rotation"][1];

            // 拡大縮小"scaling"
            objectData.transform.scaling.x = (float)transform["scaling"][0];
            objectData.transform.scaling.y = (float)transform["scaling"][2];
            objectData.transform.scaling.z = (float)transform["scaling"][1];

            // "file_name"
            if (object.contains("file_name")) {
                objectData.file_name = object["file_name"].get<std::string>();
            }

        }
    }

    //==================================================
    // レベルデータを構造体に格納していく
    //==================================================

    // レベルデータからオブジェクトを生成、配置
    for (auto& objectData : levelData->objects) {
        // ファイル名から登録済みモデルを検索
        KamataEngine::Model* model = nullptr;
        decltype(models)::iterator it = models.find(objectData.file_name);
        if (it != models.end()) {
            model = it->second;
        }
        else {
            model = KamataEngine::Model::CreateFromOBJ(objectData.file_name);
            models[objectData.file_name] = model;
        }

        // WorldTransform生成・初期化
        WorldTransform* wt = new WorldTransform();            // モデルを指定して3Dオブジェクトを生成
        wt->translation_ = objectData.transform.translation;  // 位置の設定
        wt->rotation_ = objectData.transform.rotation;        // 回転の設定
        wt->scale_ = objectData.transform.scaling;            // 拡大縮小
        wt->Initialize();

        // モデルとWorldTransformをセットで登録
        objects_.emplace_back(wt, model);
    }

    camera_.Initialize();
}

void GameScene::Update() {
   
}

void GameScene::Draw() {
    for (auto& [wt, model] : objects_) {
        model->Draw(*wt, camera_);
    }
}