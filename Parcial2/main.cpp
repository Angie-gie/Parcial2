#include <iostream>
#include <fstream>
#include <QImage>

using namespace std;

int main()
{
    string filename="../Parcial 2/Parcial2/imagenes/francia.jpg";
    QImage img(filename.c_str());

    int a=img.width();
    int b=img.height();

    cout<<a<<'x'<<b<<endl;

//    unsigned int pixelX=122;
//    unsigned int pixelY=88;
//    cout<<"valor "<<img.pixelColor(pixelX,pixelY).blue()<<endl;

    return 0;
}
