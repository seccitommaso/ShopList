
#ifndef SHOPLIST_ITEM_H
#define SHOPLIST_ITEM_H

#include <iostream>
#include <string>
class Item {
private:
    std::string name;
    std::string category;
    int quantity;
public:
    const std::string &getName() const;
    const std::string &getCategory() const;
    int getQuantity() const;
    Item(std::string nome,std::string cat,int qty);
};

#endif //SHOPLIST_ITEM_H
