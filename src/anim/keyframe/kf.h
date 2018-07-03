/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../../common.h"
#include "../../../include/gk/animation.h"

_gk_hide
bool
gkBuiltinKFAnim(GkAnimation *anim,
                GkChannel   *channel,
                GkValue     *to,
                GkValue     *delta);
GK_EXPORT
void
gkPrepChannel(GkChannel *ch);

GK_EXPORT
void
gkPrepChannelKey(GkChannel *ch);