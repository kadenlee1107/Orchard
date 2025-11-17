#pragma once

#include <dispatch/dispatch.h>

namespace orchard {

class Threading {
public:
    static void ParallelFor(size_t count, void (^block)(size_t)) {
        dispatch_apply(count, dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0), block);
    }
};

}
