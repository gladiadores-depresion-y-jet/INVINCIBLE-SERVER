//
// Created by dcamachog1501 on 01/06/19.
//

#ifndef RAID_5_RAID_CONTROLLER_H
#define RAID_5_RAID_CONTROLLER_H


#include "../Structures/List.h"
#include "Disk.h"
#include <dirent.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
class RAID_Controller
{
    private:
        int disks;
        List<Disk*>* diskList;
    public:
        RAID_Controller();
        void Initializer();
        bool dirCreator(const char* dir);
        void diskInitializer(bool exists);


};


#endif //RAID_5_RAID_CONTROLLER_H
