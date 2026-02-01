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

#define FAR 80. 
mat2 r2(in float a){ float c = cos(a), s = sin(a); return mat2(c, s, -s, c); }
float hash31( vec3 p ){ return fract(sin(dot(p, vec3(157, 113, 7)))*45758.5453); }
float hash21( vec2 p ){ return fract(sin(dot(p, vec2(41, 289)))*45758.5453); }
vec3 hash33(vec3 p){ 
    float n = sin(dot(p, vec3(7, 157, 113)));    
    return fract(vec3(2097152, 262144, 32768)*n); 
}

float n3D(vec3 p){
	const vec3 s = vec3(7, 157, 113);
	vec3 ip = floor(p); p -= ip; 
    vec4 h = vec4(0., s.yz, s.y + s.z) + dot(ip, s);
    p = p*p*(3. - 2.*p);
    h = mix(fract(sin(h)*43758.5453), fract(sin(h + s.x)*43758.5453), p.x);
    h.xy = mix(h.xz, h.yw, p.y);
    return mix(h.x, h.y, p.z); 
}

float n2D(vec2 p) {
	vec2 i = floor(p); p -= i; p *= p*(3. - p*2.);   
	return dot(mat2(fract(sin(vec4(0, 41, 289, 330) + dot(i, vec2(41, 289)))*43758.5453))*vec2(1. - p.y, p.y), vec2(1. - p.x, p.x));
}

vec2 path(in float z){ 
    return vec2(sin(z*.075)*8., cos(z*.1)*.75); // Windy path.
    
}

float smax(float a, float b, float s){
    float h = clamp(.5 + .5*(a - b)/s, 0., 1.);
    return mix(b, a, h) + h*(1. - h)*s;
}

float terrain(vec2 p){
    p /= 8.; 
    p += .5; 

    float a = 1., sum = 0., res = 0.;

    for (int i=0; i<5; i++){
        
        res += n2D(p)*a; 
        p = mat2(1, -.75, .75, 1)*p*2.72;
        sum += a; 
        a *= -.5/1.7; 
    }
    return res/sum; 
}

float map(vec3 p){
    float trSf = terrain(p.xz);
 
    p.xy -= path(p.z);

    vec2 ca = abs(p.xy*vec2(1, .7) + vec2(0, -2.75)); // Stretch and lower space.
    float n = smax(6. - mix(length(ca), max(ca.x, ca.y), .25), p.y - 1.75, 2.) + (.5 - trSf)*4.;
    return n; 
}

float trace(vec3 ro, vec3 rd){
    float t = 0., d;
    
    for (int i=0; i<160; i++){

        d = map(ro + rd*t);
        
        if(abs(d)<.001*(t*.025 + 1.) || t>FAR) break;
        
        t += d*.7;
    }
    
    return min(t, FAR);
}

float softShadow(vec3 ro, vec3 n, vec3 lp, float k, float t){
    const int maxIterationsShad = 48; 
    
    ro += n*.0015; 
    vec3 rd = lp - ro; 
 
    float shade = 1.;
    float dist = .0; 
    float end = max(length(rd), 0.0001);
    rd /= end;

    for (int i=0; i<maxIterationsShad; i++){

        float h = map(ro + rd*dist);
        shade = min(shade, smoothstep(0.0, 1.0, k*h/dist));
        dist += clamp(h, .02, .25); 

        if (h<0. || dist > end) break; 
    }

    return min(max(shade, 0.) + .15, 1.); 
}

vec3 getNormal( in vec3 p ){
    vec2 e = vec2(.001, -.001); 
    return normalize(e.xyy*map(p + e.xyy) + e.yyx*map(p + e.yyx) + e.yxy*map(p + e.yxy) + e.xxx*map(p + e.xxx));
}

float calcAO(in vec3 p, in vec3 nor){
	float sca = 1.5, occ = 0.;
    
    for(float i=0.; i<5.; i++){
        float hr = .01 + i*.5/4.;        
        float dd = map(nor*hr + p);
        occ += (hr - dd)*sca;
        sca *= .7;
    }
    
    return clamp(1. - occ, 0., 1.);    
}

float fmap(vec3 p){
    p *= vec3(1, 4, 1)/400.;    
    return n3D(p)*0.57 + n3D(p*4.)*0.28 + n3D(p*8.)*0.15;
}

vec4 cloudLayers(vec3 ro, vec3 rd, vec3 lp, float far){
    rd = (rd + (hash33(rd.zyx)*0.004-0.002)); 
    rd *= (1. + fract(sin(dot(vec3(7, 157, 113), rd.zyx))*43758.5453)*0.04-0.02); 
    float ld=0., td=0., w=0.;
    float d=1., t=0.;
    const float h = .5;
    vec3 col = vec3(0), sp;
    vec4 d4 = vec4(1, 0, 0, 0);
    vec3 sn = normalize(hash33(rd.yxz)*.03-rd);

    for (int i=0; i<4; i++) {

        if(td>1. || t>far) break;

        sp = ro + rd*t; 
        d = fmap(sp); 

        ld = (h - d) * step(d, h); 
        w = (1. - td) * ld;   

        td += w*.5 + 1./65.; 

        vec3 ld = lp-sp; 
        float lDist = max(length(ld), 0.001);
        ld/=lDist; 
        
        float atten = 100./(1. + lDist*0.005 + lDist*lDist*0.00005);
        float diff = max(dot( sn, ld ), 0.);
        float spec = pow(max( dot( reflect(-ld, sn), -rd ), 0. ), 4.);
        
        col += w*(diff + vec3(1, .75, .5)*spec + .5)*atten;//*1.25;
        t += max(d4.x*.5, 0.25)*100.; //* 0.75

    }
    
    return vec4(col, t);
        
}

vec3 getSky(in vec3 ro, in vec3 rd, vec3 lp, float t){
    float sun = max(dot(rd, normalize(lp - ro)), 0.0); // Sun strength.
    float horiz = pow(1.0-max(rd.y, 0.0), 3.)*.25; // Horizon strength.
    vec3 col = mix(vec3(.25, .5, 1)*.8, vec3(.8, .75, .7), sun*.5);//.zyx;

    col = mix(col, vec3(1, .5, .25), horiz);
    col += 0.25*vec3(1, .7, .4)*pow(sun, 5.0);
    col += 0.25*vec3(1, .8, .6)*pow(sun, 64.0);
    col += 0.15*vec3(1, .9, .7)*max(pow(sun, 512.0), .25);
    col = clamp(col + hash31(rd)*0.04 - 0.02, 0., 1.);

    float tt = (1000. - ro.y)/(rd.y + .2);

    if(t>=FAR && tt>0.){
        vec4 cl = cloudLayers(ro + rd*tt, rd, lp, FAR*3.);
        vec3 clouds = cl.xyz;
        col = mix( col, vec3(1), clouds);
    }
    
    return col;
}

vec3 getObjectColor(vec3 p, vec3 n){
    vec3 tx = vec3(0.5, 0.2, 0.1); 
    vec3 gr = mix(vec3(1), vec3(.8, 1.3, .2), smoothstep(.5, 1., n.y)); 
    return mix(tx, tx*gr, smoothstep(.7, 1., (n.y)));
}

vec3 doColor(in vec3 ro, in vec3 rd, in vec3 lp, float t){
    vec3 sceneCol = vec3(0);
    
    if(t<FAR){
        vec3 sp = ro + rd*t;
        vec3 sn = getNormal(sp);
        vec3 tx = sp;
        float sh = softShadow(sp, sn, lp, 16., t);
        float ao = calcAO(sp, sn);
        sh = (sh + ao*.25)*ao;
    
        vec3 ld = lp - sp; 
        float lDist = max(length(ld), 0.001); 
        ld /= lDist; 

        float atten = 3./(1. + lDist*0.005 + lDist*lDist*0.00005);
        float diff = max(dot(sn, ld), 0.);
        float spec = pow(max( dot( reflect(-ld, sn), -rd ), 0.0 ), 64.0);
        vec3 objCol = getObjectColor(sp, sn);
        sceneCol = objCol*(diff + ao*.5 + vec3(1, .7, .5)*spec);
        sceneCol *= atten*sh;
    }

    return sceneCol;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ){
	vec2 uv = (fragCoord - iResolution.xy*.5)/iResolution.y;
    vec3 ro = vec3(0, 2, iTime*5.); 
    vec3 lk = ro + vec3(0, -.05, .25); 
    vec3 lp = ro + vec3(8, FAR*.26, FAR*.52)*3.;

    ro.xy += path(ro.z);
    lk.xy += path(lk.z);
    lp.xy += path(lp.z);

    float FOV = 3.14159/3.; 
    vec3 forward = normalize(lk-ro);
    vec3 right = normalize(vec3(forward.z, 0., -forward.x )); 
    vec3 up = cross(forward, right);
    vec3 rd = normalize(uv.x*right + uv.y*up + forward/FOV);

    vec2 sw = path(lk.z);
    rd.xy *= r2(-sw.x/24.);
    rd.yz *= r2(-sw.y/16.);
  
    float t = trace(ro, rd);
    vec3 sky = getSky(ro, rd, lp, t);
    vec3 sceneColor = doColor(ro, rd, lp, t);
    float fog = smoothstep(0., .95, t/FAR);
    vec3 fogCol = sky;
    
    sceneColor = mix(sceneColor, fogCol, fog); 
    uv = fragCoord/iResolution.xy;
    sceneColor *= pow(16.*uv.x*uv.y*(1. - uv.x)*(1. - uv.y) , .125)*.75 + .25;
	fragColor = vec4(sqrt(clamp(sceneColor, 0.0, 1.0)), 1.0);
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
