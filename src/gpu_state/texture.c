/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../../include/gk/gk.h"
#include "../../include/gk/gpu_state.h"

#include "common.h"

GK_EXPORT
void
gkActiveTexture(GkContext * __restrict ctx,
                uint32_t               unit) {
  GkGPUStates *ast;
  
  ast = ctx->currState;
  if (ast->activeTex == unit)
    return;
  
  ast->activeTex = unit;
  glActiveTexture(GL_TEXTURE0 + unit);
}

GK_EXPORT
void
gkBindTextureTo(GkContext * __restrict ctx,
                uint32_t               unit,
                uint32_t               target,
                uint32_t               texid) {
  GkTextureState *state;
  state = gkGetOrCreatTexState(ctx, unit, target);
  if (state->texid == texid)
    return;
  
  gkActiveTexture(ctx, unit);
  glBindTexture(target, texid);
}

GK_EXPORT
void
gkBindTexture(GkContext * __restrict ctx,
              uint32_t               target,
              uint32_t               texid) {
  GkTextureState *state;
  GkGPUStates *ast;
  
  ast = ctx->currState;
  
  state = gkGetOrCreatTexState(ctx, ast->activeTex, target);
  if (state->texid == texid)
    return;
  
  glBindTexture(target, texid);
}