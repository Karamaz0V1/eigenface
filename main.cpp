/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

//#include <iostream>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>
#include <visp3/gui/vpPlot.h>
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
void q8();
void q8r();
void q10();
void q11();

const int SUBJECTS = 36;
const int IMAGES = 9;
//const int SUBJECTS = 10;
//const int IMAGES = 10;
Eigenfaces ef("../img", SUBJECTS, IMAGES);

int main( int argc, char* argv[] )
{
    //q0();
    //q3();
    //q6();
    //q8();
    q8r();
    //q10();
    q11();

    return 0;
}

void q0() {
    vpImage<uchar> A;
    ef.getA(A);
    cout << "rows: " << A.getRows() << " cols: " << A.getCols() << endl;
    vpImageIo::writePNG(A, "all_centerimages.png");
}

void q3() {
    vpImage<uchar> imean;
    ef.getMeanFace(imean);

    vpImage<uchar> iface, iface1, iface2;
    ef.getFace(iface);
    ef.getFace(iface1, 1, 10);
    ef.getFace(iface2, 1, 20);

    vpImage<uchar> icenter, icenter1, icenter2;
    ef.getCenterFace(icenter);
    ef.getCenterFace(icenter1, 10);
    ef.getCenterFace(icenter2, 20);

    vpDisplayX disp0(imean, 1000, 100, "mean face");
    vpDisplayX disp1(iface, 1100, 100, "face");
    vpDisplayX disp2(icenter, 1200, 100, "center face");
    vpDisplay::display(imean);
    vpDisplay::display(iface);
    vpDisplay::display(icenter);
    vpDisplay::flush(imean);
    vpDisplay::flush(iface);
    vpDisplay::flush(icenter);

    vpImageIo::writePNG(iface,  "q3_face_s1.png");
    vpImageIo::writePNG(iface1, "q3_face_s10.png");
    vpImageIo::writePNG(iface2, "q3_face_s20.png");

    vpImageIo::writePNG(icenter,  "q3_center_s1.png");
    vpImageIo::writePNG(icenter1, "q3_center_s10.png");
    vpImageIo::writePNG(icenter2, "q3_center_s20.png");

    vpDisplay::getClick(imean);
}

void q6() {
    vpImage<uchar> imean;
    ef.getMeanFace(imean);

    vpImage<uchar> ieface0, ieface1, ieface2, ieface3, ieface4, ieface5, ieface6;
    ef.getEigenface(ieface0);
    ef.getEigenface(ieface1, 1, 2);
    ef.getEigenface(ieface2, 1, 3);
    ef.getEigenface(ieface3, 1, 4);
    ef.getEigenface(ieface4, 1, 5);
    ef.getEigenface(ieface5, 1, 6);
    ef.getEigenface(ieface6, 1, 7);

    cout << "--- First Eigenvalues ---" << endl;
    cout << ef.getEigenvalue() << endl;
    cout << ef.getEigenvalue(1, 2) << endl;
    cout << ef.getEigenvalue(1, 3) << endl;
    cout << ef.getEigenvalue(1, 4) << endl;
    cout << ef.getEigenvalue(1, 5) << endl;
    cout << ef.getEigenvalue(1, 6) << endl;
    cout << ef.getEigenvalue(1, 7) << endl;
    cout << "-------------------------" << endl;

    vpDisplayX disp0(imean,   1000, 100, "mean face");
    vpDisplayX disp1(ieface0, 1100, 100, "eigf 1");
    vpDisplayX disp2(ieface1, 1200, 100, "eigf 2");
    vpDisplayX disp3(ieface2, 1300, 100, "eigf 3");
    vpDisplayX disp4(ieface3, 1400, 100, "eigf 4");
    vpDisplayX disp5(ieface4, 1500, 100, "eigf 5");
    vpDisplayX disp6(ieface5, 1600, 100, "eigf 6");
    vpDisplayX disp7(ieface6, 1700, 100, "eigf 7");
    vpDisplay::display(imean);
    vpDisplay::display(ieface0);
    vpDisplay::display(ieface1);
    vpDisplay::display(ieface2);
    vpDisplay::display(ieface3);
    vpDisplay::display(ieface4);
    vpDisplay::display(ieface5);
    vpDisplay::display(ieface6);
    vpDisplay::flush(imean);
    vpDisplay::flush(ieface0);
    vpDisplay::flush(ieface1);
    vpDisplay::flush(ieface2);
    vpDisplay::flush(ieface3);
    vpDisplay::flush(ieface4);
    vpDisplay::flush(ieface5);
    vpDisplay::flush(ieface6);

    vpImageIo::writePNG(ieface0, "q6_eigenface_1.png");
    vpImageIo::writePNG(ieface1, "q6_eigenface_2.png");
    vpImageIo::writePNG(ieface2, "q6_eigenface_3.png");
    vpImageIo::writePNG(ieface3, "q6_eigenface_4.png");
    vpImageIo::writePNG(ieface4, "q6_eigenface_5.png");
    vpImageIo::writePNG(ieface5, "q6_eigenface_6.png");
    vpImageIo::writePNG(ieface6, "q6_eigenface_7.png");

    vpDisplay::getClick(imean);
}

void q8() {
    cout << "Compute test image 40 2" << endl;
    vpImage<uchar> rface;
    vpColVector coord;
    ef.getFaceCoordinates(coord, 40, 2);
    ef.getFaceWithCoordinates(coord, rface);

    // Display face coordinates
    //cout << "Face coordinates: " << endl;
    //cout << coord << endl;

    cout << "Compute test image 37 1" << endl;
    vpImage<uchar> rface1;
    vpColVector coord1;
    ef.getFaceCoordinates(coord1, 37, 1);
    ef.getFaceWithCoordinates(coord1, rface1);

    cout << "Compute reference image 20 1" << endl;
    vpImage<uchar> rface2;
    vpColVector coord2;
    ef.getFaceCoordinates(coord2, 20, 1);
    ef.getFaceWithCoordinates(coord2, rface2);

    cout << "Compute reference image 20 1 with k = 50" << endl;
    vpImage<uchar> rface3;
    vpColVector coord3;
    ef.getFaceCoordinates(coord3, 20, 1, 50);
    ef.getFaceWithCoordinates(coord3, rface3);

    vpDisplayX disp0(rface,  1000, 100, "T 40 2");
    vpDisplayX disp1(rface1, 1100, 100, "T 37 1");
    vpDisplayX disp2(rface2, 1200, 100, "T 20 1");
    vpDisplayX disp3(rface3, 1300, 100, "T 20 1 k 50");
    vpDisplay::display(rface);
    vpDisplay::display(rface1);
    vpDisplay::display(rface2);
    vpDisplay::display(rface3);
    vpDisplay::flush(rface);
    vpDisplay::flush(rface1);
    vpDisplay::flush(rface2);
    vpDisplay::flush(rface3);

    vpImageIo::writePNG(rface,  "q8_40_2.png");
    vpImageIo::writePNG(rface1, "q8_37_1.png");
    vpImageIo::writePNG(rface2, "q8_20_1.png");
    vpImageIo::writePNG(rface3, "q8_20_1_k50.png");

    vpDisplay::getClick(rface);
}

void q8r() {
    vector<int> Ks = {1, 5, 10, 30, 50, 100, 200, 300, 324};
    vector<pair<int, int> > subjects = {{1, 1}, {10, 1}, {1, 10}, {10, 10}, {37, 1}, {40, 2}};


    for (vector<pair<int, int> >::const_iterator subject = subjects.begin(); subject != subjects.end(); subject++)
        for (vector<int>::const_iterator k = Ks.begin(); k != Ks.end(); k++) {
            cout << "Compute subject " << subject->first << " " << subject->second << " with k=" << *k;
            vpImage<uchar> rface;
            vpColVector coord;
            ef.getFaceCoordinates(coord, subject->first, subject->second, *k);
            ef.getFaceWithCoordinates(coord, rface);
            cout << " EQM=" << ef.getEQM(rface, subject->first, subject->second) << endl;

            stringstream filename;
            filename << "q8r_" << subject->first << "_" << subject->second << "_k" << *k  << ".png";
            vpImageIo::writePNG(rface, filename.str());
        }
}

void q10() {
    vpColVector singularValues;
    ef.getS(singularValues);
    vpColVector eigenValues = singularValues;
    kvpPow2(eigenValues);
    eigenValues = eigenValues.normalize();
    vpPlot A(1, 700, 700, 1000, 200, "Eigen Curve");
    A.initGraph(0, 2);
    A.setTitle(0, "Eigen values accumulation");
    double sum = 0;
    for (unsigned int i = 0; i < eigenValues.size(); i++) {
        sum += eigenValues[i] / eigenValues.sum();
        //A.plot(0,0,i,eigenValues[i]);
        A.plot(0, 0, i, sum);
    }
    cout << "Sum: " << sum << endl;
    cout << "Euc: " << eigenValues.euclideanNorm() << endl;
    A.getPixelValue(true);
}

void q11() {
    int m = (SUBJECTS - 1) * (IMAGES - 1);
    vpColVector eqm(m + 1);

    vpPlot A(1, 700, 1000, 1000, 200, "Mean error");
    A.initGraph(0, 1);
    A.setTitle(0, "Mean error depending on K");

    int cpt = 0;
    for (int s = 1; s <= SUBJECTS; s++)
        for (int i = 1; i <= IMAGES; i++) {
            for (int k = 1; k <= m; k++) {
                vpColVector coordinates;
                ef.getFaceCoordinates(coordinates, s, i, k);

                vpImage<uchar> face;
                ef.getFaceWithCoordinates(coordinates, face);

                double eqma = ef.getEQM(face, s, i);
                eqm[k] += eqma;

                cout << "Compute subject " << s << " image " << i << " for k=" << k << " : eqm=" << eqma << endl;
            }

            vpColVector eqmdisp = eqm / ++cpt;

            A.resetPointList(0);
            for (unsigned int k = 0; k < eqmdisp.size(); k++)
                A.plot(0, 0, k, eqmdisp[k]);
        }

    eqm /= m;
    cout << eqm << endl;

    A.getPixelValue(true);
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

