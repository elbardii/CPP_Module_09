#include "PmergeMe.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    PmergeMe sorter;
    if (!sorter.run(argc, argv)) {
        return 1;
    }

    return 0;
}
