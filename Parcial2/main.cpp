#include <iostream>
#include <fstream>
#include <QImage>

using namespace std;

int main()
{
    string filename="../Parcial 2/Parcial2/imagenes/guyana.jpg";
    QImage img(filename.c_str());

    int a=img.width();
    int b=img.height();
    int mat[3][10][10];

    fstream archivo;
    archivo.open("matrizLEDs", fstream::out);

    if(a>10 || b>10){
        //submuestrar(img);
    }else if (a>10 || b>10){
        //sobremuestrar(img);
    }else{
        for(unsigned short f=0;f<10;f++){
            for(unsigned short c=0;c<10;c++){
                int colorR=img.pixelColor(f,c).red();
                int colorG=img.pixelColor(f,c).green();
                int colorB=img.pixelColor(f,c).blue();
                mat[0][f][c]=colorR;
                mat[1][f][c]=colorG;
                mat[2][f][c]=colorB;
            }
        }
    }
    for(short i=0;i<3;i++){
        archivo<<'{';
        for(short f=0;f<10;f++){
            archivo<<'{';
            for(short c=0;c<10;c++){
                archivo<<mat[i][f][c];
                if(c!=9) archivo<<',';
            }
            archivo<<'}';
            if(f!=9) archivo<<',';
        }
        archivo<<'}';
        if(i!=2)archivo<<',';
        archivo<<'\n';
    }
    archivo.close();

    return 0;
}
