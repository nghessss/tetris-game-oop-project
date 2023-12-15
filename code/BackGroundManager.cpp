#include "BackgroundManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <algorithm>
using namespace std;
namespace fs = filesystem;

vector<string> BackgroundManager::backgrounds;
BackgroundManager::BackgroundManager() {}

void BackgroundManager::InitBackground() {
    const string backgroundFolder = "image/background";
    srand(time(0));
    for (const auto& entry : fs::directory_iterator(backgroundFolder)) {
        string temp = entry.path().string();
        replace(temp.begin(), temp.end(), '\\', '/');
        backgrounds.push_back(temp);
    }
}

const char* BackgroundManager::GetCurrentBackground() {
    if (!backgrounds.empty()) {
        int randomIndex = rand() % backgrounds.size();
        return backgrounds[randomIndex].c_str();
    } else {
        return nullptr;
    }
}