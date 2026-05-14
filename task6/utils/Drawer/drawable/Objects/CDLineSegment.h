//
// Created by xac1k on 4/9/26.
//

#ifndef TESTS_CDLINESEGMENT_H
#define TESTS_CDLINESEGMENT_H

#include "../../shape/CLineSegment.h"
#include "../Interface/ICanvasDrawable.h"

class CDLineSegment : public CLineSegment, public ICanvasDrawable {
public:
    void Draw(ICanvas &canvas) const override;
};

#endif //TESTS_CDLINESEGMENT_H