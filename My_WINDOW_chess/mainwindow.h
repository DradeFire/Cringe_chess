#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "functional"
#include <vector>
#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_p1_clicked();

    void on_p2_clicked();

    void on_p3_clicked();

    void on_p4_clicked();

    void on_p5_clicked();

    void on_p6_clicked();

    void on_p7_clicked();

    void on_p8_clicked();

    void on_p9_clicked();

    void on_p10_clicked();

    void on_p11_clicked();

    void on_p12_clicked();

    void on_p13_clicked();

    void on_p14_clicked();

    void on_p15_clicked();

    void on_p16_clicked();

    void on_p17_clicked();

    void on_p18_clicked();

    void on_p19_clicked();

    void on_p20_clicked();
    void on_p21_clicked();
    void on_p22_clicked();
    void on_p23_clicked();
    void on_p24_clicked();
    void on_p25_clicked();
    void on_p26_clicked();
    void on_p27_clicked();
    void on_p28_clicked();
    void on_p29_clicked();

    void on_p30_clicked();
    void on_p31_clicked();
    void on_p32_clicked();
    void on_p33_clicked();
    void on_p34_clicked();
    void on_p35_clicked();
    void on_p36_clicked();
    void on_p37_clicked();
    void on_p38_clicked();
    void on_p39_clicked();

    void on_p40_clicked();
    void on_p41_clicked();
    void on_p42_clicked();
    void on_p43_clicked();
    void on_p44_clicked();
    void on_p45_clicked();
    void on_p46_clicked();
    void on_p47_clicked();
    void on_p48_clicked();
    void on_p49_clicked();

    void on_p50_clicked();
    void on_p51_clicked();
    void on_p52_clicked();
    void on_p53_clicked();
    void on_p54_clicked();
    void on_p55_clicked();
    void on_p56_clicked();
    void on_p57_clicked();
    void on_p58_clicked();
    void on_p59_clicked();

    void on_p60_clicked();
    void on_p61_clicked();
    void on_p62_clicked();
    void on_p63_clicked();
    void on_p64_clicked();


    void on_endButton_clicked();

private:
    Ui::MainWindow *ui;
};

class Figura {      //Общий класс для всех фигур
public:
    int VidFigura;     //Переменная отвечает за вид фигуры(Конь, Слон, Король...)
    int Color;  //0=black 1=white 2=случайная
    Figura();    //Конструктор по умолчанию, используется для заполнения остатка клеток доски

    Figura(int v, int c);    //Конструктор, который создает фигуры

};

class Doska {

public:
    void GameOVER(int colorWin);     //Конечнаяы
    Figura matrix[8][8];     //Сама доска
    void Zamena(int x, int y, int x2, int y2);
    void MoveLadya(int x, int y, int x2, int y2);
    void MoveSlon(int x, int y, int x2, int y2);
    void MovePeshka(int x, int y, int x2, int y2,bool z);
    void Move(int x, int y, int x2, int y2);
    void Cleaner();
};

#endif // MAINWINDOW_H
