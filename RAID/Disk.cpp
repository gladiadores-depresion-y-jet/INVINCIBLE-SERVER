//
// Created by dcamachog1501 on 01/06/19.
//

#include <iostream>
#include "Disk.h"

Disk::Disk(int dNumb)
{
    this->diskN=dNumb;
    this->fileColumn= new List<FilePart*>;
    this->regfileN=0;
    this->parityN=0;
}

int Disk::getDiskN()
{
    return this->diskN;
}

int Disk::getFileN()
{
    return (this->regfileN+this->parityN);
}

int Disk::getParityN()
{
    return this->parityN;
}

List<FilePart *> *Disk::getfileColumn()
{
    return this->fileColumn;
}
void Disk::parityCounter()
{
    Node<FilePart*>* temp= this->fileColumn->getHead();
    while(temp!= nullptr)
    {
        if(temp->getValue()->getFileName().find("Parity"))
        {
            this->parityN++;
        }
        else
        {
            this->regfileN++;
        }
        temp=temp->getNext();
    }
}

void Disk::print()
{
    cout<<"------------"<<endl;
    cout<<"|  "<<"Disk_"<<to_string(this->diskN)<<"  |"<<endl;
    cout<<"------------\n"<<endl;
    cout<<"-->Files in disk: \n"<<endl;
    Node<FilePart*>* temp= this->fileColumn->getHead();
    while(temp!= nullptr)
    {
        if(temp->getValue()->getFilePartN()!=0)
            cout<<" ->"<<temp->getValue()->getFileName()<<"_"<<temp->getValue()->getFilePartN()<<endl;
        else
            cout<<" ->"<<temp->getValue()->getFileName()<<endl;

        temp=temp->getNext();
    }
    cout<<"\n"<<endl;
}
