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

float sdCircle( in vec2 p, in float r ) 
{
  return length(p)-r;
}


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 p   = (2.0*fragCoord-iResolution.xy)/iResolution.y;
	float d  = sdCircle(p,0.5);
  vec3 col = (d>0.0) ? vec3(0.0) : vec3(1.0);

  // mouse visualization
  vec2 m = (2.0*iMouse.xy-iResolution.xy)/iResolution.y;
  d = sdCircle(m,0.5);
  col = mix(col, vec3(0.0,1.0,0.0), 1.0-smoothstep(0.0, 0.005, abs(length(p-m)-abs(d))-0.0025));
  col = mix(col, vec3(0.0,1.0,0.0), 1.0-smoothstep(0.0, 0.005, length(p-m)-0.015));

	fragColor = vec4(col,1.0);
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
