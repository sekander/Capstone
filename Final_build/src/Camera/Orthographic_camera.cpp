#include "../../include/Camera/Orthographic_camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_common.hpp>
#include <glm/fwd.hpp>
#include <glm/matrix.hpp>

Orthographic_camera::Orthographic_camera( float left, float right, float bottom, float top, float zNear, float zFar) : 
	m_scale(10.0f, 10.0f) 
{
	this->m_Projection_matrix = glm::ortho(left, right, bottom, top, zNear, zFar); 
	this->m_View_matrix = glm::mat4( 1.0f);
	this->m_View_Projection_matrix = this->m_Projection_matrix * this->m_View_matrix;
	recalculate_view_matrix();
	//m_scale.x = 10.0f;
	//m_scale.y = 10.0f;
}

void Orthographic_camera::recalculate_view_matrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_positon) * 
		              glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 0, 1)) 
			      * glm::scale(glm::mat4(1.0f), glm::vec3(m_scale, 1.0f));

	//this->m_View_matrix = glm::inverse(transform);
	this->m_View_matrix = (transform);

	this->m_View_Projection_matrix = this->m_Projection_matrix * this->m_View_matrix;
}
