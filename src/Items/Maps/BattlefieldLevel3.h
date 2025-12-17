#ifndef BATTLEFIELDLEVEL3_H
#define BATTLEFIELDLEVEL3_H

#include "Map.h"

class BattlefieldLevel3: public Map {
public:
    explicit BattlefieldLevel3(QGraphicsItem *parent= nullptr);

    qreal getFloorHeight() override;
};

#endif