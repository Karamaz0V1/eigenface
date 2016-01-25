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
#include <Eigenfaces.h>
#include <kvisp.h>
#define IMGDIR "../img/"
using namespace std;

void load();
void loadImage(vpImage<unsigned char> & I, int visage, int image);
void demo_visp_broken();
void demo_visp_broken2();

void q0();
void q3();
void q6();

Eigenfaces ef("../img", 40, 10);

int main( int argc, char* argv[] )
{
    q0();
    q3();
    q6();

    return 0;
}

void q0() {
    vpImage<uchar> A;
    ef.getA(A);
    cout << "rows: " << A.getRows() << " cols: " << A.getCols() << endl;
    vpImageIo::writePNG(A, "all_images.png");
}

void q3() {
    vpImage<uchar> imean;
    ef.getMeanFace(imean);

    vpImage<uchar> iface, iface1, iface2;
    ef.getFace(iface);
    ef.getFace(iface1, 10);
    ef.getFace(iface2, 20);

    vpImage<uchar> icenter, icenter1, icenter2;
    ef.getCenterFace(icenter);
    ef.getCenterFace(icenter1, 10);
    ef.getCenterFace(icenter2, 20);

    vpImageIo::writePNG(iface,  "face_s1.png");
    vpImageIo::writePNG(iface1, "face_s10.png");
    vpImageIo::writePNG(iface2, "face_s20.png");

    vpImageIo::writePNG(icenter,  "center_s1.png");
    vpImageIo::writePNG(icenter1, "center_s10.png");
    vpImageIo::writePNG(icenter2, "center_s20.png");

    vpDisplayX disp0(imean, 1000, 100, "mean face");
    vpDisplayX disp1(iface, 1100, 100, "face");
    vpDisplayX disp2(icenter, 1200, 100, "center face");
    vpDisplay::display(imean);
    vpDisplay::display(iface);
    vpDisplay::display(icenter);
    vpDisplay::flush(imean);
    vpDisplay::flush(iface);
    vpDisplay::flush(icenter);
    vpDisplay::getClick(imean);
}

void q6() {
    vpImage<uchar> imean;
    ef.getMeanFace(imean);

    vpImage<uchar> ieface, ieface1, ieface2;
    ef.getEigenface(ieface);
    ef.getEigenface(ieface1, 10);
    ef.getEigenface(ieface2, 20);

    vpDisplayX disp0(imean, 1000, 100, "mean face");
    vpDisplayX disp1(ieface, 1100, 100, "eigenface 1");
    vpDisplayX disp2(ieface1, 1200, 100, "eigenface 10");
    vpDisplay::display(imean);
    vpDisplay::display(ieface);
    vpDisplay::display(ieface1);
    vpDisplay::flush(imean);
    vpDisplay::flush(ieface);
    vpDisplay::flush(ieface1);
    vpDisplay::getClick(imean);

    vpImage<uchar> U;
    ef.getU(U);
    vpImageIo::writePNG(U, "eigenfaces.png");
}

void demo_visp_broken() {
    int var;
    vpMatrix mat(3, 4);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            mat[i][j] = ++var;

    cout << mat << endl;

    vpRowVector row = mat.stackRows();

    cout << row << endl;

    vpMatrix remat = row.reshape(3, 4);

    cout << remat << endl;
}

void demo_visp_broken2() {
    int var;
    vpMatrix test(3, 4);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++) {
            test[i][j] = ++var;
        }

    cout << test << endl;

    vpColVector col = test.stackColumns();

    cout << col << endl;

    vpMatrix retest = col.reshape(3, 4);

    cout << retest << endl;
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
    for (unsigned int face = 0; face < I.getCols(); face++) 
        for (int i = 0; i < iheight * iwidth; i++)
            mean[i] += I[i][face];

    mean /= nbFaces * nbPicsPerFace;

    // Disp mean face
    for (int i = 0; i < iheight; i++)
        for (int j = 0; j < iwidth; j++)
            im[i][j] = mean[i*iwidth+j] * 255;

    vpDisplayX disp(im, 1000, 100, "mean face");
    vpDisplay::display(im);
    vpDisplay::flush(im);

    vpMatrix imat;
    vpImageToVpMatrix(im, imat);

    // Face center
    vpImageIo::writePGM(im, "moy.pgm");
    vpImage<unsigned char> im40_1, im40_1c;
    loadImage(im40_1, 40, 1);
    //vpMatrix c127(iwidth, iheight, 127);
    im40_1c = im40_1 - im;// + c127;
    vpDisplayX disp0(im40_1, 1000 + iwidth, 100, "face");
    vpDisplay::display(im40_1);
    vpDisplay::flush(im40_1);
    vpDisplayX disp1(im40_1c, 1000 + 2 * iwidth, 100, "center face");
    vpDisplay::display(im40_1c);
    vpDisplay::flush(im40_1c);
    vpDisplay::getClick(im);
}

void loadImage(vpImage<unsigned char> & I, int visage, int image) {
    stringstream fileURL;
    fileURL << IMGDIR << "s" << visage << "/" << image << ".pgm";
    vpImageIo::readPGM(I, fileURL.str());
}

