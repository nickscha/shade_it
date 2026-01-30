/* Shade-It basic core fragment shader */
#version 330 core

out vec4 FragColor;

/* Uniforms provided */
uniform vec3  iResolution;
uniform float iTime;
uniform float iTimeDelta;
uniform int   iFrame;
uniform float iFrameRate;
uniform vec4  iMouse;
uniform vec4  iTextureInfo;
uniform sampler2D iTexture;

void mainImage(out vec4 O, vec2 I)
{
    vec2 v = iResolution.xy, p = (I+I-v)/v.y/.3, q;   
    for(O*=q.x;q.x++<9.; O += vec4(2,2,3,0)/10./length(v))
    for(v=p,q.y=0.;q.y++<9.;v+=sin(v.yx*q.y+q+iTime)/q.y);
    O = tanh(O*O);
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
