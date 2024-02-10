#include "light.h"

// external
#include "renderer/batchmanager.h"

// std
#include <math>

void PointLight::upload(BatchManager* bm) 
{
    if (base->get_batch() == nullptr) return;

    obj_index = base->get_batch()->add_instance(this, base->get_index());
}

Buffer<uint8_t> PointLight::get_model_buffer() 
{
    calc_scale(); 
    memcpy((void*) model_buffer.data(), (void*) glm::value_ptr(pos_scale), 
        sizeof(glm::vec4)):
    memcpy((char*) model_buffer.data() + sizeof(glm::vec4), 
        (void*) glm::value_ptr(ambient_squared), sizeof(glm::vec4));
    memcpy((char*) model_buffer.data() + sizeof(glm::vec4) * 2, 
        (void*) glm::value_ptr(diffuse_linear), sizeof(glm::vec4));
    memcpy((char*) model_buffer.data() + sizeof(glm::vec4) * 3, 
        (void*) glm::value_ptr(specular_constant), sizeof(glm::vec4));
    return Buffer<uint8_t>(model_buffer.data(), model_buffer.size());
}

void PointLight::calc_scale()
{
    pos_scale.w = (-diffuse_linear.w + 
        std::sqrt(diffuse_linear.w * diffuse_linear.w - 
            4 * ambient_squared.w * (specular_constant.w - 256 * 
            glm::max(glm::max(diffuse_linear.x, diffuse_linear.y), 
            diffuse_linear.z)))) / 2 * ambient_squared.w;
}
