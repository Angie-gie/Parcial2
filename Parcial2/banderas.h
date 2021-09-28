#ifndef BANDERAS_H
#define BANDERAS_H
#include <iostream>
#include <fstream>
#include <string>
#include <QImage>

using namespace std;

class banderas: public QImage
{
public:
    banderas();
    QImage IngresoUsuario();
    void redimension();
    void submuestreo(QImage img, int mat[3][10][10]);
    void sobremuestreo(QImage img,int mat[3][10][10]);
    float valorColor(int a,int b,int c, int d,float pesox, float pesoy);
    void crear_txt();
    void getDimensiones();
private:
    QImage bandera;
    int mat[3][10][10],W,H;
};

#endif // BANDERAS_H
