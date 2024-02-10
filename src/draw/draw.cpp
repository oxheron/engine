#include "draw.h"

bgfx::Encoder* full_screen_quad(bgfx::Encoder* encoder)
{
    if (encoder == nullptr) encoder = bgfx::begin();

    encoder->setVertexCount(3);

    return encoder;
}
