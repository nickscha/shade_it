/* Shade-It Star Nest Shader using iController data */
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
uniform vec4 iController[2];

#define iterations 17
#define formuparam 0.53

#define volsteps 20
#define stepsize 0.1

#define tile   0.850

#define brightness 0.0015
#define darkmatter 0.300
#define distfading 0.730
#define saturation 0.850

bool controller_button_down(uint bit_index)
{
    uint bits = floatBitsToUint(iController[1].z);
    return (bits & (1u << bit_index)) != 0u;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 left_stick     = iController[0].xy; 
    vec2 right_stick    = iController[0].zw;
    float left_trigger  = iController[1].x;
    float right_trigger = iController[1].y;

	float zoom = 2.8 * (1.1 - left_trigger);
	float speed = 0.005 * (1.0 + 4.0 * right_trigger);

	vec2 uv=fragCoord.xy/iResolution.xy-.5;
	uv.y*=iResolution.y/iResolution.x;
	vec3 dir=vec3(uv*zoom,1.);
	float time=iTime*speed+.25;

	float a1=.5+iResolution.x/iResolution.x*2.;
	float a2=.8+iResolution.y/iResolution.y*2.;
	mat2 rot1=mat2(cos(a1),sin(a1),-sin(a1),cos(a1));
	mat2 rot2=mat2(cos(a2),sin(a2),-sin(a2),cos(a2));
	dir.xz*=rot1;
	dir.xy*=rot2;
	
	vec3 from=vec3(0.3, 0.25, 0.0);
	from.x += left_stick.x * 0.25;
	from.y += left_stick.y * 0.25;
	from+=vec3(time*2.,0.0,1.0);

	from.xz*=rot1;
	from.xy*=rot2;
	
	//volumetric rendering
	float s=0.1,fade=1.;
	vec3 v=vec3(0.);
	for (int r=0; r<volsteps; r++) {
		vec3 p=from+s*dir*.5;
		p = abs(vec3(tile)-mod(p,vec3(tile*2.))); // tiling fold
		float pa,a=pa=0.;
		for (int i=0; i<iterations; i++) { 
			p=abs(p)/dot(p,p)-formuparam; // the magic formula
			a+=abs(length(p)-pa); // absolute sum of average change
			pa=length(p);
		}
		float dm=max(0.,darkmatter-a*a*.001); //dark matter
		a*=a*a; // add contrast
		if (r>6) fade*=1.-dm; // dark matter, don't render near
		v+=fade;
		v+=vec3(s,s*s,s*s*s*s)*a*brightness*fade; // coloring based on distance
		fade*=distfading; // distance fading
		s+=stepsize;
	}
	v=mix(vec3(length(v)),v,saturation); //color adjust
	fragColor = vec4(v*.01,1.);	
	
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
