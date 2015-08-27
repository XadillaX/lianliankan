#include "MapSearch.h"
#include "cstring"

CMapSearch::CMapSearch(int _Map[][MAP_WIDTH])
{
    //初始化
    memcpy(Map, _Map, sizeof(Map));
    dir[0].Set(0, -1);
    dir[1].Set(0, 1);
    dir[2].Set(-1, 0);
    dir[3].Set(1, 0);
}

CMapSearch::~CMapSearch(void)
{
    for(STLMap::iterator i = grap.begin(); i != grap.end(); i++) i->second.clear();
    grap.clear();
}

void CMapSearch::LoadMap(int _Map[][MAP_WIDTH])
{
    //载入地图
    memcpy(Map, _Map, sizeof(_Map));
}

bool CMapSearch::Search()
{
    bool bFlag = false;

    //建立STLMap
    CreateSTLMap();
    memset(dis, 0, sizeof(dis));

    //遍历Map
    for(STLMap::iterator i = grap.begin(); i != grap.end(); i++)
    {
        Lst tmpLst = i->second;

        //求出此种方块两两之间的距离
        while(!tmpLst.empty())
        {
            CoorType c = tmpLst.front();
            tmpLst.pop_front();
            if(tmpLst.empty()) break;

            for(Lst::iterator j = tmpLst.begin(); j != tmpLst.end(); j++)
            {
                //求c和j之间的路径
                dis[c.y][c.x][j->y][j->x] = dis[j->y][j->x][c.y][c.x] = DoSearch(c.y, c.x, j->y, j->x);
                if(dis[c.y][c.x][j->y][j->x].bExist)
                {
                    Hint = dis[c.y][c.x][j->y][j->x];
                    bFlag = true;
                }
            }
        }
    }

    return bFlag;
}

PointPath CMapSearch::GetPath(int y1, int x1, int y2, int x2)
{
    return dis[y1][x1][y2][x2];
}

PointPath CMapSearch::DoSearch(int y1, int x1, int y2, int x2)
{
    PointPath ans;
    CoorType a(y1, x1), b(y2, x2), c, d;

    //如果是直线
    if(a.x == b.x || a.y == b.y)
    {
        if(Abled(a, b, true, true))
        {
            ans.bExist = true;
            ans.Num = 2;
            ans.Points[0] = a, ans.Points[1] = b;
            return ans;
        }
    }

    //如果有一个转折点
    for(int i = 0; i < 2; i++)
    {
        if(i == 0) c.Set(a.y, b.x);
        else c.Set(b.y, a.x);

        //如果转折点合法
        if(Map[c.y][c.x] == -1)
            if(Abled(a, c, true) && Abled(c, b, false, true))
            {
                ans.bExist = true;
                ans.Num = 3;
                ans.Points[0] = a, ans.Points[1] = c, ans.Points[2] = b;
                return ans;
            }
    }

    //如果有两个转折点
    for(int i = 0; i < 4; i++)
    {
        //重置转折点1
        c.Set(y1, x1);
        c += dir[i];

        //如果此转折点合法
        while(c.isIll() && Map[c.y][c.x] == -1)
        {
            if(Abled(a, c, true))
            {
                //设置转折点2
                switch(i) {
                    case 0: 
                    case 1: d.Set(b.y, c.x); break;
                    case 2: 
                    case 3: d.Set(c.y, b.x); break;
                    default: break;
                }

                //如果转折点2合法
                if(Map[d.y][d.x] == -1)
                {
                    if(Abled(c, d) && Abled(d, b, false, true))
                    {
                        ans.bExist = true;
                        ans.Num = 4;
                        ans.Points[0] = a;
                        ans.Points[1] = c;
                        ans.Points[2] = d;
                        ans.Points[3] = b;
                        return ans;
                    }
                }
            }
            else break;

            c += dir[i];
        }
    }

    ans.bExist = false;
    return ans;
}

bool CMapSearch::Abled(CoorType a, CoorType b, bool head, bool tail)
{
    CoorType ca = a, cb = b;
    if(ca.x == cb.x)
    {
        if(tail)
        {
            if(ca.y < cb.y) b.y--;
            else b.y++;
        }
        if(head)
        {
            if(ca.y < cb.y) a.y++;
            else a.y--;
        }
        int sm = ((ca.y < cb.y) ? a.y : b.y), bg = ((ca.y > cb.y) ? a.y : b.y);
        for(int i = sm; i <= bg; i++)
        {
            if(Map[i][a.x] != -1) return false;
        }
    }
    else
    if(ca.y == cb.y)
    {
        if(tail)
        {
            if(ca.x < cb.x) b.x--;
            else b.x++;
        }
        if(head)
        {
            if(ca.x < cb.x) a.x++;
            else a.x--;
        }
        int sm = ((ca.x < cb.x) ? a.x : b.x), bg = ((ca.x > cb.x) ? a.x : b.x);
        for(int i = sm; i <= bg; i++)
        {
            if(Map[a.y][i] != -1) return false;
        }
    }

    return true;
}

void CMapSearch::CreateSTLMap()
{
    //一点点的清理工作
    for(STLMap::iterator i = grap.begin(); i != grap.end(); i++) i->second.clear();
    grap.clear();

    //将各元素推入到map的list当中
    for(int i = 0; i < MAP_HEIGHT; i++)
    {
        for(int j = 0; j < MAP_WIDTH; j++)
        {
            if(Map[i][j] != -1)
            {
                CoorType tmp(i, j);
                grap[Map[i][j]].push_front(tmp);
            }
        }
    }
}

void CMapSearch::GetRandomHint(int &a, int &b)
{
    a = ID_ELEM_GUI_START + (Hint.Points[0].y * MAP_WIDTH + Hint.Points[0].x);
    b = ID_ELEM_GUI_START + (Hint.Points[Hint.Num - 1].y * MAP_WIDTH + Hint.Points[Hint.Num - 1].x);
}
