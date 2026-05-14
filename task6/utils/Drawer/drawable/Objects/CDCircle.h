//
// Created by xac1k on 4/9/26.
//

#ifndef TESTS_CDCIRCLE_H
#define TESTS_CDCIRCLE_H

#include "../../shape/CCircle.h"
#include "../Interface/ICanvasDrawable.h"

class CDCircle : public CCircle, public ICanvasDrawable {
public:
    void Draw(ICanvas &canvas) const override;
};

#endif //TESTS_CDCIRCLE_H