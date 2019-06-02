//
// Created by dcamachog1501 on 01/06/19.
//

#include "FilePart.h"

FilePart::FilePart(int fNumb, string fNam)
{
    this->filename=fNam;
    this->filePartN=fNumb;
}
FilePart::FilePart(string fNam)
{
    this->filename=fNam;
    this->filePartN=0;
}
string FilePart::getFileName()
{
    return this->filename;
}

int FilePart::getFilePartN()
{
    return this->filePartN;
}

