#include "ElemButton.h"
#include "GameWorld.h"

CElemButton::CElemButton(int _id, CGameWorld *pGameWorld, hgeSprite *pElem, hgeSprite *pSel, HEFFECT snd, hgeAnimation *pBoomAni)
: m_bSelected(false)
, timer(0.0f)
, m_bLeaving(false)
{
    id = _id;
    m_pGameWorld = pGameWorld;

    m_pElem = new hgeSprite(*pElem);
    m_pSel = new hgeSprite(*pSel);
    m_pBoomAni = new hgeAnimation(*pBoomAni);
    m_SelSE = snd;

    //GUI的真实ID
    m_nRealID = id - ID_ELEM_GUI_START;

    //GUI在地图中的坐标
    Map_y = m_nRealID / MAP_WIDTH;
    Map_x = m_nRealID % MAP_WIDTH;

    //GUI在屏幕中的坐标
    Screen_x = PADDING_LEFT + ELEM_INTERFACE_WIDTH * Map_x + ELEM_INTERFACE_OFFSET_X;
    Screen_y = PADDING_TOP + ELEM_INTERFACE_HEIGHT * Map_y + ELEM_INTERFACE_OFFSET_Y;

    bStatic = false, bVisible = true, bEnabled = true;

    rect.Set(Screen_x, Screen_y, Screen_x + 35, Screen_y + 39);
}

void CElemButton::Render()
{
    if(!m_bLeaving && bVisible)     //如果是正常状态
    {
        //如果该方块已经失去了焦点，则选择状态设为false
        if(m_pGameWorld->m_nSelArr[0] != id && m_pGameWorld->m_nSelArr[1] != id)
            m_bSelected = false;

        //画方块
        m_pElem->Render(rect.x1, rect.y1);

        if(m_bSelected) m_pSel->Render(rect.x1 + 4, rect.y1);
    }
    else
    if(m_bLeaving && bVisible)      //如果是消去动画状态
    {
        float dt = m_pGameWorld->Engine->Timer_GetDelta();
        m_pBoomAni->Update(dt);
        m_pBoomAni->Render(rect.x1, rect.y1);
    }
}

void CElemButton::ToLeave()         //消去预处理
{
    timer = 0;
    m_bLeaving = true;
    m_pBoomAni->Play();
    bEnabled = false;
}

void CElemButton::Update(float dt)
{
    //若状态为消去动画，则开始倒计时，并且同时计算爆炸透明度
    if(m_bLeaving)
    {
        timer += dt;
        int alpha = 255 - (int)((timer / 1.5) * 255);
        m_pBoomAni->SetColor(ARGB(alpha, 0xff, 0xff, 0xff));

        if(timer > 1.5)
        {
            bVisible = false;
            m_bLeaving = false;
        }
    }
    else
    if(!m_pGameWorld->m_bGameStarted && m_pGameWorld->m_bLose)         //如果时间到
    {
        bEnabled = false;
        m_pElem->SetColor(0xff999999);
    }
}

bool CElemButton::MouseLButton(bool bDown)
{
    //如果左键按下
    if(bDown)
    {
        //播放音效
        m_pGameWorld->Engine->Effect_Play(m_SelSE);
        //设置为选中
        m_bSelected = true;

        //判断客户区域选中元素
        if(m_pGameWorld->m_nSelArr[0] == id || m_pGameWorld->m_nSelArr[1] == id){}
        else
        if(m_pGameWorld->m_nSelArr[0] == -1) m_pGameWorld->m_nSelArr[0] = id;
        else
        if(m_pGameWorld->m_nSelArr[1] == -1) m_pGameWorld->m_nSelArr[1] = id;
    }

    return bDown ? false : true;
}

CElemButton::~CElemButton(void)
{
    delete m_pElem;
    delete m_pSel;
}
