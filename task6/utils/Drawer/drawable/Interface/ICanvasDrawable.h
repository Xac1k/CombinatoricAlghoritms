//
// Created by xac1k on 4/7/26.
//

#ifndef TESTS_ICANVASDRAWABLE_H
#define TESTS_ICANVASDRAWABLE_H
#include "../../canvas/Interface/ICanvas.h"


class ICanvasDrawable {
public:
    virtual ~ICanvasDrawable()=default;
    virtual void Draw(ICanvas& canvas) const=0;
};


#endif //TESTS_ICANVASDRAWABLE_H