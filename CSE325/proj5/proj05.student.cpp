/***************************************************
 * Dominic Mazza
 * Project 5
 ***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

const std::string inventoryFile = "./inventory.old";
const std::string orderFile = "./orders";


// Represents an inventory item
struct inventoryItem
{
    int idNum;
    double price;
    int quantity;
    std::string seedType;
};

// Represets an order item
struct orderItem
{
    int custId;
    int productId;
    int orderQuantity;
};

// Represents the input to the producer thread
struct prodInput
{
    std::vector<orderItem>* orders;
    std::vector<inventoryItem>* inventory;
};

// Represents a log entry
struct logEntry
{
    int custId;
    int prodId;
    std::string prodDes;
    int quantity;
    double amount;
    std::string result;
};

/************************************************************************
 * Name: consumer
 * 
 * Purpose: Consumer thread to handle order file parsing
 * Receive: Pointer to empty vector of orderItem structs
 * Returns: Pointer to filled vector of orderItem structs
 ***********************************************************************/
void* consumer(void* ptr)
{
    int custId;
    int productId;
    int orderQuantity;
    std::ifstream ordFile(orderFile);
    std::string line;
    while (std::getline(ordFile, line))
    {
        std::istringstream iss(line);
        if (!(iss >> custId >> productId >> orderQuantity))
        {
            printf("File format error");
        }
        orderItem item = {.custId=custId, .productId=productId, .orderQuantity=orderQuantity};
        ((std::vector<orderItem>*) ptr)->push_back(item);
    }
    ordFile.close();
    pthread_exit(NULL);
}

/************************************************************************
 * Name: producer
 * 
 * Purpose: Producer thread to handle orders and inventory altering
 * Receive: Pointer to prodInput struct
 * Returns: Pointer to prodInput struct
 ***********************************************************************/
void* producer(void* ptr)
{
    std::vector<orderItem> &orders = *(((prodInput*) ptr)->orders);
    std::vector<inventoryItem> &inventory = *(((prodInput*) ptr)->inventory);
    std::ofstream LogFile("log");
    for (size_t i = 0; i < orders.size(); ++i)
    {
        bool found = false;
        for (size_t j = 0; j < inventory.size(); ++j)
        {
            if (inventory[j].idNum == orders[i].productId)
            {
                found = true;
                logEntry logTemp;
                logTemp.custId = orders[i].custId;
                logTemp.prodId = orders[i].productId;
                logTemp.prodDes = inventory[j].seedType;
                logTemp.quantity = orders[i].orderQuantity;
                logTemp.amount = logTemp.quantity * inventory[j].price;

                if (logTemp.quantity > inventory[j].quantity)
                {
                    logTemp.result = "rejected";
                }
                else
                {
                    logTemp.result = "filled";
                    inventory[j].quantity -= logTemp.quantity;
                }

                LogFile << std::left << std::setw(7) << logTemp.custId << " ";
                LogFile << std::left << std::setw(6) << logTemp.prodId << " ";
                LogFile << std::left << std::setw(30) << logTemp.prodDes << " ";
                LogFile << std::left << std::setw(5) << logTemp.quantity << " ";
                LogFile << std::left << std::setw(12) << std::setprecision(2) << std::fixed << logTemp.amount << " ";
                LogFile << std::left << std::setw(8) << logTemp.result << "\n";
                std::cout << logTemp.custId << " " << logTemp.prodId << " " << logTemp.prodDes << " " << logTemp.quantity << " " << logTemp.amount << " " << logTemp.result << std::endl;
            }
        }

        if (!found)
        {
            LogFile << std::left << std::setw(7) << orders[i].custId << " ";
            LogFile << std::left << std::setw(6) << orders[i].productId << " ";
            LogFile << std::left << std::setw(30) << "NA" << " ";
            LogFile << std::left << std::setw(5) << orders[i].orderQuantity << " ";
            LogFile << std::left << std::setw(12) << std::setprecision(2) << std::fixed << 0.00 << " ";
            LogFile << std::left << std::setw(8) << "rejected" << "\n";
        }
    }
    LogFile.close();
    pthread_exit(NULL);
}

/************************************************************************
 * Name: main
 * 
 * Purpose: Handles inventory parsing, thread management, and inventory
 * reformatting
 * Receive: Nothing
 * Returns: Exit code
 ***********************************************************************/
int main()
{
    std::ifstream inFile(inventoryFile);
    int idNum, quantity;
    double price;
    std::string seedType;
    std::vector<inventoryItem> inventory;

    std::string line;
    while (std::getline(inFile, line))
    {
        std::stringstream iss(line);
        if (!(iss >> idNum >> price >> quantity))
        {
            printf("File format error");
        }
        std::getline(iss, seedType);
        seedType = seedType.substr(1, seedType.size());
        inventoryItem item = {.idNum=idNum, .price=price, .quantity=quantity, .seedType=seedType};
        inventory.push_back(item);
        
    }
    inFile.close();


    std::vector<orderItem> orders;
    pthread_t pthread_consumer;
    pthread_create(&pthread_consumer, NULL, consumer, (void*) &orders);
    pthread_join(pthread_consumer, NULL);

    prodInput prod = {.orders=&orders, .inventory=&inventory};

    pthread_t pthread_producer;
    pthread_create(&pthread_producer, NULL, producer, (void*) &prod);
    pthread_join(pthread_producer, NULL);

    std::ofstream invNew("inventory.new");

    for (size_t i = 0; i < inventory.size(); ++i)
    {
        invNew << std::left << std::setw(6) << inventory[i].idNum << " ";
        invNew << std::right << std::setw(5) << std::setprecision(2) << std::fixed << inventory[i].price << " ";
        invNew << std::right << std::setw(5) << inventory[i].quantity << " ";
        invNew << std::left << std::setw(30) << inventory[i].seedType << "\n";
    }
    invNew.close();
}

