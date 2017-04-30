/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef gk_colortex_uniform_h
#define gk_colortex_uniform_h

#include "../../include/gk.h"

void
gkUniformColorOrTex(GkColorOrTex * __restrict crtx,
                    char         * __restrict buf,
                    char         * __restrict name,
                    GLuint                    prog);

#endif /* gk_colortex_uniform_h */
