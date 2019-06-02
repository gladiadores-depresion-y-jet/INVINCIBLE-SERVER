//
// Created by dcamachog1501 on 01/06/19.
//

#ifndef RAID_5_RAID_CONTROLLER_H
#define RAID_5_RAID_CONTROLLER_H


#include "../Structures/List.h"
#include "Disk.h"
#include "../Huffman_Compressor/Compressor.h"
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <boost/algorithm/string.hpp>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class RAID_Controller
{
    private:
        int disks;
        List<Disk*>* diskList;
        Compressor *comp;
    public:
        RAID_Controller();
        void Initializer();
        bool dirCreator(const char* dir);
        void diskInitializer(bool exists);
        Disk* diskGetter(int diskN);
        void imageDecomposer(string dir,string newName);



};


#endif //RAID_5_RAID_CONTROLLER_H
