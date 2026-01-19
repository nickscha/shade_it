/* Shade-It animated FBM domain warp */
#version 330 core

out vec4 FragColor;

/* Uniforms provided */
uniform vec3  iResolution;
uniform float iTime;
uniform float iTimeDelta;
uniform int   iFrame;
uniform float iFrameRate;

void mainImage(out vec4 f, vec2 u) {
    float s=0,i,n;
    vec3 r = iResolution,p;
    for(u = (u-r.xy/2.)/r.y-s; i++ < 32. && ++s>.001;)
        for (p += vec3(u*s,s),s = p.y,
            n =.01; n < 1.;n+=n)
            s += abs(dot(sin(p.z + iTime + p/n),  r/r)) * n*.1;
    f = tanh(i*vec4(5,2,sin(iTime),0)/length(u-.1)/5e2);
}

void main()
{
    mainImage(FragColor, gl_FragCoord.xy);
}
