#ifndef VALVE_H
#define VALVE_H

#include <Arduino.h>
#define Pin_Elecreovanne_IN 7 //sur IN1 de Relais
#define Pin_Electrovanne_OUT 8 //sur IN2 de Relais

/* sur le relais, electrovanne est branche sur normaly open
donc par defaut le relais est deactivé

mettre l'entree de commande a 0 active l'electrovanne et mettre a 1 desactive 
par defaut l'entree est a etat active càd a 1 
mettre a 0 ouvre l'electrovanne et mettre a 1 ferme.
 */
#define ON 0
#define OFF 1

class valve
{
private:
    /* data */
public:
    valve(/* args */);
    void begin();
    void IN_ON();
    void IN_OFF();
    void OUT_ON();
    void OUT_OFF();
};






#endif