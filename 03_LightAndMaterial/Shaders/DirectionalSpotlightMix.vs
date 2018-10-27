#version 410 core

// Transformations for the projections
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

// The material parameters
uniform vec3 diffuse_color;
uniform vec3 ambient_color;
uniform vec3 specular_color;

// Spotlight
// Position of the light source
uniform vec4 light_position_spotlight;

// Spotlight cone parameters
uniform float cone_angle;
uniform vec3 cone_direction;

// The smoothstep delta for the cone
float smoothstep_delta = 10.0;

// The intensity values for the reflection equations
uniform float diffuse_intensity_spotlight;
uniform float ambient_intensity_spotlight;
uniform float specular_intensity_spotlight;
uniform float attenuation_Coefficient_spotlight;

// Directional Light
// Position of the light source
uniform vec4 light_position_directional;

// The intensity values for the reflection equations
uniform float diffuse_intensity_directional;
uniform float ambient_intensity_directional;
uniform float specular_intensity_directional;
uniform float attenuation_Coefficient_directional;

uniform float shininess;

// The vertex buffer input
in vec3 in_Position;
in vec3 in_Normal;

// The output color
out vec3 pass_Color;

float smoothstep(float edge0, float edge1, float x)
{
    // Scale, bias and saturate x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    // Evaluate polynomial
    return x*x*(3 - 2 * x);
}

void main(void)
{
	// Spotlight
	// Vectors
	vec3 normal_spotlight = normalize(in_Normal);
	vec4 transformedNormal_spotlight = normalize(transpose(inverse( modelMatrix)) * vec4( normal_spotlight, 1.0 ));
	vec4 surface_point_spotlight = modelMatrix * vec4(in_Position, 1.0);
	vec4 surface_to_light_spotlight = (light_position_spotlight.w == 0.0) ? normalize( light_position_spotlight) : normalize( light_position_spotlight -  surface_point_spotlight );
	
	// Diffuse Color
	float diffuse_coefficient_spotlight = max(dot(transformedNormal_spotlight, surface_to_light_spotlight), 0.0);
	vec3 out_diffuse_color_spotlight = diffuse_color  * diffuse_coefficient_spotlight * diffuse_intensity_spotlight;
	
	// Ambient color                                                                                         
	vec3 out_ambient_color_spotlight = vec3(ambient_color) * ambient_intensity_spotlight;
	
	// Specular color
	vec3 reflectionVector_spotlight = reflect(-surface_to_light_spotlight.xyz, normal_spotlight.xyz);
	mat4 inverseViewMatrix = inverse(viewMatrix);
	vec3 cameraPosition = vec3( inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);
	vec3 surfaceToCamera_spotlight = normalize(cameraPosition - surface_point_spotlight.xyz);
	float cosAngle_spotlight = max(0.0, dot(surfaceToCamera_spotlight, reflectionVector_spotlight));
	float specular_coefficient_spotlight = pow(cosAngle_spotlight, shininess);
	vec3 out_specular_color_spotlight = specular_color * specular_coefficient_spotlight * specular_intensity_spotlight;
	
	// attenuation_spotlight
	float distanceToLight_spotlight = length(light_position_spotlight.xyz - surface_point_spotlight.xyz);
	float attenuation_spotlight = 1.0 / (1.0 + attenuation_Coefficient_spotlight * pow(distanceToLight_spotlight, 2));
	
	// Spotlight
	vec3 cone_direction_norm = normalize(cone_direction);
	float light_to_surface_angle_spotlight = degrees(acos(dot(-surface_to_light_spotlight.xyz, cone_direction_norm)));
	
	attenuation_spotlight = 1.0 - smoothstep(cone_angle,  cone_angle + smoothstep_delta , light_to_surface_angle_spotlight);
	
	// Calculate the linear color
	vec3 linearColor = out_ambient_color_spotlight  + attenuation_spotlight * ( out_diffuse_color_spotlight + out_specular_color_spotlight);
	
	// Directional Light
	// Vectors
	vec3 normal_directional = normalize(in_Normal);
	vec4 transformedNormal_directional =  normalize(transpose(inverse(modelMatrix)) * vec4( normal_directional, 1.0 ));
	vec4 surface_point_directional = modelMatrix * vec4(in_Position, 1.0);
	vec4 surface_to_light_directional = (light_position_directional.w == 0.0) ? normalize( light_position_directional) : normalize( light_position_directional -  surface_point_directional );
	
	// Diffuse Color
	float diffuse_coefficient_directional = max(dot(transformedNormal_directional, surface_to_light_directional), 0.0);
	vec3 out_diffuse_color_directional = diffuse_color  * diffuse_coefficient_directional * diffuse_intensity_directional;
	
	// Ambient Color
    vec3 out_ambient_color_directional = vec3(ambient_color) * ambient_intensity_directional;
	
	// Specular Color
    vec3 reflectionVector_directional = reflect(-surface_to_light_directional.xyz, normal_directional);
    vec3 surfaceToCamera_directional = normalize(cameraPosition - surface_point_directional.xyz);
    float cosAngle_directional = max( dot(surfaceToCamera_directional, reflectionVector_directional), 0.0);
    float specular_coefficient_directional = pow(cosAngle_directional, shininess);
    vec3 out_specular_color_directional = specular_color * specular_coefficient_directional * specular_intensity_directional;
	
	// attenuation_directional
    float distanceToLight_directional = length(light_position_directional.xyz - surface_point_directional.xyz);
    float attenuation_directional = 1.0 / (1.0 + attenuation_Coefficient_directional * pow(distanceToLight_directional, 2));
	        
    // Directional light
	if(light_position_directional.w == 0.0)
	{
  		vec3 light_direction = normalize(light_position_directional.xyz);
  		float light_to_surface_angle_directional = dot(light_direction, transformedNormal_directional.xyz);
  		attenuation_directional = 1.0;//= (light_to_surface_angle_directional > 0.0) ? 1.0 : 0.0;
	}
	
	linearColor += out_ambient_color_directional + attenuation_directional * (out_diffuse_color_directional + out_specular_color_directional);
	
	vec3 gamma = vec3(1.0/2.2);
	pass_Color = pow(linearColor, gamma);
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
}