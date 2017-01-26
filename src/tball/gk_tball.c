/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "gk_tball.h"
#include "gk_tball_mouse.h"
#include "../../include/gk-transform.h"
#include "../default/gk_transform.h"
#include <string.h>

GkTrackball*
gk_tball_new() {
  GkTrackball *tball;

  tball = calloc(sizeof(*tball), 1);
  tball->enabled  = true;
  tball->mouse    = gk_tball_mouse;
  tball->mouse2   = gk_tball_mouse_ws;

  return tball;
}

void
gk_tball_init(GkTrackball * __restrict tball,
              GkScene     * __restrict scene,
              GkNode      * __restrict node,
              GkBBox      * __restrict bbox) {
  GkMatrix *trans;
  assert(tball && scene && bbox && "invalid params!");

  tball->scene    = scene;
  tball->bbox     = bbox;
  tball->velocity = 2.5f;

  trans = scene->trans;
  if (!trans) {
    trans = malloc(sizeof(*trans));
    trans->refc        = 1;
    trans->cmatIsValid = 0;

    glm_mat4_dup(GLM_MAT4_IDENTITY, trans->matrix);
    glm_mat4_dup(GLM_MAT4_IDENTITY, trans->cmat);
    scene->trans = trans;
  }

  if (node)
    tball->matrix = node->matrix;
  else
    tball->matrix = gk_def_idmat();
}

void
gkTrackballFree(GkTrackball *tball) {
  free(tball);
}

void
gk_tall_vec(GkTrackball * __restrict tball,
            GkPoint p,
            vec3    vec) {
  mat4    m;
  GkPoint c;
  GkRect  vrc;
  float   d;

  glm_mat4_mul(tball->scene->pv,
               tball->matrix->cmat,
               m);

  /* use unit sphere if needed tball->bbox->radius is available! */

  vrc = tball->scene->vrect;
  c   = gk_project2d(vrc, m, tball->bbox->center);

  vec[0] = (p.x - c.x) / vrc.size.w;
  vec[1] = (p.y - c.y) / vrc.size.h;
  d      = vec[0] * vec[0] + vec[1] * vec[1];

  if (d <= 0.5f)
    vec[2] = sqrtf(1.0f - d);
  else
    vec[2] = 0.5f / sqrtf(d);

  glm_vec_normalize(vec);
}
