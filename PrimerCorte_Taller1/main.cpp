#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"

#include "opencv2/highgui/highgui_c.h"

#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

void Dilatacion(){

    Mat A,kernel,salida;
    string nombre_ventana=" ";

    A = imread( "../Data/tutor.png",IMREAD_ANYCOLOR );
    kernel=getStructuringElement(MORPH_ELLIPSE,Size(5,5));

    dilate(A,salida,kernel);

    nombre_ventana= "Entrada";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    nombre_ventana= "Salida";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, salida);


}
void Erosion(){

    Mat A,kernel,salida;
    string nombre_ventana=" ";

    A = imread( "../Data/tutor.png",IMREAD_ANYCOLOR );
    kernel=getStructuringElement(MORPH_ELLIPSE,Size(5,5));

    erode(A,salida,kernel);

    nombre_ventana= "Entrada";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    nombre_ventana= "Salida";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, salida);


}
void Apertura(){

    Mat A,kernel,salida;
    string nombre_ventana=" ";

    A = imread( "../Data/ave2.png",IMREAD_ANYCOLOR );
    kernel=getStructuringElement(MORPH_ELLIPSE,Size(10,10));

    morphologyEx(A,salida,MORPH_OPEN,kernel);

    nombre_ventana= "Entrada";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    nombre_ventana= "Salida";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, salida);


}
void Cierre(){

    Mat A,kernel,salida;
    string nombre_ventana=" ";

    A = imread( "../Data/ave.jpg",IMREAD_ANYCOLOR );
    kernel=getStructuringElement(MORPH_ELLIPSE,Size(10,10));

    morphologyEx(A,salida,MORPH_CLOSE,kernel);

    nombre_ventana= "Entrada";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    nombre_ventana= "Salida";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, salida);

}
void RGB(){
    Mat A;
    Mat frameB = Mat(303, 338, CV_8UC3);
    Mat frameG = Mat(303, 338, CV_8UC3);
    Mat frameR = Mat(303, 338, CV_8UC3);
    string nombre_ventana=" ";

    A = imread( "../Data/imagenBGR.png",IMREAD_ANYCOLOR );
    nombre_ventana= "Entrada";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    for(int i=0;i<337;i++){
        for( int j=0;j<302;j++){

            uchar B = A.at<Vec3b>(Point(i, j))[0];
            uchar G = A.at<Vec3b>(Point(i, j))[1];
            uchar R = A.at<Vec3b>(Point(i, j))[2];

            frameB.at<Vec3b>(Point(i, j))[0]=B;
            frameB.at<Vec3b>(Point(i, j))[1]=0;
            frameB.at<Vec3b>(Point(i, j))[2]=0;

            frameG.at<Vec3b>(Point(i, j))[0]=0;
            frameG.at<Vec3b>(Point(i, j))[1]=G;
            frameG.at<Vec3b>(Point(i, j))[2]=0;

            frameR.at<Vec3b>(Point(i, j))[0]=0;
            frameR.at<Vec3b>(Point(i, j))[1]=0;
            frameR.at<Vec3b>(Point(i, j))[2]=R;


        }
    }
    nombre_ventana= "Salida B";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
    imshow(nombre_ventana, frameB);

    nombre_ventana= "Salida G";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
    imshow(nombre_ventana, frameG);

    nombre_ventana= "Salida R";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
    imshow(nombre_ventana, frameR);


}
void SaltPepper(){
    Mat A,salida,salida2;
    string nombre_ventana=" ";

    A = imread( "../Data/lenanoise.png",IMREAD_ANYCOLOR );
    nombre_ventana= "Imagen con ruido";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    medianBlur(A,salida,3);
    medianBlur(salida,salida2,3);

    nombre_ventana= "Imagen filtrada";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, salida2);


}
void Messi(){

    Mat A,entrada,salida,salida2;

    Mat frame = Mat(319, 509, CV_8UC3);
    Mat frame2 = Mat(319, 509, CV_8UC3);
    Mat frame3 = Mat(319, 509, CV_8UC3);

    Mat azul = Mat(319, 509, CV_8UC3);
    Mat azul2 = Mat(319, 509, CV_8UC3);
    Mat azul3 = Mat(319, 509, CV_8UC3);

    Mat verde = Mat(319, 509, CV_8UC3);
    Mat verde2 = Mat(319, 509, CV_8UC3);
    Mat verde3 = Mat(319, 509, CV_8UC3);

    string nombre_ventana=" ";


    A= imread( "../Data/mes.jpg",IMREAD_ANYCOLOR );
    nombre_ventana= "Entrada";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, A);

    cvtColor(A,entrada,COLOR_BGR2HSV);


    nombre_ventana= "Entrada HSV";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, entrada);


    for(int i=0;i<509;i++){
        for( int j=0;j<319;j++){
            int B = entrada.at<Vec3b>(Point(i, j))[0];
            int G = entrada.at<Vec3b>(Point(i, j))[1];
            int R = entrada.at<Vec3b>(Point(i, j))[2];

            if(150<B && 160<G && 0<R){
                frame.at<Vec3b>(Point(i, j))[0]=B;
                frame.at<Vec3b>(Point(i, j))[1]=G;
                frame.at<Vec3b>(Point(i, j))[2]=R;
            }else{
                frame.at<Vec3b>(Point(i, j))[0]=0;
                frame.at<Vec3b>(Point(i, j))[1]=0;
                frame.at<Vec3b>(Point(i, j))[2]=0;
            }
        }
    }

    cvtColor(frame,frame2,COLOR_HLS2BGR);


    for(int i=0;i<509;i++){
        for( int j=0;j<319;j++){
            int B = entrada.at<Vec3b>(Point(i, j))[0];
            int G = entrada.at<Vec3b>(Point(i, j))[1];
            int R = entrada.at<Vec3b>(Point(i, j))[2];

            if(100<B && 135>B && 160<G && 0<R){
                azul.at<Vec3b>(Point(i, j))[0]=B;
                azul.at<Vec3b>(Point(i, j))[1]=G;
                azul.at<Vec3b>(Point(i, j))[2]=R;
            }else{
                azul.at<Vec3b>(Point(i, j))[0]=0;
                azul.at<Vec3b>(Point(i, j))[1]=0;
                azul.at<Vec3b>(Point(i, j))[2]=0;
            }
        }
    }

    cvtColor(azul,azul2,COLOR_HLS2BGR);

    for(int i=0;i<509;i++){
        for( int j=0;j<319;j++){
            int B = entrada.at<Vec3b>(Point(i, j))[0];
            int G = entrada.at<Vec3b>(Point(i, j))[1];
            int R = entrada.at<Vec3b>(Point(i, j))[2];

            if(40<B && 70>B && 135<G && 0<R){
                verde.at<Vec3b>(Point(i, j))[0]=B;
                verde.at<Vec3b>(Point(i, j))[1]=G;
                verde.at<Vec3b>(Point(i, j))[2]=R;
            }else{
                verde.at<Vec3b>(Point(i, j))[0]=0;
                verde.at<Vec3b>(Point(i, j))[1]=0;
                verde.at<Vec3b>(Point(i, j))[2]=0;
            }
        }
    }

    cvtColor(verde,verde2,COLOR_HLS2BGR);

    for(int i=0;i<509;i++){

        for( int j=0;j<319;j++){
            int B1 = A.at<Vec3b>(Point(i, j))[0];
            int G1 = A.at<Vec3b>(Point(i, j))[1];
            int R1 = A.at<Vec3b>(Point(i, j))[2];

            char gray= (R1*0.299)+(G1*0.587)+(B1*0.114);

            int B2 = frame2.at<Vec3b>(Point(i, j))[0];
            int G2 = frame2.at<Vec3b>(Point(i, j))[1];
            int R2 = frame2.at<Vec3b>(Point(i, j))[2];

            int B3 = azul2.at<Vec3b>(Point(i, j))[0];
            int G3 = azul2.at<Vec3b>(Point(i, j))[1];
            int R3 = azul2.at<Vec3b>(Point(i, j))[2];

            int B4 = verde2.at<Vec3b>(Point(i, j))[0];
            int G4 = verde2.at<Vec3b>(Point(i, j))[1];
            int R4 = verde2.at<Vec3b>(Point(i, j))[2];

            if(B2==0 && G2==0 && R2==0){
                frame3.at<Vec3b>(Point(i, j))[0]=gray;
                frame3.at<Vec3b>(Point(i, j))[1]=gray;
                frame3.at<Vec3b>(Point(i, j))[2]=gray;
            }else{
                frame3.at<Vec3b>(Point(i, j))[0]=B1;
                frame3.at<Vec3b>(Point(i, j))[1]=G1;
                frame3.at<Vec3b>(Point(i, j))[2]=R1;
            }

            if(B3==0 && G3==0 && R3==0){
                azul3.at<Vec3b>(Point(i, j))[0]=gray;
                azul3.at<Vec3b>(Point(i, j))[1]=gray;
                azul3.at<Vec3b>(Point(i, j))[2]=gray;
            }else{
                azul3.at<Vec3b>(Point(i, j))[0]=B1;
                azul3.at<Vec3b>(Point(i, j))[1]=G1;
                azul3.at<Vec3b>(Point(i, j))[2]=R1;
            }
            if(B4==0 && G4==0 && R4==0){
                verde3.at<Vec3b>(Point(i, j))[0]=gray;
                verde3.at<Vec3b>(Point(i, j))[1]=gray;
                verde3.at<Vec3b>(Point(i, j))[2]=gray;
            }else{
                verde3.at<Vec3b>(Point(i, j))[0]=B1;
                verde3.at<Vec3b>(Point(i, j))[1]=G1;
                verde3.at<Vec3b>(Point(i, j))[2]=R1;
            }

        }
    }

    nombre_ventana= "Salida BGR rojo";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
    imshow(nombre_ventana, frame3);

    nombre_ventana= "Salida BGR azul";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
    imshow(nombre_ventana, azul3);

    nombre_ventana= "Salida BGR verde";
    namedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
    imshow(nombre_ventana, verde3);

}
int main()
{
    int n;
    Mat A;
    string nombre_ventana=" ";

    A = imread( "../Data/tutor.png",IMREAD_ANYCOLOR );

    if ( !A.data )
    {
        printf("No image data \n");
        return -1;
    }

    cout<<"Digite el numero de la operacion que desea realizar: "<<endl;
    cout<<"1. Dilataciòn "<<endl;
    cout<<"2. Erosiòn"<<endl;
    cout<<"3. Apertura "<<endl;
    cout<<"4. Cierre"<<endl;
    cout<<"5. Imagenes RGB"<<endl;
    cout<<"6. Eliminar ruido salt and pepper"<<endl;
    cout<<"7. Messi a colores"<<endl;
    cin>>n;

    switch (n) {

    case 1:
        Dilatacion();
    break;

    case 2:
        Erosion();
    break;

    case 3:
        Apertura();
    break;

    case 4:
        Cierre();
    break;

    case 5:
        RGB();
    break;

    case 6:
        SaltPepper();
    break;

    case 7:
        Messi();
    break;


    default:
        cout<<"no valido"<<endl;
        exit(-1);

    }

    waitKey(0);
    return 0;
}
