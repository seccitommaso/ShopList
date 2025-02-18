
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
//imposta qty a zero se viene inserito un valore negativo
Item::Item(std::string nome, std::string cat, int qty)
    : name(std::move(nome)),category(std::move(cat)),quantity(qty < 0 ? 0: qty){}
