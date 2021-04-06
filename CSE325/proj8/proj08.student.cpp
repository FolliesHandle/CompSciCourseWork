/***********************************************
 * Dominic Mazza
 * Computer Project #8
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

std::string columnHeaders = "     V M Tag  0  1  2  3  4  5  6  7\n------------------------------------\n"; // Column headers for cache

typedef unsigned short int uint16;


// Class representing register unit
class RegisterUnit
{
private:
    uint16 reg[16];

public:
    /*-------------------------------------------------------------
    Name: RegisterUnit
    Purpose: Initialize empty register unit
    -------------------------------------------------------------*/
    RegisterUnit()
    {
        for (unsigned i = 0; i < 16; i++)
            reg[i] = 0x00;
    }

    /*-------------------------------------------------------------
    Name: operator[]
    Purpose: Accesses register by index
    Receives: index of register
    Returns: contents of register
    -------------------------------------------------------------*/
    uint16 &operator[](unsigned I)
    {
        return reg[I & 0xf];
    }

    /*-------------------------------------------------------------
    Name: operator[]
    Purpose: Accesses register by index
    Receives: index of register
    Returns: contents of register
    -------------------------------------------------------------*/
    const uint16 &operator[](unsigned I) const
    {
        return reg[I & 0xf];
    }

    /*-------------------------------------------------------------
    Name: Display
    Purpose: Displays registers in format requested
    Recieves: output stream to display on
    -------------------------------------------------------------*/
    void display(std::ostream &out) const
    {
        std::ios old(nullptr);
        old.copyfmt(out);

        out << std::setfill('0') << std::hex;

        for (unsigned i = 0; i < 4; i++)
        {
            unsigned n = i;
            out << "R" << std::setw(1) << n << ": "
                << std::setw(4) << reg[n] << "  ";
            n = n + 4;
            out << "R" << std::setw(1) << n << ": "
                << std::setw(4) << reg[n] << "  ";
            n = n + 4;
            out << "R" << std::setw(1) << n << ": "
                << std::setw(4) << reg[n] << "  ";
            n = n + 4;
            out << "R" << std::setw(1) << n << ": "
                << std::setw(4) << reg[n] << std::endl;
        }

        out.copyfmt(old);
    }
};

// Class representing RAM
class RamUnit
{
public:
    std::map<int, std::vector<int>> ram;
    /*-------------------------------------------------------------
    Name: RamUnit
    Purpose: Initialize empty ramunit
    -------------------------------------------------------------*/
    RamUnit()
    {
        std::vector<int> temp;
        for (int i = 0; i < 16; i++)
        {
            temp.push_back(0x00);
        }
        for (uint16_t i = 0x0000; i < 0x0080; i += 0x0010)
        {
            ram.insert(std::make_pair(i, temp));
        }
    }
    /*-------------------------------------------------------------
    Name: Display
    Purpose: Displays ram in format requested
    -------------------------------------------------------------*/
    void Display()
    {
        for (int i = 0x0000; i < 0x0080; i += 0x0010)
        {
            std::cout << std::setfill('0') << std::setw(4) << std::hex << i << ": ";
            for (size_t j = 0; j < ram.at(i).size(); j++)
            {
                std::cout << std::setfill('0') << std::setw(2) << std::hex << ram.at(i)[j] << " ";
            }
            std::cout << std::endl;
        }
    }
    /*-------------------------------------------------------------
    Name: ParseFile
    Purpose: Parse ramFile and add ram contents to ram
    Recieves: ramFile path
    Return: bool representing success or failure
    -------------------------------------------------------------*/
    bool ParseFile(std::string ramFile)
    {
        std::ifstream inputStr(ramFile);
        if (!inputStr)
        {
            std::cout << "Invalid ram file, please try again." << std::endl;
            return false;
        }
        std::string line;
        while (std::getline(inputStr, line))
        {
            std::vector<int> temp;
            std::stringstream lineStream(line);
            std::string key;
            lineStream >> key;
            key = "0x" + key;

            int keyInt = std::strtol(key.c_str(), NULL, 0);

            for (int i = 1; i < 17; i++)
            {
                std::stringstream binaryStream;
                std::string tempStr;
                int tempU8;
                lineStream >> tempStr;
                binaryStream << std::hex << "0x" << tempStr;
                binaryStream >> tempU8;
                temp.push_back(tempU8);
            }

            std::map<int, std::vector<int>>::iterator it = ram.find(keyInt);
            if (it != ram.end())
            {   
                ram[keyInt] = temp;
            }
            else
            {
                ram.insert(std::make_pair(keyInt, temp));
            }
        }
        inputStr.close();
        return true;
    }
};

// Struct representing cache line
struct CacheLine
{
    int lineNum;
    bool valid;
    bool mem;
    int tag;
    std::vector<int> data;
};

// Class that stores and handles cache line in cache
class Cache
{
private:
    std::vector<CacheLine> cache;

public:
    /*-------------------------------------------------------------
    Name: Cache
    Purpose: Initialize empty cache
    -------------------------------------------------------------*/
    Cache()
    {
        std::vector<int> temp;
        for (int i = 0; i < 8; i++)
        {
            temp.push_back(0x00);
        }
        for (int i = 0; i<8; i++)
        {
            CacheLine c;
            c.lineNum = i;
            c.valid = false;
            c.mem = false;
            c.tag = 0x000;
            c.data = temp;
            cache.push_back(c);
        }
    }

    /*-------------------------------------------------------------
    Name: Display
    Purpose: Displays cache in format requested
    -------------------------------------------------------------*/
    void Display()
    {
        std::cout << columnHeaders;
        for (size_t i = 0; i < cache.size(); i++)
        {
           std::cout << " [" << cache[i].lineNum << "] " <<  int(cache[i].valid) << " " 
            << int(cache[i].mem) << " " << std::setfill('0') << std::setw(3) << std::hex << cache[i].tag << " ";
            for (int j = 0; j < 8; j++)
            {
                std::cout << std::setfill('0') << std::setw(2) << std::hex << cache[i].data[j] << " ";
            }
            std::cout << std::endl;
        }
    }
    /*-------------------------------------------------------------
    Name: operator[]
    Purpose: Accesses register by index
    Receives: index of register
    Returns: contents of register
    -------------------------------------------------------------*/
    CacheLine &operator[](unsigned I)
    {
        return cache[I & 0xf];
    }

    /*-------------------------------------------------------------
    Name: operator[]
    Purpose: Accesses register by index
    Receives: index of register
    Returns: contents of register
    -------------------------------------------------------------*/
    const CacheLine &operator[](unsigned I) const
    {
        return cache[I & 0xf];
    }
};

/*-------------------------------------------------------------
    Name: ParseInputFile
    Purpose: Parse inputFile and add ram contents to vector
    Recieves: inputFile path
    Return: vector of instructions
-------------------------------------------------------------*/
std::vector<std::string> ParseInputFile(std::string inputFile)
{
    std::ifstream inputStr(inputFile);
    std::vector<std::string> temp;
    if (!inputStr)
    {
        std::cout << "Invalid ram file, please try again." << std::endl;
        temp.clear();
        return temp;
    }
    std::string line;
    while(std::getline(inputStr, line))
    {
        temp.push_back(line);
    }
    return temp;
}

int main(int argc, char *argv[])
{
    std::string inputFile;
    std::string ramFile;
    bool ramFileBool = false;
    bool debug = false;
    bool inputFlag = false;

    for (int i = 1; i < argc; i++)
    {
        std::string temp = std::string(argv[i]);
        if (temp[0] == '-')
        {
            if (temp == "-input")
            {
                if (inputFlag)
                {
                    std::cout << "Too many input flags" << std::endl;
                }
                if ((i + 1) == argc)
                {
                    std::cout << "-input flag requires trailing filename" << std::endl;
                    exit(1);
                }
                else
                {
                    inputFlag = true;
                    inputFile = std::string(argv[i + 1]);
                    i++;
                }
            }
            else if (temp == "-ram")
            {
                if ((i + 1) == argc || ramFileBool)
                {
                    std::cout << "-ram flag used improperly" << std::endl;
                    exit(1);
                }
                else
                {
                    ramFile = std::string(argv[i + 1]);
                    ramFileBool = true;
                    i++;
                }
            }
            else if (temp == "-debug")
            {
                debug = true;
            }
            else
            {
                std::cout << "Invalid flag, valid flags are -input {input file}, -ram {ram file} and -debug" << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid tokens." << std::endl;
        }
    }
    RegisterUnit reg;
    Cache c;
    RamUnit r;
    if (ramFileBool)
    {
        if (!r.ParseFile(ramFile))
        {
            exit(1);
        }
    }

    if (debug)
    {
        reg.display(std::cout);
        c.Display();
        r.Display();
    }
    std::vector<std::string> instructions;
    if((instructions = ParseInputFile(inputFile)).empty())
    {
        exit(1);
    }

    for (auto item : instructions)
    {
        std::string instr;
        std::string regNum;
        std::string addressStr;
        std::stringstream itemStr(item);
        itemStr >> instr >> regNum >> addressStr;
        addressStr = "0x" + addressStr;

        uint address = std::strtol(addressStr.c_str(), NULL, 0);
        addressStr = addressStr.substr(2);
        uint cacheTag = (address >> 6);
        uint cacheLine = ((address >> 3) & ((1 << 3)-1));
        uint byteOffset = ((address >> 0) & ((1 << 3)-1));
        bool hit = true;
        if (!(c[cacheLine].valid && c[cacheLine].tag == cacheTag))
        {
            hit = false;
            if (c[cacheLine].valid && c[cacheLine].mem)
            {
                int temp_addr = (c[cacheLine].tag << 6) + (c[cacheLine].lineNum << 3);
                int ram_temp = temp_addr&0xFFF0;
                if (r.ram.find(ram_temp) == r.ram.end())
                {
                    r.ram.insert(std::make_pair(ram_temp, c[cacheLine].data));
                }
                else
                {
                    for (size_t i = 0; i < c[cacheLine].data.size(); i++)
                    {
                        r.ram[ram_temp][i + (temp_addr & 0x000F)] = c[cacheLine].data[i];
                    }
                }

            }
            if (r.ram.find(address) == r.ram.end())
            {
                std::vector<int> temp;
                for (int i = 0; i < 16; i++)
                {
                    temp.push_back(0x00);
                }
                r.ram.insert(std::make_pair((address&0xFFF0), temp));
            }
            for (uint i = 0; i < 8; i++)
            {
                if ((address&0x000F)>=0x0008)
                {
                    c[cacheLine].data[i] = r.ram[(address&0xFFF0)][i+8];
                }
                else
                {
                    c[cacheLine].data[i] = r.ram[(address&0xFFF0)][i];
                } 
            }
            c[cacheLine].mem = false;
            c[cacheLine].tag = cacheTag;
            c[cacheLine].valid = true;
        }
        int data;
        if (instr == "LDR")
        {
            data = (c[cacheLine].data[byteOffset] << 8);
            data += c[cacheLine].data[byteOffset + 1];
            reg[std::strtol(regNum.c_str(), NULL, 0)] = data;
        }
        else if (instr == "STR")
        {
            data = reg[std::strtol(regNum.c_str(), NULL, 0)];
            int dataTop = ((data & 0xFF00) >> 8);
            int dataBot = (data & 0x00FF);
            c[cacheLine].data[byteOffset] = dataTop;
            c[cacheLine].data[byteOffset + 1] = dataBot;
            c[cacheLine].mem = 1;
        }


        std::cout << instr << " " << regNum << " " << addressStr << " " << std::setfill('0') << 
        std::setw(3) << std::hex << cacheTag << " " << cacheLine << " " << byteOffset << " " << 
        (hit ? "H ": "M ") << std::setfill('0') << std::setw(4) << std::hex << data << std::endl;
        if (debug)
        {
            c.Display();
            
        }
    }
    
    reg.display(std::cout);
    std::cout << std::endl;
    c.Display();
    std::cout << std::endl;
    r.Display();
    std::cout << std::endl;
}