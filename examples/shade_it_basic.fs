/* Shade-It basic core fragment shader */
#version 330 core

out vec4 FragColor;

/* Uniforms provided */
uniform vec3  iResolution;   // viewport width and height
uniform float iTime;         // time elapsed in seconds
uniform float iTimeDelta;    // render time in seconds
uniform int   iFrame;        // total frame counter
uniform float iFrameRate;    // current frames per second
uniform vec4  iMouse;        // mouse position (x,y)
uniform vec4  iTextureInfo;  // texture width, height, cell width, cell height
uniform sampler2D iTexture;  // texture slot
uniform vec4 iController[2]; // full controller state

void mainImage(out vec4 outColor, in vec2 fragCoord)
{
  vec2 uv = fragCoord / iResolution.xy;
  float t = iTime;
  outColor = vec4(uv, 0.5 + 0.5 * sin(t), 1.0);
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
