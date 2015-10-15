/*    __________________________________________________________________    *
 *   /                                                                  \   *
 *  /          Boiler control code - Nick + Joe Piscitello 2015          \  *
 * (                                                                      ) *
 *  )   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   (  *
 * (                                                                      ) *
 *  )   Dependencies:                                                    (  *
 * (      - LedControl library: https://github.com/wayoda/LedControl      ) *
 *  )	  - Encoder library:                                             (  *
 * (             http://www.pjrc.com/teensy/td_libs_Encoder.html          ) *
 *  )     - TaskScheduler library:                                       (  *
 * (             http://playground.arduino.cc/Code/TaskScheduler          ) *
 *  )                                                                    (  *
 * (    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    ) *
 *  )                                                                    (  *
 * (    Functions:                                                        ) *
 *  )     - Sense when the coal stove is hot                             (  *
 * (        - when hot, circulate the heating loops every so often        ) *
 *  )         to prevent freezing pipes                                  (  *
 * (                                                                      ) *
 *  )     - Display and take input                                       (  *
 * (        - coal stove temperature                                      ) *
 *  )       - rest time between circulation                              (  *
 * (        - duration of circulation                                     ) *
 *  )       - temperature threshold                                      (  *
 * (                                                                      ) *
 *  )     - turn off when inactive                                       (  *
 * (        - save settings to EEPROM (if changed) to be recovered        ) *
 *  )         at next boot                                               (  *
 * (                                                                      ) *
 *  )   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   (  *
 * (                                                                      ) *
 *  \    Is it ironic that this has a boilerplate comment at the top?    /  *
 *   \__________________________________________________________________/   */

#include "Circulator.h"
#include "EEPROM.h"
#include "IO.h"
#include "MetaManagement.h"

void setup() {

}

void loop() {

}
