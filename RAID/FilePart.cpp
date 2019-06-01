//
// Created by dcamachog1501 on 01/06/19.
//

#include "FilePart.h"

FilePart::FilePart(int fNumb, string fNam)
{
    this->filename=fNam;
    this->filePartN=fNumb;
}

string FilePart::getFileName()
{
    return this->filename;
}

int FilePart::getFilePartN()
{
    return this->filePartN;
}
