#include <cstdio>
#include <glm/glm.hpp>
class Orthographic_camera
{

	public:
		Orthographic_camera(float left, float right, float bottom, float top, float zNear, float zFar);
		~Orthographic_camera(){printf("Camera Deleting~~\n");}

		const glm::vec3& GetPosition() const {return m_positon;}
		void SetPosition(const glm::vec3 position) 
		{ 
		  this->m_positon = position;
		  recalculate_view_matrix();	
		}

		float GetRotation() const {return m_rotation;}
		void SetRotation(float rotation)
		{ 
			m_rotation = rotation;
			recalculate_view_matrix();
		}

		const glm::vec2& GetScale() const {return m_scale;}
		void SetScale(glm::vec2 z_scale){
			m_scale = z_scale;
			recalculate_view_matrix();
		}

		glm::mat4 return_matrix(){
			return this->m_View_Projection_matrix;
		}

	private:

		void recalculate_view_matrix();
	
		glm::mat4 m_Projection_matrix;
		glm::mat4 m_View_matrix;
		glm::mat4 m_View_Projection_matrix;

		glm::vec3 m_positon;
		glm::vec2 m_scale;
		float m_rotation = 0.0f;
};
