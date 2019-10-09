#ifndef MACROS_H
#define MACROS_H

//Macro pour savoir si un double est très près de zéro
#define EPSILON 0.00000001
#define EGAL_ZERO(Nombre) (((Nombre) < EPSILON) && (-(Nombre) < EPSILON))

//Pour convertir les angles
#define RAD_TO_DEG(AngleRad) ((AngleRad) * 57.2957795130823208767981548141052)
#define DEG_TO_RAD(AngleDeg) ((AngleDeg) * 0.0174532925199432957692369076848861)

//Pour savoir si un nombre est dans l'intervalle [BorneMin, BorneMax]
#define DANS_INTERVALLE(Valeur, BorneMin, BorneMax) (((Valeur) >= BorneMin) && ((Valeur) <= BorneMax))

#endif