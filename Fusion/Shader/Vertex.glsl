#version 400 core
layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 TextureCoord;
layout (location = 2) in float TextureIndex;
layout (location = 3) in float QuadID;

out vec2 F_TextureCoord;
out float F_TextureIndex;
out float F_QuadID;

uniform mat4 V_Ortho;

void main() {
    F_TextureCoord = TextureCoord;
    F_TextureIndex = TextureIndex;
    F_QuadID = QuadID;

    gl_Position = V_Ortho * vec4(Position, 0.0f, 1.0f);
}
