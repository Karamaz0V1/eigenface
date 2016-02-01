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
        Eigenfaces(const std::string & dbUrl, int numberOfSubjects = 10, int numberOfImages = 5);
        void getMeanFace(vpImage<unsigned char> & meanFace) const;
        void getFace(vpImage<unsigned char> & face, int subject = 1, int image = 1) const;
        void getEigenface(vpImage<unsigned char> & eigenface, int subject = 1, int image = 1) const;
        void getCenterFace(vpImage<unsigned char> & centerFace, int subject = 1, int image = 1) const;
        void getA(vpImage<unsigned char> & A) const;
        void getU(vpImage<unsigned char> & U) const;

    protected:
        void getFace(vpMatrix & face, int subject, int image) const;
        void getEigenface(vpMatrix & eigenface, int subject, int image) const;
        void getCenterFace(vpMatrix & centerFace, int subject, int image) const;

    private:
        vpMatrix _faces;
        vpMatrix _meanFace;
        vpMatrix _eigenfaces;
        std::string _dbUrl;
        int _iwidth, _iheight; // db images size
        int _nSubjects, _nImages;

    private:
        void loadImage(vpImage<unsigned char> & I, int visage, int image) const;
        void initImageSpec();
        void loadDb(int nbSubjects, int nbImages);
        void initMeanFace();
        void computeEigenfaces();
};

#endif /* __EIGENFACES_H__ */
