#include "framebuffer.h"
#include "bgfx/defines.h"

// external
#include <bgfx/bgfx.h>

// std
#include <vector>

// A shader that can be used is
/* $output v_texcoord

void main()
{
    vec2 vertices[3] = vec2[3](vec2(-1,-1), vec2(3,-1), vec2(-1, 3));
    gl_Position = vec4(vertices[gl_VertexID], 0, 1);
    v_texcoord = 0.5 * gl_Position.xy + vec2(0.5);
} */

// Then you can use the texture bound here

TargetSpec TargetSpec::init(bgfx::TextureHandle handle, uint16_t layer)
{
    TargetSpec spec;
    spec.handle = handle;
    spec.layer = layer;
    spec.is_valid = true;
    return spec;
}

TargetSpec TargetSpec::init(bgfx::TextureFormat::Enum format)
{
    TargetSpec spec;
    spec.format = format;
    return spec;
}

TargetSpec TargetSpec::init_depth()
{
    return TargetSpec::init(
        bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::D32F, 
            BGFX_TEXTURE_RT) 
        ? bgfx::TextureFormat::D32F : bgfx::TextureFormat::D24); 
}

TargetSpec TargetSpec::init_rgba8() 
{ 
    return TargetSpec::init(bgfx::TextureFormat::RGBA8);
};

Framebuffer::Framebuffer(size_t width, size_t height, TargetSpec* targets, 
    size_t count)
{
    std::vector<bgfx::Attachment> attachments;
    
    this->width = width;
    this->height = height;

    for (size_t i = 0; i < count; i++)
    {
        bgfx::TextureHandle handle = targets[i].is_valid ?  
            targets[i].handle : 
            bgfx::createTexture2D(width, height, false, 1, targets[i].format, 
            BGFX_TEXTURE_RT); 

        attachments.push_back(bgfx::Attachment());
        attachments[i].init(handle, bgfx::Access::Write, targets[i].layer);
    }

    fb = bgfx::createFrameBuffer(count, attachments.data(), true);
}

Framebuffer::~Framebuffer()
{
    bgfx::destroy(fb);
}


bgfx::Encoder* Framebuffer::render_framebuffer(bgfx::UniformHandle handle, 
    uint8_t stage, uint8_t attachment, bgfx::Encoder* encoder)
{
    if (!encoder) encoder = bgfx::begin();

    encoder->setTexture(stage, handle, getTexture(fb, attachment));

    return encoder; 
}
