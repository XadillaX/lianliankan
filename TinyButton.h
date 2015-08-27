//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, 艾克视图(X2Studio.Net)
///     All rights reserved.
///
/// @file TinyButton.h
/// @brief 普通GUI按钮类文件
///
/// 普通GUI按钮类的实现文件
/// @version 1.0
/// @author 死月
/// @date 2010年10月5日
///
///
///     修订说明：最初版本
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "hgegui.h"

/**
 * @brief 普通GUI按钮类
 *
 * 普通的按钮类，继承自HGE引擎的hgeGUIObject类
 */
class CTinyButton : public hgeGUIObject
{
private:
    HEFFECT m_ClickEffect;                                          ///< 按钮点击时的音效
    hgeSprite *m_BtnDown;                                           ///< 按钮按下时的图片精灵指针
    hgeSprite *m_BtnUp;                                             ///< 按钮没按下时的图片精灵指针
    hgeSprite *m_Now;                                               ///< 按钮当前图片精灵指针（指向按下图片精灵或者没按下图片精灵）
    float h;                                                        ///< 按钮高
    float w;                                                        ///< 按钮宽
    HGE *Engine;                                                    ///< HGE引擎指针，指向父对象的引擎

public:
      /**
     * @brief 构造函数
     * 根据传入参数创建一个GUI
     *
     * @param _id GUI的ID
     * @param *_Engine HGE引擎指针，指向父对象的Engine
     * @param *tex GUI的纹理，用于渲染该GUI
     * @param _x 该GUI在客户区域坐标的x轴数值
     * @param _y 该GUI在客户区域坐标的y轴数值
     * @param _w 该GUI的宽
     * @param _h 该GUI的高
     * @param ClickEffect 该GUI按下时的音效
     * @param debug 是否是“调位模式”，因为在鼠标没按下时GUI为透明，所以在“调位模式”中将该状态的GUI改为红色
     */
    CTinyButton(int _id, HGE *_Engine, HTEXTURE tex, float _x, float _y, float _w, float _h, HEFFECT ClickEffect, bool debug = false);
    ~CTinyButton(void);
    
      /**
     * @brief GUI左键状态函数（虚函数）
     * 方块GUI左键按下时所对应的动作
     *
     * @param bDown 鼠标左键的状态，若为按下则为true，否则为false
     * @return 如果控件已经编辑了它自身的状态，并且想要通知调用者， MouseLButton应返回true。否则它应返回false。
     */
    virtual bool MouseLButton(bool bDown);
    
      /**
     * @brief 渲染方块GUI（虚函数）
     * 进行对方块GUI的渲染
     */
    virtual void Render();
};
