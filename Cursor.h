#ifndef CURSOR_H
#define CURSOR_H

#include "Sprite.h"

class Cursor : public Sprite{
private:
    /** Singleton */
    Cursor();
    static Cursor* instance;

public:
    static Cursor* getInstance();
    ~Cursor();
};

#endif /* CURSOR_H */