/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __EIGENFACES_H__
#define __EIGENFACES_H__
#include <string>
#include <visp/vpImage.h>

class Eigenfaces {
    public:
        Eigenfaces(const std::string & dbUrl, int numberOfFaces = 10, int numberOfImagesPerFace = 5);
        void getMeanFace(vpImage<unsigned char> & meanFace) const;
        void getFace(vpImage<unsigned char> & face, int visage = 1, int image = 1) const;
        void getCenterFace(vpImage<unsigned char> & centerFace, int visage = 1, int image = 1) const;

    protected:
        void loadImage(vpImage<unsigned char> & I, int visage, int image) const;

    private:
        vpMatrix _faces;
        vpMatrix _meanFace;
        std::string _dbUrl;
        int _iwidth, _iheight; // db images size
};

#endif /* __EIGENFACES_H__ */
