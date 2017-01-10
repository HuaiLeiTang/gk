/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/gk.h"

void
gkRenderModel(GkScene     *scene,
              GkModelBase *modelBase,
              GkMatrix    *pmat,
              GkProgInfo  *pprog) {
  GkMatrix   *mat;
  GkProgInfo *prog;
  uint32_t    updt;

  mat  = modelBase->matrix;
  prog = modelBase->pinfo;

  if (!mat)
    modelBase->matrix = mat = pmat;

  updt = !pmat->cmatIsValid || !mat->cmatIsValid;

  if (updt){
    if (pmat != mat) {
      glm_mat4_mul(pmat->matrix,
                   mat->matrix,
                   mat->cmat);
      mat->cmatIsValid = 0;
    }

    if (!mat->cmvp)
      mat->cmvp = malloc(sizeof(mat4));

    glm_mat4_mul(scene->pv,
                 mat->cmat,
                 *mat->cmvp);
  } else if(!scene->pvIsValid) {
    if (!mat->cmvp)
      mat->cmvp = malloc(sizeof(mat4));

    glm_mat4_mul(scene->pv,
                 mat->cmat,
                 *mat->cmvp);
  }

  if (!prog)
    modelBase->pinfo = prog = pprog;

  gkUniformMatrix(modelBase);

  /* pre events */
  if (modelBase->events && modelBase->events->onDraw)
    modelBase->events->onDraw(modelBase, NULL, false);

  /* render */
  if (modelBase->flags & GK_COMPLEX) {
    GkComplexModel *model;
    uint32_t        index;

    model = (GkComplexModel *)modelBase;

    for (index = 0; index < model->vaoCount; index++) {
      glBindVertexArray(model->vao[index]);

      if (modelBase->flags & GK_DRAW_ELEMENTS) {
        glDrawElements(model->modes[index],
                       model->count[index],
                       GL_UNSIGNED_INT, /* TODO: ? */
                       NULL);;
      } else if (modelBase->flags & GK_DRAW_ARRAYS) {
        glDrawArrays(model->modes[index],
                     0,
                     model->count[index]);
      }
    }
  } else {
    GkModel *model;
    model = (GkModel *)modelBase;

    glBindVertexArray(model->vao);

    if (modelBase->flags & GK_DRAW_ELEMENTS)
      glDrawElements(model->mode,
                     model->count,
                     GL_UNSIGNED_INT, /* TODO: ? */
                     NULL);
    else if (modelBase->flags & GK_DRAW_ARRAYS)
      glDrawArrays(model->mode, 0, model->count);
  }

  glBindVertexArray(0);

  /* post events */
  if (modelBase->events && modelBase->events->onDraw)
    modelBase->events->onDraw(modelBase, NULL, true);

  if(updt && mat != pmat)
    mat->cmatIsValid = 1;
}