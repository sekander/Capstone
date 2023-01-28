#include <iostream>
#include <memory>
#include "../../include/Components/RenderComponent.h"
#include "../../include/Graphics/texture.h"

using std::cout;
RenderComponent::RenderComponent(Component* parent_  ) : Component(parent_)
{
	//Will change implementation
}

RenderComponent::~RenderComponent()
{
//	onDestroy();
	cout << "Render Component Removed\n";	
//	glDeleteVertexArrays(1, &this->quadVAO);
}

bool RenderComponent::onCreate(){
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


        std::cout << "ON CREATE  *****************************************************************************" << std::endl;

	return true;
}

void RenderComponent::LoadSprite(
		       const char* fileName,
		       vec2 position, 
		       vec2 size, 
		       unsigned int x_frame, 
		       unsigned int y_frame, 
		       float rotation, 
		       vec3 colour, 
		       vec2 frames,
                       bool isAlpha)
{
	
	smart_sprite = std::make_shared<sprite>(fileName, 
						position, 
						size, 
						x_frame, 
						y_frame, 
						rotation, 
						colour, 
						frames,
                                                isAlpha);
}

void RenderComponent::LoadTiles(
		       std::shared_ptr<Texture2D> texture,
		       vec2 position, 
		       vec2 size, 
		       unsigned int x_frame, 
		       unsigned int y_frame, 
		       float rotation, 
		       vec3 colour, 
		       vec2 frames)
{
	smart_sprite = std::make_shared<sprite>();	


	smart_sprite->set_texture(texture);
	smart_sprite->set_position(position);
	smart_sprite->set_size(size);
	smart_sprite->set_num_x_frames(x_frame);
	smart_sprite->set_num_y_frames(y_frame);
	smart_sprite->set_rotation(rotation);
	smart_sprite->set_color(colour);
	smart_sprite->set_frames(frames);

	

}
void RenderComponent::initRenderData()
{

    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
     //glFlush();


        std::cout << "REGULAR TEXTURE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}


void RenderComponent::initLineRenderData(vec2 start, vec2 end)
{
   
	float vertices[] = {
             start.x, start.y, 
             end.x, end.y 
        };
        
        glGenVertexArrays(1, &VAO);

        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
 
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        //glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
 
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 
        std::cout << "LINE DRAW ##################################################################################" << std::endl;
 
}

void RenderComponent::drawLine()
{
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
}
void RenderComponent::drawLine(glm::vec2 origin, glm::vec2 dest)
{
	//Temporary hack
	initLineRenderData(origin, dest);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
}


//void RenderComponent::renderData(unsigned int num_x_frame,unsigned int num_y_frames, float x_frame, float y_frame)
void RenderComponent::renderData(uint8_t num_x_frame,uint8_t num_y_frames,uint8_t  x_frame,uint8_t y_frame)
{

    float clip_size = 1.0/num_y_frames;
    float clip_size_x = 1.0/num_x_frame;

    auto x = num_x_frame;
    auto y = num_y_frames;

    auto m_frame_x = x_frame;
    auto m_frame_y = y_frame;


    //Temp animation code
    if(m_frame_x < num_x_frame)
    {
   	m_frame_x++; 
    }
    else
	    m_frame_x = 0;


    unsigned int VBO;
    float vertices[] = { 
        // pos      				// tex
        //Triangle 1
	0.0f   		    	    , 1.0f/y 	   , 	   0.0f   	  + (clip_size_x * m_frame_x), 	1.0f/y + (clip_size * m_frame_y),
        1.0f/x + 0.00f	            , 0.0f         , 	   1.0f/x         + (clip_size_x * m_frame_x), 	0.0f + (clip_size * m_frame_y),
        0.0f   		    	    , 0.0f         , 	   0.0f   	  + (clip_size_x * m_frame_x), 	0.0f + (clip_size * m_frame_y), 
    

	//Triangle 2
        0.0f    	      	    , 1.0f/y       ,       0.0f   	  + (clip_size_x * m_frame_x),  1.0f/y + (clip_size * m_frame_y),
        1.0f/x  + 0.00f             , 1.0f/y       ,       1.0f/x         + (clip_size_x * m_frame_x),  1.0f/y + (clip_size * m_frame_y),
        1.0f/x  + 0.00f             , 0.0f         , 	   1.0f/x         + (clip_size_x * m_frame_x),  	0.0f + (clip_size * m_frame_y)       
    };    

 
     glGenVertexArrays(1, &this->quadVAO);
     glGenBuffers(1, &VBO);
     //GL_BACK
 
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
 
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     glBlendEquation(GL_FUNC_ADD);
     glBindVertexArray(this->quadVAO);
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);

        std::cout << "TEXTURE RENDER ???????????????????????????????????????????????????????????????????????" << std::endl;
}

void RenderComponent::drawSprites()
{

    	glActiveTexture(GL_TEXTURE0);
	smart_sprite.get()->get_smart_texture()->Bind();

    	glBindVertexArray(this->quadVAO);
	glDrawBuffer(GL_BACK);
	//glDrawBuffer(GL_FRONT);
    	//glDrawArrays(GL_TRIANGLES, 0, 6);
    	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    	glBindVertexArray(0);
}

void RenderComponent::drawTexture(Texture2D& texture)
{
//	initRenderData();

    	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
    		//temp_sprite->get_texture()->Bind();
    		//texture.Bind();

    	glBindVertexArray(this->quadVAO);
    	glDrawArrays(GL_TRIANGLES, 0, 6);
    	glBindVertexArray(0);
}

void RenderComponent::drawSquare()
{
    	glBindVertexArray(this->quadVAO);
    	glDrawArrays(GL_TRIANGLES, 0, 6);
    	glBindVertexArray(0);
}

void RenderComponent::draw() const {

        // draw our first triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 
}



