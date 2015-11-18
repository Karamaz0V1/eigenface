/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include <visp/vpImageIo.h>
using namespace std;

void load();

int main( int argc, char* argv[] )
{
    int ret = 0;
    
    load();

    return ret;
}

void load() {
    string fileURL = "../s1/1.pgm";
    vpImage<unsigned char> im;
    vpImageIo::readPGM(im, fileURL);
    cout << im.getRows() << endl;
    cout << im.getCols() << endl;

}

