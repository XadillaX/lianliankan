//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, 艾克视图(X2Studio.Net)
///     All rights reserved.
///
/// @file Global.h
/// @brief 全局变量文件
///
/// 储存了一些全局变量
/// @version 1.0
/// @author 死月
/// @date 2010年10月5日
///
///
///     修订说明：最初版本
//////////////////////////////////////////////////////////////////////////
#include "GameWorld.h"

extern CGameWorld *g_GameWorld;             ///< 核心游戏类的实例

/**
 * 游戏逻辑函数
 * 逻辑函数，HGE引擎开始后将不停调用它\n
 * 这里的函数将调用CGameWorld类的全局变量g_GameWorld中的GameLogicFunc函数
 *
 * @see CGameWorld::GameLogicFunc
 * @return 若程序将关闭则返回true，否则返回false
 */
extern bool LogicFunc();

/**
 * 游戏渲染函数
 * 渲染函数，HGE引擎开始后将不停调用它\n
 * 这里的函数将调用CGameWorld类的全局变量g_GameWorld中的GameRenderFunc函数
 *
 * @see CGameWorld::GameRenderFunc
 * @return 若程序将关闭则返回true，否则返回false
 */
extern bool RenderFunc();

extern Coor GetElemTex[4];                  ///< 各方块图片中四个方块的顶点坐标
