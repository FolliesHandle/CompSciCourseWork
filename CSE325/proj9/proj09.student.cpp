/*******************************************************
 * Dominic Mazza
 * Project 9
*******************************************************/ 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>


/**
 * Struct representing a single pagetable entry
*/
struct PageTableEntry{
    bool valid;
    bool writeable;
    bool present;
    bool referenced;
    bool modified;
    int frameNum;
};

/**
 * Class representing a pagetable
*/
class PageTable
{
private:
    std::vector<PageTableEntry> mPageTable; ///< vector of page table entries
public:
    /**
     * Name: PageTable
     * 
     * Purpose: Initialize empty pagetable
     * Receive: None
     * Return: None
    */
    PageTable()
    {
        for (int i = 0; i < 16; i++)
        {
            PageTableEntry pte;
            pte.valid = false;
            pte.writeable = false;
            pte.present = false;
            pte.referenced = false;
            pte.modified = false;
            pte.frameNum = 0x00;
            mPageTable.push_back(pte);
        }
    }

    /**
     * Name: ParseFile
     * 
     * Purpose: Parses proc file given with -proc
     * Receives: Filepath for proc file
     * Returns: bool representing whether or not parsing was successful
    */
    bool ParseFile(std::string inputFile)
    {
        std::ifstream stream(inputFile);
        if (!stream)
        {
            std::cout << "Invalid ram file, please try again." << std::endl;
            return false;
        }
        
        std::string line;

        while(std::getline(stream, line))
        {
            std::stringstream ss(line);
            std::string pageNum;
            ss >> pageNum;
            pageNum = "0x" + pageNum;

            int pageInt = std::strtol(pageNum.c_str(), NULL, 0);

            std::string write;
            ss >> write;
            mPageTable[pageInt].valid = true;
            if (write == "1")
            {
                mPageTable[pageInt].writeable = true;
            }
        }
        return true;
    }

    /**
     * Name: Display
     * 
     * Purpose: Displays page table per formatting specifications
     * Receives: None
     * Returns: None
    */
    void Display()
    {
        std::cout << "     V W P R M FN\n-----------------\n";
        for (size_t i = 0; i < mPageTable.size(); i++)
        {
            std::cout << "[" << std::hex << i << "]: ";
            std::cout << (mPageTable[i].valid ? "1" : "0") << " ";
            std::cout << (mPageTable[i].writeable ? "1" : "0") << " ";
            std::cout << (mPageTable[i].present ? "1" : "0") << " ";
            std::cout << (mPageTable[i].referenced ? "1" : "0") << " ";
            std::cout << (mPageTable[i].modified ? "1" : "0") << " ";
            std::cout << std::setfill('0') << std::setw(2) << std::hex << mPageTable[i].frameNum;
            std::cout << std::endl;
        }
    }
};


int main(int argc, char* argv[])
{
    std::string procFile;
    std::string refFile;
    bool debug = false;
    bool proc = false;
    bool ref = false;
    /**
     * Loop for handling arguments
    */
    for (int i = 1; i < argc; i++)
    {
        std::string temp = std::string(argv[i]);
        if (temp[0] == '-')
        {
            if (temp == "-proc")
            {
                if (proc)
                {
                    std::cout << "Used -proc too many times\n";
                    exit(1); 
                }
                else if ((i + 1) == argc)
                {
                    std::cout << "-proc flag requires a trailing filename\n";
                    exit(1);
                }
                else
                {
                    procFile = std::string(argv[i+1]);
                    i++;
                    proc = true;
                }
            }
            else if (temp == "-refs")
            {
                if (ref)
                {
                    std::cout << "Used -refs too many times\n";
                    exit(1); 
                }
                else if ((i + 1) == argc)
                {
                    std::cout << "-refs flag requires a trailing filename\n";
                    exit(1);
                }
                else
                {
                    refFile = std::string(argv[i+1]);
                    i++;
                    ref = true;
                }
            }
            else if (temp == "-debug")
            {
                debug = true;
            }
            else
            {
                std::cout << "Invalid flag, valid flags are -proc <procFile>, -refs <refFile>, or -debug\n";
            }
        }
        else
        {
            std::cout << "Invalid token supplied\n";
            exit(1);
        }
    }

    /**
     * Page table initialization and proc file parsing
    */
    PageTable pt;
    if(!pt.ParseFile(procFile))
    {
        exit(1);
    }
    pt.Display();
    std::ifstream inStr(refFile);

    if (!inStr)
    {
        std::cout << "Invalid ref file";
        exit(1);
    }

    int wrCount = 0;
    int rdCount = 0;

    /**
     * Ref parsing
    */
    std::string line;
    while (std::getline(inStr, line))
    {
        std::stringstream ss(line);
        std::string op;
        ss >> op;
        if (op == "RD")
        {
            rdCount++;
        }
        else if (op == "WR")
        {
            wrCount++;
        }
        std::string address;
        ss >> address;
        address = "0x" + address;

        int addressInt = std::strtol(address.c_str(), NULL, 0);

        int pageNum = addressInt >> 10;
        int pageOffset = (addressInt >> 0) & ((1<<11)-1);

        address = address.substr(2);
        std::cout << op << " " << address << " " << std::hex << pageNum << " " 
            << std::setfill('0') << std::setw(3) << std::hex << pageOffset << std::endl;
        if (debug)
        {
            pt.Display();
            std::cout << std::endl;
        }
    }
    std::cout << "Read Operations: " << std::dec << rdCount << std::endl;
    std::cout << "Write Operations: " << std::dec << wrCount << std::endl;
    pt.Display();
}