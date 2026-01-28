#version 330 core

out vec4 FragColor;

/* Uniforms provided */
uniform vec3  iResolution;
uniform float iTime;
uniform vec4  iMouse;

float hash(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453123);
}

float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    float a = hash(i + vec2(0.0, 0.0));
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));
    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

float fbm(vec2 p) {
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 1.0;
    for (int i = 0; i < 8; i++) {
        value += amplitude * noise(p * frequency);
        frequency *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}

void mainImage(out vec4 outColor, in vec2 fragCoord) {
    vec2 uv = fragCoord / iResolution.xy;
    uv = uv * 2.0 - 1.0;
    vec2 offset = vec2(iMouse.x / iResolution.x, iMouse.y / iResolution.y) * 2.0;
    float t = iTime * 0.2;
    float n = fbm(uv * 3.0 + offset + vec2(t, t));
    vec3 col = vec3(1.0) * n;

    outColor = vec4(col, 1.0);
}

void main() {
    mainImage(FragColor, gl_FragCoord.xy);
}
