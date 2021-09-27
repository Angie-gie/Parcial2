#include <iostream>
#include <fstream>
#include <QImage>

using namespace std;
void submuestreo(QImage img,int mat[3][10][10],int W, int H);
void sobremuestrar(QImage img,int mat[3][10][10],float W, float H);
float valorColor(int a,int b,int c, int d,float pesox, float pesoy);

int main()
{
    string filename="../Parcial 2/Parcial2/imagenes/guyana2.jpg";
    QImage img(filename.c_str());

    int a=img.width();
    int b=img.height();
    int mat[3][10][10];

    fstream archivo;
    archivo.open("matrizLEDs", fstream::out);

    if(a>10 || b>10){
        submuestreo(img,mat,a,b);
    }else if (a<10 || b<10){
        sobremuestrar(img,mat,float(a),float(b));
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
void sobremuestrar(QImage img,int mat[3][10][10],float W, float H){
    float radiox=(W-1)/10;
    float radioy=(H-1)/10;
    int aR,aG,aB,bR,bG,bB,cR,cG,cB,dR,dG,dB;

    for(unsigned short f=0;f<10;f++){
        for(unsigned short c=0;c<10;c++){
            int x1=radiox*c, y1=radioy*f,
                x2=(radiox*c)+1,y2=(radioy*f)+1;
            float pesox=(radiox*c)-x1;
            float pesoy=(radioy*f)-y1;

            aR=img.pixelColor(y1,x1).red();
            aG=img.pixelColor(y1,x1).green();
            aB=img.pixelColor(y1,x1).blue();

            bR=img.pixelColor(y1,x2).red();
            bG=img.pixelColor(y1,x2).green();
            bB=img.pixelColor(y1,x2).blue();

            cR=img.pixelColor(y2,x1).red();
            cG=img.pixelColor(y2,x1).green();
            cB=img.pixelColor(y2,x1).blue();

            dR=img.pixelColor(y2,x2).red();
            dG=img.pixelColor(y2,x2).green();
            dB=img.pixelColor(y2,x2).blue();

            mat[0][c][f]=int(valorColor(aR,bR,cR,dR,pesox,pesoy));
            mat[1][c][f]=int(valorColor(aG,bG,cG,dG,pesox,pesoy));
            mat[2][c][f]=int(valorColor(aB,bB,cB,dB,pesox,pesoy));
        }
    }
}
float valorColor(int a,int b,int c, int d,float pesox, float pesoy){
    float val=a * (1 - pesox) * (1 - pesoy)+ b *  pesox * (1 - pesoy) +
            c * pesoy * (1 -  pesox) + d *  pesox * pesoy;
    return val;
}
