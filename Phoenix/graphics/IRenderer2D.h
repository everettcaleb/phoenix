#pragma once
#ifndef INCLUDE_PHOENIX_IRENDERER2D_H
#define INCLUDE_PHOENIX_IRENDERER2D_H

#include "Color.h"
#include "Point.h"
#include "Rect.h"

class IRenderer2D
{
private:
    IRenderer2D(const IRenderer2D& other) {}
    
protected:
    IRenderer2D() {}
    
public:
    virtual ~IRenderer2D() {}
    
    virtual void clear(const Color color) = 0;
    virtual void drawLine(const Color color, const Point &point1, const Point &point2) = 0;
    virtual void drawPoint(const Color color, const Point &point) = 0;
    virtual void drawRect(const Color color, const Rect &rect) = 0;
    virtual void drawCircle(const Color color, const Point &center, const int radius) = 0;
    virtual void drawTriangle(const Color color, const Point& point1, const Point& point2, const Point& point3) = 0;
    virtual void fillRect(const Color color, const Rect &rect) = 0;
    virtual void fillCircle(const Color color, const Point &center, const int radius) = 0;
    virtual void fillTriangle(const Color color, const Point& point1, const Point& point2, const Point& point3) = 0;
    virtual void present() = 0;
};

#endif //INCLUDE_PHOENIX_IRENDERER2D_H
