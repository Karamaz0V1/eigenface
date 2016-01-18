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

Eigenfaces::Eigenfaces(const std::string & dbUrl, int numberOfFaces, int numberOfImagesPerFace) :
    _dbUrl(dbUrl) 
{
    // Load files specs
    vpImage<unsigned char> im;
    loadImage(im, 1, 1);
    _iheight = im.getHeight();
    _iwidth = im.getWidth();

    // Build matrix
    _faces = vpMatrix(_iheight * _iwidth, numberOfImagesPerFace * numberOfFaces);

    // Load matrix
    for (int f = 0; f < numberOfFaces; f++) 
        for (int pf = 0; pf < numberOfImagesPerFace; pf++) {
            loadImage(im, f + 1, pf + 1);
            for (int j = 0; j < _iwidth; j++)
                for (int i = 0; i < _iheight; i++)
                    _faces[i * _iwidth + j][f * numberOfImagesPerFace + pf] = im(i, j) / 255.0;
        }

    // Calculate mean face
    _meanFace = vpColVector(_iheight * _iwidth);
    for (int face = 0; face < _faces.getCols(); face++) 
        for (int i = 0; i < _iheight * _iwidth; i++)
            _meanFace[i] += _faces[i][face];

    _meanFace /= numberOfFaces * numberOfImagesPerFace;
}

void Eigenfaces::getMeanFace(vpImage<unsigned char> & meanFace) const {
    meanFace = vpImage<unsigned char>(_iheight, _iwidth);

    for (int i = 0; i < _iheight; i++)
        for (int j = 0; j < _iwidth; j++)
            meanFace[i][j] = _meanFace[i*_iwidth+j] * 255;
}

void Eigenfaces::getCenterFace(vpImage<unsigned char> & centerFace, int visage, int image) const {
    centerFace = vpImage<unsigned char>(_iheight, _iwidth);
    vpImage<unsigned char> face;
    vpMatrix mface;

    loadImage(face, visage, image);
    vpImageToVpMatrix(face, mface);
}

void Eigenfaces::loadImage(vpImage<unsigned char> & I, int visage, int image) const {
    stringstream fileURL;
    fileURL << _dbUrl << "/s" << visage << "/" << image << ".pgm";
    vpImageIo::readPGM(I, fileURL.str());
}
