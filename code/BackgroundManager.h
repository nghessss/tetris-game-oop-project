#pragma once
#ifndef BACK_GROUND_H
#define BACK_GROUND_H

#include <iostream>
#include <vector>
using namespace std;

class BackgroundManager {
private:
    static vector<string> backgrounds;
public:
    BackgroundManager();
    static void InitBackground();
    static const char* GetCurrentBackground();
};

#endif