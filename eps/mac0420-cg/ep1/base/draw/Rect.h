#ifndef RECT_H_
#define RECT_H_

#include "../Drawable.h"
#include "../Vector2D.h"

class Rect: public Drawable {
public:
	Rect(Vector2D size) : Drawable(), size_(size) {}
    virtual ~Rect() {}
    Vector2D size() const { return size_; }

    void Render();
private:
    Vector2D size_;
};

#endif /* RECT_H_ */
