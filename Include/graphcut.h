#include <iostream>
#include "CImg.h"
#include <stdlib.h> /* div, div_t */
#include "GCO/GCoptimization.h"
#include "switch.h"

using namespace std;

cimg_library::CImg<unsigned char> graphcut(cimg_library::CImg<unsigned char> image,int** tabVect,int xmin,int xmax,int ymin,int ymax,int w,float beta,int nb);
