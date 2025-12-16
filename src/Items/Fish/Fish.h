#ifndef FISH_H
#define FISH_H

#include "../Item.h"

class Fish : public Item {
public:
    enum FishType { PLAYER, SMALL, BIG };
    
    explicit Fish(QGraphicsItem *parent, const QString &pixmapPath, FishType type, int size);
    
    int getSize() const { return size; }
    FishType getType() const { return type; }
    
    virtual void grow(int amount);
    
protected:
    FishType type;
    int size;
};

#endif