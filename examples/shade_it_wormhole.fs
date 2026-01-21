/* Shade-It animated FBM domain warp */
#version 330 core

out vec4 FragColor;

/* Uniforms provided */
uniform vec3  iResolution;
uniform float iTime;
uniform float iTimeDelta;
uniform int   iFrame;
uniform float iFrameRate;

vec2 r(vec2 v,float t){
    float s=sin(t);
    float c=cos(t);
    return mat2(c,-s,s,c)*v;
}

vec3 a(vec3 c)
{
    c = pow(c, vec3(1.1, 1.0, 0.9));

    c = vec3(
        c.r * 0.8 + c.b * 0.2,
        c.g * 0.9 + c.b * 0.1,
        c.b * 1.2
    );

    return clamp(c, 0.0, 1.0);
}

float n(vec3 p)
{
    const float PHI = 1.618033988;
    
    const mat3 GOLD = mat3(
        -0.571464913, +0.814921382, +0.096597072,
        -0.278044873, -0.303026659, +0.911518454,
        +0.772087367, +0.494042493, +0.399753815
    );

    return dot(cos(GOLD * p), sin(PHI * p * GOLD));
}

void mainImage(out vec4 o,in vec2 u){
    float i,s,t=iTime;
    vec3 p,l,b,d;p.z=t;

    d=normalize(vec3(2.*u-iResolution.xy,iResolution.y));

    for(o*=i;i<8.;i++){
        b=p;
        b.xy=r(sin(b.xy),t*1.5+b.z*3.);
        s=.001+abs(n(b*12.)/12.-n(b))*.6;
        s=max(s,2.-length(p.xy));
        s+=abs(p.y*.75+sin(p.z+t*.1+p.x*1.5))*.2;
        p+=d*s;
        l+=(1.+sin(i+length(p.xy*.1)+vec3(3,1.5,1)))/s;
    }

    o.rgb=a(l*l/10e2);   
}

void main()
{
    mainImage(FragColor, gl_FragCoord.xy);
}
