/* Shade-It debug shader for XInput controller support */
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

/* iController layout:
   [0] = (StickLx, StickLy, StickRx, StickRy)
   [1] = (TrigL,   TrigR,   PACKED_BITS,  PADDING)
*/
bool controller_button_down(uint bit_index)
{
    uint bits = floatBitsToUint(iController[1].z);
    return (bits & (1u << bit_index)) != 0u;
}

void mainImage(out vec4 outColor, in vec2 fragCoord)
{
    // Access Analog Sticks
    vec2 left_stick  = iController[0].xy;
    vec2 right_stick = iController[0].zw;
    
    // Access Triggers
    float left_trigger  = iController[1].x;
    float right_trigger = iController[1].y;

    // Access Buttons
    bool btn_a = controller_button_down(0u);
    bool btn_b = controller_button_down(1u);
    bool btn_x = controller_button_down(2u);
    bool btn_y = controller_button_down(3u);
    bool dpad_up = controller_button_down(8u);
    
    if (btn_a) 
    {
      outColor = vec4(0.0, 0.4, 0.0, 1.0);
    } 
    else if (btn_b) 
    {
      outColor = vec4(0.4, 0.0, 0.0, 1.0);
    }
    else if (btn_x) 
    {
      outColor = vec4(0.0, 0.0, 0.4, 1.0);
    }
    else if (btn_y) 
    {
      outColor = vec4(0.6, 0.6, 0.0, 1.0);
    }
    else 
    {
      float r = left_stick.x * 0.5 + 0.5;
      float g = right_stick.y * 0.5 + 0.5;
      float b = right_trigger * 0.5 + 0.5;
      outColor = vec4(r, g, b, 1.0);
    }
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
