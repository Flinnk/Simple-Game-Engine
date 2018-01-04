#pragma once 

const char* DefaultVertexShader =
"#version 330 core\n"

"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"layout(location = 2) in vec2 uv;\n"

"out vec2 UV;\n"
"out vec3 tintColor;\n"

"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"void main()\n"
"{\n"
"	gl_Position = projection * view * vec4(position.xy, 0.0, 1.0);\n"
"	UV = uv;\n"
"	tintColor = color;\n"
"}";


const char* DefaultFragmentShader =
"#version 330 core\n"

"out vec4 Color;\n"
"in vec2 UV;\n"
"in vec3 tintColor;\n"

"uniform sampler2D image;\n"

"void main()\n"
"{\n"
"	Color = vec4(tintColor, 1.0) * texture(image, UV);\n"
"}\n";


const char* TextVertexShader =
"#version 330 core\n"
"layout(location = 0) in vec4 vertex;\n"
"out vec2 TexCoords;\n"

"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"void main()\n"
"{\n"
"	gl_Position = projection * view * vec4(vertex.xy, 0.0, 1.0);\n"
"	TexCoords = vertex.zw;\n"
"} ";

const char* TextFragmentShader =

"#version 330 core\n"
"in vec2 TexCoords; \n"
"out vec4 color; \n"

"uniform sampler2D text; \n"
"uniform vec3 textColor; \n"

"void main()\n"
"{\n"
"	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r); \n"
"	color = vec4(textColor, 1.0) * sampled; \n"
"}";

