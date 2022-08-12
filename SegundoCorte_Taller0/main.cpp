#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"

#include "opencv2/highgui/highgui_c.h"

#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

void Punto1(){
    Mat entrada,HSV;
    Mat frame = Mat(525, 700, CV_8UC3);
    Mat frame2 = Mat(525, 700, CV_8UC3);
    Mat frame3 = Mat(525, 700, CV_8UC3);

    string nombre_ventana=" ";

    entrada= imread( "../Data/entrada.png",IMREAD_ANYCOLOR );
    nombre_ventana= "Entrada";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, entrada);

    cvtColor(entrada,HSV,COLOR_BGR2HSV);

    nombre_ventana= "Entrada HSV";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, HSV);

    for(int i=0;i<700;i++){
        for( int j=0;j<525;j++){
            int B = HSV.at<Vec3b>(Point(i, j))[0];
            int G = HSV.at<Vec3b>(Point(i, j))[1];
            int R = HSV.at<Vec3b>(Point(i, j))[2];

            int B1 = entrada.at<Vec3b>(Point(i, j))[0];
            int G1 = entrada.at<Vec3b>(Point(i, j))[1];
            int R1 = entrada.at<Vec3b>(Point(i, j))[2];

            if(90<B && 130>B && 50<G && 0<R){
                frame.at<Vec3b>(Point(i, j))[0]=B1;
                frame.at<Vec3b>(Point(i, j))[1]=G1;
                frame.at<Vec3b>(Point(i, j))[2]=R1;
            }else{
                frame.at<Vec3b>(Point(i, j))[0]=0;
                frame.at<Vec3b>(Point(i, j))[1]=0;
                frame.at<Vec3b>(Point(i, j))[2]=0;
            }
        }
    }

    nombre_ventana= "Salida";
    namedWindow( nombre_ventana, CV_WINDOW_AUTOSIZE );
    imshow(nombre_ventana, frame);
}

void Punto2(){
    Mat imagen1 = imread("../Data/koruny_black1.jpg");
    Mat gray;
        cvtColor(imagen1, gray, COLOR_BGR2GRAY);
        blur(gray, gray, Size(4,4));
        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                     gray.rows/8,  // change this value to detect circles with different distances to each other
                     250, 70, 52, 0  // change the last two parameters
                // (min_radius & max_radius) to detect larger circles
        );
        int cor=0;
        int change = 0;
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Vec3i c = circles[i];
            Point center = Point(c[0], c[1]);
            // circle center
            circle( imagen1, center, 1, Scalar(0,100,100), 3, LINE_AA);
            // circle outline
            cor=cor+20;
            int radius = c[2];
            circle( imagen1, center, radius, Scalar(255,0,0), 3, LINE_AA);

            if ((radius >= 100) && (radius<160))
            {
                change = change + 1; //Moneda de $1

            }else if((radius >= 160) && (radius<170)){

                change = change + 2; //Moneda de $2

            }else if((radius >= 170) && (radius<180)){

                change = change + 5; //Moneda de $5

            }else if((radius >= 180) && (radius<190)){

                change = change + 10; //Moneda de $10

            }else if((radius>=190)){

                change = change + 20; //Moneda de $20

            }

        }

        putText(imagen1,"Dinero total: "+to_string(change)+"Kc",Point(10,80),FONT_HERSHEY_PLAIN, 1.6, Scalar(0,0,255,255), 2);

        namedWindow( "Monedas", CV_WINDOW_NORMAL );
        imshow("Monedas", imagen1);
}
void Punto3(){
    Mat imagen2 = imread("../Data/smarties.png");
    Mat gray1;
        cvtColor(imagen2, gray1, COLOR_BGR2GRAY);
        medianBlur(gray1, gray1, 5);
        vector<Vec3f> circles1;
        HoughCircles(gray1, circles1, HOUGH_GRADIENT, 1,gray1.rows/16,100, 30, 1, 30 );
        int size = circles1.size();
        for( size_t i = 0; i < circles1.size(); i++ )
        {
            Vec3i c = circles1[i];
            Point center = Point(c[0], c[1]);
            // circle center
            circle( imagen2, center, 1, Scalar(0,100,100), 3, LINE_AA);
            // circle outline
            int radius = c[2];
            circle( imagen2, center, radius, Scalar(255,0,255), 3, LINE_AA);
        }
        Mat out3;
        vector<vector<Point> > contours;
        findContours(out3, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
        string str = to_string(size);
        putText(imagen2,"Numero de caramelos: "+str,Point(10,80),FONT_HERSHEY_PLAIN, 1, Scalar(0,0,255,255), 2);

        namedWindow( "Sparkies", CV_WINDOW_NORMAL );
        imshow("Sparkies", imagen2);
}
void Punto4(){
    Mat imagen3 = imread("../Data/mano-in.png",IMREAD_COLOR);
    Mat HSV,kernel,kernel2;
    Mat frame = Mat(590, 434, CV_8UC3);
    Mat frame2 = Mat(590, 434, CV_8UC3);

    kernel=getStructuringElement(MORPH_ELLIPSE,Size(5,5));
    kernel2=getStructuringElement(MORPH_ELLIPSE,Size(5,5));

    cvtColor(imagen3,HSV,COLOR_BGR2HSV);

    for(int i=0;i<434;i++){
        for( int j=0;j<590;j++){
            int B = HSV.at<Vec3b>(Point(i, j))[0];
            int G = HSV.at<Vec3b>(Point(i, j))[1];
            int R = HSV.at<Vec3b>(Point(i, j))[2];

            if(30<B && 140>B && 0<G && 0<R){
                frame.at<Vec3b>(Point(i, j))[0]=0;
                frame.at<Vec3b>(Point(i, j))[1]=0;
                frame.at<Vec3b>(Point(i, j))[2]=0;
            }else{
                frame.at<Vec3b>(Point(i, j))[0]=255;
                frame.at<Vec3b>(Point(i, j))[1]=255;
                frame.at<Vec3b>(Point(i, j))[2]=255;
            }
        }
    }

    namedWindow( "Mano", CV_WINDOW_NORMAL );
    imshow("Mano", frame);


    morphologyEx(frame,frame2,MORPH_CLOSE,kernel2);
    morphologyEx(frame2,frame,MORPH_OPEN,kernel);


    namedWindow( "Mano2", CV_WINDOW_NORMAL );
    imshow("Mano2", frame);

    for(int i=0;i<434;i++){
        for( int j=0;j<590;j++){
            int B = frame.at<Vec3b>(Point(i, j))[0];
            int G = frame.at<Vec3b>(Point(i, j))[1];
            int R = frame.at<Vec3b>(Point(i, j))[2];

            if(127>B && 127>G && 127>R){
                frame2.at<Vec3b>(Point(i, j))[0]=0;
                frame2.at<Vec3b>(Point(i, j))[1]=0;
                frame2.at<Vec3b>(Point(i, j))[2]=0;
            }else{
                frame2.at<Vec3b>(Point(i, j))[0]=128;
                frame2.at<Vec3b>(Point(i, j))[1]=0;
                frame2.at<Vec3b>(Point(i, j))[2]=128;
            }
        }
    }

    namedWindow( "Mano3", CV_WINDOW_NORMAL );
    imshow("Mano3", frame2);
}
void Punto5(){
    Mat lena = imread("../Data/lena.jpg");
    Mat kernel,dst;
    Mat hsv,lena_hsv;

    cvtColor(lena,lena_hsv, CV_BGR2HSV);
    namedWindow("HSV_lena", WINDOW_AUTOSIZE);
    imshow("HSV_lena",lena_hsv);

    Mat thre_lena;
    for(int i = 0; i < lena.rows;i++){
        for(int j = 0; j < lena.cols; j++){
            if((j < 185 || j > 380) || i < 200){
                lena_hsv.at<Vec3b>(i,j)[1] = 0;
                lena_hsv.at<Vec3b>(i,j)[0] = 0;
                lena_hsv.at<Vec3b>(i,j)[2] = 0;
            }
        }
    }

    Mat thre_lena_red, thre_lena_purple;

    inRange(lena_hsv,Scalar(0,30,90),Scalar(15,255,255),thre_lena_red);
    inRange(lena_hsv,Scalar(174,10,10),Scalar(179,255,255),thre_lena_purple);

    imshow("purple",thre_lena_purple);
    imshow("red",thre_lena_red);

    thre_lena =  thre_lena_red + thre_lena_purple;

    kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
    dilate(thre_lena,thre_lena,kernel,Point(-1,-1),1);

    imshow("Lena",lena);
    imshow("HSV_lena_blanco",thre_lena);

    Mat res_lena,lena_hsv_copy;
    bitwise_and(lena,lena,res_lena,thre_lena);

    cvtColor(lena,lena_hsv_copy,CV_BGR2HSV);

    for(int i = 0; i < lena.rows;i++){
        for(int j = 0; j < lena.cols; j++){
            unsigned char v = res_lena.at<Vec3b>(i,j)[2];
            if(v > 1){

                lena_hsv_copy.at<Vec3b>(i, j)[2] = 100;
            }
        }
    }

    cvtColor(lena_hsv_copy,lena,CV_HSV2BGR);

    imshow("HSV_lena_color",lena_hsv_copy);
    imshow("lena_color",lena);

    waitKey(0);
}

int main()
{
    int n;

    cout<<"Digite el numero del punto que desea vizualizar: "<<endl;
    cin>>n;

    switch (n) {

    case 1:
        Punto1();
    break;

    case 2:
        Punto2();
    break;

    case 3:
        Punto3();
    break;

    case 4:
        Punto4();
    break;

    case 5:
        Punto5();
    break;


    default:
        cout<<"no valido"<<endl;
        exit(-1);

    }
    waitKey(0);
    return 0;
}
