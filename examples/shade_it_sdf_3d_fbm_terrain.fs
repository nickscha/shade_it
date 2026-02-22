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

float smin(float a, float b, float k) {
  float h = max(k-abs(a-b), 0.0)/k;
  return min(a,b) - h*h*h*k*(1.0/6.0);
}

float smax( float a, float b, float k )
{
    float h = max(k-abs(a-b),0.0);
    return max(a, b) + h*h*0.25/k;
}

float sph( ivec3 i, vec3 f, ivec3 c )
{
    vec3  p = 17.0*fract( (i+c)*0.3183099+vec3(0.11,0.17,0.13) );
    float w = fract( p.x*p.y*p.z*(p.x+p.y+p.z) );
    float r = 0.7*w*w;
    return length(f-c) - r; 
}

float sdBase( vec3 p )
{
   ivec3 i = ivec3(floor(p));
    vec3 f =       fract(p);
   // distance to the 8 corners spheres
   return min(min(min(sph(i,f,ivec3(0,0,0)),
                      sph(i,f,ivec3(0,0,1))),
                  min(sph(i,f,ivec3(0,1,0)),
                      sph(i,f,ivec3(0,1,1)))),
              min(min(sph(i,f,ivec3(1,0,0)),
                      sph(i,f,ivec3(1,0,1))),
                  min(sph(i,f,ivec3(1,1,0)),
                      sph(i,f,ivec3(1,1,1)))));
}

float sdFbm( vec3 p, float d, float k )
{
   float s = 1.0;
   for( int i=0; i<11; i++ )
   {
       float n = s*sdBase(p);

       n = smax(n, d-0.1*s, k + 0.3*s);
       d = smin(n, d      , k + 0.3*s);

       p = mat3( 0.00, 1.60, 1.20,
                -1.60, 0.72,-0.96,
                -1.20,-0.96, 1.28 )*p;
       s = 0.5*s;
   }
   return d;
}

float map(in vec3 pos, in float t)
{
    float precis = 0.0005;
    float d = pos.y - 0.2;
    float k = t * precis;
    return sdFbm(pos*0.8, d, k);
}

vec3 calc_normal(in vec3 pos)
{
  vec2 e = vec2(0.0001, 0.0);

  return normalize(vec3(
    map(pos+e.xyy, 0.0) - map(pos-e.xyy, 0.0),
    map(pos+e.yxy, 0.0) - map(pos-e.yxy, 0.0),
    map(pos+e.yyx, 0.0) - map(pos-e.yyx, 0.0)
  ));
}

float cast_ray(in vec3 ro, in vec3 rd) {

  float t = 0.0;

  for (int i = 0; i < 200; ++i) 
  {
    vec3 pos = ro + t*rd;

    float h = map(pos, t);

    if (h < 0.001) 
    {
      break;
    }

    t += h;

    if (t > 10.0) 
    {
      break;
    }
  }

  if (t > 10.0)
  {
    t = -1.0;
  }

  return t;
}

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
  vec2 p = (2.0 * fragCoord - iResolution.xy) / iResolution.y;
  
  float an = iTime; //10.0 * iMouse.x / iResolution.x;

  vec3 ro = vec3(0.2, 0.29, 0.5); // ray origin
  vec3 ta = vec3(1.0, 0.0, 0.0);

  vec3 ww = normalize(ta-ro);
  vec3 uu = normalize(cross(ww, vec3(0, 1, 0)));
  vec3 vv = normalize(cross(uu, ww));

  vec3 rd = normalize(p.x * uu + p.y * vv + 1.5 * ww); // ray direction


  // 49:12
  vec3 col = vec3(0.4, 0.75, 1.0) - 0.7 * rd.y; // sky, darker the higher

  float t = cast_ray(ro, rd);

  if (t > 0.0) 
  {
    vec3 pos = ro + t * rd;
    vec3 nor = calc_normal(pos);

    vec3 mate = vec3(0.18);
    vec3  lig = normalize( vec3(-0.1, 0.3, 0.6) );
    vec3 sun_dir  = normalize(vec3(0.8, 0.4, 0.2));
    float sun_dif = clamp(dot(nor, sun_dir), 0.0, 1.0);
    float sky_dif = clamp(0.5 + 0.5 * dot(nor, vec3(0.0, 1.0, 0.0)), 0.0, 1.0);
    float bou_dif = clamp(0.5 + 0.5 * dot(nor, vec3(0.0, -1.0, 0.0)), 0.0, 1.0);
    col  = mate * vec3(7.0, 4.5, 3.0) * sun_dif;
    col += mate * vec3(0.5, 0.8, 0.9) * sky_dif;
    col += mate * vec3(0.7, 0.3, 0.2) * bou_dif; // bounce light
    //col = nor;
  }

  col = pow(col, vec3(0.4545));  

  fragColor = vec4(col, 1.0);
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
