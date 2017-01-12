/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef gk_h
#define gk_h
#ifdef __cplusplus
extern "C" {
#endif

#include "gk-common.h"
#include "gk-shader.h"
#include "gk-program.h"

#include <stdlib.h>
#include <cglm.h>

#define GK_DRAW_ELEMENTS (1 << 0)
#define GK_DRAW_ARRAYS   (1 << 1)
#define GK_COMPLEX       (1 << 2)

#include "gk-model.h"

typedef struct GkNode {
  GkNodeFlags    flags;
  GkProgInfo    *pinfo;
  GkMatrix      *matrix;
  GkModelInst   *model;
  struct GkNode *next;
  struct GkNode *chld;
  struct GkNode *nodeInst;
} GkNode;

typedef struct GkScene {
  mat4        v;
  mat4        pv;
  GkNode     *rootNode;
  GkProgInfo *pinfo;
  uint32_t    pvIsValid;
  uint32_t    vIsValid;
} GkScene;

GkModelInst *
gkMakeInstance(GkModelBase *model);

void
gkUniformMatrix(GkModelInst *modelInst);

void
gkRenderModel(GkScene     *scene,
              GkModelInst *modelInst,
              GkMatrix    *parentMat,
              GkProgInfo  *parentProg);

void
gkRenderNode(GkScene    *scene,
             GkNode     *node,
             GkMatrix   *parentMat,
             GkProgInfo *parentProg);

void
gkRenderScene(GkScene * scene);

#ifdef __cplusplus
}
#endif
#endif /* gk_h */
