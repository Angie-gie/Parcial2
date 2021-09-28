#include "banderas.h"

banderas::banderas()
{
    bandera=IngresoUsuario();
}

QImage banderas::IngresoUsuario()
{
    string ruta;
    cout<<"Ingreso la ruta absoluta de la imagen a representar"<<endl;
    getline(cin,ruta);
    QImage img(ruta.c_str());
    return img;
}

void banderas::redimension()
{
    getDimensiones();
    if((W>10 && H<10) || (W<10 && H>10)){
        sobremuestreo(bandera,mat);
    }else if(W>10 || H>10){
        submuestreo(bandera,mat);
    }else if (W<10 || H<10){
        sobremuestreo(bandera,mat);
    }else{
        for(unsigned short f=0;f<10;f++){
            for(unsigned short c=0;c<10;c++){
                int colorR=bandera.pixelColor(c,f).red();
                int colorG=bandera.pixelColor(c,f).green();
                int colorB=bandera.pixelColor(c,f).blue();
                if(colorR==255){
                    colorR=254;
                }
                mat[0][c][f]=colorR;
                mat[1][c][f]=colorG;
                mat[2][c][f]=colorB;
            }
        }
    }
}

void banderas::submuestreo(QImage img, int mat[3][10][10])
{
    int sobrantex=W%10;
    int sobrantey=H%10;
    int posx=sobrantex/2,posy=sobrantey/2, newc=0,newf=0,k;

    if(posy>0)posy-=1;
    if(posx>0){
        posx-=1;
        float x=sobrantex/2.0;
        int r=(x-sobrantex/2)*10;
        if(r%2!=0)
            k=r/2;
        else k=1;
    }else k=0;

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
        if(posx!=W-((W/10)+((sobrantex/2)+k))){
            posx+=(W/10);
            newc++;
        }else{
            if(cont%10==0 && cont!=0 && sobrantex/2>0){
                posx=(sobrantex/2)-1;
            }else{
                posx=sobrantex/2;
            }
            newc=0;
        }
        if(cont%10==0 && cont!=0){
             posy+=H/10;
             newf++;
        }
   }
}

void banderas::sobremuestreo(QImage img,int mat[3][10][10])
{
    float nW=float(W);
    float nH=float(H);
    float radiox=(nW-1)/10;
    float radioy=(nH-1)/10;
    int aR,aG,aB,bR,bG,bB,cR,cG,cB,dR,dG,dB;

    for(int f=0;f<10;f++){
        for(int c=0;c<10;c++){
            int x1=radiox*c, y1=radioy*f,
                x2=(radiox*c)+1,y2=(radioy*f)+1;
            float pesox=(radiox*c)-float(x1);
            float pesoy=(radioy*f)-float(y1);

            aR=img.pixelColor(x1,y1).red();
            aG=img.pixelColor(x1,y1).green();
            aB=img.pixelColor(x1,y1).blue();

            bR=img.pixelColor(x1,y2).red();
            bG=img.pixelColor(x1,y2).green();
            bB=img.pixelColor(x1,y2).blue();

            cR=img.pixelColor(x2,y1).red();
            cG=img.pixelColor(x2,y1).green();
            cB=img.pixelColor(x2,y1).blue();

            dR=img.pixelColor(x2,y2).red();
            dG=img.pixelColor(x2,y2).green();
            dB=img.pixelColor(x2,y2).blue();

            int ColorR=int(valorColor(aR,bR,cR,dR,pesox,pesoy));
            int ColorG=int(valorColor(aG,bG,cG,dG,pesox,pesoy));
            int ColorB=int(valorColor(aB,bB,cB,dB,pesox,pesoy));
            if(ColorR==255){
                ColorR=254;
            }else if(ColorR==0){
                ColorR=2;
            }
            mat[0][c][f]=ColorR;
            mat[1][c][f]=ColorG;
            mat[2][c][f]=ColorB;
        }
    }
}

float banderas::valorColor(int a, int b, int c, int d, float pesox, float pesoy)
{
    float val=a * (1 - pesox) * (1 - pesoy)+ b *  pesox * (1 - pesoy) +
            c * pesoy * (1 -  pesox) + d *  pesox * pesoy;
    return val;
}

void banderas::crear_txt()
{
    fstream archivo;
    archivo.open("matrizLEDs", fstream::out);
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
}

void banderas::getDimensiones()
{
    W=bandera.width();
    H=bandera.height();
}
