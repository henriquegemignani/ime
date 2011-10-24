#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "../Drawable.h"

class Circle: public Drawable {
public:
    Circle(float radius) : Drawable(), radius_(radius) {}
    virtual ~Circle() {}
    float radius() const { return radius_; }

    void Render();
private:
    float radius_;
};

#endif /* CIRCLE_H_ */
