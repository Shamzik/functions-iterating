#include "processor.h"
#include "queue.h"
#include "with_multiplicity.h"

class LoggerCallback {
public:
    bool operator()(auto v) {
        std::cout << v << std::endl;
        return false;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "ERROR: arguments count must be 3" << std::endl;
        return 1;
    }
    auto queue = Queue(WithMultiplicity(LinearFunction(1, 0)),
                       LinearFunction(2, std::strtoull(argv[1], nullptr, 10)),
                       LinearFunction(3, std::strtoull(argv[2], nullptr, 10)),
                       LinearFunction(6, std::strtoull(argv[3], nullptr, 10))
    );
//    auto processor = Processor<MultiplicityChecker>();
    auto processor = Processor<LoggerCallback, MultiplicityChecker>();
    processor.Process(
        queue, WithMultiplicity(LinearFunction(100'000'000, 100'000'000))
    );
}
