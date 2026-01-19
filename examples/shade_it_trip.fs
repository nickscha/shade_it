/* Shade-It Example */
#version 330 core

out vec4 FragColor;

/* Uniforms provided */
uniform vec3  iResolution;
uniform float iTime;
uniform float iTimeDelta;
uniform int   iFrame;
uniform float iFrameRate;

void mainImage(out vec4 f, in vec2 fc) {
    vec2 r = iResolution.xy;
    vec4 c = vec4(0.0);
    float l = 0.0, z = iTime;
    
    vec2 uv = fc / r - 0.5;
    uv.x *= r.x / r.y;

    float angle = iTime * 0.1; // rotation speed
    float s = sin(angle);
    float co = cos(angle);
    mat2 rot = mat2(co, -s, s, co);
    
    uv = rot * uv;

    vec2 p0 = uv;
    vec2 p1 = uv; 
    vec2 p2 = uv; 
    vec2 p3 = uv;

    z+=.06; l=length(p0); c[0]=.01/length(fract(p0 + p0/length(p0)*(sin(z)+1.)*abs(cos(l*8.-z-z)))-.5);
    z+=.07; l=length(p1); c[1]=.01/length(fract(p1 + p1/length(p1)*(cos(z)+1.)*abs(sin(l*12.-z-z)))-.5);
    z+=.06; l=length(p2); c[2]=.01/length(fract(p2 + p2/length(p2)*(sin(z)+1.)*abs(cos(l*8.-z-z)))-.5);
    z+=.07; l=length(p3); c[3]=.01/length(fract(p3 + p3/length(p3)*(cos(z)+1.)*abs(sin(l*16.-z-z)))-.5);

    f = vec4(c.xyz / l, iTime);
}


void main()
{
    mainImage(FragColor, gl_FragCoord.xy);
}
