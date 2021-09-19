#include <iostream>
#include <fstream>
#include <QImage>

using namespace std;

int main()
{
    string filename="../Parcial2/imagenes/francia.jpg";
    QImage img(filename.c_str());

    unsigned int pixelX=122;
    unsigned int pixelY=88;
    cout<<"valor "<<img.pixelColor(pixelX,pixelY).blue()<<endl;

    return 0;
}
