// EventHandler.h
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class EventHandler {
public:
    virtual ~EventHandler() = default;
    virtual bool pollEvent() = 0;
    virtual int getEventType() = 0;
    virtual bool isQuitEvent() = 0;
    virtual bool isKeyDownEvent() = 0;
    virtual int getKeyCode() = 0;
};

#endif // EVENTHANDLER_H
