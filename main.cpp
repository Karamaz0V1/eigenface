/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include <visp/vpImageIo.h>
#define IMGDIR "../"
using namespace std;

void load();
void loadImage(vpImage<unsigned char> & I, int visage, int image);

int main( int argc, char* argv[] )
{
    int ret = 0;
    
    load();

    return ret;
}

void load() {
    int nbFaces = 40;
    int nbPicsPerFace = 5;

    // Load files specs
    vpImage<unsigned char> im;
    loadImage(im, 1, 1);
    int iheight = im.getHeight();
    int iwidth = im.getWidth();

    // Build matrix
    vpMatrix I(iheight * iwidth, nbPicsPerFace * nbFaces);

    // Load matrix
    for (int f = 0; f < nbFaces; f++) 
        for (int pf = 0; pf < nbPicsPerFace; pf++) {
            loadImage(im, f + 1, pf + 1);
            for (int j = 0; j < iheight; j++)
                for (int i = 0; i < iwidth; i++)
                    I[i * iwidth + j][f * nbPicsPerFace + pf] = im(i, j) / 255.0;
        }

    //
    for (int i = 0; i < I.getCols(); i++) {
        for (int j = 0; j < I.getRows(); j++)
            cout << I[i][j] << ' ';
        cout << endl;
    }

}

void loadImage(vpImage<unsigned char> & I, int visage, int image) {
    stringstream fileURL;
    fileURL << IMGDIR << "s" << visage << "/" << image << ".pgm";
    vpImageIo::readPGM(I, fileURL.str());
}

