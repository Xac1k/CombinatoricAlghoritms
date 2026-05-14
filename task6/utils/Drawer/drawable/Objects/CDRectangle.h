//
// Created by xac1k on 4/9/26.
//

#ifndef TESTS_CDRECTANGLE_H
#define TESTS_CDRECTANGLE_H


#include "../../shape/CRectangle.h"
#include "../Interface/ICanvasDrawable.h"

class CDRectangle : public CRectangle, public ICanvasDrawable {
public:
    void Draw(ICanvas &canvas) const override;
};

#endif //TESTS_CDRECTANGLE_H