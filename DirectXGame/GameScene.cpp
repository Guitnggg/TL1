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
}

void GameScene::Update() {

}

void GameScene::Draw() {

}