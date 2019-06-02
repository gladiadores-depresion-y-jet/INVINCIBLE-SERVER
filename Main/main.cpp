#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include "../RAID/RAID_Controller.h"
#include "../Huffman_Compressor/Compressor.h"

using namespace std;
int main()
{
    auto *r= new RAID_Controller();
    r->imageDecomposer("Prueba.jpg","Prueba.txt");

    /*auto c= new Compressor();
    string s="Colapsar restos";
    vector<char> vec(s.length());
    copy(s.begin(),s.end(),vec.begin());
    c->compress(vec);*/
}