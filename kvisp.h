/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __KVISP_H__
#define __KVISP_H__
#include <visp/vpColVector.h>
#include <visp/vpImagePoint.h>
#include <visp/vpImage.h>

vpColVector vpColVector3(const double x, const double y, const double z);
vpColVector vpColVector4(const double x, const double y, const double z, const double w);
vpImagePoint vpColVectorToVpImagePoint(vpColVector & vect);
void vpImageToVpMatrix(const vpImage<unsigned char> & image, vpMatrix & matrix);
void vpMatrixToVpImage(const vpMatrix & matrix, vpImage<unsigned char> & image);
void vpMatrixNormalize(vpMatrix & matrix);
void kvpPow2(vpArray2D<double> & array);
double keqm(const vpArray2D<double> & array1, const vpArray2D<double> & array2);

#endif /* __KVISP_H__ */
