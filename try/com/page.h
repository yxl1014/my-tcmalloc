//
// Created by yxl on 22-11-16.
//

#ifndef MY_TCMALLOC_PAGE_H
#define MY_TCMALLOC_PAGE_H


#include <cstdlib>
#include <atomic>
#include "common.h"

using namespace std;
namespace MyTCMalloc {
    namespace Common {
        atomic_long page_index(0);

        class Page {
        public:
            explicit Page(void *addr) {
                pageId = page_index++;
                start_addr = addr;
            }
            int getPageId() const {
                return pageId;
            }
            void *getStartAddr() const {
                return start_addr;
            }
        private:
            int pageId;
            void *start_addr;
        };
    }
}


#endif //MY_TCMALLOC_PAGE_H
