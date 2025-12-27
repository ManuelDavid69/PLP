#ifndef LAMBDA_H
#define LAMBDA_H

/* Reconnaît la forme (lambda x.<expression>) <argument>. */
int is_lambda_expression(const char *ligne);

/* Analyse et évalue une expression lambda. Retourne 1 en cas de succès. */
int eval_lambda_expression(const char *ligne, double *resultat);

#endif
