//
// Created by dcamachog1501 on 01/06/19.
//

#include "RAID_Controller.h"

RAID_Controller::RAID_Controller()
{
    Initializer();
}

void RAID_Controller::Initializer()
{
    this->diskList=new List<Disk*>();
    DIR *rDir=opendir("RAID");
    if(rDir== nullptr)
    {
        if (dirCreator("RAID"))
        {
            cout << "RAID creado\n";
            diskInitializer(false);
        }
        else
        {
            cout<<"No se puede crear el RAID"<<endl;
        }

    }
    else
    {
        cout<<"El RAID ya existe"<<endl;
        diskInitializer(true);
    }


}

void RAID_Controller::diskInitializer(bool exists)
{
    if(exists)
    {

    }
    else
    {
        for(int i=1; i<=4;i++)
        {
            auto* d = new Disk(i);
            this->diskList->add(d);
            dirCreator(("RAID/Disk_"+to_string(i)).c_str());
        }
        cout<<"Discos inicializados correctamente"<<endl;
    }

}

bool RAID_Controller::dirCreator(const char* dir)
{
    if (mkdir(dir, 0777) == -1)
    {
        cerr << "Error :  " << strerror(errno) << endl;
        return false;
    }
    return true;
}
