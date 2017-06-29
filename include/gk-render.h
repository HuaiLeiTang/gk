/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef gk_render_h
#define gk_render_h
#ifdef __cplusplus
extern "C" {
#endif

#include "gk-common.h"

void
gkUniformMatrix(GkModelInst *modelInst);

void
gkPrepModel(GkScene     *scene,
            GkModelInst *modelInst,
            GkTransform *ptr,
            GkProgInfo  *pprog);

void
gkRenderModel(GkScene     *scene,
              GkModelInst *modelInst,
              GkTransform *ptr,
              GkProgInfo  *pprog);

void
gkPrepNode(GkScene     *scene,
           GkNode      *node,
           GkTransform *ptr,
           GkProgInfo  *pprog);

void
gkRenderNode(GkScene     *scene,
             GkNode      *node,
             GkTransform *ptr,
             GkProgInfo  *pprog);

void
gkRenderScene(GkScene * scene);

#ifdef __cplusplus
}
#endif
#endif /* gk_render_h */
