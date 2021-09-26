#include <iostream>
#include <fstream>
#include <QImage>

using namespace std;
void submuestreo(QImage img,int mat[3][10][10],int W, int H);

int main()
{
    string filename="../Parcial 2/Parcial2/imagenes/brasil.jpg";
    QImage img(filename.c_str());

    int a=img.width();
    int b=img.height();
    int mat[3][10][10];

    fstream archivo;
    archivo.open("matrizLEDs", fstream::out);

    if(a>10 || b>10){
        submuestreo(img,mat,a,b);
    }else if (a>10 || b>10){
        //sobremuestrar(img);
    }else{
        for(unsigned short x=0;x<10;x++){
            for(unsigned short y=0;y<10;y++){
                int colorR=img.pixelColor(x,y).red();
                int colorG=img.pixelColor(x,y).green();
                int colorB=img.pixelColor(x,y).blue();
                mat[0][x][y]=colorR;
                mat[1][x][y]=colorG;
                mat[2][x][y]=colorB;
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

void submuestreo(QImage img, int mat[3][10][10],int W, int H){
    int posx=0,posy=0, newposx=0,newposy=0;
    int sobrantex=W%10;
    int sobrantey=H%10;
    string info;

    if(sobrantex==0 && sobrantey==0){
        for(int cont=1;cont<=100;cont++){
            int sumR=0,sumG=0,sumB=0;
            for(unsigned short y=0;y<H/10;y++){
                for(unsigned short x=0;x<W/10;x++){
                    sumR+=img.pixelColor(x+posx,y+posy).red();
                    sumG+=img.pixelColor(x+posx,y+posy).green();
                    sumB+=img.pixelColor(x+posx,y+posy).blue();
                }
            }
            mat[0][newposx][newposy]=sumR/((H/10)*(W/10));
            mat[1][newposx][newposy]=sumG/((H/10)*(W/10));
            mat[2][newposx][newposy]=sumB/((H/10)*(W/10));
            if(posx!=W-(W/10)){
                posx+=W/10;
                newposx++;
            }else{
                posx=0;
                newposx=0;
            }
            if(cont%10==0 && cont!=0){
                 posy+=H/10;
                 newposy++;
            }

       }
    }
}
