#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Buffer.h"
#include "Framebuffer.h"
#include "Program.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "constants.h"
#include "math/Mat4.h"
#include <string>

namespace charm::gl {

void init(GLFWglproc (*fn)(const char*));

void disable(int capability);
void enable(int capability);

void depth_mask(bool flag);
void depth_func(unsigned int func);

void viewport(int x, int y, int width, int height);

void clear_color(float r, float g, float b, float a);
void clear(unsigned int mask);

[[nodiscard]] Shader create_shader(int type, const std::string& source);
[[nodiscard]] Program create_program(const std::string& vertex_source, const std::string& fragment_source);
void use(const Program& program);
[[nodiscard]] int get_uniform_location(Program& program, const std::string&);
void set_uniform(Program& program, const std::string&, const Mat4&);
void set_uniform(Program& program, const std::string&, int);

[[nodiscard]] VertexArray gen_vertex_array();
void bind(const VertexArray& vertex_array);
void reset_vertex_array();
void enable_vertex_attrib_array(unsigned int index);
void vertex_attrib_pointer(unsigned int index, int size, int type, bool normalized, int stride, const void* pointer);
void vertex_attribi_pointer(unsigned int index, int size, int type, int stride, const void* pointer);

[[nodiscard]] Buffer gen_buffer();
void bind(unsigned int type, const Buffer& buffer);
void reset_buffer(unsigned int type);
void buffer_data(int type, int size, const void* data, int usage);
void buffer_sub_data(int target, int offset, int size, const void* data);

void draw_elements(int mode, int count, int type, const void* indices);

[[nodiscard]] Texture gen_texture();
void active_texture(unsigned int unit);
void bind(unsigned int target, const Texture& texture);
void reset_texture(unsigned int target);
void tex_parameteri(unsigned int target, unsigned int name, int param);
void tex_image2d(unsigned int target, int level, int internal_format, int width, int height, int border, unsigned int format, unsigned int type, const void* data);
void generate_mipmap(unsigned int target);

[[nodiscard]] Framebuffer gen_framebuffer();
void bind(unsigned int target, const Framebuffer& framebuffer);
void reset_framebuffer(unsigned int target);
[[nodiscard]] bool check_framebuffer_status(unsigned int target);
void framebuffer_texture2d(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level);

void blend_func(unsigned int sfactor, unsigned int dfactor);

}