#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <utility>
#include <sys/time.h>

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int>  _deq;

    // Helper functions for parsing
    bool isValidPositiveInteger(const std::string& str, int& value) const;

    // Ford-Johnson (Merge-Insertion Sort) for std::vector
    void sortVector(std::vector<int>& arr);
    std::vector<size_t> generateJacobsthalSequence(size_t size) const;

    // Ford-Johnson (Merge-Insertion Sort) for std::deque
    void sortDeque(std::deque<int>& arr);
    std::deque<size_t> generateJacobsthalSequenceDeque(size_t size) const;

    // Time helper
    static double getCurrentTimeInUs();

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    bool run(int argc, char** argv);
};

#endif
