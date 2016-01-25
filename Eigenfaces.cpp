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
    for (int f = 1; f <= numberOfSubjects; f++)
        for (int pf = 1; pf <= numberOfImages; pf++) {
            cout << "Loading face " << f << " expression " << pf << endl;
            vpImage<unsigned char> imface;
            loadImage(imface, f, pf);

            vpMatrix mimface;
            vpImageToVpMatrix(imface, mimface);

            _faces.stack(mimface.stackRows());
        }
    cout << numberOfImages * numberOfSubjects << " images in db" << endl;

    // Calculate mean face
    cout << "Calculate mean face..." << endl;
    initMeanFace();

    // Calculate the eigenfaces
    cout << "Calculate the eigenfaces..." << endl;
    computeEigenfaces();

    cout << "Initialization done" << endl;
}

void Eigenfaces::getMeanFace(vpImage<unsigned char> & meanFace) const {
    vpMatrixToVpImage(_meanFace, meanFace);
}

void Eigenfaces::getEigenface(vpImage<unsigned char> & eigenface, int subject, int image) const {
    vpMatrix meigenface;
    getEigenface(meigenface, subject, image);
    vpMatrixToVpImage(meigenface, eigenface);
}

void Eigenfaces::getFace(vpImage<unsigned char> & face, int subject, int image) const {
    vpMatrix mface;
    getFace(mface, subject, image);
    vpMatrixToVpImage(mface, face);
}

void Eigenfaces::getFace(vpMatrix & face, int subject, int image) const {
    face = _faces.getRow((subject - 1) * _nImages + image - 1).reshape(_iheight, _iwidth);
}

void Eigenfaces::getEigenface(vpMatrix & eigenface, int subject, int image) const {
    eigenface = _eigenfaces.getRow((subject - 1) * _nImages + image - 1).reshape(_iheight, _iwidth);
}

void Eigenfaces::getCenterFace(vpImage<unsigned char> & centerFace, int subject, int image) const {
    vpMatrix mcenterFace;
    getCenterFace(mcenterFace, subject, image);
    vpMatrixNormalize(mcenterFace);
    vpMatrixToVpImage(mcenterFace, centerFace);
}

void Eigenfaces::getCenterFace(vpMatrix & centerFace, int subject, int image) const {
    vpMatrix face;
    getFace(face, subject, image);
    centerFace = face -_meanFace;
}

void Eigenfaces::loadImage(vpImage<unsigned char> & I, int visage, int image) const {
    stringstream fileURL;
    fileURL << _dbUrl << "/s" << visage << "/" << image << ".pgm";
    vpImageIo::readPGM(I, fileURL.str());
}

void Eigenfaces::initMeanFace() {
    vpRowVector rmean(_iwidth * _iheight);

    for (unsigned int i = 0; i < _faces.getRows(); i++)
        rmean += _faces.getRow(i);

    rmean /= _faces.getRows();
    _meanFace = rmean.reshape(_iheight, _iwidth);
}

void Eigenfaces::getA(vpImage<unsigned char> & A) const {
    vpMatrixToVpImage(_faces, A);
}

void Eigenfaces::computeEigenfaces() {
    _eigenfaces = _faces;
    vpColVector S;
    vpMatrix V;
    _eigenfaces.svd(S, V);
}
