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


using namespace cv;
using namespace std;

using namespace cv::xfeatures2d;
using std::cout;
using std::endl;

int Number;

void drawText(Mat & image);

std::vector<DMatch> good_matches;
Mat img_object,img_scene;

//-- Draw matches
Mat img_matches;
std::vector<KeyPoint> keypoints_object,keypoints_scene;

int main()
{
   string NamFil_objet,NamFil_scene;

   NamFil_objet="../Data/box.png";
   img_object=imread(NamFil_objet,IMREAD_GRAYSCALE);

   NamFil_scene="../Data/box_in_scene.png";
   img_scene=imread(NamFil_scene,IMREAD_GRAYSCALE);

//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//
   int nfeatures = 0;
   int n_OctaveLayers = 3;
   double contrastThreshold = 0.04;
   double edgeThreshold = 10;
   double sigma = 1.6;

   Ptr<SIFT> detector_SIFT=SIFT::create(nfeatures,n_OctaveLayers,contrastThreshold,edgeThreshold,sigma); //Keypoints SIFT
//---------------------------------------------------------------------------------------------------------------------//
   int thresh=30;
   int octavesb=3;
   float patternScaleb=1.0f;

   Ptr<BRISK> detector_BRISK=BRISK::create(thresh,octavesb,patternScaleb); //Keypoints BRISK
//---------------------------------------------------------------------------------------------------------------------//
   Ptr<FREAK> detector_FREAK=FREAK::create(); // Keypoints Freak
//---------------------------------------------------------------------------------------------------------------------//
                               // con 50 en hessina me ngenreo 773 keypoints
   double hessianThreshold=50; // con 100 en hessina me ngenreo 400 keypoints
                               // con 500 en hessina me ngenreo 159 keypoints
   int nOctaves = 4;
   int nOctaveLayers = 3;
   bool extended = false;
   bool upright = false;

   Ptr<SURF> detector_SURF = SURF::create( hessianThreshold,nOctaves,nOctaveLayers,extended,upright );//Keypoints SURF
//---------------------------------------------------------------------------------------------------------------------//
   nfeatures=500;
   float scaleFactor=1.2f;
   int nlevels=8;
   edgeThreshold=31;
   int firstLevel=0;
   int WTA_K=2;
   ORB::ScoreType scoreType=ORB::HARRIS_SCORE;
   int patchSize=31;
   int fastThreshold=20;

   Ptr<ORB> detector_ORB = ORB::create(nfeatures, scaleFactor,nlevels, edgeThreshold,firstLevel, WTA_K, scoreType, patchSize, fastThreshold);//Keypoints ORB
//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//

   std::vector<KeyPoint> keypoints_object_surf, keypoints_scene_surf;
   //std::vector<KeyPoint> keypoints_object_sift, keypoints_scene_sift;
   //std::vector<KeyPoint> keypoints_object_brisk, keypoints_scene_brisk;
   //std::vector<KeyPoint> keypoints_object_freak, keypoints_scene_freak;
   //std::vector<KeyPoint> keypoints_object_orb, keypoints_scene_orb;

   //std::vector<KeyPoint> keypoints_object_surf_sift, keypoints_scene_surf_sift;
   //std::vector<KeyPoint> keypoints_object_sift_surf, keypoints_scene_sift_surf;
   //std::vector<KeyPoint> keypoints_object_surf_brisk, keypoints_scene_surf_brisk;
   //std::vector<KeyPoint> keypoints_object_brisk_surf, keypoints_scene_brisk_surf;
   //std::vector<KeyPoint> keypoints_object_surf_freak, keypoints_scene_surf_freak;
   //std::vector<KeyPoint> keypoints_object_freak_surf, keypoints_scene_freak_surf;
   //std::vector<KeyPoint> keypoints_object_surf_orb, keypoints_scene_surf_orb;
   //std::vector<KeyPoint> keypoints_object_orb_surf, keypoints_scene_orb_surf;

   //std::vector<KeyPoint> keypoints_object_sift_brisk, keypoints_scene_sift_brisk;
   //std::vector<KeyPoint> keypoints_object_brisk_sift, keypoints_scene_brisk_sift;
   //std::vector<KeyPoint> keypoints_object_sift_orb, keypoints_scene_sift_orb;
   //std::vector<KeyPoint> keypoints_object_orb_sift, keypoints_scene_orb_sift;

   std::vector<KeyPoint> keypoints_object_orb_brisk, keypoints_scene_orb_brisk;
   std::vector<KeyPoint> keypoints_object_brisk_orb, keypoints_scene_brisk_orb;



   Mat descriptors_object_surf_surf, descriptors_scene_surf_surf;
   //Mat descriptors_object_sift_sift, descriptors_scene_sift_sift;
   //Mat descriptors_object_brisk_brisk, descriptors_scene_brisk_brisk;
   //Mat descriptors_object_freak_freak, descriptors_scene_freak_freak;
   //Mat descriptors_object_orb_orb, descriptors_scene_orb_orb;

   //Mat descriptors_object_surf_sift, descriptors_scene_surf_sift;
   //Mat descriptors_object_sift_surf, descriptors_scene_sift_surf;
   //Mat descriptors_object_surf_brisk, descriptors_scene_surf_brisk;
   //Mat descriptors_object_brisk_surf, descriptors_scene_brisk_surf;
   //Mat descriptors_object_surf_freak, descriptors_scene_surf_freak;
   //Mat descriptors_object_freak_surf, descriptors_scene_freak_surf;
   //Mat descriptors_object_surf_orb, descriptors_scene_surf_orb;
   //Mat descriptors_object_orb_surf, descriptors_scene_orb_surf;

   //Mat descriptors_object_sift_brisk, descriptors_scene_sift_brisk;
   //Mat descriptors_object_brisk_sift, descriptors_scene_brisk_sift;
   //Mat descriptors_object_sift_orb, descriptors_scene_sift_orb;
   //Mat descriptors_object_orb_sift, descriptors_scene_orb_sift;

   Mat descriptors_object_orb_brisk, descriptors_scene_orb_brisk;
   Mat descriptors_object_brisk_orb, descriptors_scene_brisk_orb;


//---------------------------------------------------------------------------------------------------------------------//

    //SURF_SURF:
    detector_SURF->detectAndCompute(img_object,noArray(),keypoints_object_surf,descriptors_object_surf_surf);
    detector_SURF->detectAndCompute(img_scene,noArray(),keypoints_scene_surf,descriptors_scene_surf_surf);

    //SIFT_SIFT:
    //detector_SIFT->detectAndCompute(img_object,noArray(),keypoints_object_sift,descriptors_object_sift_sift);
    //detector_SIFT->detectAndCompute(img_scene,noArray(),keypoints_scene_sift,descriptors_scene_sift_sift);

    //BRISK_BRISK:
    //detector_BRISK->detectAndCompute(img_object,noArray(),keypoints_object_brisk,descriptors_object_brisk_brisk);
    //detector_BRISK->detectAndCompute(img_scene,noArray(),keypoints_scene_brisk,descriptors_scene_brisk_brisk);

    //FREAK_FREAK:
    //detector_FREAK->detectAndCompute(img_object,noArray(),keypoints_object_freak,descriptors_object_freak_freak);
    //detector_FREAK->detectAndCompute(img_scene,noArray(),keypoints_scene_freak,descriptors_scene_freak_freak);

    //ORB_ORB:
    //detector_ORB->detectAndCompute(img_object,noArray(),keypoints_object_orb,descriptors_object_orb_orb);
    //detector_ORB->detectAndCompute(img_scene,noArray(),keypoints_scene_orb,descriptors_scene_orb_orb);

    //SURF_SIFT:
    //detector_SURF->detect(img_object,keypoints_object_surf_sift,descriptors_object_surf_sift);
    //detector_SIFT->compute(img_object,keypoints_object_surf_sift,descriptors_object_surf_sift);

    //detector_SURF->detect(img_scene,keypoints_scene_surf_sift,descriptors_scene_surf_sift);
    //detector_SIFT->compute(img_scene,keypoints_scene_surf_sift,descriptors_scene_surf_sift);

    //SIFT_SURF
    //detector_SIFT->detect(img_object,keypoints_object_sift_surf,descriptors_object_sift_surf);
    //detector_SURF->compute(img_object,keypoints_object_sift_surf,descriptors_object_sift_surf);

    //detector_SIFT->detect(img_scene,keypoints_scene_sift_surf,descriptors_scene_sift_surf);
    //detector_SURF->compute(img_scene,keypoints_scene_sift_surf,descriptors_scene_sift_surf);

    //SURF_BRISK:
    //detector_SURF->detect(img_object,keypoints_object_surf_brisk,descriptors_object_surf_brisk);
    //detector_BRISK->compute(img_object,keypoints_object_surf_brisk,descriptors_object_surf_brisk);

    //detector_SURF->detect(img_scene,keypoints_scene_surf_brisk,descriptors_scene_surf_brisk);
    //detector_BRISK->compute(img_scene,keypoints_scene_surf_brisk,descriptors_scene_surf_brisk);

    //BRISK_SURF:
    //detector_BRISK->detect(img_object,keypoints_object_brisk_surf,descriptors_object_brisk_surf);
    //detector_SURF->compute(img_object,keypoints_object_brisk_surf,descriptors_object_brisk_surf);

    //detector_BRISK->detect(img_scene,keypoints_scene_brisk_surf,descriptors_scene_brisk_surf);
    //detector_SURF->compute(img_scene,keypoints_scene_brisk_surf,descriptors_scene_brisk_surf);

    //SURF_FREAK:
    //detector_SURF->detect(img_object,keypoints_object_surf_freak,descriptors_object_surf_freak);
    //detector_FREAK->compute(img_object,keypoints_object_surf_freak,descriptors_object_surf_freak);

    //detector_SURF->detect(img_scene,keypoints_scene_surf_freak,descriptors_scene_surf_freak);
    //detector_FREAK->compute(img_scene,keypoints_scene_surf_freak,descriptors_scene_surf_freak);

    //FREAK_SURF:
    //detector_FREAK->detect(img_object,keypoints_object_freak_surf,descriptors_object_freak_surf);
    //detector_SURF->compute(img_object,keypoints_object_freak_surf,descriptors_object_freak_surf);

    //detector_FREAK->detect(img_scene,keypoints_scene_freak_surf,descriptors_scene_freak_surf);
    //detector_SURF->compute(img_scene,keypoints_scene_freak_surf,descriptors_scene_freak_surf);

    //SURF_ORB:
    //detector_SURF->detect(img_object,keypoints_object_surf_orb,descriptors_object_surf_orb);
    //detector_ORB->compute(img_object,keypoints_object_surf_orb,descriptors_object_surf_orb);

    //detector_SURF->detect(img_scene,keypoints_scene_surf_orb,descriptors_scene_surf_orb);
    //detector_ORB->compute(img_scene,keypoints_scene_surf_orb,descriptors_scene_surf_orb);

    //ORB_SURF:
    //detector_ORB->detect(img_object,keypoints_object_orb_surf,descriptors_object_orb_surf);
    //detector_SURF->compute(img_object,keypoints_object_orb_surf,descriptors_object_orb_surf);

    //detector_ORB->detect(img_scene,keypoints_scene_orb_surf,descriptors_scene_orb_surf);
    //detector_SURF->compute(img_scene,keypoints_scene_orb_surf,descriptors_scene_orb_surf);

    //SIFT_BRISK
    //detector_SIFT->detect(img_object,keypoints_object_sift_brisk,descriptors_object_sift_brisk);
    //detector_BRISK->compute(img_object,keypoints_object_sift_brisk,descriptors_object_sift_brisk);

    //detector_SIFT->detect(img_scene,keypoints_scene_sift_brisk,descriptors_scene_sift_brisk);
    //detector_BRISK->compute(img_scene,keypoints_scene_sift_brisk,descriptors_scene_sift_brisk);

    //BRISK_SIFT
    //detector_BRISK->detect(img_object,keypoints_object_brisk_sift,descriptors_object_brisk_sift);
    //detector_SIFT->compute(img_object,keypoints_object_brisk_sift,descriptors_object_brisk_sift);

    //detector_BRISK->detect(img_scene,keypoints_scene_brisk_sift,descriptors_scene_brisk_sift);
    //detector_SIFT->compute(img_scene,keypoints_scene_brisk_sift,descriptors_scene_brisk_sift);

    //SIFT_ORB
    //detector_SIFT->detect(img_object,keypoints_object_sift_orb,descriptors_object_sift_orb);
    //detector_ORB->compute(img_object,keypoints_object_sift_orb,descriptors_object_sift_orb);

    //detector_SIFT->detect(img_scene,keypoints_scene_sift_orb,descriptors_scene_sift_orb);
    //detector_ORB->compute(img_scene,keypoints_scene_sift_orb,descriptors_scene_sift_orb);

    //ORB_SIFT
    //detector_ORB->detect(img_object,keypoints_object_orb_sift,descriptors_object_orb_sift);
    //detector_SIFT->compute(img_object,keypoints_object_orb_sift,descriptors_object_orb_sift);

    //detector_ORB->detect(img_scene,keypoints_scene_orb_sift,descriptors_scene_orb_sift);
    //detector_SIFT->compute(img_scene,keypoints_scene_orb_sift,descriptors_scene_orb_sift);

    //ORB_BRISK
    //detector_ORB->detect(img_object,keypoints_object_orb_brisk,descriptors_object_orb_brisk);
    //detector_BRISK->compute(img_object,keypoints_object_orb_brisk,descriptors_object_orb_brisk);

    //detector_ORB->detect(img_scene,keypoints_scene_orb_brisk,descriptors_scene_orb_brisk);
    //detector_BRISK->compute(img_scene,keypoints_scene_orb_brisk,descriptors_scene_orb_brisk);

    //BRISK_ORB
    detector_BRISK->detect(img_object,keypoints_object_brisk_orb,descriptors_object_brisk_orb);
    detector_ORB->compute(img_object,keypoints_object_brisk_orb,descriptors_object_brisk_orb);

    detector_BRISK->detect(img_scene,keypoints_scene_brisk_orb,descriptors_scene_brisk_orb);
    detector_ORB->compute(img_scene,keypoints_scene_brisk_orb,descriptors_scene_brisk_orb);


//---------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//

    Ptr<DescriptorMatcher> matcher=DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    std::vector< std::vector<DMatch> > knn_matches;

    matcher->knnMatch(descriptors_object_surf_surf, descriptors_scene_surf_surf,knn_matches, 2 ); //CAMBIAR


   //-- Filter matches using the Lowe's ratio test
   const float ratio_thresh = 0.75f;

   for (size_t i = 0; i < knn_matches.size(); i++)
   {
       if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
       {
           good_matches.push_back(knn_matches[i][0]);
       }
   }




   Number = good_matches.size();
   cout<<"Matches:"<<Number<<endl;

   keypoints_object=keypoints_object_surf;
   keypoints_scene=keypoints_scene_surf;


//---------------------------------------------------------------------------------------------------------------------//

   //-- Draw matches
   Mat img_matches;
   drawMatches( img_object, keypoints_object, img_scene, keypoints_scene, good_matches, img_matches );
   //-- Show detected matches
   imshow("Matches", img_matches );


   //-- Localize the object
   std::vector<Point2f> obj;
   std::vector<Point2f> scene;
   for( size_t i = 0; i < good_matches.size(); i++ )
   {
       //-- Get the keypoints from the good matches
       obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
       scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
   }
   Mat H = findHomography( obj, scene, RANSAC );
   //-- Get the corners from the image_1 ( the object to be "detected" )
   std::vector<Point2f> obj_corners(4);
   obj_corners[0] = Point2f(0, 0);
   obj_corners[1] = Point2f( (float)img_object.cols, 0 );
   obj_corners[2] = Point2f( (float)img_object.cols, (float)img_object.rows );
   obj_corners[3] = Point2f( 0, (float)img_object.rows );
   std::vector<Point2f> scene_corners(4);
   perspectiveTransform( obj_corners, scene_corners, H);
   //-- Draw lines between the corners (the mapped object in the scene - image_2 )
   line( img_matches, scene_corners[0] + Point2f((float)img_object.cols, 0),
         scene_corners[1] + Point2f((float)img_object.cols, 0), Scalar(0, 255, 0), 4 );
   line( img_matches, scene_corners[1] + Point2f((float)img_object.cols, 0),
         scene_corners[2] + Point2f((float)img_object.cols, 0), Scalar( 0, 255, 0), 4 );
   line( img_matches, scene_corners[2] + Point2f((float)img_object.cols, 0),
         scene_corners[3] + Point2f((float)img_object.cols, 0), Scalar( 0, 255, 0), 4 );
   line( img_matches, scene_corners[3] + Point2f((float)img_object.cols, 0),
         scene_corners[0] + Point2f((float)img_object.cols, 0), Scalar( 0, 255, 0), 4 );
   //-- Show detected matches
   imshow("Good Matches & Object detection", img_matches );

   waitKey();
   return 0;

}
