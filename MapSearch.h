//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, 艾克视图(X2Studio.Net)
///     All rights reserved.
///
/// @file MapSearch.h
/// @brief 地图搜索逻辑文件
///
/// 地图搜索时的主要逻辑类实现
/// @version 1.0
/// @author 死月
/// @date 2010年10月6日
///
///
///     修订说明：最初版本
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>
#include <list>
using namespace std;

#define MAP_HEIGHT              10                  ///< 地图高度
#define MAP_WIDTH               18                  ///< 地图宽度
#define ID_ELEM_GUI_START       50                  ///< 方块GUI的起始ID

/**
 * @brief 地图坐标结构体
 *
 * 地图坐标结构体，包含x轴值、y轴值
 * 以及一些操作函数。
 */
struct CoorType {
    int x;                                          ///< x轴
    int y;                                          ///< y轴
    
    /**
     * 重载构造函数
     * 将x、y值各初始化为-1
     */
    CoorType()
    {
        x = -1, y = -1;
    }

    /**
     * 构造函数重载
     * 将x、y各赋值为b、a
     * @param a 将要赋值的y轴数值
     * @param b 将要赋值的x轴数值
     */
    CoorType(int a, int b)
    {
        y = a, x = b;
    }
    
    /**
     * 设置坐标
     * 将x、y各赋值为b、a
     * @param a 将要赋值的y轴数值
     * @param b 将要赋值的x轴数值
     */
    void Set(int a, int b)
    {
        y = a, x = b;
    }

    /**
     * 运算符"+="重载
     * 将此坐标与另一坐标相加
     * @param &a 另一坐标
     * @return 返回结果坐标值
     */
    CoorType & operator += (const CoorType &a)
    {
        y += a.y, x += a.x;
        return *this;
    }

    /**
     * 重载运算符"!="
     * 判断与另一坐标是否表示同一个值
     * @param &a 另一坐标
     * @return 返回布尔类型表示是否相等
     */
    bool operator != (const CoorType &a)
    {
        if(y != a.y || x != a.x) return false;
        else return true;
    }

    /**
     * 判断此坐标是否合法
     * 若出界则不合法
     * @return 返回布尔类型表示是否合法
     */
    bool isIll()
    {
        if(y >= 0 && x >= 0 && y < MAP_HEIGHT && x < MAP_WIDTH) return true;
        else return false;
    }
};

typedef list<CoorType> Lst;                         ///< 将list<CoorType>重命名为Lst
typedef map<int, Lst> STLMap;                       ///< 将map<int, list<CoorType>>重命名为STLMap

/**
 * @brief 路线结构体
 *
 * 合法路线结构体
 * 储存最多四个点（起点终点和两个转折点）
 */
struct PointPath {
    bool bExist;                                    ///< 是否有路径
    int Num;                                        ///< 驻点个数
    CoorType Points[4];                             ///< 各驻点
};

/**
 * @brief 地图搜索类
 *
 * 根据指定地图搜索出各合法路径。
 */
class CMapSearch
{
private:
    int Map[MAP_HEIGHT][MAP_WIDTH];                                             ///< 地图数据矩阵
    PointPath dis[MAP_HEIGHT][MAP_WIDTH][MAP_HEIGHT][MAP_WIDTH];                ///< 路径数组
    STLMap grap;                                                                ///< STL映射
    CoorType dir[4];                                                            ///< 常量坐标增量
    PointPath Hint;                                                             ///< 提示时用的合法路径
    
    /**
     * @brief 两点寻径
     *
     * 对(x1, y1)和(x2, y2)进行寻径
     * @param x1 第一个坐标的x轴
     * @param y1 第一个坐标的y轴
     * @param x2 第二个坐标的x轴
     * @param y2 第二个坐标的y轴
     * @return 返回一个路线结构体的值，若不存在路径，则结构体的bExist为假
     * @see Abled
     */
    PointPath DoSearch(int y1, int x1, int y2, int x2);
    
public:
    /**
     * @brief 构造函数
     * 
     * @param _Map[][Map_Width] 地图矩阵
     */
    CMapSearch(int _Map[][MAP_WIDTH]);
    
    /**
     * @brief 析构函数
     */
    ~CMapSearch(void);
    
    /**
     * @brief 载入地图
     * 从矩阵中载入地图到对象
     * 
     * @param _Map[][Map_Width] 地图矩阵
     */
    void LoadMap(int _Map[][MAP_WIDTH]);
    
    /**
     * @brief 搜索地图
     * 对整个地图进行搜索每两个相同方块之间的路径
     * 
     * @return 如果存在至少一条路径则返回真，否则为假，用于是否重列
     * @see CreateSTLMap
     * @see DoSearch
     */
    bool Search();
    
    /**
     * @brief 创建map映射
     * 创建一个方块ID的映射，对每个ID创建一条的该ID的方块在地图中的各坐标的链表
     */
    void CreateSTLMap();
    
    /**
     * @brief 判断是否有障碍
     * 对于a、b两坐标（在同一直线）进行判断期间是否有方块障碍而导致不能连线
     *
     * @param a 坐标a（头坐标）
     * @param b 坐标b（尾坐标）
     * @param head 若包括头坐标则为true，否则为false
     * @param tail 若包括尾坐标则为true，否则为false
     * @return 若有障碍则返回false，否则为true
     */
    bool Abled(CoorType a, CoorType b, bool head = false, bool tail = false);
    
    /**
     * @brief 得到路径
     * 得到两个坐标的连线具体路径
     *
     * @param y1 第一个坐标的y轴
     * @param x1 第一个坐标的x轴
     * @param y2 第二个坐标的y轴
     * @param x2 第二个坐标的x轴
     * @return 返回一个路线结构体，表示该两个坐标直接的路线
     */
    PointPath GetPath(int y1, int x1, int y2, int x2);
    
    /**
     * @brief 得到提示路径
     * 得到一条提示的路径的相应两个方块
     *
     * @param &a 接受第一个方块ID的变量
     * @param &b 接受第二个方块ID的变量
     */
    void GetRandomHint(int &a, int &b);
};
