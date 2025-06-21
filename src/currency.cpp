#include "currency.h"

void Currency::addBronze(int64_t amount) {
    if (amount > 0)
        total_ += amount;
}

void Currency::addSilver(int64_t amount) {
    addBronze(amount * 100);
}

void Currency::addGold(int64_t amount) {
    addBronze(amount * 10000);
}

void Currency::addPlatinum(int64_t amount) {
    addBronze(amount * 1000000);
}

bool Currency::subtractBronze(int64_t amount) {
    if (amount < 0 || amount > total_)
        return false;
    total_ -= amount;
    return true;
}

int64_t Currency::totalBronze() const {
    return total_;
}

int Currency::bronze() const {
    return static_cast<int>(total_ % 100);
}

int Currency::silver() const {
    return static_cast<int>((total_ / 100) % 100);
}

int Currency::gold() const {
    return static_cast<int>((total_ / 10000) % 100);
}

int Currency::platinum() const {
    return static_cast<int>(total_ / 1000000);
}
