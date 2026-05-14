//
// Created by xac1k on 4/10/26.
//

#ifndef MAIN_PARSERSTDIN_H
#define MAIN_PARSERSTDIN_H

#include "../drawable/Interface/ICanvasDrawable.h"
#include "memory"

class ParserJSON {
public:
    static std::vector<std::unique_ptr<ICanvasDrawable>> Parse(const std::string& line);
};

#endif //MAIN_PARSERSTDIN_H