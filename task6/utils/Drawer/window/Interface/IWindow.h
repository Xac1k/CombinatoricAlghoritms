//
// Created by xac1k on 5/7/26.
//

#ifndef MAIN_IWINDOW_H
#define MAIN_IWINDOW_H

#include "EventDispatcher.h"
#include "../../canvas/Interface/ICanvas.h"

class IWindow : public ICanvas, public EventDispatcher {};

#endif //MAIN_IWINDOW_H