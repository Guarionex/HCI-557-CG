#version 410 core

// Transformations for the projections
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

// The material parameters
uniform vec3 diffuse_color;
uniform vec3 ambient_color;
uniform vec3 specular_color;

// Position of the light source
uniform vec4 light_position;

// The intensity values for the reflection equations
uniform float diffuse_intensity;
uniform float ambient_intensity;
uniform float specular_intensity;
uniform float shininess;
uniform float attenuation_Coefficient;

// The vertex buffer input
in vec3 in_Position;
in vec3 in_Normal;

// The output color
out vec3 pass_Color;

void main(void)
{
	// Vectors
	vec3 normal = normalize(in_Normal);
	vec4 transformedNormal =  normalize(transpose(inverse(modelMatrix)) * vec4( normal, 1.0 ));
	vec4 surface_point = modelMatrix * vec4(in_Position, 1.0);
	vec4 surface_to_light = (light_position.w == 0.0) ? normalize( light_position) : normalize( light_position -  surface_point );
	
	// Diffuse Color
	float diffuse_coefficient = max(dot(transformedNormal, surface_to_light), 0.0);
	vec3 out_diffuse_color = diffuse_color  * diffuse_coefficient * diffuse_intensity;
	
	// Ambient Color
    vec3 out_ambient_color = vec3(ambient_color) * ambient_intensity;
	
	// Specular Color
    vec3 reflectionVector = reflect(-surface_to_light.xyz, normal);
	mat4 inverseViewMatrix = inverse(viewMatrix);
    vec3 cameraPosition = vec3( inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);
    vec3 surfaceToCamera = normalize(cameraPosition - surface_point.xyz);
    float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);
    float specular_coefficient = pow(cosAngle, shininess);
    vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity;
	
	// Attenuation
    float distanceToLight = length(light_position.xyz - surface_point.xyz);
    float attenuation = 1.0 / (1.0 + attenuation_Coefficient * pow(distanceToLight, 2));
	        
    // Directional light
	if(light_position.w == 0.0)
	{
  		vec3 light_direction = normalize(light_position.xyz);
  		float light_to_surface_angle = dot(light_direction, transformedNormal.xyz);
  		attenuation = (light_to_surface_angle > 0.0) ? 1.0 : 0.0;
	}
	
	// Mix All
	vec3 linearColor = out_ambient_color  + attenuation * ( out_diffuse_color + out_specular_color);
	vec3 gamma = vec3(1.0/2.2);
	pass_Color = pow(linearColor, gamma);
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
}