#version 330 core

out vec4 FragColor;

/* Uniforms provided */
uniform vec3  iResolution;
uniform float iTime;
uniform vec4  iMouse;

void mainImage(out vec4 outColor, in vec2 fragCoord)
{
    vec2 uv = fragCoord / iResolution.xy;
    uv = uv * 2.0 - 1.0;
    float waveSpeed = 0.5 + 0.5 * iMouse.x / iResolution.x;
    float waveFreq  = 2.0 + 4.0 * iMouse.y / iResolution.y;
    float wave = sin(uv.x * waveFreq + iTime * waveSpeed) + cos(uv.y * waveFreq + iTime * waveSpeed * 1.2);
    vec3 color = vec3(0.2, 0.4, 0.8) + 0.5 * vec3(sin(wave), cos(wave*1.5), sin(wave*0.7));

    outColor = vec4(color, 1.0);
}

void main()
{
    vec2 fragCoord = gl_FragCoord.xy;
    mainImage(FragColor, fragCoord);
}
