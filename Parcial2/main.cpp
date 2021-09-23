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

    if(a>10 || b>10){
        submuestrar(img);
    }else if (a>10 || b>10){
        sobremuestrar(img);
    }else{
        for(unsigned short f=0;f<10;f++){
            for(unsigned short c=0;c<10;c++){

            }
        }
    }

//    unsigned int pixelX=122;
//    unsigned int pixelY=88;
//    cout<<"valor "<<img.pixelColor(pixelX,pixelY).blue()<<endl;

    return 0;
}
