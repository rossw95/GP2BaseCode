/*
 * @brief Planar shadows fragment shader.
 */

#version 120

uniform vec4 LIGHT;

varying vec4 point;

/*
 * @brief
 */
void ShadowFragment(void) {

    float dist = distance(LIGHT.xyz, point.xyz / point.w);

    float intensity = (LIGHT.w - dist) / LIGHT.w;

    if (intensity <= 0.0)
        discard;

    gl_FragColor.a = min(gl_Color.a, intensity);
}

/*
 * @brief Program entry point.
 */
void main(void) {

    gl_FragColor = gl_Color;

    ShadowFragment();
}