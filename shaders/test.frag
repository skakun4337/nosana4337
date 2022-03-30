#version 430 core
out vec4 FragColor;
  
in VData{
  vec2 texCoords;
  vec3 normals;
} vdata; 

uniform sampler2D tex;

void main()
{
	FragColor=texture(tex, vdata.texCoords);
}
