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
        double getEigenvalue(int subject = 1, int image = 1) const;

        void getFaceCoordinates(vpColVector & coordinates, int subject = 1, int image = 1, int k = 0) const;
        void getFaceWithCoordinates(const vpColVector & coordinates, vpImage<unsigned char> & face) /*const*/;
        double getEQM(const vpImage<unsigned char> & faceReconstructed, int subject = 1, int image = 1) const;
        void getEk(vpMatrix & Ek, int subject = 1, int image = 1, int k = 1, int K = 20) /*const*/;

        // TODO: vpMat access
        void getI(vpImage<unsigned char> & I) const;
        void getA(vpImage<unsigned char> & A) const;
        void getU(vpImage<unsigned char> & U) const;
        void getS(vpColVector & S) const;

    protected:
        void getFace(vpMatrix & face, int subject, int image) const;
        void getEigenface(vpMatrix & eigenface, int subject, int image) const;
        void getCenterFace(vpMatrix & centerFace, int subject, int image) const;
        void getFaceWithCoordinates(const vpColVector & coordinates, vpMatrix & face) /*const*/;

    private:
        vpMatrix _faces;
        vpMatrix _meanFace;
        vpMatrix _centerfaces;
        vpMatrix _eigenfaces;
        vpColVector _eigenvalues;
        std::string _dbUrl;
        int _iwidth, _iheight; // db images size
        int _nSubjects, _nImages;

    private:
        void loadImage(vpImage<unsigned char> & I, int visage, int image) const;
        void loadImage(vpMatrix & I, int visage, int image) const;
        void initImageSpec();
        void loadDb(int nbSubjects, int nbImages);
        void initMeanFace();
        void computeCenterfaces();
        void computeEigenfaces();
};

#endif /* __EIGENFACES_H__ */
