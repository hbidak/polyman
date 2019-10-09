#ifndef _HEADER_TEMPS_H_
#define _HEADER_TEMPS_H_

/**
 * @class Temps
 * @brief Definition d'une classe pour stocker le temps
 *
 * Définition de la classe Temps qui représente une position temporelle.
 * Le temps peut s'incrémenter de une unité ou se décrémenter de une unité.
 */
class Temps
{
public:
   Temps( double temps = 0 ) : t( temps ) {};
   operator double( void ) const { return t; };
   const Temps & operator=( const Temps &tem ) { t = tem.t; return *this; };
   const Temps & operator++( void ) { t++; return *this; };
   const Temps & operator--( void ) { t--; return *this; };

   // impression des attributs
   friend std::ostream& operator<<( std::ostream& o, const Temps& tem )
   { o << "Temps=" << tem.t << endl; return o; }

protected:
   double t;
};

#endif
