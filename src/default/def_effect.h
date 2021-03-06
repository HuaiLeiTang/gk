/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef gk_def_effect_h
#define gk_def_effect_h

#include "../../include/gk/gk.h"
#include "../../include/gk/material.h"

GkMaterial*
gk_def_material(void);

GkTechnique*
gk_def_material_phong(void);

GkTechnique*
gk_def_material_blinn(void);

GkTechnique*
gk_def_material_lambert(void);

GkTechnique*
gk_def_material_constant(void);

GkMetalRough*
gk_def_material_mtlrough(void);

GkSpecGloss*
gk_def_material_specgloss(void);

#endif /* gk_def_effect_h */
