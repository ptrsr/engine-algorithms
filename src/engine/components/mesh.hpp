#ifndef MESH_HPP_
#define MESH_HPP_

#include <engine/core/component.hpp>

class Mesh : public Component {
public:
		void load(const std::string& file_name);

        void streamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pUVsAttrib);



	protected:




		
};

#endif//MESH_HPP_
