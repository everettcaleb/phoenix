#pragma once
#ifndef INCLUDE_PHOENIX_EVID_H
#define INCLUDE_PHOENIX_EVID_H

enum EVID : unsigned int {
    EVID_TICK = 1,
    EVID_SWITCH_TO_FOREGROUND = 2,
    EVID_SWITCH_TO_BACKGROUND = 3
};

#endif //INCLUDE_PHOENIX_EVID_H