#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

namespace shader_utils {

unsigned int create_program(const std::string& vertex_path, const std::string& fragment_path);
void delete_program(unsigned int program);

}


#endif
