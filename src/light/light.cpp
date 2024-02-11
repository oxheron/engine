#include "light.h"

// external
#include "renderer/batchmanager.h"

// std
#include <cmath>

void PointLight::upload(BatchManager* bm) 
{
    if (base->get_batch() == nullptr) return;

    obj_index = base->get_batch()->add_instance(this, base->get_index());
}

void PointLight::update()
{
    base->get_batch()->edit_model_data(this, obj_index);
}

Buffer<uint8_t> PointLight::get_model_buffer() 
{
    calc_scale(); 
    memcpy((void*) model_buffer.data(), (void*) glm::value_ptr(pos_scale), 
        sizeof(glm::vec4));
    memcpy((char*) model_buffer.data() + sizeof(glm::vec4), 
        (void*) glm::value_ptr(ambient), sizeof(glm::vec4));
    memcpy((char*) model_buffer.data() + sizeof(glm::vec4) * 2, 
        (void*) glm::value_ptr(color), sizeof(glm::vec4));
    memcpy((char*) model_buffer.data() + sizeof(glm::vec4) * 3, 
        (void*) glm::value_ptr(att), sizeof(glm::vec4));
    return Buffer<uint8_t>(model_buffer.data(), model_buffer.size());
}

void PointLight::calc_scale()
{
    pos_scale.w = (-att.y + 
        std::sqrt(att.y * att.y - 
            4 * att.x * (att.z - 256 * 
            glm::max(glm::max(color.x, color.y), 
            color.z)))) / 2 * att.x;
}
