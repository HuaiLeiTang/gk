/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef gk_scene_h
#define gk_scene_h
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

struct GkPassOut;
struct FListItem;
struct GkScene;
struct GkContext;

typedef enum GkSceneFlags {
  GK_SCENEF_NONE          = 0,
  GK_SCENEF_DRAW_BBOX     = 1 << 0,
  GK_SCENEF_UPDT_VIEW     = 1 << 1,
  GK_SCENEF_UPDT_PROJ     = 1 << 2,
  GK_SCENEF_UPDT_LIGHTS   = 1 << 3,
  GK_SCENEF_ONCE          = 1 << 4,
  GK_SCENEF_RENDERING     = 1 << 5,
  GK_SCENEF_RENDERED      = 1 << 6,
  GK_SCENEF_RENDER        = 1 << 7,
  GK_SCENEF_UPDT_VIEWPROJ = GK_SCENEF_UPDT_VIEW | GK_SCENEF_UPDT_PROJ,
  GK_SCENEF_NEEDS_RENDER  = GK_SCENEF_RENDER
                          | GK_SCENEF_UPDT_VIEW
                          | GK_SCENEF_UPDT_PROJ
                          | GK_SCENEF_UPDT_LIGHTS,
  GK_SCENEF_INIT          = GK_SCENEF_NEEDS_RENDER,
} GkSceneFlags;

GK_MAKE_C_ENUM(GkSceneFlags)

typedef struct GkScenePrivateFields {
  struct GkContext *ctx;
  struct GkPass     *overridePass;     /* override all passes    */
  struct GkMaterial *overrideMaterial; /* override all materials */
} GkScenePrivateFields;

typedef struct GkScene {
  GkScenePrivateFields _priv;
  GkCamera         *camera;
  GkTransform      *trans;  /* free camera */
  GkNode           *rootNode;
  GkProgram        *prog;
  GkLightRef       *lights;
  GkBBox           *bbox;
  struct GkPassOut *finalOutput; /* set NULL for default FBO (screen) */
  GkRect            vrect;
  uint32_t          lightCount;
  uint32_t          lastLightIndex;
  GLenum            usage;
  GkSceneFlags      flags;
  GLenum            internalFormat;
  float             backingScale;
  float             fpsApprx;
} GkScene;

#ifdef __cplusplus
}
#endif
#endif /* gk_scene_h */
