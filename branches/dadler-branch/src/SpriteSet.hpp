#ifndef SPRITE_SET_HPP
#define SPRITE_SET_HPP

#include "Shape.hpp"

//
// SPRITESET
//

class SpriteSet : public Shape {
private:
  ARRAY<Vertex> vertex;
  ARRAY<float>  size;

public:
  SpriteSet(Material& in_material, int nvertex, double* vertex, int nsize, double* size);
  ~SpriteSet();
  void render(RenderContext* renderContext);
  void draw(RenderContext* renderContext);
};

#endif // SPRITE_SET_HPP
