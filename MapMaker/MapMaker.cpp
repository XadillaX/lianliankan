#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdio>
using namespace std;

int num;
int cnt;
FILE *fp;

int map[10][18];

int main()
{
    cout << "Input the No. ";
    cin >> num;
    cout << "Input the count of elements: ";
    cin >> cnt;
    
    memset(map, 0, sizeof(map));
    
    char fn[256];
    sprintf(fn, "Map%d.txt", num);
    fp = fopen(fn, "w+");
    
    srand((unsigned)time(0));
    
    for(int i = 0; i < cnt; i++)
    {
        int id = rand() % 180;
        while(map[id / 18][id % 18]) id = rand() % 180;
        map[id / 18][id % 18] = 1;
    }
    
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 18; j++) fprintf(fp, "%d", map[i][j]);
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    
    return 0;
}

