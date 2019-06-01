//
// Created by dcamachog1501 on 01/06/19.
//

#ifndef RAID_5_DISK_H
#define RAID_5_DISK_H


#include "FilePart.h"
#include "../Structures/List.h"

class Disk
{
    private:
        int diskN;
        int fileN;
        int parityN;
        List <FilePart*>* fileColumn;

    public:
        Disk(int dNumb);
        void fileCounter();
        void parityCounter();


};


#endif //RAID_5_DISK_H
