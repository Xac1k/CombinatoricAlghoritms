//
// Created by xac1k on 4/9/26.
//

#ifndef TESTS_CDTRIANGLE_H
#define TESTS_CDTRIANGLE_H

#include "../../shape/CTriangle.h"
#include "../Interface/ICanvasDrawable.h"

class CDTriangle : public CTriangle, public ICanvasDrawable {
public:
    void Draw(ICanvas &canvas) const override;
};


#endif //TESTS_CDTRIANGLE_H