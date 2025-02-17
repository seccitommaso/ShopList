//
// Created by tommaso on 17/02/25.
//

#include "Item.h"
#include <utility>
const std::string &Item::getName() const{
    return name;
}

const std::string &Item::getCategory() const {
    return category;
}

int Item::getQuantity() const {
    return quantity;
}

Item::Item(std::string nome, std::string cat, int qty) : name(std::move(nome)),category(std::move(cat)),quantity(qty){}
