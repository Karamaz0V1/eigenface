/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>
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
            for (int j = 0; j < iwidth; j++)
                for (int i = 0; i < iheight; i++)
                    I[i * iwidth + j][f * nbPicsPerFace + pf] = im(i, j) / 255.0;
        }

    // Disp matrix
    //cout << I ;

    // Compute mean face
    vpColVector mean(iheight * iwidth);
    for (int face = 0; face < I.getCols(); face++) 
        for (int i = 0; i < iheight * iwidth; i++)
            mean[i] += I[i][face];

    mean /= nbFaces * nbPicsPerFace;

    // Disp mean face
    for (int i = 0; i < iheight; i++)
        for (int j = 0; j < iwidth; j++)
            im[i][j] = mean[i*iwidth+j] * 255;

    vpDisplayX disp(im, 10, 10, "mean face");
    vpDisplay::display(im);
    vpDisplay::flush(im);

    // Face center
    vpImageIo::writePGM(im, "moy.pgm");
    vpImage<unsigned char> im40_1, im40_1c;
    loadImage(im40_1, 40, 1);
    //vpMatrix c127(iwidth, iheight, 127);
    im40_1c = im40_1 - im;// + c127;
    vpDisplayX disp0(im40_1, 10 + iwidth, 10, "face");
    vpDisplay::display(im40_1);
    vpDisplay::flush(im40_1);
    vpDisplayX disp1(im40_1c, 10 + 2 * iwidth, 10, "center face");
    vpDisplay::display(im40_1c);
    vpDisplay::flush(im40_1c);
    vpDisplay::getClick(im);
}

void loadImage(vpImage<unsigned char> & I, int visage, int image) {
    stringstream fileURL;
    fileURL << IMGDIR << "s" << visage << "/" << image << ".pgm";
    vpImageIo::readPGM(I, fileURL.str());
}

