//
// Created by yxl on 22-11-15.
//

#ifndef MY_TCMALLOC_MY_PAGE_H
#define MY_TCMALLOC_MY_PAGE_H

#include "common.h"

namespace MyTCMalloc {
    namespace Common {
        size_t min_page_size = MyTCMalloc::kMinPages;

        class Page {
        public:

        private:
            int pageId;
            void *start_addr;
        };
    }
}


#endif //MY_TCMALLOC_MY_PAGE_H
