#pragma once

// external
#include "nlohmann/json.hpp"
#include "renderer/model/mesh.h"
#include "glm/glm.hpp"

class PointLight : public Model 
{
private:
    BaseInstance<PosOnly>* base;

    glm::vec4 pos_scale;

    glm::vec4 ambient;
    glm::vec4 color;
    glm::vec4 att;

    // Condensed form of all of the data
    std::vector<uint8_t> model_buffer;

    size_t obj_index;
   
public:
    PointLight(BaseInstance<PosOnly>* base)
    {
        this->base = base;
    }

    ~PointLight()
    {
        base->get_batch()->remove_instance(obj_index);
    }

    glm::vec3 get_ambient() { return glm::vec3(ambient); }
    void set_ambient(glm::vec3 ambient) 
        { this->ambient = glm::vec4(glm::vec3(ambient), 1); }

    glm::vec3 get_color() { return glm::vec3(color); }
    void set_color(glm::vec3 color) 
        { this->color = glm::vec4(glm::vec3(color), 1); }

    glm::vec3 get_att() 
        { return glm::vec3(att); };
    void set_att(glm::vec3 att)
    { 
        this->att = glm::vec4(att, 1);
    }

    glm::vec3 get_pos() { return glm::vec3(pos_scale); };
    void set_pos(glm::vec3 pos) { pos_scale = glm::vec4(pos, pos_scale.w); }

    void upload(BatchManager* bm = nullptr) override;
    void update();

    Buffer<uint8_t> get_model_buffer() override;
    Buffer<uint8_t> get_vertex_buffer() override { return base->get_vertex_buffer(); };
    Buffer<uint8_t> get_index_buffer() override { return base->get_index_buffer(); };

    size_t animation_start() override { return 0; }
    size_t animation_length() override 
        { return get_index_buffer().size() / sizeof(uint32_t); };

private:
    void calc_scale();
};
