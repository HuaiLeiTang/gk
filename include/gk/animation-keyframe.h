/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef gk_keyframe_animation_h
#define gk_keyframe_animation_h
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "value.h"

struct GkAnimation;
struct GkScene;
struct GkNode;

typedef enum GkTargetPropertyType {
  GK_TARGET_UNKNOWN  = 0,
  GK_TARGET_X        = 1,
  GK_TARGET_Y        = 2,
  GK_TARGET_Z        = 3,
  GK_TARGET_XY       = 4,
  GK_TARGET_XYZ      = 5,
  GK_TARGET_ANGLE    = 6,
  GK_TARGET_POSITION = 7,
  GK_TARGET_SCALE    = 8,
  GK_TARGET_ROTATE   = 9,
  GK_TARGET_QUAT     = 10
} GkTargetPropertyType;

typedef enum GkSamplerBehavior {
  GK_SAMPLER_UNDEFINED      = 0,
  GK_SAMPLER_CONSTANT       = 1,
  GK_SAMPLER_GRADIENT       = 2,
  GK_SAMPLER_CYCLE          = 3,
  GK_SAMPLER_OSCILLATE      = 4,
  GK_SAMPLER_CYCLE_RELATIVE = 5
} GkSamplerBehavior;

typedef struct GkAnimSampler {
  GkBuffer         *input;
  GkBuffer         *output;
  GkBuffer         *interp;
  GkBuffer         *inTangent;
  GkBuffer         *outTangent;
  GkSamplerBehavior preBehavior;
  GkSamplerBehavior postBehavior;
  GkInterpType      uniInterp;
  uint32_t          inTangentStride;
  uint32_t          outTangentStride;
} GkAnimSampler;

typedef struct GkChannel {
  struct GkChannel    *next;
  GkAnimSampler       *sampler;
  GkNode              *node;         /* required if target is node transform */
  void                *target;
  GkType               targetType;
  GkTargetPropertyType property;
  GkInterpType         lastInterp;
  uint32_t             keyIndex;
  GkValue              ov[2];
  GkValue              kv[2];
  GkValue              delta;
  GkValue              curr;
  double               beginAt;         /* start time on timeline (relative) */
  double               endAt;           /* start time on timeline (relative) */
  double               beginTime;       /* start time for channel            */
  double               endTime;         /* end time for channel              */
  double               keyBeginTime;    /* start time for single key         */
  double               keyEndTime;      /* end time for  single key          */
  double               duration;
  double               keyPercent;
  bool                 isTransform:1;
  bool                 isLocalTransform:1;
  bool                 isPrepared:1;
  bool                 isPreparedKey:1;
  bool                 isFinished:1;    /* all keys are finished             */
  bool                 computeDelta:1;
  bool                 currValuePrepared:1;
} GkChannel;

typedef struct GkKeyFrameAnimation {
  GkAnimation  base;
  GkChannel   *channel;
  uint32_t     channelCount;
} GkKeyFrameAnimation;

typedef struct GkAnimationClip {
  GkAnimation *anim;
  double       start;
  double       end;
} GkAnimationClip;

GK_EXPORT
GkKeyFrameAnimation*
gkKeyFrameAnimation(void);

#ifdef __cplusplus
}
#endif
#endif /* gk_keyframe_animation_h */
