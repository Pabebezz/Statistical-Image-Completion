#include "Include/graphcut.h"

cimg_library::CImg<unsigned char> graphcut(cimg_library::CImg<unsigned char> image,int** tabVect,int xmin,int xmax,int ymin,int ymax,int w,float beta,int nb)
{
    cout<<"Graphcut:"<<endl;
    int width = image.width();
    int height = image.height();
    int nb2=nb;
    int widthZone = xmax-xmin+1;
    int heightZone = ymax-ymin+1;
    int num_pixels = widthZone*heightZone;
    int* result = new int[num_pixels];
    int xPix;
    int yPix;
    div_t divresult;
    int x;
    int y;


    for(int i=0; i<nb; i++)
    {
        if ((xmax+tabVect[i][0])>=width || (xmin+tabVect[i][0])<0 || (ymax+tabVect[i][1])>=height || (ymin+tabVect[i][1])<0)
        {
            nb2=nb-1;
        }
    }

    int** newTab= new int* [nb2];
    nb2=0;

    for(int i=0; i<nb; i++)
    {
        if ((xmax+tabVect[i][0])>=width || (xmin+tabVect[i][0])<0 || (ymax+tabVect[i][1])>=height || (ymin+tabVect[i][1])<0)
        {
            nb2+=1;
        }
        else
        {
            newTab[i-nb2]=new int [2];
            newTab[i-nb2][0]=tabVect[i][0];
            newTab[i-nb2][1]=tabVect[i][1];
        }
    }

    nb2=nb-nb2;



    try
    {
        GCoptimizationGridGraph* gc = new GCoptimizationGridGraph(widthZone,heightZone,nb2);
        for(int i=0; i<num_pixels; i++)
        {
            for(int j=0; j<nb2; j++)
            {
                divresult = div (i,widthZone);
                xPix = divresult.rem;
                yPix = divresult.quot;
                x=xPix+xmin;
                y=yPix+ymin;


                gc->setDataCost(i,j,((abs((image.atXY(x,y,0))-(image.atXY(x+newTab[j][0],y+newTab[j][1],0))) + abs((image.atXY(x,y,1))-(image.atXY(x+newTab[j][0],y+newTab[j][1],1))) + abs((image.atXY(x,y,2))-(image.atXY(x+newTab[j][0],y+newTab[j][1],2))))*min(heightZone,widthZone))/(1+(min(min(min(xPix,yPix),heightZone-1-yPix),widthZone-1-xPix))));

            }

        }


        for (int l1=0; l1<nb2; l1++)
        {
            for(int l2=0; l2<nb2; l2++)
            {

                if(l1==l2)
                {
                    gc->setSmoothCost(l1,l2,-beta*255);
                }
                else gc->setSmoothCost(l1,l2,0);
            }

        }

        gc->swap(2);
        for(int i = 0; i<num_pixels; i++)
        {
            result[i] = gc->whatLabel(i);

        }
        delete gc;

        return switchImage(image,newTab,result,xmin,xmax,ymin,ymax);
    }
    catch(GCException e)
    {
        e.Report();
    }

}
