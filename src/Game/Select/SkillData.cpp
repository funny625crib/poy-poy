#include <System/Scene.h>
#include "SkillData.h"
#include <fstream>
#include <sstream>
#include <string>
namespace Select {

bool SkillData::Init()
{
    std::ifstream ifs("data/Game/Select/SkillData.csv");
    //ファイルが開かなかったらfalseを返す
    if(!ifs.is_open()) {
        return false;
    };
    // 1行ずつ読み込む
    std::string line;
    //getline関数でifsの中身を一文づつ読み込み
    while(std::getline(ifs, line)) {
        std::stringstream ss(line);    //ssに切り取った一文を入れる
        std::string       type;
        std::string       name;
        std::string       description;
        std::string       iconPath;
        std::string       colum;
        // カンマ区切りで分割
        while(std::getline(ss, colum, ',')) {
            // item に1つのデータが入る
            // ここで必要な処理を行う
            file_count_++;
            if(file_count_ == 1) {
                type = colum;
            }
            else if(file_count_ == 2) {
                name = colum;
            }
            else if(file_count_ == 3) {
                description = colum;
            }
            else if(file_count_ == 4) {
                iconPath = colum;
            }
            if(file_count_ >= 4) {
                file_count_ = 0;
            }
        }
    }
    ifs.close();
    return true;
}
void SkillData::Update()
{
}
}    // namespace Select
