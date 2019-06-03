//
// Created by dcamachog1501 on 01/06/19.
//

#ifndef RAID_5_COMPRESSOR_H
#define RAID_5_COMPRESSOR_H


#include <vector>
#include "Huffman_Node.h"
#include "../Structures/List.h"
#include "Huffman_Tree.h"

using namespace std;
class Compressor
{
    public:
        struct Code
        {
            private:
                char character;
                string coded;
            public:
                Code(Huffman_Node::Character ch, string cd)
                {
                    this->character=*ch.getDigit();
                    this->coded=cd;
                }
                string getCoded()
                {
                    return this->coded;
                }
                char getCharacter()
                {
                    return this->character;
                }
        };
        struct Codified_File
        {
            private:
                string codigote;
                string ext;
                string name;
                Huffman_Tree tree;
        public:
            Codified_File(string c, Huffman_Tree ht,string ext,string nam)
            {
                this->codigote=c;
                this->tree=ht;
                this->ext=ext;
                this->name=nam;
            }
            string getCodigote()
            {
                return this->codigote;
            }
            Huffman_Tree getTree()
            {
                return this->tree;
            }
            string getExt()
            {
                return this->ext;
            }
            string getName()
            {
                return this->name;
            }
        };
        struct Decodified_File
        {
            private:
                vector<char> digits;
                string ext;
                string name;
            public:
                Decodified_File(vector<char> v,string ex,string n)
                {
                    this->digits=v;
                    this->ext=ex;
                    this->name=n;
                }
                vector<char> getDigits()
                {
                    return this->digits;
                }
                string getExt()
                {
                    return this->ext;
                }
                string getName()
                {
                    return this->name;
                }

        };
        Compressor();
        Codified_File* compress(vector<char> digits,string ext,string nam);
        Decodified_File* decompress(Codified_File* code);
        List<Huffman_Node *> * VecToList(vector<Huffman_Node::Character> vec);
        List<Huffman_Node*>* sort(List<Huffman_Node*>* list);
        vector<Code> codifier(Huffman_Tree tree,vector<Huffman_Node::Character> keys);
        void print(List<Huffman_Node*> list);
        string backTrackCoder(char key, Huffman_Node* temp,string code);
        void print(vector<Code>,vector<char> word);
        string encoder(vector<Code> codes, vector<char> keys);
};


#endif //RAID_5_COMPRESSOR_H
