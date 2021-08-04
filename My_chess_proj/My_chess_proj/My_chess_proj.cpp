#include <iostream>
using namespace std;

int cur_white = 16, cur_black = 16;
/* 
*   start_pos_func() - нач. позиции
*   logic_mov_func() - перемещение любой фигуры
*       pesh_log_mov()
*       bash_log_mov()
*       horse_log_mov()
*       lad_log_mov()
*       king_log_mov()
*       queen_log_mov()
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
class chess {
public:
    unsigned short desk_NxN = 8, max_x = desk_NxN, max_y = desk_NxN, cur_x, cur_y;
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

void pesh_log_mov(chess mobj){}
void bash_log_mov(chess mobj){}
void horse_log_mov(chess mobj){}
void lad_log_mov(chess mobj){}
void king_log_mov(chess mobj){}
void queen_log_mov(chess mobj){}

void logic_mov_func(chess obj)
{
    // Фигура на текущей позиции
    int cur_figure = obj.total[obj.cur_y][obj.cur_x];
   
    // Проверка, какая фигура будет ходить?
    if (cur_figure == 0)
        printf("Здесь нету фигуры");
    else if (cur_figure == 1 || cur_figure == 8 || cur_figure == 25 || cur_figure == 32)
        bash_log_mov(obj);
    else if (cur_figure == 2 || cur_figure == 7 || cur_figure == 26 || cur_figure == 31)
        horse_log_mov(obj);
    else if (cur_figure == 3 || cur_figure == 6 || cur_figure == 27 || cur_figure == 30)
        lad_log_mov(obj);
    else if (cur_figure == 4 || cur_figure == 29)
        king_log_mov(obj);
    else if (cur_figure == 5 || cur_figure == 28)
        queen_log_mov(obj);
    else pesh_log_mov(obj);
}
chess change_cur_XY(chess obj)
{
    int f_cur_x, f_cur_y;
    cout << "Выбери ячейку, где находится фигура для передвижения\n";
    do
    { 
        cout << " y: ";
        cin >> f_cur_y;

        cout << "\n x: ";
        cin >> f_cur_x;
    }     
    while (f_cur_y > 7 || f_cur_y < 0 || f_cur_x > 7 || f_cur_x < 0);

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
void win_lose_logic(int win_com)
{
    if (win_com == 1)
        printf("White win!");
    else printf("Black win!");
    exit(0);
}

int main()
{
    chess desk_chess;
    
    // Расставление фигур по начальным позициям
    desk_chess = start_pos_func();
    printf("\nx=%d, y=%d\n", desk_chess.cur_x, desk_chess.cur_y);

    desk_chess = change_cur_XY(desk_chess);

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
            printf("%u ", desk_chess.total[i][j]);
        cout << endl;
    }
    printf("\nx=%d, y=%d", desk_chess.cur_x, desk_chess.cur_y);
}
