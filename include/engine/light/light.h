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

    glm::vec4 ambient_squared;
    glm::vec4 diffuse_linear;
    glm::vec4 specular_constant;

    // Condensed form of all of the data
    std::vector<uint8_t> model_buffer;

    size_t obj_index;
   
public:
    glm::vec3 get_ambient() { return glm::vec3(ambient_squared); }
    void set_ambient(glm::vec3 ambient) 
        { ambient_squared = glm::vec4(ambient.xyz(), ambient_squared.w); }

    glm::vec3 get_diffuse() { return glm::vec3(diffuse_linear); }
    void set_diffuse(glm::vec3 diffuse) 
        { diffuse_linear = glm::vec4(diffuse.xyz(), diffuse_linear.w); }

    glm::vec3 get_specular() { return glm::vec3(specular_constant); }
    void set_specular(glm::vec3 ambient) 
        { specular_constant = glm::vec4(ambient.xyz(), specular_constant.w); }

    glm::vec3 get_att() 
        { return glm::vec3(ambient_squared.w, diffuse_linear.w, specular_constant.w); };
    void set_att(glm::vec3 att)
    { 
        ambient_squared.w = att.x; 
        diffuse_linear.w = att.y;
        specular_constant.w = att.z;
    }

    glm::vec3 get_pos() { return glm::vec3(pos); };
    void set_pos(glm::vec3 pos) { pos_scale = glm::vec4(pos, pos_scale.w); }

    void upload(BatchManager* bm = nullptr) override;

    Buffer<uint8_t> get_model_buffer() override;
    Buffer<uint8_t> get_vertex_buffer() { return base->get_vertex_buffer(); }
    Buffer<uint8_t> get_index_buffer() { return base->get_index_buffer(); };

private:
    void calc_scale();
};
