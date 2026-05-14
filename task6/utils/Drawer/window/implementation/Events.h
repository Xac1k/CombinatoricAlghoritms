//
// Created by xac1k on 5/7/26.
//

#include "../Interface/Events.h"

// Конкретные события
class MouseMoveEvent : public IEvent {
public:
    DECLARE_EVENT_TYPE(MouseMoveEvent)
    float x, y;
    MouseMoveEvent(float x, float y) : x(x), y(y) {}
};

class MouseClickEvent : public IEvent {
public:
    DECLARE_EVENT_TYPE(MouseClickEvent)
    enum class Button { Left, Right, Middle };
    Button button;
    float x, y;
    MouseClickEvent(Button btn, float x, float y) : button(btn), x(x), y(y) {}
};

class KeyPressEvent : public IEvent {
public:
    DECLARE_EVENT_TYPE(KeyPressEvent)
    int keyCode;
    bool alt, ctrl, shift;
    KeyPressEvent(const int code, const bool a, const bool c, const bool s)
        : keyCode(code), alt(a), ctrl(c), shift(s) {}
};

class WindowResizeEvent : public IEvent {
public:
    DECLARE_EVENT_TYPE(WindowResizeEvent)
    int width, height;
    WindowResizeEvent(int w, int h) : width(w), height(h) {}
};
