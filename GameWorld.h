//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, 艾克视图(X2Studio.Net)
///     All rights reserved.
///
/// @file GameWorld.h
/// @brief 连连看游戏主类文件
///
/// 整个游戏的主要类，包括HGE引擎、渲染函数、逻辑函数等。
/// @version 1.0
/// @author 死月
/// @date 2010年10月5日
///
///
///     修订说明：最初版本
//////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef GAMEWORLD
#define GAMEWORLD

#include <hge.h>
#include <hgegui.h>
#include <hgefont.h>
#include "TinyButton.h"
#include "ElemButton.h"
#include <hgeanim.h>
#include "MapSearch.h"
#include "list"

#define IMAGE_ZIP               "Texture.X2Pak"            ///< 纹理资源包文件名
#define MUSIC_ZIP               "Music.X2Pak"              ///< 音乐资源包文件名
#define MAP_ZIP                 "Maps.X2Pak"               ///< 地图种子资源包文件名
#define IMAGE_ZIP_PASSWORD      "X2Studio"                 ///< 纹理资源包密码
#define MUSIC_ZIP_PASSWORD      "X2Studio"                 ///< 音乐资源包密码
#define MAP_ZIP_PASSWORD        "X2Studio"                 ///< 地图种子资源包密码
#define MAX_ELEM_TEXTURE        10                         ///< 方块资源文件数

#define ID_START_BTN            1                          ///< 开始按钮ID
#define ID_HINT_BTN             2                          ///< 提示按钮ID
#define ID_RESORT_BTN           3                          ///< 重列按钮ID

#define MAP_SEED_NUM            16                         ///< 地图种子数

#define MAP_HEIGHT              10                         ///< 地图高度
#define MAP_WIDTH               18                         ///< 地图宽度
#define MAX_TIME_BAR            330                        ///< 最大时间条

#define MAX_TIME                45.0f                      ///< 最长寻找时间
#define ID_ELEM_GUI_START       50                         ///< 方块GUI的起始ID

/**
 * @brief 客户端屏幕坐标类型
 *
 * 客户端屏幕坐标，x、y为浮点型
 */
struct Coor {
    float x;                                                ///< 客户区域的x轴坐标值
    float y;                                                ///< 客户区域的y轴坐标值
};

/**
 * @brief 地图种子类型
 *
 * Num为地图种子编号，地图种子为H * W的布尔矩阵，表示有无方块
 */
struct MapSeedType {
    int Num;                                               ///< 种子编号
    bool Seed[MAP_HEIGHT][MAP_WIDTH];                      ///< 地图种子矩阵
};

#ifndef MAPTYPE
#define MAPTYPE
/**
 * @brief 地图类型
 *
 * 这是游戏中的地图类型，nLeft为此地图剩下的方块数，Map是一个int数组，
 * 表示各行各列的元素id，若为空则为-1
 */
struct MapType {
    int nLeft;                                              ///< 地图剩下的方块
    int Map[MAP_HEIGHT][MAP_WIDTH];                         ///< 地图二维数组
};
#endif

/**
 * @brief 地图类型
 *
 * 这是游戏中的地图类型，nLeft为此地图剩下的方块数，Map是一个int数组，
 * 表示各行各列的元素id，若为空则为-1
 */
struct MapCoorType {
    int x;                                                  ///< x轴坐标
    int y;                                                  ///< y轴坐标
    /**
     * 转换函数
     * 将方块GUI的ID转换为地图坐标并赋值给结构体
     * @param id 方块GUI的ID
     * @note 以ID_ELEM_GUI_START为起始ID
     */     
    void ToCoor(int id)
    {
        id -= ID_ELEM_GUI_START;
        y = id / MAP_WIDTH;
        x = id % MAP_WIDTH;
    }
};

/**
 * @brief 动画精灵类型
 *
 * 动画精灵的结构体，包括精灵的存活时间、精灵已运行的时间和精灵的位置x、y
 */
struct BoomAni {
    float timer;                                            ///< 动画精灵的寿命
    float delay;                                            ///< 计时器
    hgeAnimation *ani;                                      ///< 动画纹理
    float x;                                                ///< 动画位置x坐标
    float y;                                                ///< 动画位置y坐标
    /**
     * 动画类型构造函数
     * @param a HGE引擎的动画精灵类
     */
    BoomAni(hgeAnimation a)
    {
        ani = new hgeAnimation(a);
        timer = 0;
        delay = 1.0f;
    }
};

const char szElemFileNamePrefix[]       = "Elem";           ///< 方块资源文件名前缀
const char szElemFileNameSuffix[]       = ".png";           ///< 方块资源文件名后缀
const char szMapSeedFileNamePrefix[]    = "Map";            ///< 方块资源文件名前缀
const char szMapSeedFileNameSuffix[]    = ".txt";           ///< 方块资源文件名后缀

bool LogicFunc();
bool RenderFunc();

class CMapSearch;
struct PointPath;

/**
 * @brief 游戏类
 *
 * 连连看游戏的核心类，包含主要的逻辑、渲染等函数及变量。
 */
class CGameWorld
{
private:
    hgeQuad Background;                                                                              ///< 背景四边形图元

    HTEXTURE m_CursorTexture;                                                                        ///< 鼠标纹理
    HTEXTURE StartBtnTexture;                                                                        ///< 开始按钮纹理
    HTEXTURE m_ElemTexture[MAX_ELEM_TEXTURE];                                                        ///< 方块纹理数组
    HTEXTURE m_ElemSelTexture;                                                                       ///< 方块选中效果纹理
    HTEXTURE m_BoomTexture;                                                                          ///< 爆炸动画纹理
    HTEXTURE m_ElecTexture[6];                                                                       ///< 闪电动画纹理数组
    HTEXTURE m_TimeBarTexture;                                                                       ///< 时间轴纹理
    HTEXTURE m_HintTexture;                                                                          ///< 提示道具纹理
    HTEXTURE m_ResortTexture;                                                                        ///< 重排道具纹理
    
    hgeGUI *gui;                                                                                     ///< 界面GUI变量        

    hgeSprite *m_pCursor;                                                                            ///< HGE鼠标精灵
    hgeSprite *m_pElement[MAX_ELEM_TEXTURE * 4];                                                     ///< HGE方块精灵数组
    hgeSprite *m_pElemSel;                                                                           ///< HGE选中效果精灵
    hgeSprite *m_pTimeBar;                                                                           ///< HGE时间轴精灵
    
    HEFFECT BGM;                                                                                     ///< 背景音乐
    HEFFECT StartSE;                                                                                 ///< 开始按钮SE
    HEFFECT ElemSelSE;                                                                               ///< 选中效果SE
    HEFFECT ElecSE;                                                                                  ///< 闪电SE
    HEFFECT EndSE;                                                                                   ///< 游戏结束SE
    HEFFECT ItemBoomSE;                                                                              ///< 方块爆炸SE
    HEFFECT LessTimeSE;                                                                              ///< 时间快到SE
    HEFFECT HintSE;                                                                                  ///< 提示道具SE
    HEFFECT ResortSE;                                                                                ///< 重拍道具SE
    
    MapSeedType m_MapSeed[MAP_SEED_NUM];                                                             ///< 地图种子
    
    int m_nLastGUIID;                                                                                ///< 最后按下的GUI的ID
    int m_nSeedID;                                                                                   ///< 当前地图的种子ID
    HCHANNEL BGMChannel;                                                                             ///< HGE的BGM频道
    MapType m_Map;                                                                                   ///< 地图
    hgeFont *fnt;                                                                                    ///< HGE字体
    
    hgeAnimation *m_BoomAni;                                                                         ///< 爆炸动画精灵
    hgeAnimation *m_ThunderAni[6];                                                                   ///< 闪电动画精灵
    CElemButton *m_pElemButtonArr[300];                                                              ///< 方块GUI数组
    CMapSearch *m_pMapSearch;                                                                        ///< 地图搜索类的实例
    float m_thisTime;                                                                                ///< 这一次的计时
    list<BoomAni> BA;                                                                                ///< 当前需要显示的动画链表
    
private:
    /**
     * @brief 闪电动画渲染
     * 对链表中的闪电动画进行渲染，过时的动画从链表中删除
     */
    void BoomLineRender();
    
public:
    HGE *Engine;                                                                                     ///< *核心 —— HGE引擎
    bool m_bGameStarted;                                                                             ///< 游戏是否开始
    bool m_bLose;                                                                                    ///< 游戏是否失败
    bool m_bWin;                                                                                     ///< 游戏是否胜利
    bool m_bTimeNotified;                                                                            ///< 是否已经提示时间过
    int m_nSelArr[2];                                                                                ///< 选中方块的ID(最多选中2个)
    
public:
    CGameWorld(void);
    ~CGameWorld(void);
    
    /**
     * @brief 初始化函数
     * 对类进行初始化，包括资源载入以及HGE引擎的初始化
     *
     * @see LoadResource
     */
    void Init();
    
    /**
     * @brief 资源载入函数
     * 将需要的资源载入到内存当中
     *
     * @return 若有至少一个资源载入失败则返回false，否则返回true
     */
    bool LoadResource();
    
    /**
     * @brief 四边形图元载入
     * 从文件载入一个四边形图元
     *
     * @param quad 将接受四边形图元的变量
     * @param filename 图片文件名
     * @return 若载入成功则返回true，否则返回false
     */
    bool QLoad(hgeQuad &quad, char *filename);
    
    /**
     * @brief 四边形图元纹理坐标设置
     * 设置一个图元的纹理坐标（这里设置一个矩形）
     *
     * @param quad 将接受设置四边形图元的变量
     * @param x1 左上角x坐标
     * @param y1 左上角y坐标
     * @param x2 右下角x坐标
     * @param y2 右下角y坐标
     */
    void QuadTexture(hgeQuad &quad, float x1, float y1, float x2, float y2);
    
    /**
     * @brief 四边形图元客户区域坐标设置
     * 设置一个图元的客户区域坐标（这里设置一个矩形）
     *
     * @param quad 将接受设置四边形图元的变量
     * @param x1 左上角x坐标
     * @param y1 左上角y坐标
     * @param x2 右下角x坐标
     * @param y2 右下角y坐标
     */
    void QuadScreen(hgeQuad &quad, float x1, float y1, float x2, float y2);
    
    /**
     * @brief 删除资源
     * 游戏退出之前释放资源\n
     * *这个函数没有很好地完成
     */  
    void DelResource();
    
    /**
     * @brief 游戏逻辑函数
     * 游戏的动作在此，比如按钮按下、方块按下、计时器等
     *
     * @see GameStart
     * @see Resort
     * @see CMapSearch::GetPath
     * @see PutAni
     * @see ToSearchMap
     * @return 若将要退出游戏程序则返回true，否则返回false
     */  
    bool GameLogicFunc();
    
      /**
     * @brief 游戏渲染函数
     * 进行游戏画面渲染
     *
     * @see BoomLineRender
     * @return 若将要退出游戏程序则返回true，否则返回false
     */  
    bool GameRenderFunc();
    
    /**
     * @brief 游戏开始函数
     * 开始游戏时的一些初始化设置
     *
     * @see GameReset
     * @see MakeMap
     * @see CreateElemGUI
     * @see ToSearchMap
     */  
    void GameStart();
    
    /**
     * @brief 游戏重置函数
     * 重置一些游戏数据
     *
     * @see ClearElemGUI
     */  
    void GameReset();
    
    /**
     * @brief 创建地图函数
     * 随机生成一个种子ID，并根据该种子随机生成地图
     *
     * @see ClearElemGUI
     */  
    void MakeMap();
    
    /**
     * @brief 创建方块GUI
     * 根据地图信息新建方块GUI
     *
     * @see CElemButton::CElemButton
     */  
    void CreateElemGUI();
    
    /**
     * @brief 删除方块GUI
     * 删除全部方块GUI
     */ 
    void ClearElemGUI();
    
    /**
     * @brief 开始搜索地图
     * 将地图参数传入CMapSearch类的实例，并让该实例进行搜索
     *
     * @see CMapSearch
     * @see CMapSearch::Search
     * @see Resort
     */ 
    void ToSearchMap();
    
    /**
     * @brief 放动画函数
     * 将需要显示的闪电动画（不同坐标）放入一条链表
     *
     * @param path 路线结构体，函数将在此路线上每一个地图坐标放上一个闪电动画精灵加入链表
     */ 
    void PutAni(PointPath path);
    
    /**
     * @brief 重排地图函数
     * 将地图根据当前状态重新排列（用于道具重列或者当前状态无解的情况）
     *
     * @see ClearElemGUI
     * @see CreateElemGUI
     * @see ToSearchMap
     */ 
    void Resort();
};

#endif
