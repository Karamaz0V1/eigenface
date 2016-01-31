/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include <visp/vpImageIo.h>
#include <Eigenfaces.h>
#include <kvisp.h>

using namespace std;

Eigenfaces::Eigenfaces(const std::string & dbUrl, int numberOfSubjects, int numberOfImages) :
    _dbUrl(dbUrl), 
    _nSubjects(numberOfSubjects),
    _nImages(numberOfImages)
{
    // Get image specs
    vpImage<unsigned char> im;
    loadImage(im, 1, 1);
    _iheight = im.getHeight();
    _iwidth = im.getWidth();

    // Load matrix
    cout << "Load faces database..." << endl;
    loadDb(numberOfSubjects, numberOfImages);

    // Compute mean face
    cout << "Compute mean face..." << endl;
    initMeanFace();

    // Compute the center faces
    cout << "Compute the center faces..." << endl;
    computeCenterfaces();

    // Compute the eigenfaces
    cout << "Compute the eigenfaces..." << endl;
    computeEigenfaces();

    cout << "Initialization done" << endl;
}

void Eigenfaces::getMeanFace(vpImage<unsigned char> & meanFace) const {
    vpMatrixToVpImage(_meanFace, meanFace);
}

void Eigenfaces::getEigenface(vpImage<unsigned char> & eigenface, int subject, int image) const {
    vpMatrix meigenface;
    getEigenface(meigenface, subject, image);
    vpMatrixNormalize(meigenface);
    vpMatrixToVpImage(meigenface, eigenface);
}

void Eigenfaces::getFace(vpImage<unsigned char> & face, int subject, int image) const {
    vpMatrix mface;
    getFace(mface, subject, image);
    vpMatrixToVpImage(mface, face);
}

void Eigenfaces::getFace(vpMatrix & face, int subject, int image) const {
    face = _faces.getCol((subject - 1) * _nImages + image - 1).t().reshape(_iheight, _iwidth);
}

void Eigenfaces::getEigenface(vpMatrix & eigenface, int subject, int image) const {
    eigenface = _eigenfaces.getCol((subject - 1) * _nImages + image - 1).t().reshape(_iheight, _iwidth);
}

double Eigenfaces::getEigenvalue(int subject, int image) const {
    double val = _eigenvalues[(subject - 1) * _nImages + image - 1];
    return val * val;
}

void Eigenfaces::getCenterFace(vpImage<unsigned char> & centerFace, int subject, int image) const {
    vpMatrix mcenterFace;
    getCenterFace(mcenterFace, subject, image);
    vpMatrixNormalize(mcenterFace);
    vpMatrixToVpImage(mcenterFace, centerFace);
}

void Eigenfaces::getFaceCoordinates(vpColVector & coordinates, int subject, int image) const {
    coordinates.clear();
    vpImage<uchar> face;
    loadImage(face, subject, image);
    vpMatrix mface;
    vpImageToVpMatrix(face, mface);

    vpRowVector rface = (mface - _meanFace).stackRows();

    for (unsigned int i = 0; i < _nSubjects * _nImages; i++)
        coordinates.stack(rface * _centerfaces.getCol(i));
}

void Eigenfaces::getCenterFace(vpMatrix & centerFace, int subject, int image) const {
    centerFace = _centerfaces.getCol((subject - 1) * _nImages + image - 1).t().reshape(_iheight, _iwidth);
}

void Eigenfaces::loadImage(vpImage<unsigned char> & I, int visage, int image) const {
    stringstream fileURL;
    fileURL << _dbUrl << "/s" << visage << "/" << image << ".pgm";
    vpImageIo::readPGM(I, fileURL.str());
}

void Eigenfaces::initMeanFace() {
    vpColVector rmean(_iwidth * _iheight);

    for (unsigned int i = 0; i < _faces.getCols(); i++)
        rmean += _faces.getCol(i);

    rmean /= _faces.getCols();
    _meanFace = rmean.t().reshape(_iheight, _iwidth);
}

void Eigenfaces::getI(vpImage<unsigned char> & I) const {
    vpMatrixToVpImage(_faces, I);
}

void Eigenfaces::getA(vpImage<unsigned char> & A) const {
    vpMatrix centerfaces = _centerfaces;
    vpMatrixNormalize(centerfaces);
    vpMatrixToVpImage(centerfaces, A);
}

void Eigenfaces::getU(vpImage<unsigned char> & U) const {
    vpMatrixToVpImage(_eigenfaces, U);
}

void Eigenfaces::computeEigenfaces() {
    _eigenfaces = _centerfaces;
    vpMatrix V;
    _eigenfaces.svd(_eigenvalues, V);
    _eigenvalues.normalize();
    vpMatrixNormalize(_eigenfaces);
}

void Eigenfaces::computeCenterfaces() {
    vpRowVector mean = _meanFace.stackRows();

    for (unsigned int i = 0; i < _faces.getCols(); i++)
        _centerfaces.stack(_faces.getCol(i).t() - mean);

    _centerfaces = _centerfaces.t();
}

void Eigenfaces::loadDb(int nbSubjects, int nbImages) {
    for (int f = 1; f <= nbSubjects; f++)
        for (int pf = 1; pf <= nbImages; pf++) {
            cout << "Loading face " << f << " expression " << pf << endl;
            vpImage<unsigned char> imface;
            loadImage(imface, f, pf);

            vpMatrix mimface;
            vpImageToVpMatrix(imface, mimface);

            _faces.stack(mimface.stackRows());
        }
    _faces = _faces.t();
    cout << nbImages * nbSubjects << " images in db" << endl;
}
