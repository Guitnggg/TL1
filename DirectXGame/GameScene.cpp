#include "GameScene.h"

#include <cassert>
#include <fstream>

using namespace KamataEngine;

GameScene::~GameScene() {

}

void GameScene::Initialize() {
    // 連結してフルパスを得る
    const std::string fullpath = kDefaultBaseDirectory + filename + kExtension;

    // ファイルストリーム
    std::ifstream file;

    // ファイルを開く
    file.open(fullpath);
    // ファイルオープン失敗をチェック
    if (file.fall()) {
        assert(0);
    }

    // JSON文字列から解凍したデータ
    nlohmann::json deserialized;

    // 解凍
    file >> deserialized;

    // 正しいレベルデータファイルかチェック
    assert(deserialized.is_object());
    assert(deserialized.contains("name"));
    assert(deserialized["name"].is_string());

    // "name"を文字列として取得
    std::string name = deserialized["name"].get<std::string>();
    // 正しいレベルデータファイルかチェック
    assert(name.compare("scene") == 0);

    // レベルデータ格納用インスタンスを生成
    LevelData* levelData = new LevelData();

    // "objects"の全オブジェクトを走査
    for (nlohmann::json& object : deserialized["objects"]) {
        assert(object.contains("type"));

        // 種類を判別
        std::string type = object["type"].get<std::string>();

        // 種類ごとの処理

        // 再起関数

    }


}

void GameScene::Update() {

}

void GameScene::Draw() {

}