/* Shade-It Debug UI Shader for testing */
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

float hash(vec2 p)
{
    p = fract(p * vec2(123.34, 456.21));
    p += dot(p, p + 78.233);
    return fract(p.x * p.y);
}

float noise(vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);
    f = f * f * (3.0 - 2.0 * f);

    float a = hash(i);
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));

    return mix(mix(a, b, f.x), mix(c, d, f.x), f.y);
}

float fbm(vec2 p)
{
    float v = 0.0;
    float a = 0.5;

    for (int i = 0; i < 5; i++)
    {
        v += a * noise(p);
        p = p * 2.0 + vec2(100.0);
        a *= 0.5;
    }

    return v;
}

void mainImage(out vec4 outColor, in vec2 fragCoord)
{
    vec2 uv = (fragCoord - 0.5 * iResolution.xy) / iResolution.y;

    float t = iTime * 0.2;

    /* Time-varying domain warp */
    vec2 warp;
    warp.x = fbm(uv * 2.0 + vec2(0.0, t));
    warp.y = fbm(uv * 2.0 + vec2(t, 0.0));

    /* Apply warp */
    vec2 p = uv + 0.6 * warp;

    /* Final noise */
    float n = fbm(p * 3.0);

    /* Color */
    vec3 col = vec3(0.15, 0.3, 0.6);
    col = mix(col, vec3(0.9, 0.95, 1.0), n);
    
    /* ############################## */
    /* # Mouse visualization        # */
    /* ############################## */
    if (iMouse.x >= 0.0)
    {
        vec2 mouse = iMouse.xy;
        float d = length(fragCoord - mouse); /* distance in pixels */
        float dotMask = exp(-d * 0.08);      /* soft dot */
        vec3 mouseCol = vec3(1.0, 0.2, 0.1); /* red/orange */

        col += mouseCol * dotMask * 1.2;
    }

    /* ############################## */
    /* # Texture visualization      # */
    /* ############################## */
    vec2 cornerSize = iTextureInfo.xy; // size in pixels
    vec2 cornerPos  = vec2(10, 10);    // offset from bottom-left

    if (fragCoord.x >= cornerPos.x && fragCoord.x < cornerPos.x + cornerSize.x &&
        fragCoord.y >= cornerPos.y && fragCoord.y < cornerPos.y + cornerSize.y)
    {
        /* map fragCoord to [0,1] UV for the texture */
        vec2 texUV;
        texUV.x = (fragCoord.x - cornerPos.x) / cornerSize.x;
        texUV.y = 1.0 - (fragCoord.y - cornerPos.y) / cornerSize.y;  // flip Y

        vec3 texCol = texture(iTexture, texUV).rrr; // grayscale font
        col = mix(col, vec3(0.0), texCol.r);        // overlay black font
    }

    /* ############################## */
    /* # Screen Border              # */
    /* ############################## */
    float border = 1.0;

    if (fragCoord.x < border ||
        fragCoord.y < border ||
        fragCoord.x >= iResolution.x - border ||
        fragCoord.y >= iResolution.y - border)
    {
        col = vec3(0.0, 1.0, 0.0);
    }

    outColor = vec4(col, 1.0);
}

void main()
{
    mainImage(FragColor, gl_FragCoord.xy);
}
