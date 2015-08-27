//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, 艾克视图(X2Studio.Net)
///     All rights reserved.
///
/// @file LinkMe.cpp
/// @brief 连连看游戏入口文件
///
/// 游戏入口文件
/// @version 1.0
/// @author 死月
/// @date 2010年10月5日
///
///
///     修订说明：最初版本
//////////////////////////////////////////////////////////////////////////
#include "GameWorld.h"
#include "Global.h"

/**
 * 程序入口函数WinMain
 * 该函数实例化一个CGameWorld类并进行初始化运行
 */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    g_GameWorld = new CGameWorld();
    g_GameWorld->Init();

    return 0;
}
