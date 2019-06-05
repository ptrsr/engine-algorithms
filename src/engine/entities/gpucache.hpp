#ifndef GPU_CACHE_HPP_
#define GPU_CACHE_HPP_

#include <glbinding/gl/types.h>  

class GpuCache {
    GLuint index_buffer_id;
    GLuint vertex_buffer_id;
    GLuint normal_buffer_id;
    GLuint uv_buffer_id;
};

#endif//GPU_CACHE_HPP_
