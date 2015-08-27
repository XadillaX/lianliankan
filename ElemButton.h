//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, 艾克视图(X2Studio.Net)
///     All rights reserved.
///
/// @file ElemButton.h
/// @brief 方块GUI类文件
///
/// 方块GUI类的实现文件
/// @version 1.0
/// @author 死月
/// @date 2010年10月5日
///
///
///     修订说明：最初版本
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <hge.h>
#include <hgegui.h>
#include <hgeanim.h>

class CGameWorld;

#define PADDING_TOP             172                 ///< 游戏区域顶部距离
#define PADDING_LEFT            20                  ///< 游戏区域左部距离

#define MAP_HEIGHT              10                  ///< 地图高度
#define MAP_WIDTH               18                  ///< 地图宽度
#define ID_ELEM_GUI_START       50                  ///< 方块GUI的起始ID

#define ELEM_INTERFACE_HEIGHT   36                  ///< 方块表面的高度
#define ELEM_INTERFACE_WIDTH    32                  ///< 方块表面的宽度
#define ELEM_INTERFACE_OFFSET_X -4                  ///< 方块的x轴偏移量
#define ELEM_INTERFACE_OFFSET_Y 0                   ///< 方块的y轴偏移量

/**
 * @brief 方块GUI类
 *
 * 方块GUI类，继承自HGE引擎的hgeGUIObject类。
 * 游戏中的所有方块都是这个类的实例。
 */
class CElemButton : public hgeGUIObject
{
private:
    hgeSprite *m_pElem;                             ///< 方块GUI的画面精灵，内含方块纹理
    hgeSprite *m_pSel;                              ///< 方块GUI选中效果精灵
    CGameWorld *m_pGameWorld;                       ///< 游戏核心类指针，指向它的父对象
    float Screen_x;                                 ///< 该GUI在客户区域中的x坐标
    float Screen_y;                                 ///< 该GUI在客户区域中的y坐标
    int Map_x;                                      ///< 该GUI在地图中的x坐标
    int Map_y;                                      ///< 该GUI在地图中的y坐标
    int m_nRealID;                                  ///< 该GUI的实际ID（减去起始点 ID_ELEM_GUI_START）
    HEFFECT m_SelSE;                                ///< 选中该GUI时的音效
    hgeAnimation *m_pBoomAni;                       ///< 该GUI消去时的动画
    float timer;                                    ///< 该GUI的消去计时（时间到动画停止播放并且GUI消失）
    bool m_bLeaving;                                ///< GUI是否正在消失

public:
    bool m_bSelected;                               ///< GUI是否被选中
    
      /**
     * @brief 构造函数
     * 根据传入参数创建一个方块GUI
     *
     * @param _id 该方块的ID（起始ID为ID_ELEM_GUI_START）
     * @param *pGameWorld 游戏类指针，指向父对象
     * @param *pElem 该方块GUI所对应的图像精灵指针，用于创建该方块样式
     * @param *pSel 方块GUI选中效果所对应的图像精灵指针
     * @param snd 方块GUI的音效
     * @param *pBoomAni 方块GUI爆炸时所对应的动画精灵指针
     */
    CElemButton(int _id, CGameWorld *pGameWorld, hgeSprite *pElem, hgeSprite *pSel, HEFFECT snd, hgeAnimation *pBoomAni);
    ~CElemButton(void);
    
      /**
     * @brief 渲染方块GUI（虚函数）
     * 进行对方块GUI的渲染
     */
    virtual void Render();
    
      /**
     * @brief 方块GUI左键状态函数（虚函数）
     * 方块GUI左键按下时所对应的动作
     *
     * @param bDown 鼠标左键的状态，若为按下则为true，否则为false
     * @return 如果控件已经编辑了它自身的状态，并且想要通知调用者， MouseLButton应返回true。否则它应返回false。
     */
    virtual bool MouseLButton(bool bDown);
    
      /**
     * @brief 每次GUI更新时调用，用于更新控件动画。（虚函数）
     *
     * @param dt 自上一次调用Update方法至今的时间间隔，以秒为单位。 
     */
    virtual void Update(float dt);
    
      /**
     * @brief 设置该方块的状态为将要离去
     */
    void ToLeave();
};
