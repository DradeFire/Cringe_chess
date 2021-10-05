#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector"
#include "string"
#include "functional"

#include <iostream>

std::vector<QPushButton*> qp (64);
QPushButton* endB;
bool isClicked = false;
int x_1, y_1, x_2, y_2,
    hod = 1; // 1 - white; 0 - black
Doska MyDoska;

Figura::Figura(){     //Конструктор по умолчанию, используется для заполнения остатка клеток доски
    VidFigura = 0;
    Color = 2;
}
Figura::Figura(int v, int c) {     //Конструктор, который создает фигуры
    VidFigura = v;
    Color = c;

}

void Doska::GameOVER(int colorWin){ // 0 - black, 1 - white
    endB->setGeometry(0, 0, 741, 741);
    if(colorWin == 0){
        endB->setText(QString("Black win!!!"));
    }
    else{
        endB->setText(QString("White win!!!"));
    }
}

void Doska::Zamena(int x, int y, int x2, int y2) {                 //Эта функция заменяет фигуру(кроме пешки)
    if (matrix[x2][y2].Color != matrix[x][y].Color) {
        int col = matrix[x][y].Color;
        if((col == 1 && hod == 1) || (col == 0 && hod == 0)){
            if (matrix[x2][y2].VidFigura == 4) {     //Если был кароль, то конечная
                GameOVER(col);
            }

            int curWidth = qp.at((x * 8) + y)->iconSize().width() , curHeight = qp.at((x * 8) + y)->iconSize().height();
            QIcon qIcon = qp.at((x * 8) + y)->icon();

            qp.at((x2 * 8) + y2)->setIcon(QIcon(""));
            qp.at((x2 * 8) + y2)->setIconSize(QSize(curWidth,curHeight));
            qp.at((x2 * 8) + y2)->setIcon(qIcon);


            matrix[x2][y2] = matrix[x][y]; //В новую клетку закидываем фигуру из старой, в старую забиваем фигуру по умолчанию
            matrix[x][y] = Figura();
            qp.at((x * 8) + y)->setIcon(QIcon(""));

            if(col == 0)
                hod = 1;
            else
                hod = 0;
        }
    }

    isClicked = false;
    qp.at((x * 8) + y)->setDefault(false);

}

void Doska::MoveLadya(int x, int y, int x2, int y2) {          //Функция хода ладьи
    if (x == x2 || y == y2) {     //Если Не равна вертикаль и горизонталь, то ладья так не ходит, аривидерчи
        if (x == x2) {     //Если статична вертикаль
            if (y - y2 > 0) {     //То смотрим в какую сторону ходит ладья
                int j = 0;     //Переменная счетчик
                for (int i = 1; i < y - y2; i++) {     //Цикл, который пробегает клетки, которые должна пройти фигура
                    if (matrix[x][y - i].VidFigura != 0) {     //Если встречается фигура
                        j++;     //Увиличиваем
                    }
                }
                if (j == 0) {     //Если мы не встретили фигуру, то счетчик будет равен 0, значит ход возможен
                    Zamena(x, y, x2, y2);

                }
                else {
                    isClicked = false;
                    qp.at((x * 8) + y)->setDefault(false);
                }

            }
            else {     //Та же операция, только если ладья ходит в другую сторону
                int j = 0;
                for (int i = 1; i < y2 - y; i++) {
                    if (matrix[x][y + i].VidFigura != 0) {
                        j++;
                    }
                }
                if (j == 0) {
                    Zamena(x, y, x2, y2);
                }
                else {
                    isClicked = false;
                    qp.at((x * 8) + y)->setDefault(false);
                }
            }
        }
        else {     //Все то же самое, только если статичная не вертикаль, а горизонталь

            if (x - x2 > 0) {
                int j = 0;
                for (int i = 1; i < x - x2; i++) {
                    if (matrix[x - i][y].VidFigura != 0) {
                        j++;
                    }
                }
                if (j == 0) {
                    Zamena(x, y, x2, y2);
                }
                else {
                    isClicked = false;
                    qp.at((x * 8) + y)->setDefault(false);
                }

            }
            else {
                int j = 0;
                for (int i = 1; i < x2 - x; i++) {
                    if (matrix[x + i][y].VidFigura != 0) {
                        j++;
                    }
                }
                if (j == 0) {
                    Zamena(x, y, x2, y2);
                }
                else {
                    isClicked = false;
                    qp.at((x * 8) + y)->setDefault(false);
                }
            }

        }

    }
    else {
        isClicked = false;
        qp.at((x * 8) + y)->setDefault(false);
    }
}

void Doska::MoveSlon(int x, int y, int x2, int y2) {           //Функция хода слона
    if (abs(x2 - x) == abs(y2 - y)) {   //Если разность х и у по модулю не одинакова, то слон так не ходит
        if (x - x2 > 0) {     //Узнаем в какую сторону ходит слон
            if (y - y2 > 0) {
                int j = 0;     //Та же схема, что и с ладьей
                for (int i = 1; i < y - y2; i++) {

                    if (matrix[x - i][y - i].VidFigura != 0) {
                        j++;
                    }
                }
                if (j == 0) {
                    Zamena(x, y, x2, y2);
                }
                else {
                    isClicked = false;
                    qp.at((x * 8) + y)->setDefault(false);
                }
            }
            else {     //Если слон идет в другую сторону
                int j = 0;
                for (int i = 1; i < y2 - y; i++) {

                    if (matrix[x - i][y + i].VidFigura != 0) {
                        j++;
                    }
                }
                if (j == 0) {
                    Zamena(x, y, x2, y2);
                }
                else {
                    isClicked = false;
                    qp.at((x * 8) + y)->setDefault(false);
                }
            }
        }
        else {     //Опять же если в другую, все то же самое
            if (y - y2 > 0) {
                int j = 0;
                for (int i = 1; i < y - y2; i++) {

                    if (matrix[x + i][y - i].VidFigura != 0) {
                        j++;
                    }
                }
                if (j == 0) {
                    Zamena(x, y, x2, y2);
                }
                else {
                    isClicked = false;
                    qp.at((x * 8) + y)->setDefault(false);
                }
            }
            else {
                int j = 0;
                for (int i = 1; i < y2 - y; i++) {

                    if (matrix[x + i][y + i].VidFigura != 0) {
                        j++;
                    }
                }
                if (j == 0) {
                    Zamena(x, y, x2, y2);
                }
                else {
                    isClicked = false;
                    qp.at((x * 8) + y)->setDefault(false);
                }
            }
        }

    }
    else
    {
        isClicked = false;
        qp.at((x * 8) + y)->setDefault(false);
    }
}

void Doska::MovePeshka(int x, int y, int x2, int y2, bool z) {             //Функция хода пешки, если bool z=тру, тогда пешка бьет фигуру, а если фолс, тогда просто ходит
    int curWidth = qp.at((x * 8) + y)->iconSize().width() , curHeight = qp.at((x * 8) + y)->iconSize().height();
    QIcon qIcon = qp.at((x * 8) + y)->icon();
    int col = matrix[x][y].Color;
    if((col == 1 && hod == 1) || (col == 0 && hod == 0)) {
        if (z) {
            if (matrix[x2][y2].VidFigura == 4)  {   //Если был кароль, то конечная
                GameOVER(col);
            }
        }
        qp.at((x2 * 8) + y2)->setIcon(QIcon(""));
        qp.at((x2 * 8) + y2)->setIconSize(QSize(curWidth,curHeight));
        qp.at((x2 * 8) + y2)->setIcon(qIcon);

        matrix[x2][y2] = matrix[x][y]; //В новую клетку закидываем фигуру из старой, в старую забиваем фигуру по умолчанию
        matrix[x][y] = Figura();
        qp.at((x * 8) + y)->setIcon(QIcon(""));

        if(col == 0)
            hod = 1;
        else
            hod = 0;

        if(col == 0 && x2 == 7){
            matrix[x2][y2].VidFigura = 5;
            qp.at((x2 * 8) + y2)->setIconSize(QSize(91, 91));
            qp.at((x2 * 8) + y2)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\queen_black.bmp"));
        }
        else if(col == 1 && x2 == 0){
            matrix[x2][y2].VidFigura = 5;
            qp.at((x2 * 8) + y2)->setIconSize(QSize(91, 91));
            qp.at((x2 * 8) + y2)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\queen_white.bmp"));
        }
    }

            isClicked = false;

            qp.at(x * 8 + y)->setDefault(false);

}

void Doska::Move(int x, int y, int x2, int y2){     //Функция хода (х и у - старая клетка, х2 и у2 - клетка новая)
    if (x < 0 || y < 0 || x2 < 0 || y2 < 0 || x > 7 || y > 7 || x2 > 7 || y2 > 7) {     //проверка на выход за пределы доски
        isClicked = false;
        qp.at((x * 8) + y)->setDefault(false);
    }
    else {
        if (matrix[x][y].VidFigura == 1) {      //Ладья
            MoveLadya(x, y, x2, y2);
        }
        if (matrix[x][y].VidFigura == 2) { //Конь
            if (
                (x2 == (x - 2) && (y2 == y + 1 || y2 == y - 1))||     //Если выбранная клетка не соответствует той куда может ходить конь, аривидерчи
                (x2 == (x - 1) && (y2 == y + 2 || y2 == y - 2))||
                (x2 == (x + 1) && (y2 == y + 2 || y2 == y - 2))||
                (x2 == (x + 2) && (y2 == y + 1 || y2 == y - 1))
                ) {
                Zamena(x, y, x2, y2);

            }
            else {
                isClicked = false;
                qp.at((x * 8) + y)->setDefault(false);
            }
        }
        if (matrix[x][y].VidFigura == 3)   //Слон
        {
            MoveSlon(x, y, x2, y2);
        }
        if (matrix[x][y].VidFigura == 4) {   //Король
            if (
                ((abs(x2 - x) == 1)&&(abs(y2 - y)==1))||   //Если по диагоналям, и по прямым разность не равна 1
                ((y==y2)&&(abs(x2 - x) == 1))||
                ((x==x2)&& (abs(y2 - y) == 1))
                ) {
                Zamena(x, y, x2, y2);
            }
            else {
                isClicked = false;
                qp.at((x * 8) + y)->setDefault(false);
            }
        }
        if (matrix[x][y].VidFigura == 5) {   //Ферзь
            if (
                (x==x2||y==y2)||   //Если ходит иначе, чем слон или ладья, то ошибка
                (abs(x2 - x) == abs(y2 - y))
                ) {
                if (x == x2 || y == y2) {     //Если одна из линий не меняется, то ходит, как ладья, а значит все то же самое
                    MoveLadya(x, y, x2, y2);
                }
                else {     //Если же не как ладья, то как слон, копируем код от туда...
                    MoveSlon(x, y, x2, y2);
                }
            }
            else {
                isClicked = false;
                qp.at((x * 8) + y)->setDefault(false);
            }
        }
        if (matrix[x][y].VidFigura == 6) {   //Пешка
            if (matrix[x][y].Color==1) {   //Проверка на цвет (белый)
                if (x == 6) {   //Проверка на начальную клетку
                    if ((x2 == (x - 1)) || (x2 == (x - 2))) {   //Если на начальной клетке, то может ходить на две клетки
                        if (x2 == (x - 2)) {     //Если на две, то проверяем две клетки
                            if (matrix[x2][y].Color == 2 && y2 == y) {
                                MovePeshka(x, y, x2, y2, false);
                            }
                            else
                            {
                                isClicked = false;
                                qp.at((x * 8) + y)->setDefault(false);
                            }
                        }
                        else {
                            if (matrix[x2][y].Color == 2 && y2 == y) {     //на одну, то проверяем одну
                                MovePeshka(x, y, x2, y2, false);
                            }
                            else
                            {
                                isClicked = false;
                                qp.at((x * 8) + y)->setDefault(false);
                            }
                            if ((y < 7 && matrix[x2][y + 1].Color == 0 && y2 == (y + 1))
                                 || (y > 0 && matrix[x2][y - 1].Color == 0 && y2 == (y - 1))) {    //Пешка так же может кушать, если рядом есть фигуры
                                MovePeshka(x, y, x2, y2, true);
                            }
                        }

                    }
                    else
                    {
                        isClicked = false;
                        qp.at((x * 8) + y)->setDefault(false);
                    }
                }
                else   //Если позиция не начальная, то на одну
                {
                    if (x > 0 && x2 == (x - 1) && y2 == y) {     //Проверка клетки
                        if (matrix[x - 1][y].Color == 2) {
                            MovePeshka(x, y, x2, y2, false);
                        }
                        else
                        {
                            isClicked = false;
                            qp.at((x * 8) + y)->setDefault(false);
                        }
                    }
                    else
                    {
                        isClicked = false;
                        qp.at((x * 8) + y)->setDefault(false);
                    }
                    if (( x > 0 && y < 7 && matrix[x - 1][y + 1].Color == 0 && y2 == (y + 1)) ||
                            (x > 0 && y > 0 && matrix[x - 1][y - 1].Color == 0 && y2 == (y - 1))) {
                        MovePeshka(x, y, x2, y2, true);

                    }
                }
            }
            else { //(чёрные)
                if (x == 1) {   //то же самое для черных
                    if ((x2 == (x + 1)) || (x2 == (x + 2))) {
                        if (x2 == (x + 2)) {     //Если нa две
                            if (matrix[x2][y].Color == 2 && y2 == y) {
                                MovePeshka(x, y, x2, y2, false);
                            }
                            else
                            {
                                isClicked = false;
                                qp.at((x * 8) + y)->setDefault(false);
                            }
                        }
                        else {      // Если нa одну
                            if (matrix[x2][y].Color == 2 && y2 == y) {
                                MovePeshka(x, y, x2, y2, false);
                            }
                            else
                            {
                                isClicked = false;
                                qp.at((x * 8) + y)->setDefault(false);
                            }
                        }
                        if ((x < 7 && y < 7 && matrix[x + 1][y + 1].Color == 1 && y2 == (y + 1)) ||
                                (x < 7 && y > 0 && matrix[x + 1][y - 1].Color == 1 && y2 == (y - 1))) {
                            MovePeshka(x, y, x2, y2, true);

                        }
                    }
                    else
                    {
                        isClicked = false;
                        qp.at((x * 8) + y)->setDefault(false);
                    }
                }
                else
                {
                    if (x < 7 && x2 == (x + 1) && matrix[x + 1][y].Color == 2 && y2 == y) {     //Если на одну
                        MovePeshka(x, y, x2, y2, false);
                    }
                    else
                    {
                        isClicked = false;
                        qp.at((x * 8) + y)->setDefault(false);
                    }
                    if ((x < 7 && y < 7 && matrix[x + 1][y + 1].Color == 1 && y2 == (y + 1)) ||
                            (x < 7 && y > 0 && matrix[x + 1][y - 1].Color == 1 && y2 == (y - 1))) {
                        MovePeshka(x, y, x2, y2, true);
                    }
                }
            }

        }
        else{
            isClicked = false;
            qp.at((x * 8) + y)->setDefault(false);
        }
    }

}

void Doska::Cleaner(){     //Функция расстановки фигур
    matrix[0][0] = Figura(1, 0);      //Заполнение черных фигур
    qp.at(0)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\lad_black.bmp"));
    matrix[0][7] = Figura(1, 0);
    qp.at(7)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\lad_black.bmp"));

    matrix[0][1] = Figura(2, 0);
    qp.at(1)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\hourse_black.bmp"));
    matrix[0][6] = Figura(2, 0);
    qp.at(6)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\hourse_black.bmp"));

    matrix[0][2] = Figura(3, 0);
    qp.at(2)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\slon_black.bmp"));
    matrix[0][5] = Figura(3, 0);
    qp.at(5)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\slon_black.bmp"));

    matrix[0][3] = Figura(5, 0);
    qp.at(3)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\queen_black.bmp"));
    matrix[0][4] = Figura(4, 0);
    qp.at(4)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\king_black.bmp"));

    for (int i = 0; i < 8;i++) {
        matrix[1][i] = Figura(6, 0);
        qp.at(8 + i)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\peshka_black.bmp"));
    }
    matrix[7][0] = Figura(1, 1);     //Белых
    matrix[7][7] = Figura(1, 1);
    qp.at(56)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\lad_white.bmp"));
    qp.at(63)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\lad_white.bmp"));

    matrix[7][1] = Figura(2, 1);
    matrix[7][6] = Figura(2, 1);
    qp.at(57)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\hourse_white.bmp"));
    qp.at(62)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\hourse_white.bmp"));

    matrix[7][2] = Figura(3, 1);
    matrix[7][5] = Figura(3, 1);
    qp.at(58)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\slon_white.bmp"));
    qp.at(61)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\slon_white.bmp"));

    matrix[7][3] = Figura(4, 1);
    qp.at(59)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\king_white.bmp"));

    matrix[7][4] = Figura(5, 1);
    qp.at(60)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\queen_white.bmp"));

    for (int i = 0; i < 8; i++) {
        matrix[6][i] = Figura(6, 1);
        qp.at(48 + i)->setIcon(QIcon("P:\\VS_studing_projects\\My_WINDOW_chess\\chess_figures\\peshka_white.bmp"));
    }
    for (int i = 2; i < 6; i++) {     //Пустые
        for (int j = 0; j < 8; j++) {
            matrix[i][j] = Figura();
        }
    }
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qp = {ui->p1,
          ui->p2,
          ui->p3,
          ui->p4,
          ui->p5,
          ui->p6,
                                    ui->p7,
                                    ui->p8,
                                    ui->p9,
                                    ui->p10,
                                    ui->p11,
                                    ui->p12,
                                    ui->p13,
                                    ui->p14,
                                    ui->p15,
                                    ui->p16,
                                    ui->p17,
                                    ui->p18,
                                    ui->p19,
                                    ui->p20,
                                    ui->p21,
                                    ui->p22,
                                    ui->p23,
                                    ui->p24,
                                    ui->p25,
                                    ui->p26,
                                    ui->p27,
                                    ui->p28,
                                    ui->p29,
                                    ui->p30,
                                    ui->p31,
                                    ui->p32,
                                    ui->p33,
                                    ui->p34,
                                    ui->p35,
                                    ui->p36,
                                    ui->p37,
                                    ui->p38,
                                    ui->p39,
                                    ui->p40,
                                    ui->p41,
                                    ui->p42,
                                    ui->p43,
                                    ui->p44,
                                    ui->p45,
                                    ui->p46,
                                    ui->p47,
                                    ui->p48,
                                    ui->p49,
                                    ui->p50,
                                    ui->p51,
                                    ui->p52,
                                    ui->p53,
                                    ui->p54,
                                    ui->p55,
                                    ui->p56,
                                    ui->p57,
                                    ui->p58,
                                    ui->p59,
                                    ui->p60,
                                    ui->p61,
                                    ui->p62,
                                    ui->p63,ui->p64};

    endB = ui->endButton;
    endB->setGeometry(0, 0, 0, 0);

    MyDoska.Cleaner();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_p1_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(0)->setDefault(true);
        x_1 = 0;
        y_1 = 0;
    }
    else{
         x_2 = 0;
         y_2 = 0;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p2_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(1)->setDefault(true);
        x_1 = 0;
        y_1 = 1;
    }
    else{
         x_2 = 0;
         y_2 = 1;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p3_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(2)->setDefault(true);
        x_1 = 0;
        y_1 = 2;
    }
    else{
         x_2 = 0;
         y_2 = 2;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p4_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(3)->setDefault(true);
        x_1 = 0;
        y_1 = 3;
    }
    else{
         x_2 = 0;
         y_2 = 3;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p5_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(4)->setDefault(true);
        x_1 = 0;
        y_1 = 4;
    }
    else{
         x_2 = 0;
         y_2 = 4;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p6_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(5)->setDefault(true);
        x_1 = 0;
        y_1 = 5;
    }
    else{
         x_2 = 0;
         y_2 = 5;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p7_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(6)->setDefault(true);
        x_1 = 0;
        y_1 = 6;
    }
    else{
         x_2 = 0;
         y_2 = 6;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p8_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(7)->setDefault(true);
        x_1 = 0;
        y_1 = 7;
    }
    else{
         x_2 = 0;
         y_2 = 7;
         MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p9_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(8)->setDefault(true);
        x_1 = 1;
        y_1 = 0;
    }
    else{
         x_2 = 1;
         y_2 = 0;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p10_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(9)->setDefault(true);
        x_1 = 1;
        y_1 = 1;
    }
    else{
         x_2 = 1;
         y_2 = 1;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p11_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(10)->setDefault(true);
        x_1 = 1;
        y_1 = 2;
    }
    else{
         x_2 = 1;
         y_2 = 2;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p12_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(11)->setDefault(true);
        x_1 = 1;
        y_1 = 3;
    }
    else{
         x_2 = 1;
         y_2 = 3;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p13_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(12)->setDefault(true);
        x_1 = 1;
        y_1 = 4;
    }
    else{
         x_2 = 1;
         y_2 = 4;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p14_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(13)->setDefault(true);
        x_1 = 1;
        y_1 = 5;
    }
    else{
         x_2 = 1;
         y_2 = 5;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p15_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(14)->setDefault(true);
        x_1 = 1;
        y_1 = 6;
    }
    else{
         x_2 = 1;
         y_2 = 6;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p16_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(15)->setDefault(true);
        x_1 = 1;
        y_1 = 7;
    }
    else{
         x_2 = 1;
         y_2 = 7;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p17_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(16)->setDefault(true);
        x_1 = 2;
        y_1 = 0;
    }
    else{
         x_2 = 2;
         y_2 = 0;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p18_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(17)->setDefault(true);
        x_1 = 2;
        y_1 = 1;
    }
    else{
         x_2 = 2;
         y_2 = 1;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p19_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(18)->setDefault(true);
        x_1 = 2;
        y_1 = 2;
    }
    else{
         x_2 = 2;
         y_2 = 2;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p20_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(19)->setDefault(true);
        x_1 = 2;
        y_1 = 3;
    }
    else{
         x_2 = 2;
         y_2 = 3;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p21_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(20)->setDefault(true);
        x_1 = 2;
        y_1 = 4;
    }
    else{
         x_2 = 2;
         y_2 = 4;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p22_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(21)->setDefault(true);
        x_1 = 2;
        y_1 = 5;
    }
    else{
         x_2 = 2;
         y_2 = 5;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p23_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(22)->setDefault(true);
        x_1 = 2;
        y_1 = 6;
    }
    else{
         x_2 = 2;
         y_2 = 6;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p24_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(23)->setDefault(true);
        x_1 = 2;
        y_1 = 7;
    }
    else{
         x_2 = 2;
         y_2 = 7;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p25_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(24)->setDefault(true);
        x_1 = 3;
        y_1 = 0;
    }
    else{
         x_2 = 3;
         y_2 = 0;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p26_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(25)->setDefault(true);
        x_1 = 3;
        y_1 = 1;
    }
    else{
         x_2 = 3;
         y_2 = 1;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p27_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(26)->setDefault(true);
        x_1 = 3;
        y_1 = 2;
    }
    else{
         x_2 = 3;
         y_2 = 2;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p28_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(27)->setDefault(true);
        x_1 = 3;
        y_1 = 3;
    }
    else{
         x_2 = 3;
         y_2 = 3;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p29_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(28)->setDefault(true);
        x_1 = 3;
        y_1 = 4;
    }
    else{
         x_2 = 3;
         y_2 = 4;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p30_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(29)->setDefault(true);
        x_1 = 3;
        y_1 = 5;
    }
    else{
         x_2 = 3;
         y_2 = 5;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p31_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(30)->setDefault(true);
        x_1 = 3;
        y_1 = 6;
    }
    else{
         x_2 = 3;
         y_2 = 6;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p32_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(31)->setDefault(true);
        x_1 = 3;
        y_1 = 7;
    }
    else{
         x_2 = 3;
         y_2 = 7;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p33_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(32)->setDefault(true);
        x_1 = 4;
        y_1 = 0;
    }
    else{
         x_2 = 4;
         y_2 = 0;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p34_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(33)->setDefault(true);
        x_1 = 4;
        y_1 = 1;
    }
    else{
         x_2 = 4;
         y_2 = 1;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p35_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(34)->setDefault(true);
        x_1 = 4;
        y_1 = 2;
    }
    else{
         x_2 = 4;
         y_2 = 2;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p36_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(35)->setDefault(true);
        x_1 = 4;
        y_1 = 3;
    }
    else{
         x_2 = 4;
         y_2 = 3;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p37_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(36)->setDefault(true);
        x_1 = 4;
        y_1 = 4;
    }
    else{
         x_2 = 4;
         y_2 = 4;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p38_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(37)->setDefault(true);
        x_1 = 4;
        y_1 = 5;
    }
    else{
         x_2 = 4;
         y_2 = 5;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p39_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(38)->setDefault(true);
        x_1 = 4;
        y_1 = 6;
    }
    else{
         x_2 = 4;
         y_2 = 6;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p40_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(39)->setDefault(true);
        x_1 = 4;
        y_1 = 7;
    }
    else{
         x_2 = 4;
         y_2 = 7;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p41_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(40)->setDefault(true);
        x_1 = 5;
        y_1 = 0;
    }
    else{
         x_2 = 5;
         y_2 = 0;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p42_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(41)->setDefault(true);
        x_1 = 5;
        y_1 = 1;
    }
    else{
         x_2 = 5;
         y_2 = 1;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p43_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(42)->setDefault(true);
        x_1 = 5;
        y_1 = 2;
    }
    else{
         x_2 = 5;
         y_2 = 2;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p44_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(43)->setDefault(true);
        x_1 = 5;
        y_1 = 3;
    }
    else{
         x_2 = 5;
         y_2 = 3;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p45_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(44)->setDefault(true);
        x_1 = 5;
        y_1 = 4;
    }
    else{
         x_2 = 5;
         y_2 = 4;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p46_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(45)->setDefault(true);
        x_1 = 5;
        y_1 = 5;
    }
    else{
         x_2 = 5;
         y_2 = 5;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p47_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(46)->setDefault(true);
        x_1 = 5;
        y_1 = 6;
    }
    else{
         x_2 = 5;
         y_2 = 6;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p48_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(47)->setDefault(true);
        x_1 = 5;
        y_1 = 7;
    }
    else{
         x_2 = 5;
         y_2 = 7;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p49_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(48)->setDefault(true);
        x_1 = 6;
        y_1 = 0;
    }
    else{
         x_2 = 6;
         y_2 = 0;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p50_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(49)->setDefault(true);
        x_1 = 6;
        y_1 = 1;
    }
    else{
         x_2 = 6;
         y_2 = 1;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p51_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(50)->setDefault(true);
        x_1 = 6;
        y_1 = 2;
    }
    else{
         x_2 = 6;
         y_2 = 2;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p52_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(51)->setDefault(true);
        x_1 = 6;
        y_1 = 3;
    }
    else{
         x_2 = 6;
         y_2 = 3;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p53_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(52)->setDefault(true);
        x_1 = 6;
        y_1 = 4;
    }
    else{
         x_2 = 6;
         y_2 = 4;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p54_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(53)->setDefault(true);
        x_1 = 6;
        y_1 = 5;
    }
    else{
         x_2 = 6;
         y_2 = 5;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p55_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(54)->setDefault(true);
        x_1 = 6;
        y_1 = 6;
    }
    else{
         x_2 = 6;
         y_2 = 6;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p56_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(55)->setDefault(true);
        x_1 = 6;
        y_1 = 7;
    }
    else{
         x_2 = 6;
         y_2 = 7;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p57_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(56)->setDefault(true);
        x_1 = 7;
        y_1 = 0;
    }
    else{
         x_2 = 7;
         y_2 = 0;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p58_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(57)->setDefault(true);
        x_1 = 7;
        y_1 = 1;
    }
    else{
         x_2 = 7;
         y_2 = 1;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p59_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(58)->setDefault(true);
        x_1 = 7;
        y_1 = 2;
    }
    else{
         x_2 = 7;
         y_2 = 2;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p60_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(59)->setDefault(true);
        x_1 = 7;
        y_1 = 3;
    }
    else{
         x_2 = 7;
         y_2 = 3;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p61_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(60)->setDefault(true);
        x_1 = 7;
        y_1 = 4;
    }
    else{
         x_2 = 7;
         y_2 = 4;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p62_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(61)->setDefault(true);
        x_1 = 7;
        y_1 = 5;
    }
    else{
         x_2 = 7;
         y_2 = 5;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p63_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(62)->setDefault(true);
        x_1 = 7;
        y_1 = 6;
    }
    else{
         x_2 = 7;
         y_2 = 6;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}
void MainWindow::on_p64_clicked()
{
    if(isClicked == false)
    {
        isClicked = true;
        qp.at(63)->setDefault(true);
        x_1 = 7;
        y_1 = 7;
    }
    else{
         x_2 = 7;
         y_2 = 7;
        MyDoska.Move(x_1,y_1,x_2,y_2);
    }
}

void MainWindow::on_endButton_clicked()
{
    endB->setText(QString(""));
    endB->setGeometry(0, 0, 0, 0);
    MyDoska.Cleaner();
}
