/*
 * Layer.h
 *
 *  Created on: 31/03/2011
 *      Author: Henrique
 */
#ifndef LAYER_H_
#define LAYER_H_

#include <vector>
#include "../Displayable.h"

class Layer : public Displayable {
public:
    Layer() { childs_.clear(); }
    virtual ~Layer();

    void AddDisplayable(Displayable *obj);
    void RemoveDisplayable(Displayable *obj);

    virtual void Update(float delta_t);
    virtual void Render();

private:
    std::vector<Displayable*> childs_;
};

#endif /* LAYER_H_ */
