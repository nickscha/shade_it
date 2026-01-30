/* Shade-It procedural texture generator */
#version 330 core

out vec4 FragColor;

/* Uniforms */
uniform vec3  iResolution;
uniform float iTime;
uniform vec4  iMouse;

float hash(vec2 p)
{
    p = fract(p * vec2(123.34, 456.21));
    p += dot(p, p + 45.32);
    return fract(p.x * p.y);
}

float noise(vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);
    f = f * f * (3.0 - 2.0 * f);

    float a = hash(i);
    float b = hash(i + vec2(1, 0));
    float c = hash(i + vec2(0, 1));
    float d = hash(i + vec2(1, 1));

    return mix(mix(a, b, f.x), mix(c, d, f.x), f.y);
}

float fbm(vec2 p)
{
    float v = 0.0;
    float a = 0.5;

    for (int i = 0; i < 8; i++)
    {
        v += a * noise(p);
        p = p * 2.0 + vec2(17.0);
        a *= 0.5;
    }
    return v;
}

void mainImage(out vec4 outColor, in vec2 fragCoord)
{
    vec2 uv = fragCoord / iResolution.xy;
    uv = uv * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y;

    float t = iTime * 0.2;

    vec2 m = vec2(0.0);
    float seed = floor(iTime * 0.5);
    float rnd  = hash(vec2(seed, seed + 13.0));

    vec2 warp;
    warp.x = fbm(uv * 2.0 + rnd * 5.0 + t);
    warp.y = fbm(uv * 2.0 + rnd * 10.0 - t);

    vec2 p = uv + warp * (0.6 + 0.5 * rnd) + m * 0.15;

    float n1 = fbm(p * 8.0);
    float n2 = fbm(p * 6.0 + 10.0);
    float n3 = noise(p * 12.0);

    float pattern;
    if (rnd < 0.33)
        pattern = n1;
    else if (rnd < 0.66)
        pattern = abs(n1 - n2);
    else
        pattern = smoothstep(0.3, 0.7, n3); 

    /* Color palette */
    vec3 baseA = vec3(0.2, 0.3, 0.6);
    vec3 baseB = vec3(0.9, 0.6, 0.2);
    vec3 baseC = vec3(0.1, 0.8, 0.5);

    vec3 col = mix(baseA, baseB, pattern);
    col = mix(col, baseC, n2 * 0.5);
    col = pow(col, vec3(1.2));
    col += 0.1 * vec3(n3);

    outColor = vec4(col, 1.0);
}

void main()
{
    mainImage(FragColor, gl_FragCoord.xy);
}