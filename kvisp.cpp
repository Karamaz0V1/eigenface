/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "kvisp.h"
#include <cstring>

vpColVector vpColVector3(const double x, const double y, const double z) {
    vpColVector cv(3);
    cv[0] = x;
    cv[1] = y;
    cv[2] = z;
    return cv;
}

vpColVector vpColVector4(const double x, const double y, const double z, const double w) {
    vpColVector cv(4);
    cv[0] = x;
    cv[1] = y;
    cv[2] = z;
    cv[3] = w;
    return cv;
}
vpImagePoint vpColVectorToVpImagePoint(const vpColVector & vect) {
    return vpImagePoint(vect[0], vect[1]);
}

void vpImageToVpMatrix(const vpImage<unsigned char> & image, vpMatrix & matrix) {
    matrix = vpMatrix(image.getHeight(), image.getWidth());
    std::memcpy(matrix.data, image.bitmap, image.getHeight() * image.getWidth());
}
