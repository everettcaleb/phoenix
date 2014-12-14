#pragma once
#ifndef INCLUDE_PHOENIX_IGAMELOOP_H
#define INCLUDE_PHOENIX_IGAMELOOP_H

class IGameLoop 
{
private:
    IGameLoop(const IGameLoop& other) {}

protected:
    IGameLoop() {}

public:
    virtual ~IGameLoop() {}

    virtual float getDeltaTime() const = 0;

    virtual void run() = 0;
};

#endif //INCLUDE_PHOENIX_IGAMELOOP_H