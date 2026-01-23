/* Shade-It animated pixel art clouds */
#version 330 core

out vec4 FragColor;

/* Uniforms */
uniform vec3  iResolution;
uniform float iTime;
uniform float iTimeDelta;
uniform int   iFrame;
uniform float iFrameRate;

/* Hash */
float hash(vec2 p)
{
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453123);
}

/* Smooth value noise */
float noise(vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);

    float a = hash(i);
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
           (c - a) * u.y * (1.0 - u.x) +
           (d - b) * u.x * u.y;
}

/* Fractal Brownian Motion */
float fbm(vec2 p)
{
    float v = 0.0;
    float a = 0.5;

    for (int i = 0; i < 5; i++)
    {
        v += a * noise(p);
        p *= 2.0;
        a *= 0.5;
    }
    return v;
}

void mainImage(out vec4 outColor, in vec2 fragCoord)
{
    /* Virtual pixel resolution */
    vec2 pixelRes = vec2(320.0, 160.0);

    vec2 pixelCoord = floor(fragCoord * pixelRes / iResolution.xy);
    vec2 uv = pixelCoord / pixelRes;

    /* Scroll clouds */
    vec2 p = uv * 6.0;
    p.x += iTime * 0.05;
    p.y += iTime * 0.02;

    float c = fbm(p);

    /* Shape clouds */
    c = smoothstep(0.45, 0.75, c);

    /* Sky gradient */
    vec3 skyTop    = vec3(0.10, 0.20, 0.35);
    vec3 skyBottom = vec3(0.60, 0.75, 0.90);
    vec3 sky = mix(skyBottom, skyTop, uv.y);

    /* Cloud color */
    vec3 cloud = vec3(1.0);
    vec3 col = mix(sky, cloud, c);

    /* Pixel-art posterization */
    col = floor(col * 6.0) / 6.0;

    outColor = vec4(col, 1.0);
}

void main()
{
    mainImage(FragColor, gl_FragCoord.xy);
}
