#include "TinyButton.h"

CTinyButton::CTinyButton(int _id, HGE *_Engine, HTEXTURE tex, float _x, float _y, float _w, float _h, HEFFECT ClickEffect, bool debug)
{
    Engine = _Engine;
    id = _id;
    w = _w, h = _h;
    m_BtnDown = new hgeSprite(tex, 0, 0, w, h);
    m_BtnUp = new hgeSprite(*m_BtnDown);
    m_Now = m_BtnUp;
    m_ClickEffect = ClickEffect;

    //设置是否在调位置模式
    if(!debug) m_BtnUp->SetColor(0x00ff0000);
    else m_BtnUp->SetColor(0xffff0000);

    bStatic = false, bVisible = true, bEnabled = true;

    //设置按钮区域
    rect.Set(_x, _y, _x + w, _y + h);
}

CTinyButton::~CTinyButton(void)
{
    Engine->Effect_Free(m_ClickEffect);
    delete m_BtnDown;
    delete m_BtnUp;
}

bool CTinyButton::MouseLButton(bool bDown)
{
    if(bDown)
    {
        Engine->Effect_Play(m_ClickEffect);
        m_Now = m_BtnDown;
    }
    else m_Now = m_BtnUp;

    return (bDown) ? false : true;
}

void CTinyButton::Render()
{
    m_Now->Render(rect.x1, rect.y1);
}
