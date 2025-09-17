#include <cstdlib>
#include <ctime>

class numberguessing {
  public:
    numberguessing() : value(0), times(0) {}

    void Set(int v) {
        value = v;
    }

    int Get() const {
        return value;
    }

    int Guesser(int v) {
        if (v < value) {
            times++;
            return -1;
        } else if (v > value) {
            times++;
            return 1;
        } else {
            return 0;
        }
    }

    int Time() const {
        return times;
    }

    void Reset() {
        times = 0;
    }

  private:
    int value;
    int times;
};
