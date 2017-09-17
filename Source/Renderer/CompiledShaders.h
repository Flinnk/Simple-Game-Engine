const char* DefaultVertexShader =
"#version 330 core\n"

"layout(location = 0) in vec4 data;\n"

"out vec2 UV;\n"

"uniform mat4 model;\n"
"uniform mat4 projection;\n"

"void main()\n"
"{\n"
"	gl_Position = projection * model * vec4(data.xy, 0.0, 1.0);\n"
"	UV = data.zw;\n"
"}";


const char* DefaultFragmentShader =
"#version 330 core\n"

"out vec4 Color;\n"
"in vec2 UV;\n"

"uniform sampler2D image;\n"
"uniform vec3 tintColor;\n"

"void main()\n"
"{\n"
"	Color = vec4(tintColor, 1.0) * texture(image, UV);\n"
"}\n";
