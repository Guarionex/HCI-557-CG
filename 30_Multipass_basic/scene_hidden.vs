#version 410 core                                                 
                                                                 
uniform mat4 projectionMatrix;                                    
uniform mat4 viewMatrix;                                           
uniform mat4 modelMatrix;  

in vec3 in_Position;                                                                                                           
in vec3 in_Normal;         
                                       
out vec3 pass_Normal; 
out vec3 pass_Position;
out vec4 pass_Color;                                             
                                                                
void main(void)                                                  
{            
	// for difuse lighting
	pass_Position = (viewMatrix * modelMatrix  *  vec4(in_Position, 1.0)).xyz;    
	
	// make it red
	pass_Color = vec4(1.0,0.0,0.0,1.0);   

    pass_Normal =  (transpose(inverse(modelMatrix)) *  vec4(normalize(in_Normal), 1.0)).xyz;                         
			
	// pass the position				                       
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);       
	       
		
}                                                            