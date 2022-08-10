#pragma once

#include "gamestruct/size.hpp"

namespace manager{
    // la size della finersta
    const Size kGameWindowsSize = {22, 60};
    const Size kItemAreaSize = {5,17};
    const Size kLogAreaSize = {kItemAreaSize.riga,kGameWindowsSize.colonna-(kItemAreaSize.colonna+1)};
    const Size kGameAreaSize = {kGameWindowsSize.riga-kItemAreaSize.riga, kGameWindowsSize.colonna};
    const Size kPaddingLogArea = {1,1};

    // Decide ogni quanti millisecondi avviene un update a schermo
    const int kSleepTime = 50;

    // Descrive ogni quanti frame si può muovere un nemico
    const int kObjectTimer = 10;

}; //namespace manager