#ifndef ENCCOUNTER_h
#define ENCCOUNTER_h

// //#include"gr_common/rx63n/iodefine_gcc63n.h"
#include "RZ_A1H.h"

#define ENC_INIT_VAL 0x7FFF

class encCounter
{
public:
    encCounter(int);
    int getCount();
    void init();

private:
    bool ch_available;
    unsigned short int pre_rawcount;
    int encount;
    int g_ch;
};

#endif //処理ブロックの最後を明示
