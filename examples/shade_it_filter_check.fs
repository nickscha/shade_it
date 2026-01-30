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

float checkersTextureGradBox( in vec2 p, in vec2 ddx, in vec2 ddy )
{
  vec2 w = max(abs(ddx), abs(ddy)) + 0.01;  
  vec2 i = 2.0*(abs(fract((p-0.5*w)/2.0)-0.5)-abs(fract((p+0.5*w)/2.0)-0.5))/w;
  return 0.5 - 0.5*i.x*i.y;                  
}

float checkersTexture( in vec2 p )
{
  vec2 q = floor(p);
  return mod( q.x+q.y, 2.0 );  
}

float softShadowSphere( in vec3 ro, in vec3 rd, in vec4 sph )
{
  vec3 oc = sph.xyz - ro;
  float b = dot( oc, rd );

  float res = 1.0;

  if( b>0.0 )
  {
    float h = dot(oc,oc) - b*b - sph.w*sph.w;
    res = smoothstep( 0.0, 1.0, 2.0*h/b );
  }

  return res;
}

float occSphere( in vec4 sph, in vec3 pos, in vec3 nor )
{
  vec3 di = sph.xyz - pos;
  float l = length(di);
  return 1.0 - dot(nor,di/l)*sph.w*sph.w/(l*l); 
}

float iSphere( in vec3 ro, in vec3 rd, in vec4 sph )
{
  float t = -1.0;
	vec3  ce = ro - sph.xyz;
	float b = dot( rd, ce );
	float c = dot( ce, ce ) - sph.w*sph.w;
	float h = b*b - c;
	if( h>0.0 )
	{
		t = -b - sqrt(h);
	}
	
	return t;
}

// spheres
const vec4 sc0 = vec4(  3.0, 0.5, 0.0, 0.5 );
const vec4 sc1 = vec4( -4.0, 2.0,-5.0, 2.0 );
const vec4 sc2 = vec4( -4.0, 2.0, 5.0, 2.0 );
const vec4 sc3 = vec4(-30.0, 8.0, 0.0, 8.0 );

float intersect( vec3 ro, vec3 rd, out vec3 pos, out vec3 nor, out float occ, out int matid )
{
    // raytrace
	float tmin = 10000.0;
	nor = vec3(0.0);
	occ = 1.0;
	pos = vec3(0.0);
  matid = -1;
	
	// raytrace-plane
	float h = (0.01-ro.y)/rd.y;

	if( h>0.0 ) 
	{ 
		tmin = h; 
		nor = vec3(0.0,1.0,0.0); 
		pos = ro + h*rd;
		matid = 0;
		occ = occSphere( sc0, pos, nor ) * 
			  occSphere( sc1, pos, nor ) *
			  occSphere( sc2, pos, nor ) *
			  occSphere( sc3, pos, nor );
	}


	// raytrace-sphere
	h = iSphere( ro, rd, sc0 );
	if( h>0.0 && h<tmin ) 
	{ 
		tmin = h; 
    pos = ro + h*rd;
		nor = normalize(pos-sc0.xyz); 
		matid = 1;
		occ = 0.5 + 0.5*nor.y;
	}

	h = iSphere( ro, rd, sc1 );
	if( h>0.0 && h<tmin ) 
	{ 
		tmin = h; 
    pos = ro + tmin*rd;
		nor = normalize(pos-sc1.xyz); 
		matid = 2;
		occ = 0.5 + 0.5*nor.y;
	}

	h = iSphere( ro, rd, sc2 );
	if( h>0.0 && h<tmin ) 
	{ 
		tmin = h; 
    pos = ro + tmin*rd;
		nor = normalize(pos-sc2.xyz); 
		matid = 3;
		occ = 0.5 + 0.5*nor.y;
	}

	h = iSphere( ro, rd, sc3 );
	if( h>0.0 && h<tmin ) 
	{ 
		tmin = h; 
    pos = ro + tmin*rd;
		nor = normalize(pos-sc3.xyz); 
		matid = 4;
		occ = 0.5 + 0.5*nor.y;
	}

	return tmin;	
}

vec2 texCoords( in vec3 pos, int mid )
{
  vec2 matuv;
  
  if( mid==0 )
  {
    matuv = pos.xz;
  }
  else if( mid==1 )
  {
    vec3 q = normalize( pos - sc0.xyz );
    matuv = vec2( atan(q.x,q.z), acos(q.y ) )*sc0.w;
  }
  else if( mid==2 )
  {
    vec3 q = normalize( pos - sc1.xyz );
    matuv = vec2( atan(q.x,q.z), acos(q.y ) )*sc1.w;
  }
  else if( mid==3 )
  {
    vec3 q = normalize( pos - sc2.xyz );
    matuv = vec2( atan(q.x,q.z), acos(q.y ) )*sc2.w;
  }
  else if( mid==4 )
  {
    vec3 q = normalize( pos - sc3.xyz );
    matuv = vec2( atan(q.x,q.z), acos(q.y ) )*sc3.w;
  }

	return 12.0*matuv;
}


void calcCamera( out vec3 ro, out vec3 ta )
{
	float an = 0.1*sin(0.1*iTime);
	ro = vec3( 5.0*cos(an), 0.5, 5.0*sin(an) );
  ta = vec3( 0.0, 1.0, 0.0 );
}

vec3 doLighting( in vec3 pos, in vec3 nor, in float occ, in vec3 rd )
{
  float sh = min( min( min( 
    softShadowSphere( pos, vec3(0.57703), sc0 ),
    softShadowSphere( pos, vec3(0.57703), sc1 )),
    softShadowSphere( pos, vec3(0.57703), sc2 )),
    softShadowSphere( pos, vec3(0.57703), sc3 ));

  float dif = clamp(dot(nor,vec3(0.57703)),0.0,1.0);
  float bac = clamp(0.5+0.5*dot(nor,vec3(-0.707,0.0,-0.707)),0.0,1.0);
  
  vec3 lin = dif*vec3(1.50,1.40,1.30)*sh;
  lin += occ*vec3(0.15,0.20,0.30);
  lin += bac*vec3(0.10,0.10,0.10)*(0.2+0.8*occ);

  return lin;
}

void calcRayForPixel( in vec2 pix, out vec3 resRo, out vec3 resRd )
{
	vec2 p = (-iResolution.xy + 2.0*pix) / iResolution.y;
	vec3 ro, ta;

	calcCamera( ro, ta );

  vec3 ww = normalize( ta - ro );
  vec3 uu = normalize( cross(ww,vec3(0.0,1.0,0.0) ) );
  vec3 vv = normalize( cross(uu,ww));
	vec3 rd = normalize( p.x*uu + p.y*vv + 2.0*ww );
	
	resRo = ro;
	resRd = rd;
}


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 p = (-iResolution.xy + 2.0*fragCoord) / iResolution.y;

  float th = (2.0*iMouse.x-iResolution.x)/iResolution.y;

	vec3 ro, rd, ddx_ro, ddx_rd, ddy_ro, ddy_rd;
	calcRayForPixel( fragCoord + vec2(0.0,0.0), ro, rd );
	calcRayForPixel( fragCoord + vec2(1.0,0.0), ddx_ro, ddx_rd );
	calcRayForPixel( fragCoord + vec2(0.0,1.0), ddy_ro, ddy_rd );
		
  // trace
	vec3 pos, nor;
	float occ;
  int mid;
  float t = intersect( ro, rd, pos, nor, occ, mid );

	vec3 col = vec3(0.9);
	if( mid!=-1 )
	{
		// computer ray differentials
		vec3 ddx_pos = ddx_ro - ddx_rd*dot(ddx_ro-pos,nor)/dot(ddx_rd,nor);
		vec3 ddy_pos = ddy_ro - ddy_rd*dot(ddy_ro-pos,nor)/dot(ddy_rd,nor);

		// calc texture sampling footprint		
		vec2     uv = texCoords(     pos, mid );
		vec2 ddx_uv = texCoords( ddx_pos, mid ) - uv;
		vec2 ddy_uv = texCoords( ddy_pos, mid ) - uv;

		vec3 mate = vec3(0.0);

    if( p.x<th ) mate = vec3(1.0)*checkersTexture( uv );
    else         mate = vec3(1.0)*checkersTextureGradBox( uv, ddx_uv, ddy_uv );
        
    // lighting	
    vec3 lin = doLighting( pos, nor, occ, rd );	
    col = mate * lin;
    col = mix( col, vec3(0.9), 1.0-exp( -0.00001*t*t ) );
	}
	
	col = pow( col, vec3(0.4545) );
	col *= smoothstep( 1.0, 2.0, abs(p.x-th)/(2.0/iResolution.y) );
	
	fragColor = vec4( col, 1.0 );
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
