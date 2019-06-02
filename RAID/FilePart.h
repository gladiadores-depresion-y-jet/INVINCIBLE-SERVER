//
// Created by dcamachog1501 on 01/06/19.
//

#ifndef RAID_5_FILEPART_H
#define RAID_5_FILEPART_H

#include <string>

using namespace std;
class FilePart
{
    private:
        string filename;
        int filePartN;
    public:
        FilePart(int fNumb, string fNam);
        FilePart(string fNam);
        string getFileName();
        int getFilePartN();

};


#endif //RAID_5_FILEPART_H
