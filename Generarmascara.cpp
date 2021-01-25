#include <opencv.hpp>
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;
using namespace std;

Mat image, original;

int connectivity = 4;
int newMaskVal = 255;

int main (int arcg, char *argv[]){
    cout << "Prueba - Marcela Zhagui" << endl;
    Mat imgen1 = imread("ZHAGUI_PUGO_MARCELA_CATALINA-1.png");
    Mat imgen2 = imread("ZHAGUI_PUGO_MARCELA_CATALINA-2.png");

    Mat circulo = imgen2.clone();
    Mat resta;
    Vec3b pixel;

    circle(circulo,Point(72,96),18,Scalar(255,255,255),1); 
    absdiff(imgen2,circulo,resta);
    Mat resultado;

    int nPixelesTotales = 0;
    //int nPixelesDerecha = 0;
    //int nPixelesIzquierda = 0;
    int nPixelesCirculo = 0;
  

   // for (int i =0; i < imagen1.rows ; i++){
      //  for(int j=0; j<imagen1.cols;j++){
            nPixelesTotales++;
        //}
    //}

    if (resultado.empty()){
        resultado = Mat(Size(imgen1.cols,imgen1.rows), CV_8UC3, Scalar(255,255,255));
    }

    for (int i = 0; i < resta.rows; i++){
        int min =0;
        int max = imgen1.cols;
        for (int j = 0; j < resta.cols; j++){
            pixel = resta.at<Vec3b>(i,j);
            if (pixel[0] > 0 && pixel[1] > 0 && pixel[2] > 0){
                if (min < j) min =j;
                if (max > j) max =j;
            }
        }
        
        for (int j = 0; j < resta.cols; j++){
            pixel = resta.at<Vec3b>(i,j);
            if (j> min || j < max){
                resultado.at<Vec3b>(i,j) = imgen1.at<Vec3b>(i,j);
            }else{
                resultado.at<Vec3b>(i,j) = imgen2.at<Vec3b>(i,j);
            }       
        }
    }
    
    namedWindow("IMGEN1", WINDOW_AUTOSIZE);
    namedWindow("IMGEN2", WINDOW_AUTOSIZE);
    namedWindow("Resultado", WINDOW_AUTOSIZE);

    imshow("IMG1", imgen1);
    imshow("IMG2", imgen2);
    imshow("Resultado", resultado);
    imwrite("Restaurar.png",resultado);
    
    waitKey(0);
    destroyAllWindows();

    return 0;
}
