#pragma once

// external
#include <bgfx/bgfx.h>

struct TargetSpec
{
    bgfx::TextureHandle handle;
    bool is_valid = false;
    uint16_t layer = 0;
    bgfx::TextureFormat::Enum format;

    static TargetSpec init(bgfx::TextureHandle handle, uint16_t layer = 0);
    static TargetSpec init(bgfx::TextureFormat::Enum format);
    static TargetSpec init_depth();
    static TargetSpec init_rgba8();
};

// RAII object for framebuffer with managment options 
class Framebuffer
{
private:
    bgfx::FrameBufferHandle fb; 

    size_t width, height;

public:
    Framebuffer(Framebuffer&) = delete;
    Framebuffer& operator=(Framebuffer&) = delete;
    explicit Framebuffer(size_t width, size_t height, TargetSpec* targets, 
        size_t count);

    ~Framebuffer();

    void set_view(bgfx::ViewId id) 
    { 
        bgfx::setViewFrameBuffer(id, fb);
        bgfx::setViewRect(id, 0, 0, width, height); 
    }; 

    bgfx::Encoder* render_framebuffer(bgfx::UniformHandle handle, 
        uint8_t stage = 0, uint8_t attachment = 0, 
        bgfx::Encoder* encoder = nullptr);
};


