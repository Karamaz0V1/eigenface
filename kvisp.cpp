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
    for (int i = 0; i < image.getHeight(); i ++)
        for (int j = 0; j < image.getWidth(); j++)
            matrix[i][j] = image(i, j);
}

void vpMatrixToVpImage(const vpMatrix & matrix, vpImage<unsigned char> & image) {
    image = vpImage<unsigned char>(matrix.getRows(), matrix.getCols());
    for (int i = 0; i < image.getHeight(); i ++)
        for (int j = 0; j < image.getWidth(); j++)
            image[i][j] = matrix[i][j] * 255;
}
