//
// Created by xac1k on 4/4/26.
//

#ifndef TESTS_ISOLIDSHAPE_H
#define TESTS_ISOLIDSHAPE_H
#include "IShape.h"


class ISolidShape : public IShape {
public:
    uint32_t GetFillColor() const;
    ISolidShape& SetFillColor(uint32_t color);

private:
    uint32_t m_FillColor = 0;
};


#endif //TESTS_ISOLIDSHAPE_H