#ifndef HASHKEYS_H
#define HASHKEYS_H

// file: hashkeys.h

#include <stdint.h>
#include "position.h"

uint64_t generate_position_key(const struct POSITION *pos);

#endif
