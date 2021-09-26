#include <iostream>
#include <fstream>
#include <QImage>

using namespace std;
void submuestreo(QImage img,int mat[3][10][10],int W, int H);

int main()
{
    string filename="../Parcial 2/Parcial2/imagenes/mexico.jpg";
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
        for(unsigned short f=0;f<10;f++){
            for(unsigned short c=0;c<10;c++){
                int colorR=img.pixelColor(c,f).red();
                int colorG=img.pixelColor(c,f).green();
                int colorB=img.pixelColor(c,f).blue();
                if(colorR==255){
                    colorR=254;
                }
                mat[0][c][f]=colorR;
                mat[1][c][f]=colorG;
                mat[2][c][f]=colorB;
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
    int posx=0,posy=0, newc=0,newf=0;
    int sobrantex=W%10;

    for(int cont=1;cont<=100;cont++){
        int sumR=0,sumG=0,sumB=0;
        for(unsigned short f=0;f<H/10;f++){
            for(unsigned short c=0;c<W/10;c++){
                sumR+=img.pixelColor(c+posx,f+posy).red();
                sumG+=img.pixelColor(c+posx,f+posy).green();
                sumB+=img.pixelColor(c+posx,f+posy).blue();
            }
        }if(sumR/((H/10)*(W/10))!=255){
            mat[0][newc][newf]=sumR/((H/10)*(W/10));
        }else{
            mat[0][newc][newf]=(sumR/((H/10)*(W/10)))-1;
        }
        mat[1][newc][newf]=sumG/((H/10)*(W/10));
        mat[2][newc][newf]=sumB/((H/10)*(W/10));
        if(posx!=W-((W/10)+sobrantex)){
            posx+=W/10;
            newc++;
        }else{
            posx=0;
            newc=0;
        }
        if(cont%10==0 && cont!=0){
             posy+=H/10;
             newf++;
        }
   }

}
