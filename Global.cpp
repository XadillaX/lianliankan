#include "Global.h"
CGameWorld *g_GameWorld;
bool LogicFunc() { return g_GameWorld->GameLogicFunc(); }
bool RenderFunc() { return g_GameWorld->GameRenderFunc(); }

Coor GetElemTex[4] = { {0, 0}, {35, 0}, {0, 39}, {35, 39} };