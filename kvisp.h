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

#endif /* __KVISP_H__ */
