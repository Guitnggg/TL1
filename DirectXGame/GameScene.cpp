#include "GameScene.h"

#include <string>
#include <json.hpp>
#include <fstream>
#include <cassert>
#include <vector>

using namespace KamataEngine;

GameScene::~GameScene() {

}

void GameScene::Initialize() {
    //========================================
    // jsonファイルのデシリアライズ化
    //========================================

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

    //========================================
    // レベルデータを構造体に格納していく
    //========================================

    LevelData* levelData = new LevelData();

    // 
    levelData->name = deserialized["name"].get < std::string>();
    assert(levelData->name == "scene");  // 

    // "objects"の全オブジェクトの走査
    for (nlohmann::json& object : deserialized["objects"]) {
        // 
        assert(object["type"].get<std::string>() == "MESH") {
            // 
            levelData->objects.emplace_back(ObjectData{});
            ObjectData& objectData = levelData->objects.back();
        }
    }
}

void GameScene::Update() {

}

void GameScene::Draw() {

}