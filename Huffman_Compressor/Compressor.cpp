//
// Created by dcamachog1501 on 01/06/19.
//

#include <algorithm>
#include <iostream>
#include "Compressor.h"
#include "../Structures/List.h"
#include "Huffman_Tree.h"

Compressor::Compressor()
{

}

void Compressor::compress(vector<char> digits)
{
    vector<Huffman_Node::Character> output;
    vector<char> found;
    for (int i = 0; i < digits.size(); i++)
    {
        auto it = std::find(found.begin(), found.end(), digits.at(i));
        if (it == found.end()) {
            int cont = 0;
            for (int j = 0; j < digits.size(); j++)
            {
                if (digits.at(j) == digits.at(i))
                {
                    cont++;
                }
            }
            auto d = Huffman_Node::Character();
            d.setDigit(digits.at((i)));
            d.setTimes(cont);
            output.push_back(d);
            found.push_back(digits.at(i));
        }
    }
    List<Huffman_Node*>*HuffList= VecToList(output);
    while(HuffList->getLength()>=2)
    {
        HuffList=sort(HuffList);
        Huffman_Node::Character c= Huffman_Node::Character();
        c.setTimes(HuffList->getHead()->getValue()->getValue()->getTimes()+HuffList->getHead()->getNext()->getValue()->getValue()->getTimes());
        c.setDigit(nullptr);
        Huffman_Node *n= new Huffman_Node(c);
        n->setRight(HuffList->getHead()->getValue());
        n->setleft(HuffList->getHead()->getNext()->getValue());
        HuffList->delFirst();
        HuffList->delFirst();
        HuffList->add(n);
    }
    Huffman_Tree HuffTree= Huffman_Tree();
    HuffTree.setTop(HuffList->getHead()->getValue());
    vector<Code> codified=codifier(HuffTree,output);
    print(codified,digits);
    string codigote=encoder(codified,digits);
    cout<<"Codigote: "<<codigote<<endl;




}

List<Huffman_Node*>* Compressor::VecToList(vector<Huffman_Node::Character> vec)
{
    List<Huffman_Node*>*out= new List<Huffman_Node*>();
    for(int i= 0;i<vec.size();i++)
    {
        Huffman_Node* h= new Huffman_Node(vec.at(i));
        out->add(h);
    }
    return out;
}

List<Huffman_Node*>* Compressor::sort(List<Huffman_Node*>* list)
{
    Node<Huffman_Node*>* temp= list->getHead();
    while((temp->getNext()!= nullptr)&&(temp->getNext()->getNext()!= nullptr))
    {
        bool cond=((temp->getNext()->getValue()->getValue()->getTimes()==temp->getNext()->getNext()->getValue()->getValue()->getTimes())&&(temp->getNext()->getValue()->getValue()->getDigit()!=nullptr)&&(temp->getNext()->getNext()->getValue()->getValue()->getDigit()==nullptr));
        if(temp->getValue()->getValue()->getDigit()==list->getHead()->getValue()->getValue()->getDigit())
        {
            bool subcond=((temp->getValue()->getValue()->getTimes()==temp->getNext()->getValue()->getValue()->getTimes())&&(temp->getNext()->getValue()->getValue()->getDigit()==nullptr)&&(temp->getValue()->getValue()->getDigit()!=nullptr));
            bool altercond=(temp->getValue()->getValue()->getTimes())>(temp->getNext()->getValue()->getValue()->getTimes());
            if(altercond||subcond)
            {
                list->setHead(temp->getNext());
                temp->setNext(temp->getNext()->getNext());
                list->getHead()->setNext(temp);
                temp=list->getHead();
            }
        }
        if(temp->getNext()->getNext()!= nullptr)
        {
            if ((temp->getNext()->getNext()->getValue()->getValue()->getTimes()<temp->getNext()->getValue()->getValue()->getTimes())||cond)
            {
                Node<Huffman_Node *> *temp2 = temp->getNext()->getNext();
                temp->getNext()->setNext(temp2->getNext());
                temp2->setNext(temp->getNext());
                temp->setNext(temp2);
                temp = list->getHead();
            }
            else
            {
                temp=temp->getNext();
            }
        }
    }
    list->arrange();
    return list;
}

void Compressor::print(List<Huffman_Node *> list)
{
    Node<Huffman_Node*>* temp=list.getHead();
    while(temp!= nullptr)
    {
        cout<<" = "<<to_string(temp->getValue()->getValue()->getTimes())<<endl;
        temp=temp->getNext();
    }
}

vector<Compressor::Code> Compressor::codifier(Huffman_Tree tree,vector<Huffman_Node::Character> keys)
{
    vector<Code> codes;
    for(int i=0;i<keys.size();i++)
    {
        string cd=backTrackCoder(*keys.at(i).getDigit(),tree.getTop(),"");
        Code c= Code(keys.at(i),cd);
        codes.push_back(c);
    }
    return codes;

}

string Compressor::backTrackCoder(char key, Huffman_Node* temp,string code)
{

    if(temp->getValue()->getDigit()!= nullptr)
    {
        if(*temp->getValue()->getDigit()==key)
        {
            return code;
        }
        else
        {
            return "-1";
        }
    }
    else
    {
        string ret=backTrackCoder(key,temp->getRight(),code+"1");
        if(ret=="-1")
        {
            string retleft=backTrackCoder(key,temp->getLeft(),code+"0");
            if(retleft=="-1")
            {
                return "-1";
            }
            else
            {
                return retleft;
            }
        }
        else
        {
            return ret;
        }
    }
}

void Compressor::print(vector<Compressor::Code> codes, vector<char> digits)
{
    string word="";
    for(int i=0;i<digits.size();i++)
    {
        string s;
        s.push_back(digits.at(i));
        word+=s;
    }
    cout<<"Palabra: "<<word<<"\n"<<endl;
    for(int j=0;j<codes.size();j++)
    {
        cout<<codes.at(j).getCharacter()<<" : "<<codes.at(j).getCoded()<<"\n"<<endl;
    }

}

string Compressor::encoder(vector<Compressor::Code> codes, vector<char>keys)
{
    string out="";
    int size=keys.size();
    int cont=0;
    int its=0;
    for(int i=0;i<keys.size();i++)
    {
        for(int j=0;j<codes.size();j++)
        {
            if(codes.at(j).getCharacter()==keys.at(i))
            {
                out+=codes.at(j).getCoded();
                cont++;
            }
        }
        its++;
    }
    cout<<"Real bit size: "<<to_string(size*8)<<"\n"<<endl;
    cout<<"Compressed bit size:"<<out.size()<<endl;
    return out;
}
