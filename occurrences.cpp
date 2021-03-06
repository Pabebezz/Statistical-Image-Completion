#include "Include/occurrences.h"

int** occurrenceOffsets(int** offsetField,cimg_library::CImg<unsigned char> image,int w,int nb)
{
    cout<<"Keep only good vectors"<<endl;
    int* tabNbOccur = new int [nb];
    int** tabVect = new int* [nb];
    int width = image.width();
    int height = image.height();
    int sizeField = (width-w+1)*(height-w+1);
    int** occurrence=new int* [2*width];
    int* minimum;
    int position;
    int currentVal;

    for (int i =0; i<nb; i++)
    {
        tabVect[i]=new int[2];
        tabNbOccur[i]=0;
    }



    for (int i =0; i<2*width; i++)
    {
        occurrence[i]=new int[2*height];
        for(int j=0; j<2*height; j++)
        {
            (occurrence[i])[j]=0;
        }
    }


    for (int k=0; k< sizeField; k++)
    {
        (occurrence[((offsetField[k])[0])+width])[((offsetField[k])[1])+height]+=1;
    }

    for(int i =0; i<2*width; i++)
    {
        for(int j =0; j<2*height; j++)
        {
            minimum=min_element(tabNbOccur,tabNbOccur+nb);
            position=minimum-tabNbOccur;
            currentVal=(occurrence[i])[j];
            if (currentVal>*minimum)
            {
                tabNbOccur[position]=currentVal;
                tabVect[position][0]=i-width;
                tabVect[position][1]=j-height;
            }
        }
    }


    delete [] tabNbOccur;
    delete [] occurrence;

    return tabVect;
}
