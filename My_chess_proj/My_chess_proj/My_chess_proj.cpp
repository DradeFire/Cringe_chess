#include <iostream>
#include <iomanip>
using namespace std;

void win_lose_logic(int k);

uint8_t cur_white = 16, cur_black = 16;
/* 
*   start_pos_func() - нач. позиции
*   logic_mov_func() - перемещение любой фигуры
*       pesh_log_mov()
*       bash_log_mov()
*       horse_log_mov()
*       lad_log_mov()
*       king_log_mov()
*       queen_log_mov()
*   menu() - интерактивное меню
*   win_lose_logic() - проверка конца игры

  short = 2 байта 
* byte = 1 байт
* 
* 64 * short = 128 байт
* 64 * uint8_t(byte) = 64 байт
* 
* uint8_t = [1 - 32] => 32 фигуры 
* 1 - 16 = "белые", 17 - 32 = "чёрные"
* 1Б-8Б|25Ч-32Ч - основная линия > 9Б-16Б|17Ч-24Ч - линия пешек
* 
* 1Б,8Б,25Ч,32Ч - башни
* 2Б,7Б,26Ч,31Ч - конь
* 3Б,6Б,27Ч,30Ч - ладья
* 4Б,29Ч - король
* 5Б,28Ч - ферзь
* 0 - свободно
*/
// Объект "шахматная доска" со всей информацией об текущей игре
class chess {
public:
    unsigned short cur_x, cur_y;
    uint8_t total[8][8];
    chess()
    {
        cur_x = 0;
        cur_y = 0;
    }
};

chess start_pos_func() //задаёт начальные положения фигур
{
    chess obj;
    size_t figure_num = 1;
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            obj.total[i][j] = figure_num++;
        }
    }
    for (size_t i = 2; i < 6; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            obj.total[i][j] = 0;
        }
    }
    for (size_t i = 6; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            obj.total[i][j] = figure_num++;
        }
    }

    return obj;
}
/*
void pesh_log_mov(chess mobj) //r1
{
    // 1 - проверка на ходящую сторону
    // 2 - проверка на допустимость хода
    // 3 - ход и модификация доски
    if (mobj.total[mobj.cur_y][mobj.cur_x] <= 16) //white
    {
        if (mobj.cur_y < 7  // можно сделать минимум 1 ход + впереди свободно
            && (mobj.total[mobj.cur_y + 1][mobj.cur_x] == 0 || mobj.total[mobj.cur_y + 1][mobj.cur_x - 1] != 0 || mobj.total[mobj.cur_y + 1][mobj.cur_x + 1] != 0)) // + может, вражеская фигура в зоне досигаемости        
        {   // ход (прямо)
            mobj.total[mobj.cur_y + 1][mobj.cur_x] = mobj.total[mobj.cur_y][mobj.cur_x];
            mobj.total[mobj.cur_y][mobj.cur_x] = 0;
        }
    }
    else if (mobj.total[mobj.cur_y][mobj.cur_x] >= 17) //black
    {
        if (mobj.cur_y > 0  // можно сделать минимум 1 ход + впереди свободно
            && (mobj.total[mobj.cur_y - 1][mobj.cur_x] == 0 || mobj.total[mobj.cur_y - 1][mobj.cur_x - 1] != 0 || mobj.total[mobj.cur_y - 1][mobj.cur_x + 1] != 0)) // + может, вражеская фигура в зоне досигаемости        
        {   // ход (прямо)
            mobj.total[mobj.cur_y - 1][mobj.cur_x] = mobj.total[mobj.cur_y][mobj.cur_x];
            mobj.total[mobj.cur_y][mobj.cur_x] = 0;
        }
    }
    
}
void bash_log_mov(chess mobj) //r1
{
    // 1 - проверка на ходящую сторону
    // 2 - проверка на допустимость хода
    // 3 - ход и модификация доски
    int x_mov,y_mov; //интерактивно задаётся
    if (mobj.total[mobj.cur_y][mobj.cur_x] < 9) //white
    {
        if (mobj.cur_y == 0) //y = 0?
        {
            if (mobj.cur_x == 0) // |_
            {
                if((y_mov == 0 && 0 <= x_mov < 8) || (x_mov == 0 && 0 <= y_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }   
            }
            else if (mobj.cur_x == 7) _|
            {
                if((y_mov == 0 && 0 <= x_mov < 8) || (x_mov == 7 && 0 <= y_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }
            }
            else //cur_x = [1..6] _
            {
                if(( 0 <= y_mov < 8 && mobj.cur_x == x_mov) || (y_mov == 0 && 0 <= x_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }
            }
        }
        else if(mobj.cur_y == 7) //y = 7?
        {
            if (mobj.cur_x == 0)
            {
                if((y_mov == 7 && 0 <= x_mov < 8) || (x_mov == 0 && 0 <= y_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }  
            }
            else if (mobj.cur_x == 7)
            {
                if((y_mov == 7 && 0 <= x_mov < 8) || (x_mov == 7 && 0 <= y_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }
            }
            else //cur_x = [1..6] 
            {
                if(( 0 <= y_mov < 8 && mobj.cur_x == x_mov) || (y_mov == 7 && 0 <= x_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }
            }
        }
        else // cur_y = [1..6]
        {
            if((y_mov == mobj.cur_y && 0 <= x_mov < 8) || (x_mov == mobj.cur_x && 0 <= y_mov < 8))
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }  
        }
    }
    else if (mobj.total[mobj.cur_y][mobj.cur_x] > 24) //black
    {
        if (mobj.cur_y == 0) //y = 0?
        {
            if (mobj.cur_x == 0) // |_
            {
                if((y_mov == 0 && 0 <= x_mov < 8) || (x_mov == 0 && 0 <= y_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }   
            }
            else if (mobj.cur_x == 7) _|
            {
                if((y_mov == 0 && 0 <= x_mov < 8) || (x_mov == 7 && 0 <= y_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }
            }
            else //cur_x = [1..6] _
            {
                if(( 0 <= y_mov < 8 && mobj.cur_x == x_mov) || (y_mov == 0 && 0 <= x_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }
            }
        }
        else if(mobj.cur_y == 7) //y = 7?
        {
            if (mobj.cur_x == 0)
            {
                if((y_mov == 7 && 0 <= x_mov < 8) || (x_mov == 0 && 0 <= y_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }  
            }
            else if (mobj.cur_x == 7)
            {
                if((y_mov == 7 && 0 <= x_mov < 8) || (x_mov == 7 && 0 <= y_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }
            }
            else //cur_x = [1..6] 
            {
                if(( 0 <= y_mov < 8 && mobj.cur_x == x_mov) || (y_mov == 7 && 0 <= x_mov < 8))
                {
                    mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                    mobj.total[mobj.cur_y][mobj.cur_x] = 0;
                }
            }
        }
        else // cur_y = [1..6]
        {
            if((y_mov == mobj.cur_y && 0 <= x_mov < 8) || (x_mov == mobj.cur_x && 0 <= y_mov < 8))
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }  
        }
    }
}
void horse_log_mov(chess mobj)
{
    int x_mov, y_mov;
    if (1)
    {
        if (mobj.cur_y == 0) //y = 0?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else if (mobj.cur_y == 7) //y = 7?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else // cur_y = [1..6]
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
    }
    else
    {
        if (mobj.cur_y == 0) //y = 0?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else if (mobj.cur_y == 7) //y = 7?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else // cur_y = [1..6]
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
    }
}
void lad_log_mov(chess mobj)
{
    int x_mov, y_mov;
    if (1)
    {
        if (mobj.cur_y == 0) //y = 0?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else if (mobj.cur_y == 7) //y = 7?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else // cur_y = [1..6]
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
    }
    else
    {
        if (mobj.cur_y == 0) //y = 0?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else if (mobj.cur_y == 7) //y = 7?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else // cur_y = [1..6]
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
    }
}
void king_log_mov(chess mobj){}
void queen_log_mov(chess mobj)
{
    int x_mov, y_mov;
    if (1)
    {
        if (mobj.cur_y == 0) //y = 0?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else if (mobj.cur_y == 7) //y = 7?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else // cur_y = [1..6]
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
    }
    else
    {
        if (mobj.cur_y == 0) //y = 0?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else if (mobj.cur_y == 7) //y = 7?
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
        else // cur_y = [1..6]
        {
            if (mobj.cur_x == 0)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else if (mobj.cur_x == 7)
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
            else //cur_x = [1..6] 
            {
                mobj.total[y_mov][x_mov] = mobj.total[mobj.cur_y][mobj.cur_x];
                mobj.total[mobj.cur_y][mobj.cur_x] = 0;
            }
        }
    }
}
*/
chess logic_mov_func(chess obj)
{
    // Фигура на текущей позиции
    int cur_figure = obj.total[obj.cur_y][obj.cur_x];
   /*
    // Проверка, какая фигура будет ходить?
    if (cur_figure == 0)
        {
            printf("Здесь нету фигуры");
            return obj;
        }
    else if (cur_figure == 1 || cur_figure == 8 || cur_figure == 25 || cur_figure == 32)
        return bash_log_mov(obj);
    else if (cur_figure == 2 || cur_figure == 7 || cur_figure == 26 || cur_figure == 31)
        return horse_log_mov(obj);
    else if (cur_figure == 3 || cur_figure == 6 || cur_figure == 27 || cur_figure == 30)
        return lad_log_mov(obj);
    else if (cur_figure == 4 || cur_figure == 29)
        return king_log_mov(obj);
    else if (cur_figure == 5 || cur_figure == 28)
        return queen_log_mov(obj);
    else return pesh_log_mov(obj);*/
    return obj;
}
chess change_cur_XY(chess obj)
{
    int f_cur_x = 0, f_cur_y = 0;
    cout << "Выбери ячейку, где находится фигура для передвижения\n";
    
    do
    {
        cout << " y: ";
        cin >> f_cur_y;

        cout << "\n x: ";
        cin >> f_cur_x;

    } while (f_cur_y > 7 || f_cur_y < 0 || f_cur_x > 7 || f_cur_x < 0);

    cout << endl;
    obj.cur_x = f_cur_x;
    obj.cur_y = f_cur_y;
    
    return obj;
}

int check_win_lose()
{
    if (cur_black == 0)
        return 1; //white win
    else if (cur_white == 0)
        return 2; //black win
    else return 0; //continue game
}

void game_active_menu()
{
    chess desk_chess;
    desk_chess = start_pos_func();

    int kek;
    while (1)
    {
        if (check_win_lose() != 0)
            win_lose_logic(check_win_lose());

        for (short i = 7; i >= 0; i--)
        {
            for (short j = 0; j < 8; j++)
            {
                printf("%2d ", desk_chess.total[i][j]);
            }
            cout << endl;
        }

        desk_chess = change_cur_XY(desk_chess);
        desk_chess = logic_mov_func(desk_chess);
    }
}
void win_lose_logic(int win_com)
{
    if (win_com == 1)
        printf("White win!");
    else printf("Black win!");
    exit(0);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    game_active_menu();
}
