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

vec3 palette(float d){
	return mix(vec3(0.5,0.2,0.1),vec3(0.9,0.5,1.),d);
}

vec2 rotate(vec2 p,float a){
	float c = cos(a);
  float s = sin(a);
  return p*mat2(c,s,-s,c);
}

float map(vec3 p){
  for( int i = 0; i<8; ++i){
      float t = iTime*0.2;
      p.xz =rotate(p.xz,t);
      p.xy =rotate(p.xy,t*1.89);
      p.xz = abs(p.xz);
      p.xz-=.5;
	}
	return dot(sign(p),p)/5.;
}

vec4 rm(vec3 ro, vec3 rd){
    float t = 0.;
    vec3 col = vec3(0.);
    float d;
    for(float i =0.; i<64.; i++){
		  vec3 p = ro + rd*t;
      d = map(p)*.5;
      if(d<0.02){
          break;
      }
      if(d>100.){
        break;
      }
      col+=palette(length(p)*.1)/(400.*(d));
      t+=d;
    }
    return vec4(col,1./(d*100.));
}
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = (fragCoord-(iResolution.xy/2.))/iResolution.x;
	  vec3 ro = vec3(0.,0.,-60.);
    ro.xz = rotate(ro.xz,iTime);
    vec3 cf = normalize(-ro);
    vec3 cs = normalize(cross(cf,vec3(0.,1.,0.)));
    vec3 cu = normalize(cross(cf,cs));
    vec3 uuv = ro+cf*3. + uv.x*cs + uv.y*cu;
    vec3 rd = normalize(uuv-ro);
    vec4 col = rm(ro,rd);   
    
    fragColor = col;
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
