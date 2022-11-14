#include <iostream>

using namespace std;

extern int define1();

class Test {
public:
    void setXxx(int xxxxx) {
        xxx = xxxxx;
    }

    void setYyy(char yyyyy) {
        yyy = yyyyy;
    }

    void xxxx() {
        cout << xxx << endl;
    }

    void yyyy() {
        cout << yyy << endl;
    }

private:
    union {
        int xxx;
        char yyy;
    };


};

union TestUnion {
    char c;
    int i;
    float f;
};

int main() {
    define1();
    std::cout << "Hello, World!" << std::endl;
    Test *t = new Test;
    t->xxxx();
    t->yyyy();
    t->setXxx(97);
    t->xxxx();
    t->yyyy();
    cout << sizeof(TestUnion) << endl;
    return 0;
}
