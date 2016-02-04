/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <kvisp.h>
#include <cstring>
#include <assert.h>

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
    for (unsigned int i = 0; i < image.getHeight(); i ++)
        for (unsigned int j = 0; j < image.getWidth(); j++)
            matrix[i][j] = image(i, j) * 1.0 / 255;
}

void vpMatrixToVpImage(const vpMatrix & matrix, vpImage<unsigned char> & image) {
    image = vpImage<unsigned char>(matrix.getRows(), matrix.getCols());
    for (unsigned int i = 0; i < image.getHeight(); i ++)
        for (unsigned int j = 0; j < image.getWidth(); j++)
            image[i][j] = matrix[i][j] * 255;
}

void vpMatrixNormalize(vpMatrix & matrix) {
    double min = matrix.data[0];
    double max = matrix.data[0];

    for (unsigned int i = 1; i < matrix.getRows() * matrix.getCols(); i++)
        if (matrix.data[i] > max) max = matrix.data[i];
        else if (matrix.data[i] < min) min = matrix.data[i];

    for (unsigned int i = 0; i < matrix.getRows() * matrix.getCols(); i++)
        matrix.data[i] = (matrix.data[i] - min) / (max - min);
}

void kvpPow2(vpArray2D<double> & array) {
    for (double * it = array.data; it != array.data + array.size(); it++)
        *it = *it * *it;
}

double keqm(const vpArray2D<double> & array1, const vpArray2D<double> & array2) {
    assert(array1.size() == array2.size());

    double sum = 0;

    double * j = array2.data;
    for (double * i = array1.data; i != array1.data + array1.size(); i++, j++)
        sum += (*i - *j) * (*i - *j);

    return sum / array1.size();
}

double keqm(const vpImage<unsigned char> & array1, const vpImage<unsigned char> & array2) {
    assert(array1.getSize() == array2.getSize());

    double sum = 0;

    unsigned char * j = array2.bitmap;
    for (unsigned char * i = array1.bitmap; i != array1.bitmap + array1.getSize(); i++, j++)
        sum += (*i - *j) * (*i - *j);

    return sum / array1.getSize();
}
