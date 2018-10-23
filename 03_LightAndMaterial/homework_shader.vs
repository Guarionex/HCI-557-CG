#version 410 core                                                 
                                                            
uniform mat4 projectionMatrix;                                   
uniform mat4 viewMatrix;                                         
uniform mat4 modelMatrix;                                         
in vec3 in_Position;                                               
in vec3 in_Normal;            

// Position of the light source
uniform vec3 locationLight;  

// Diffuse light
uniform vec3 diffusecolor;   
uniform float diffuseIntensity;   

// Specular light
uniform vec3 specularColor;  
uniform float speculuar_coeff;
uniform float specular_intensity;  

// Ambient light
uniform vec3 ambientcolor;
uniform float ambientIntensity; 
  

out vec3 pass_Color;     

void main(void)                                                  
{  

	// TODO: Add your vector calculations and the components that you need for 
	// diffuse, specular, and ambient light. 
    
    
    // Vectors
    
    
    // Diffuse color                                                                                          
  

    // Ambient color                                                                                         
    

    // specular color   
    
    
    // Mix all.
    // Note, I currently pass the normal vectors out as color. You
    // have to replace in_Normal with your color components. 
    pass_Color =  in_Normal;
                                                           
   
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0); 
	
}                                                                 