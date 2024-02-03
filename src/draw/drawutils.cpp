#include "drawutils.h"

// Todo: replace w/ vertex count
void draw_vertex_count(uint16_t num_verticies, bgfx::Encoder* encoder)
{
    bgfx::VertexLayout layout;
    layout.begin().add(bgfx::Attrib::Position, 1, bgfx::AttribType::Uint8).end();
    bgfx::TransientVertexBuffer tbh;
    bgfx::allocTransientVertexBuffer(&tbh, num_verticies, layout);
    encoder->setVertexBuffer(0, &tbh);
}
