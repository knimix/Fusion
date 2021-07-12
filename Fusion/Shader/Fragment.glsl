#version 330 core

out vec4 OutColor;

in vec2 F_TextureCoord;
in float F_TextureIndex;
in float F_QuadID;

uniform vec4[1000] F_QuadColor;
uniform vec4[1000] F_QuadBorderColor;
uniform float[1000] F_QuadBorderThickness;
uniform vec4[1000] F_QuadCornerRadius;
uniform vec2[1000] F_QuadPosition;
uniform vec2[1000] F_QuadSize;
uniform int[1000] F_QuadDecoration;
uniform vec4[1000] F_QuadCutoff;

uniform sampler2D F_Texture0;
uniform sampler2D F_Texture1;
uniform sampler2D F_Texture2;
uniform sampler2D F_Texture3;
uniform sampler2D F_Texture4;
uniform sampler2D F_Texture5;
uniform sampler2D F_Texture6;
uniform sampler2D F_Texture7;
uniform sampler2D F_Texture8;
uniform sampler2D F_Texture9;
uniform sampler2D F_Texture10;
uniform sampler2D F_Texture11;
uniform sampler2D F_Texture12;
uniform sampler2D F_Texture13;
uniform sampler2D F_Texture14;
uniform sampler2D F_Texture15;

uniform vec2 F_ScreenResolution;

const float Smoothness = 2.0f;
const vec4 BackgroundColor = vec4(0.0, 0.0, 0.0, 0.0);

float RoundedQuad(vec2 centerPosition, vec2 size, vec4 cornerRadius) {
    cornerRadius.xy = (centerPosition.x>0.0f)?cornerRadius.xy : cornerRadius.zw;
    cornerRadius.x  = (centerPosition.y>0.0f)?cornerRadius.x  : cornerRadius.y;
    vec2 q = abs(centerPosition)-size+cornerRadius.x;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - cornerRadius.x;
}

void main() {
    int textureIndex = int(F_TextureIndex);
    int id = int(F_QuadID);
    vec2 pos = vec2(gl_FragCoord.x, F_ScreenResolution.y - gl_FragCoord.y);
    if (pos.x < F_QuadCutoff[id].x || pos.y < F_QuadCutoff[id].y ||pos.x > F_QuadCutoff[id].z || pos.y > F_QuadCutoff[id].w){
        discard;
    }
    vec4 texture;
    switch (textureIndex){
        case -1:{
            texture = vec4(F_QuadColor[id].rgba);
            break;
        }
        case 0:{
            texture = texture2D(F_Texture0, F_TextureCoord);
            break;
        }
        case 1:{
            texture = texture2D(F_Texture1, F_TextureCoord);
            break;
        }
        case 2:{
            texture = texture2D(F_Texture2, F_TextureCoord);
            break;
        }
        case 3:{
            texture = texture2D(F_Texture3, F_TextureCoord);
            break;
        }
        case 4:{
            texture = texture2D(F_Texture4, F_TextureCoord);
            break;
        }
        case 5:{
            texture = texture2D(F_Texture5, F_TextureCoord);
            break;
        }
        case 6:{
            texture = texture2D(F_Texture6, F_TextureCoord);
            break;
        }
        case 7:{
            texture = texture2D(F_Texture7, F_TextureCoord);
            break;
        }
        case 8:{
            texture = texture2D(F_Texture8, F_TextureCoord);
            break;
        }
        case 9:{
            texture = texture2D(F_Texture9, F_TextureCoord);
            break;
        }
        case 10:{
            texture = texture2D(F_Texture10, F_TextureCoord);
            break;
        }
        case 11:{
            texture = texture2D(F_Texture11, F_TextureCoord);
            break;
        }
        case 12:{
            texture = texture2D(F_Texture12, F_TextureCoord);
            break;
        }
        case 13:{
            texture = texture2D(F_Texture13, F_TextureCoord);
            break;
        }
        case 14:{
            texture = texture2D(F_Texture14, F_TextureCoord);
            break;
        }
        case 15:{
            texture = texture2D(F_Texture15, F_TextureCoord);
            break;
        }
    }
    if(textureIndex > -1){
        texture.rgb += F_QuadColor[id].rgb;
    }
    if(bool(F_QuadDecoration[id])){
        vec2 center = vec2(F_QuadPosition[id].x + (F_QuadSize[id].x / 2.0f), F_ScreenResolution.y - (F_QuadPosition[id].y +(F_QuadSize[id].y / 2.0f)));
        float distance = RoundedQuad(gl_FragCoord.xy - center, (F_QuadSize[id] - 1.0f) / 2.0f, F_QuadCornerRadius[id]);
        float smoothedAlpha = 1.0f-smoothstep(0.0f, Smoothness, distance);
        float borderAlpha = 1.0f-smoothstep(F_QuadBorderThickness[id] - Smoothness, F_QuadBorderThickness[id], abs(distance));
        OutColor = mix(BackgroundColor,mix(texture, F_QuadBorderColor[id], borderAlpha), smoothedAlpha);
    }else{
        OutColor = vec4(F_QuadColor[id].rgb + texture.rgb,F_QuadColor[id].a * texture.a);
    }

}
