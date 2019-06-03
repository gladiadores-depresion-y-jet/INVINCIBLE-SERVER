#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include "../RAID/RAID_Controller.h"
#include "../Huffman_Compressor/Compressor.h"

using namespace std;
int main()
{
    auto comp= new Compressor();

    auto *r= new RAID_Controller();
    Compressor::Codified_File* c=r->imageDecomposer("Prueba2.jpg");
    Compressor::Decodified_File* dec=comp->decompress(c);
    r->compose(dec);
}