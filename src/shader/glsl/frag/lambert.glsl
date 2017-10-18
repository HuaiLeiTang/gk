/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

GK_STRINGIFY(

void main() {
  vec4  lightc;
  vec3  L;
  float a, Ld;

  switch (lightType) {
    case SpotLight:
      a = spot(L);
      break;
    case PointLight:
      a = point(L);
      break;
    case DirectionalLight:
      a = directional(L);
      break;
    default:
      discard;
      return;
  }

  lightc = light.color * a;
  Ld     = max(0.0, dot(vNormal, L));

  fragColor =
\n#ifdef DIFFUSE_TEX\n
  lightc * texture(tex2D[mat.diffuse], vTexCoord[mat.diffuse]) * Ld
\n#elif defined(DIFFUSE_COLOR)\n
  lightc * mat.diffuse * Ld
\n#else\n
  lightc * vec4(0, 0, 0, 1)
\n#endif\n

\n#ifdef AMBIENT_TEX\n
  + texture(tex2D[mat.ambient], vTexCoord[mat.ambient])
\n#elif defined(AMBIENT_COLOR)\n
  + mat.ambient
\n#endif\n

\n#ifdef EMISSION_TEX\n
  + texture(tex2D[mat.emission], vTexCoord[mat.emission])
\n#elif defined(EMISSION_COLOR)\n
  + mat.emission
\n#endif\n
;

}
)