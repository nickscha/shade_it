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

vec4 sdgBox( in vec3 p, in vec3 b, in float r )
{
  vec3  w = abs(p)-(b-r);
  float g = max(w.x,max(w.y,w.z));
  vec3  q = max(w,0.0);
  float l = length(q);
  vec4  f = (g>0.0)?vec4(l, q/l) :
                    vec4(g, w.x==g?1.0:0.0,
                            w.y==g?1.0:0.0,
                            w.z==g?1.0:0.0);

  return vec4(f.x-r, f.yzw*sign(p));
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // camera movement	
	  float an = 0.5*(iTime-10.0);
	  vec3  ro = 1.2*vec3( 1.0*cos(an), 0.65, 1.0*sin(an) );
    vec3  ta = vec3( 0.0, -0.15, 0.0 );
    // camera matrix
    vec3  ww = normalize( ta - ro );
    vec3  uu = normalize( cross(ww,vec3(0.0,1.0,0.0) ) );
    vec3  vv = normalize( cross(uu,ww));
    // animate box
    vec3  si = vec3(0.6,0.2,0.6)+0.15*sin(iTime*vec3(1.0,1.7,2.1));
    float ra = min(0.1+0.05*sin(iTime),si.y);
    
    // render    
    vec3 tot = vec3(0.0);
    #if AA>1
    for( int m=0; m<AA; m++ )
    for( int n=0; n<AA; n++ )
    {
      // pixel coordinates
      vec2 o = vec2(float(m),float(n)) / float(AA) - 0.5;
      vec2 p = (2.0*(fragCoord+o)-iResolution.xy)/iResolution.y;
    #else    
      vec2 p = (2.0*fragCoord-iResolution.xy)/iResolution.y;
    #endif

    // create view ray
      vec3 rd = normalize( p.x*uu + p.y*vv + 1.5*ww );

      // raymarch
      const float tmax = 5.0;
      float t = 0.0;
      for( int i=0; i<256; i++ )
      {
          vec3 pos = ro + t*rd;
          float h = sdgBox(pos,si,ra).x;
          //h = max(h,pos.z); // use to see interior gradient
          if( h<0.0001 || t>tmax ) break;
          t += h;
      }
  
      // shading/lighting	
      vec3 col = vec3(0.0);
      if( t<tmax )
      {
          vec3 pos = ro + t*rd;
          vec3 nor = sdgBox(pos,si,ra).yzw;
          float dif = clamp( dot(nor,vec3(0.57703)), 0.0, 1.0 );
          float amb = 0.5 + 0.5*dot(nor,vec3(0.0,1.0,0.0));
          col = vec3(0.2,0.3,0.4)*amb + vec3(0.85,0.75,0.65)*dif;
          col *= (0.5+0.5*nor)*(0.5+0.5*nor);
      }

      // gamma (yes, before accumulation even though light accum is linear)
      col = sqrt( col );
    tot += col;
  #if AA>1
  }
  tot /= float(AA*AA);
  #endif

	fragColor = vec4( tot, 1.0 );
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
