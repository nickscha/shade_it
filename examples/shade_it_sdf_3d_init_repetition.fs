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

mat2 rot2d(float angle) {
  float s = sin(angle);
  float c = cos(angle);
  return mat2(c, -s, s, c);
}

float sdSphere(in vec3 pos, float radius) {
  return length(pos) - radius;
}

float sdBox( vec3 p, vec3 b )
{
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}


float sdBoxFrame( vec3 p, vec3 b, float e )
{
       p = abs(p  )-b;
  vec3 q = abs(p+e)-e;
  return min(min(
      length(max(vec3(p.x,q.y,q.z),0.0))+min(max(p.x,max(q.y,q.z)),0.0),
      length(max(vec3(q.x,p.y,q.z),0.0))+min(max(q.x,max(p.y,q.z)),0.0)),
      length(max(vec3(q.x,q.y,p.z),0.0))+min(max(q.x,max(q.y,p.z)),0.0));
}

float map(in vec3 pos) 
{
  // world pos
  vec3 sphere_pos = vec3(sin(iTime) * 0.3, 0.0, 0.0);
  float sphere = sdSphere(pos - sphere_pos, 0.35); 

  // box
  vec3 q = pos;
  vec3 box_pos = vec3(-0.4, 0.0, 0.0);
  vec3 box_pos_transform = q - box_pos;
  box_pos_transform.xy *= rot2d(iTime * 0.05); 
  box_pos_transform.y -= iTime * 0.5;
  box_pos_transform = fract(box_pos_transform) - 0.5;

  float box = sdBoxFrame(box_pos_transform, vec3(0.15), 0.015);
  // float box = sdBoxFrame(box_pos_transform, vec3(0.15));

  // ground
  float ground = pos.y - (-0.25); 

  return smin(ground,smin(sphere, box, 0.4), 0.2);
}

vec3 calc_normal(in vec3 pos)
{
  vec2 e = vec2(0.0001, 0.0);

  return normalize(vec3(
    map(pos+e.xyy) - map(pos-e.xyy),
    map(pos+e.yxy) - map(pos-e.yxy),
    map(pos+e.yyx) - map(pos-e.yyx)
  ));
}

float cast_ray(in vec3 ro, in vec3 rd) {

  float t = 0.0;

  for (int i = 0; i < 100; ++i) 
  {
    vec3 pos = ro + t*rd;

    float h = map(pos);

    if (h < 0.001) 
    {
      break;
    }

    t += h;

    if (t > 20.0) 
    {
      break;
    }
  }

  if (t > 20.0)
  {
    t = -1.0;
  }

  return t;
}

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
  vec2 p = (2.0 * fragCoord - iResolution.xy) / iResolution.y;
  
  float an = 0.1 * iTime; //10.0 * iMouse.x / iResolution.x;

  vec3 ro = vec3(1.0 * sin(an), 0.0, 1.0 * cos(an)); // ray origin
  vec3 ta = vec3(0.0, 0.0, 0.0);

  vec3 ww = normalize(ta-ro);
  vec3 uu = normalize(cross(ww, vec3(0, 1, 0)));
  vec3 vv = normalize(cross(uu, ww));

  vec3 rd = normalize(p.x * uu + p.y * vv + 1.5 * ww); // ray direction


  // 49:12
  vec3 col = vec3(0.4, 0.75, 1.0) - 0.7 * rd.y; // sky, darker the higher
  col = mix(col, vec3(0.7, 0.75, 0.8), exp(-10.0*rd.y)); // above ground light horizon
  
  float t = cast_ray(ro, rd);

  if (t > 0.0) 
  {
    vec3 pos = ro + t * rd;
    vec3 nor = calc_normal(pos);

    vec3 mate = vec3(0.18);

    vec3 sun_dir  = normalize(vec3(0.8, 0.4, 0.2));
    float sun_dif = clamp(dot(nor, sun_dir), 0.0, 1.0);
    float sun_sha = step(cast_ray(pos + nor * 0.001, sun_dir), 0.0);
    float sky_dif = clamp(0.5 + 0.5 * dot(nor, vec3(0.0, 1.0, 0.0)), 0.0, 1.0);
    float bou_dif = clamp(0.5 + 0.5 * dot(nor, vec3(0.0, -1.0, 0.0)), 0.0, 1.0);

    col  = mate * vec3(7.0, 4.5, 3.0) * sun_dif * sun_sha;
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
