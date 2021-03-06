#include "LineStripSet.hpp"

LineStripSet::LineStripSet(Material& in_material, int in_nvertices, double* in_vertex, bool in_ignoreExtent, bool in_bboxChange)
  : PrimitiveSet(in_material, in_nvertices, in_vertex, GL_LINE_STRIP, 1, in_ignoreExtent, in_bboxChange)
{
  material.lit = false;
  if (material.line_antialias) blended = true;
}

void LineStripSet::drawElement(RenderContext* renderContext, int index)
{
  if (index < nvertices-1) 
    glDrawArrays(type, index*nverticesperelement, 2*nverticesperelement);
}  
