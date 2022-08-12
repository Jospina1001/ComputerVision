#include <stdint.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdio.h>

#include "opencv2/imgcodecs.hpp"
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include "opencv2/core/utility.hpp"




using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;
using std::cout;
using std::endl;

using cv::BRISK;

String face_cascade_name ="../data/haarcascades/haarcascade_frontalface_alt.xml";
String eyes_cascade_name ="../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;


Mat FaceDetector(Mat target);

int main()
{
    //-- 1. Load the cascades

    if( !face_cascade.load( face_cascade_name ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };
    if( !eyes_cascade.load( eyes_cascade_name ) )
    {
        cout << "--(!)Error loading eyes cascade\n";
        return -1;
    };


    Mat objeto,escena ;
    objeto = imread("../data/book.png", IMREAD_GRAYSCALE);
    escena = imread("../data/entorno.PNG",IMREAD_GRAYSCALE);
//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//
    Mat face = FaceDetector(objeto);
    int thresh = 15;

    Ptr<BRISK> detector = BRISK::create(thresh);
    Ptr<BRISK> detector_scene = BRISK::create(thresh);


    std::vector<KeyPoint> keypoints_scene;
    Mat descriptors_scene;
    std::vector<KeyPoint> keypoints_object;
    Mat descriptors_object;



    detector_scene->detectAndCompute(escena, noArray() ,keypoints_scene, descriptors_scene);
    detector->detectAndCompute(face, noArray(),keypoints_object,descriptors_object);

    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_SL2);
    std::vector<std::vector<DMatch>> knn_matcher;

    matcher->knnMatch(descriptors_object,descriptors_scene,knn_matcher,2);

    const float ratio = 0.99f;
    std::vector<DMatch> good_matches;
    for(size_t i = 0; i < knn_matcher.size(); i++){
        if(knn_matcher[i][0].distance < ratio * knn_matcher[i][1].distance){
            good_matches.push_back(knn_matcher[i][0]);
        }
    }

    Mat img_match;
    std::vector<char> match_mask(good_matches.size(),1);

    drawMatches(face,keypoints_object,escena,keypoints_scene,good_matches, img_match,Scalar::all(-1),Scalar::all(-1)
                ,match_mask,DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    imshow("BRISK", img_match);

//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//
    Ptr<FREAK> detector_freak_object = FREAK::create();
    Ptr<FREAK> detector_scene_freak = FREAK::create();
    //detector_freak_object->compute();
   // detector_freak_object->detect();//Extrae key points y el compute calcula las caracteristicas visuales
    detector_freak_object->compute(escena,keypoints_scene,descriptors_scene);
    detector_scene_freak->compute(face,keypoints_object,descriptors_object);

    Ptr<DescriptorMatcher> matcher_freak = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_SL2);

    std::vector<std::vector<DMatch>> knn_matcher_freak;
    matcher_freak->knnMatch(descriptors_object,descriptors_scene,knn_matcher_freak,3);

    const float ratio_freak = 2.0f;
    std::vector<DMatch> good_matches_freak;
    for(size_t i = 0; i < knn_matcher_freak.size(); i++){
        if(knn_matcher_freak[i][0].distance < ratio_freak * knn_matcher_freak[i][1].distance){
            good_matches_freak.push_back(knn_matcher_freak[i][0]);
        }
    }

    Mat img_match_FREAK;
    std::vector<char> match_mask_freak(good_matches_freak.size(),1);

    drawMatches(face,keypoints_object,escena,keypoints_scene,good_matches_freak, img_match_FREAK,Scalar::all(-1),Scalar::all(-1)
                ,match_mask_freak,DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    imshow("Freak", img_match_FREAK);

//---------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------VIDEO------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//

    VideoCapture capture("../data/blais.mp4");
     if (!capture.isOpened())
        {
        cout << "Unable to open file!" << endl;
        return 0;
        }
     Mat img_scene,img_scene1,img_scen_gris;

     //namedWindow("video",WINDOW_AUTOSIZE);


 while(true){
     capture >> img_scene;
     capture >> img_scene1;

     cvtColor(img_scene,img_scen_gris,COLOR_BGR2GRAY);

      if (img_scen_gris.empty() ){
          cout << "no image frame;" << endl;
          break;
      }
      //imshow("video", img_scen_gris);
      std::vector<KeyPoint> keypoints_scene;
      Mat descriptors_scene;
      std::vector<KeyPoint> keypoints_object;
      Mat descriptors_object;

      detector_scene->detectAndCompute(img_scen_gris, noArray() ,keypoints_scene, descriptors_scene);
      detector->detectAndCompute(face, noArray(),keypoints_object,descriptors_object);

      std::vector<std::vector<DMatch>> knn_matcher;
      matcher->knnMatch(descriptors_object,descriptors_scene,knn_matcher,2);

      std::vector<DMatch> good_matches;

      for(size_t i = 0; i < knn_matcher.size(); i++){
          if(knn_matcher[i][0].distance < ratio * knn_matcher[i][1].distance){
              good_matches.push_back(knn_matcher[i][0]);
          }
      }
  //---------------------------------------------------------------------------------------------------------------------//
  //---------------------------------------------------------------------------------------------------------------------//


        Mat img_match;

        //-- Localize the object
        std::vector<Point2f> detector;
        std::vector<Point2f> detector_scene;
        for( size_t i = 0; i < good_matches.size(); i++ )
        {
        //-- Get the keypoints from the good matches
            detector.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
            detector_scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
        }
        Mat H1 = findHomography( detector, detector_scene, RANSAC );
        //--- Get the corners from the image_1 ( the object to be "detected" )
        std::vector<Point2f> obj_cornersd(4);
        obj_cornersd[0] = Point2f(0, 0);
        obj_cornersd[1] = Point2f( (float)face.cols, 0 );
        obj_cornersd[2] = Point2f( (float)face.cols, (float)face.rows );
        obj_cornersd[3] = Point2f( 0, (float)face.rows );
        std::vector<Point2f> scene_cornersd(4);
        perspectiveTransform( obj_cornersd, scene_cornersd, H1);
        std::vector<DMatch>matcherr;
        for( size_t i = 0; i < good_matches.size(); i++)
        {
            if((keypoints_scene[good_matches[i].trainIdx].pt.x > (scene_cornersd[0].x)||
                keypoints_scene[good_matches[i].trainIdx].pt.x > (scene_cornersd[1].x)||
                keypoints_scene[good_matches[i].trainIdx].pt.x > (scene_cornersd[2].x)||
                keypoints_scene[good_matches[i].trainIdx].pt.x > (scene_cornersd[3].x))&&
               (keypoints_scene[good_matches[i].trainIdx].pt.x < (scene_cornersd[0].x)||
                keypoints_scene[good_matches[i].trainIdx].pt.x < (scene_cornersd[1].x)||
                keypoints_scene[good_matches[i].trainIdx].pt.x < (scene_cornersd[2].x)||
                keypoints_scene[good_matches[i].trainIdx].pt.x < (scene_cornersd[3].x))&&
               (keypoints_scene[good_matches[i].trainIdx].pt.y > (scene_cornersd[0].y)||
                keypoints_scene[good_matches[i].trainIdx].pt.y > (scene_cornersd[1].y)||
                keypoints_scene[good_matches[i].trainIdx].pt.y > (scene_cornersd[2].y)||
                keypoints_scene[good_matches[i].trainIdx].pt.y > (scene_cornersd[3].y))&&
               (keypoints_scene[good_matches[i].trainIdx].pt.y < (scene_cornersd[0].y)||
                keypoints_scene[good_matches[i].trainIdx].pt.y < (scene_cornersd[1].y)||
                keypoints_scene[good_matches[i].trainIdx].pt.y < (scene_cornersd[2].y)||
                keypoints_scene[good_matches[i].trainIdx].pt.y < (scene_cornersd[3].y)))
            {
                matcherr.push_back(good_matches[i]);
            }
        }

        drawMatches(face,keypoints_object,img_scene1,keypoints_scene,matcherr,img_match,Scalar::all(-1),Scalar::all(-1)
                    ,std::vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

        //-- Draw lines between the corners (the mapped object in the scene - image_2 )
        line( img_match, scene_cornersd[0] + Point2f((float)face.cols, 0),
              scene_cornersd[1] + Point2f((float)face.cols, 0), Scalar(0, 255, 0), 4 );
        line( img_match, scene_cornersd[1] + Point2f((float)face.cols, 0),
              scene_cornersd[2] + Point2f((float)face.cols, 0), Scalar( 0, 255, 0), 4 );
        line( img_match, scene_cornersd[2] + Point2f((float)face.cols, 0),
              scene_cornersd[3] + Point2f((float)face.cols, 0), Scalar( 0, 255, 0), 4 );
        line( img_match, scene_cornersd[3] + Point2f((float)face.cols, 0),
              scene_cornersd[0] + Point2f((float)face.cols, 0), Scalar( 0, 255, 0), 4 );

        imshow("homography_Brisk",img_match);
        imshow("Cara",face);


//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//

        detector_freak_object->compute(img_scen_gris,keypoints_scene,descriptors_scene);
        detector_scene_freak->compute(face,keypoints_object,descriptors_object);


        std::vector<std::vector<DMatch>> knn_matcher_freak;
        matcher_freak->knnMatch(descriptors_object,descriptors_scene,knn_matcher_freak,3);


        std::vector<DMatch> good_matches_freak;
        for(size_t i = 0; i < knn_matcher_freak.size(); i++){
            if(knn_matcher_freak[i][0].distance < ratio_freak * knn_matcher_freak[i][1].distance){
                good_matches_freak.push_back(knn_matcher_freak[i][0]);
            }
        }

        Mat img_match_FREAK;

        //-- Localize the object
        std::vector<Point2f> detector_freak_object;
        std::vector<Point2f> detector_scene_freak;
        for( size_t i = 0; i < good_matches_freak.size(); i++ )
        {
            //-- Get the keypoints from the good matches
            detector_freak_object.push_back( keypoints_object[ good_matches_freak[i].queryIdx ].pt );
            detector_scene_freak.push_back( keypoints_scene[ good_matches_freak[i].trainIdx ].pt );
        }
        Mat H = findHomography( detector_freak_object, detector_scene_freak, RANSAC );
        //-- Get the corners from the image_1 ( the object to be "detected" )
        std::vector<Point2f> obj_cornersf(4);
        obj_cornersf[0] = Point2f(0, 0);
        obj_cornersf[1] = Point2f( (float)face.cols, 0 );
        obj_cornersf[2] = Point2f( (float)face.cols, (float)face.rows );
        obj_cornersf[3] = Point2f( 0, (float)face.rows );
        std::vector<Point2f> scene_cornersf(4);
        perspectiveTransform( obj_cornersf, scene_cornersf, H);
        std::vector<DMatch>matcherre;
        for( size_t i = 0; i < good_matches_freak.size(); i++)
        {
            if((keypoints_scene[good_matches_freak[i].trainIdx].pt.x > (scene_cornersf[0].x)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.x > (scene_cornersf[1].x)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.x > (scene_cornersf[2].x)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.x > (scene_cornersf[3].x))&&
               (keypoints_scene[good_matches_freak[i].trainIdx].pt.x < (scene_cornersf[0].x)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.x < (scene_cornersf[1].x)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.x < (scene_cornersf[2].x)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.x < (scene_cornersf[3].x))&&
               (keypoints_scene[good_matches_freak[i].trainIdx].pt.y > (scene_cornersf[0].y)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.y > (scene_cornersf[1].y)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.y > (scene_cornersf[2].y)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.y > (scene_cornersf[3].y))&&
               (keypoints_scene[good_matches_freak[i].trainIdx].pt.y < (scene_cornersf[0].y)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.y < (scene_cornersf[1].y)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.y < (scene_cornersf[2].y)||
                keypoints_scene[good_matches_freak[i].trainIdx].pt.y < (scene_cornersf[3].y)))
            {
                matcherre.push_back(good_matches_freak[i]);
            }
        }

        drawMatches(face,keypoints_object,img_scene1,keypoints_scene,matcherre, img_match_FREAK,Scalar::all(-1),Scalar::all(-1)
                    ,std::vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
        //-- Draw lines between the corners (the mapped object in the scene - image_2 )
        line( img_match_FREAK, scene_cornersf[0] + Point2f((float)face.cols, 0),
              scene_cornersf[1] + Point2f((float)face.cols, 0), Scalar(0, 255, 0), 4 );
        line( img_match_FREAK, scene_cornersf[1] + Point2f((float)face.cols, 0),
              scene_cornersf[2] + Point2f((float)face.cols, 0), Scalar( 0, 255, 0), 4 );
        line( img_match_FREAK, scene_cornersf[2] + Point2f((float)face.cols, 0),
              scene_cornersf[3] + Point2f((float)face.cols, 0), Scalar( 0, 255, 0), 4 );
        line( img_match_FREAK, scene_cornersf[3] + Point2f((float)face.cols, 0),
              scene_cornersf[0] + Point2f((float)face.cols, 0), Scalar( 0, 255, 0), 4 );

        imshow("Homography_Freak",img_match_FREAK);

//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------DETECTOR DE CARA--------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//
                 Mat frame_gray;
                 cvtColor(img_scene, frame_gray, COLOR_BGR2GRAY);
                 equalizeHist( frame_gray, frame_gray );
                 //-- Detect faces
                 std::vector<Rect> faces;
                 face_cascade.detectMultiScale(frame_gray, faces);
                 for ( size_t i = 0; i < faces.size(); i++ )
                 {
                     Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
                     ellipse( img_scene, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
                     Mat faceROI = frame_gray( faces[i] );
                     //-- In each face, detect eyes
                     std::vector<Rect> eyes;
                     eyes_cascade.detectMultiScale( faceROI, eyes );
                     for ( size_t j = 0; j < eyes.size(); j++ )
                     {
                         Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
                         int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
                         circle( img_scene, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
                     }
                 }
                 //-- Show what you got
                 imshow( "Deteccion de rostro", img_scene );

               int keyboard = waitKey(30);
               if ( keyboard == 'q' || keyboard == 27 )
                   break;

           //===================================================Fin lee video ============================================================================================================================
           }
    waitKey(0);
    capture.release();
    img_match.release();
    img_match_FREAK.release();
    return 0;
    }


Mat FaceDetector( Mat target)
{

    equalizeHist(target,target);
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(target,faces);

    Mat face_indent;

    for(size_t i = 0; i < faces.size();i++){
        rectangle(target,faces[i],Scalar(255,0,255),4,LINE_8,0);
        face_indent = target( faces[i] );
    }

    return face_indent;
}

