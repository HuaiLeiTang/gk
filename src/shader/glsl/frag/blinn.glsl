/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "common.glsl"

GK_STRINGIFY(

void main() {
  vec4  clr, lightc;
  vec3  L, H;
  float a, Ld, Ls;

\n#ifdef SHADOWMAP\n
  float shadow = shadowCoef();
\n#endif\n

  a = getLight(L);

\n#ifdef TRANSP\n
   lightAttn = a;
\n#endif\n

  lightc = vec4(light.color.rgb, 1.0) * a;

\n#ifndef TRANSP\n
  H  = normalize(L + vEye);
  Ld = max(0.0, dot(vNormal, L));
  Ls = max(0.0, dot(vNormal, H));
  if (Ld == 0.0)
    Ls = 0.0;
  else
    Ls = pow(Ls, uShininess);
\n#else\n
  vec3 N;

  N  = vNormal * sign(dot(vNormal, L));
  H  = normalize(L + vEye);
  Ld = max(0.0, dot(N, L));
  Ls = max(0.0, dot(N, H));
  if (Ld == 0.0)
    Ls = 0.0;
  else
    Ls = pow(Ls, uShininess);
\n#endif\n

  clr =
\n#ifdef SHADOWMAP\n
  shadow * (
\n#endif\n

\n#ifdef DIFFUSE_TEX\n
  lightc * texture(uDiffuseTex, DIFFUSE_TEXCOORD) * Ld
\n#elif defined(DIFFUSE_COLOR)\n
  lightc * uDiffuse * Ld
\n#else\n
  lightc * vec4(1, 1, 1, 1) * Ld
\n#endif\n

\n#ifdef AMBIENT_TEX\n
  + texture(uAmbientTex, AMBIENT_TEXCOORD)
\n#elif defined(AMBIENT_COLOR)\n
  + uAmbient
\n#endif\n

\n#ifdef EMISSION_TEX\n
  + texture(uEmissionTex, EMISSION_TEXCOORD)
\n#elif defined(EMISSION_COLOR)\n
  + uEmission
\n#endif\n

\n#ifdef SPECULAR_TEX\n
  +  lightc * texture(uSpecularTex, SPECULAR_TEXCOORD) * Ls
\n#elif defined(SPECULAR_COLOR)\n
  +  lightc * uSpecular * Ls
\n#else\n
  + lightc * vec4(1, 1, 1, 1) * Ls
\n#endif\n
                
\n#ifdef SHADOWMAP\n
  )
\n#endif\n
;

  write(clr);
}
)
