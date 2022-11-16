//
// Created by yxl on 22-11-16.
//

#include "Span.h"

int MyTCMalloc::Common::Span::getPageNum() const {
    return page_num;
}

void *MyTCMalloc::Common::Span::getStart() const {
    return start;
}

MyTCMalloc::ClassSizeInfo MyTCMalloc::Common::Span::getPageSize(size_t malloc_size) {
    for (ClassSizeInfo csi: MyTCMalloc::kSizeClassesList) {
        if (csi.size < malloc_size)
            continue;
        else {
            return csi;
        }
    }
}
