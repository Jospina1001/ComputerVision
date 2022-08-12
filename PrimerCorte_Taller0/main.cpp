#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"

#include "opencv2/highgui/highgui_c.h"

#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

void DisplayIm(){

    Mat A,B,C,D,E,F;
    string nombre_ventana=" ";

    A = imread( "../Data/lena.jpg",IMREAD_ANYCOLOR );
    B = imread( "../Data/Anime.jpg",IMREAD_ANYCOLOR );
    C = imread( "../Data/baboon.jpg",IMREAD_ANYCOLOR );
    D = imread( "../Data/landscape.jpg",IMREAD_ANYCOLOR );
    E = imread( "../Data/Noise.jpg",IMREAD_ANYCOLOR );
    F = imread( "../Data/Liverpool.jpg",IMREAD_ANYCOLOR );

    nombre_ventana= "foto A";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    nombre_ventana= "foto B";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, B);

    nombre_ventana= "foto C";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, C);

    nombre_ventana= "foto D";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, D);

    nombre_ventana= "foto E";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, E);

    nombre_ventana= "foto F";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, F);

}

void Ventana(){

    Mat A,B,C,D,E,F;
    string nombre_ventana=" ";
    Mat frame = Mat(1024, 1536, CV_8UC3);

    A = imread( "../Data/lena.jpg",IMREAD_ANYCOLOR );
    B = imread( "../Data/Anime.jpg",IMREAD_ANYCOLOR );
    C = imread( "../Data/baboon.jpg",IMREAD_ANYCOLOR );
    D = imread( "../Data/landscape.jpg",IMREAD_ANYCOLOR );
    E = imread( "../Data/Noise.jpg",IMREAD_ANYCOLOR );
    F = imread( "../Data/Liverpool.jpg",IMREAD_ANYCOLOR );


    for (int i=0;i<=511;i++){

        for (int j=0;j<=511;j++){

            uchar B = A.at<Vec3b>(Point(i, j))[0];
            uchar G = A.at<Vec3b>(Point(i, j))[1];
            uchar R = A.at<Vec3b>(Point(i, j))[2];

            frame.at<Vec3b>(Point(i, j))[0]=B;
            frame.at<Vec3b>(Point(i, j))[1]=G;
            frame.at<Vec3b>(Point(i, j))[2]=R;
        }
     for(int j=512;j<=1023;j++){

            uchar B2 = B.at<Vec3b>(Point(i, j-512))[0];
            uchar G2 = B.at<Vec3b>(Point(i, j-512))[1];
            uchar R2 = B.at<Vec3b>(Point(i, j-512))[2];

            frame.at<Vec3b>(Point(i, j))[0]=B2;
            frame.at<Vec3b>(Point(i, j))[1]=G2;
            frame.at<Vec3b>(Point(i, j))[2]=R2;
     }
    }

    for (int i=512;i<=1023;i++){
           for (int j=0;j<=511;j++){

               uchar B = C.at<Vec3b>(Point(i-512, j))[0];
               uchar G =  C.at<Vec3b>(Point(i-512, j))[1];
               uchar R = C.at<Vec3b>(Point(i-512, j))[2];

               frame.at<Vec3b>(Point(i, j))[0]=B;
               frame.at<Vec3b>(Point(i, j))[1]=G;
               frame.at<Vec3b>(Point(i, j))[2]=R;
           }
        for(int j=512;j<=1023;j++){

            uchar B2 = D.at<Vec3b>(Point(i-512, j-512))[0];
            uchar G2 = D.at<Vec3b>(Point(i-512, j-512))[1];
            uchar R2 = D.at<Vec3b>(Point(i-512, j-512))[2];

            frame.at<Vec3b>(Point(i, j))[0]=B2;
            frame.at<Vec3b>(Point(i, j))[1]=G2;
            frame.at<Vec3b>(Point(i, j))[2]=R2;
        }
       }
    for (int i=1024;i<=1536;i++){
           for (int j=0;j<=511;j++){

               uchar B = E.at<Vec3b>(Point(i-1024, j))[0];
               uchar G =  E.at<Vec3b>(Point(i-1024, j))[1];
               uchar R = E.at<Vec3b>(Point(i-1024, j))[2];

               frame.at<Vec3b>(Point(i, j))[0]=B;
               frame.at<Vec3b>(Point(i, j))[1]=G;
               frame.at<Vec3b>(Point(i, j))[2]=R;
           }
        for(int j=512;j<=1023;j++){

            uchar B2 = F.at<Vec3b>(Point(i-1024, j-512))[0];
            uchar G2 = F.at<Vec3b>(Point(i-1024, j-512))[1];
            uchar R2 = F.at<Vec3b>(Point(i-1024, j-512))[2];

            frame.at<Vec3b>(Point(i, j))[0]=B2;
            frame.at<Vec3b>(Point(i, j))[1]=G2;
            frame.at<Vec3b>(Point(i, j))[2]=R2;
        }
       }
    nombre_ventana= "Todas las fotos";
    namedWindow(nombre_ventana, CV_WINDOW_NORMAL );
    imshow(nombre_ventana, frame);

}

void Negro(){

    int n;
    Mat A,B,C,D,E,F;
    Mat frame = Mat(512, 512, CV_8UC3);
    string nombre_ventana=" ";


    cout<<"elija la imagen a la que quiere hacer el cambio"<<endl;
    cin>>n;

    switch (n) {

    case 1:
        A = imread( "../Data/lena.jpg",IMREAD_ANYCOLOR );
    break;

    case 2:
        A = imread( "../Data/Anime.jpg",IMREAD_ANYCOLOR );
    break;

    case 3:
        A=imread( "../Data/baboon.jpg",IMREAD_ANYCOLOR );
    break;

    case 4:
        A=imread( "../Data/landscape.jpg",IMREAD_ANYCOLOR );
    break;

    case 5:
        A=imread( "../Data/Noise.jpg",IMREAD_ANYCOLOR );
    break;

    case 6:
        A=imread( "../Data/Liverpool.jpg",IMREAD_ANYCOLOR );
    break;

    default:
        cout<<"Opcion invalida"<<endl;

    }

    nombre_ventana= "Entrada";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    for(int i=0;i<511;i++){
        for( int j=0;j<511;j++){

            if(i>156 && i<356 && j>156 && j<356){

                uchar B = A.at<Vec3b>(Point(i, j))[0];
                uchar G = A.at<Vec3b>(Point(i, j))[1];
                uchar R = A.at<Vec3b>(Point(i, j))[2];

                uchar gray= (R*0.299)+(G*0.587)+(B*0.114);

                frame.at<Vec3b>(Point(i, j))[0]=gray;
                frame.at<Vec3b>(Point(i, j))[1]=gray;
                frame.at<Vec3b>(Point(i, j))[2]=gray;

            }else{
                uchar B = A.at<Vec3b>(Point(i, j))[0];
                uchar G = A.at<Vec3b>(Point(i, j))[1];
                uchar R = A.at<Vec3b>(Point(i, j))[2];

                frame.at<Vec3b>(Point(i, j))[0]=B;
                frame.at<Vec3b>(Point(i, j))[1]=G;
                frame.at<Vec3b>(Point(i, j))[2]=R;
            }


        }
    }
    nombre_ventana= "Salida";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
    imshow(nombre_ventana, frame);


}
void Binario(){


    int n;
    Mat A,B,C,D,E,F;
    Mat frame = Mat(512, 512, CV_8UC3);
    string nombre_ventana=" ";


    cout<<"elija la imagen a la que quiere hacer el cambio"<<endl;
    cin>>n;

    switch (n) {

    case 1:
        A = imread( "../Data/lena.jpg",IMREAD_ANYCOLOR );
    break;

    case 2:
        A = imread( "../Data/Anime.jpg",IMREAD_ANYCOLOR );
    break;

    case 3:
        A=imread( "../Data/baboon.jpg",IMREAD_ANYCOLOR );
    break;

    case 4:
        A=imread( "../Data/landscape.jpg",IMREAD_ANYCOLOR );
    break;

    case 5:
        A=imread( "../Data/Noise.jpg",IMREAD_ANYCOLOR );
    break;

    case 6:
        A=imread( "../Data/Liverpool.jpg",IMREAD_ANYCOLOR );
    break;

    default:
        cout<<"Opcion invalida"<<endl;

    }

    nombre_ventana= "Entrada";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    for(int i=0;i<511;i++){
        for( int j=0;j<511;j++){

            if(i>156 && i<356 && j>156 && j<356){

                uchar B = A.at<Vec3b>(Point(i, j))[0];
                uchar G = A.at<Vec3b>(Point(i, j))[1];
                uchar R = A.at<Vec3b>(Point(i, j))[2];

                uchar gray= (R*0.299)+(G*0.587)+(B*0.114);

                if(gray<127){
                    frame.at<Vec3b>(Point(i, j))[0]=0;
                    frame.at<Vec3b>(Point(i, j))[1]=0;
                    frame.at<Vec3b>(Point(i, j))[2]=0;

                }else{
                    frame.at<Vec3b>(Point(i, j))[0]=255;
                    frame.at<Vec3b>(Point(i, j))[1]=255;
                    frame.at<Vec3b>(Point(i, j))[2]=255;
                }

            }else{
                uchar B = A.at<Vec3b>(Point(i, j))[0];
                uchar G = A.at<Vec3b>(Point(i, j))[1];
                uchar R = A.at<Vec3b>(Point(i, j))[2];

                frame.at<Vec3b>(Point(i, j))[0]=B;
                frame.at<Vec3b>(Point(i, j))[1]=G;
                frame.at<Vec3b>(Point(i, j))[2]=R;


        }
        }
    }
    nombre_ventana= "Salida";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
    imshow(nombre_ventana, frame);

}


void Deteccion(){

    Mat A,B;
    string nombre_ventana=" ";
    Mat frame = Mat(480, 640, CV_8UC3);

    A = imread( "../Data/imA.jpg",IMREAD_ANYCOLOR );
    B = imread( "../Data/imB.jpg",IMREAD_ANYCOLOR );

    nombre_ventana= "Imagen A";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    nombre_ventana= "Imagen B";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, B);

    for(int i=0;i<640;i++){
        for( int j=0;j<480;j++){

            uchar B1 = A.at<Vec3b>(Point(i, j))[0];
            uchar G1 = A.at<Vec3b>(Point(i, j))[1];
            uchar R1 = A.at<Vec3b>(Point(i, j))[2];

            uchar B2 = B.at<Vec3b>(Point(i, j))[0];
            uchar G2 = B.at<Vec3b>(Point(i, j))[1];
            uchar R2 = B.at<Vec3b>(Point(i, j))[2];

            uchar B = abs(B2-B1);
            uchar G = abs(G2-G1);
            uchar R = abs(R2-R1);

            uchar RGB=(R+G+B)/3;

            if (RGB<50){
                frame.at<Vec3b>(Point(i, j))[0]=0;
                frame.at<Vec3b>(Point(i, j))[1]=0;
                frame.at<Vec3b>(Point(i, j))[2]=0;

            }else{
                frame.at<Vec3b>(Point(i, j))[0]=B;
                frame.at<Vec3b>(Point(i, j))[1]=G;
                frame.at<Vec3b>(Point(i, j))[2]=R;
            }



        }
    }
    nombre_ventana= "Salida";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
    imshow(nombre_ventana, frame);
}

void Deteccion2(){

    Mat A,B;
    string nombre_ventana=" ";
    Mat frame = Mat(480, 640, CV_8UC3);

    A = imread( "../Data/imA.jpg",IMREAD_ANYCOLOR );
    B = imread( "../Data/imB.jpg",IMREAD_ANYCOLOR );

    nombre_ventana= "Imagen A";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    nombre_ventana= "Imagen B";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, B);

    for(int i=0;i<640;i++){
        for( int j=0;j<480;j++){

            uchar B1 = A.at<Vec3b>(Point(i, j))[0];
            uchar G1 = A.at<Vec3b>(Point(i, j))[1];
            uchar R1 = A.at<Vec3b>(Point(i, j))[2];

            uchar B2 = B.at<Vec3b>(Point(i, j))[0];
            uchar G2 = B.at<Vec3b>(Point(i, j))[1];
            uchar R2 = B.at<Vec3b>(Point(i, j))[2];

            uchar B = abs(B2-B1);
            uchar G = abs(G2-G1);
            uchar R = abs(R2-R1);

            uchar RGB= (R+G+B)/3;

            if(RGB>50){

                frame.at<Vec3b>(Point(i, j))[0]=B1;
                frame.at<Vec3b>(Point(i, j))[1]=G1;
                frame.at<Vec3b>(Point(i, j))[2]=R1;

            }else{
                frame.at<Vec3b>(Point(i, j))[0]=255;
                frame.at<Vec3b>(Point(i, j))[1]=255;
                frame.at<Vec3b>(Point(i, j))[2]=255;
            }

        }
    }
    nombre_ventana= "Salida";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
    imshow(nombre_ventana, frame);

}

int main()
{

    Mat A;
    int n;
    //Lectura de imagenes
    A = imread( "../Data/lena.jpg",IMREAD_ANYCOLOR );


    if ( !A.data )
    {
        printf("No image data \n");
        return -1;
    }

    cout<<"Digite el numero para realizar una operacion: "<<endl;
    cout<<"1: abrir las imagenes de forma individual "<<endl;
    cout<<"2: abrir una ventana que junta todas las imagenes"<<endl;
    cout<<"3: imagen con cuadro blanco y negro"<<endl;
    cout<<"4: Binarizarada"<<endl;
    cout<<"5: Deteccion de triceratops"<<endl;
    cout<<"6: Deteccion de triceratops en color original"<<endl;
    cout<<" "<<endl;
    cin>>n;

    switch (n) {

    case 1:
        DisplayIm();
    break;

    case 2:
        Ventana();
    break;

    case 3:
        Negro();
    break;

    case 4:
        Binario();
    break;

    case 5:
        Deteccion();
    break;

    case 6:
        Deteccion2();
    break;

    default:
        cout<<"no valido"<<endl;
        exit(-1);

    }

    waitKey(0);
    destroyAllWindows();

    return 0;
}
