#include "PmergeMe.hpp"
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <climits>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

double PmergeMe::getCurrentTimeInUs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (static_cast<double>(tv.tv_sec) * 1000000.0) + static_cast<double>(tv.tv_usec);
}

bool PmergeMe::isValidPositiveInteger(const std::string& str, int& value) const {
    if (str.empty())
        return false;

    size_t i = 0;
    if (str[i] == '+')
        i++;
    if (i == str.length())
        return false;

    for (; i < str.length(); ++i) {
        if (!isdigit(str[i]))
            return false;
    }

    std::stringstream ss(str);
    long long num;
    ss >> num;

    if (ss.fail() || !ss.eof() || num <= 0 || num > INT_MAX)
        return false;

    value = static_cast<int>(num);
    return true;
}

std::vector<size_t> PmergeMe::generateJacobsthalSequence(size_t size) const {
    std::vector<size_t> order;
    if (size <= 1)
        return order;

    std::vector<size_t> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    while (jacob.back() < size) {
        size_t nextJ = jacob.back() + 2 * jacob[jacob.size() - 2];
        jacob.push_back(nextJ);
    }

    size_t lastIndex = 1;
    for (size_t k = 3; k < jacob.size(); ++k) {
        size_t currJacob = jacob[k];
        size_t limit = (currJacob < size) ? currJacob : size;
        for (size_t idx = limit; idx > lastIndex; --idx) {
            order.push_back(idx - 1);
        }
        lastIndex = limit;
        if (lastIndex >= size)
            break;
    }
    return order;
}

void PmergeMe::sortVector(std::vector<int>& arr) {
    if (arr.size() <= 1)
        return;

    bool hasStraggler = false;
    int straggler = 0;
    if (arr.size() % 2 != 0) {
        hasStraggler = true;
        straggler = arr.back();
        arr.pop_back();
    }

    std::vector<std::pair<int, int> > pairs;
    pairs.reserve(arr.size() / 2);
    for (size_t i = 0; i < arr.size(); i += 2) {
        if (arr[i] < arr[i + 1])
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
        else
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
    }

    std::vector<int> larger;
    larger.reserve(pairs.size());
    for (size_t i = 0; i < pairs.size(); ++i) {
        larger.push_back(pairs[i].first);
    }

    sortVector(larger);

    std::vector<int> main_chain;
    std::vector<int> pend;
    main_chain.reserve(arr.size() + (hasStraggler ? 1 : 0));
    pend.reserve(pairs.size());

    std::vector<bool> used(pairs.size(), false);
    for (size_t i = 0; i < larger.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (!used[j] && pairs[j].first == larger[i]) {
                main_chain.push_back(pairs[j].first);
                pend.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }

    if (!pend.empty()) {
        main_chain.insert(main_chain.begin(), pend[0]);
    }

    std::vector<size_t> jacobOrder = generateJacobsthalSequence(pend.size());
    for (size_t i = 0; i < jacobOrder.size(); ++i) {
        size_t idx = jacobOrder[i];
        int valToInsert = pend[idx];

        std::vector<int>::iterator limit = std::find(main_chain.begin(), main_chain.end(), larger[idx]);
        std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), limit, valToInsert);
        main_chain.insert(pos, valToInsert);
    }

    if (hasStraggler) {
        std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
        main_chain.insert(pos, straggler);
    }

    arr = main_chain;
}

std::deque<size_t> PmergeMe::generateJacobsthalSequenceDeque(size_t size) const {
    std::deque<size_t> order;
    if (size <= 1)
        return order;

    std::deque<size_t> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    while (jacob.back() < size) {
        size_t nextJ = jacob.back() + 2 * jacob[jacob.size() - 2];
        jacob.push_back(nextJ);
    }

    size_t lastIndex = 1;
    for (size_t k = 3; k < jacob.size(); ++k) {
        size_t currJacob = jacob[k];
        size_t limit = (currJacob < size) ? currJacob : size;
        for (size_t idx = limit; idx > lastIndex; --idx) {
            order.push_back(idx - 1);
        }
        lastIndex = limit;
        if (lastIndex >= size)
            break;
    }
    return order;
}

void PmergeMe::sortDeque(std::deque<int>& arr) {
    if (arr.size() <= 1)
        return;

    bool hasStraggler = false;
    int straggler = 0;
    if (arr.size() % 2 != 0) {
        hasStraggler = true;
        straggler = arr.back();
        arr.pop_back();
    }

    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size(); i += 2) {
        if (arr[i] < arr[i + 1])
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
        else
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
    }

    std::deque<int> larger;
    for (size_t i = 0; i < pairs.size(); ++i) {
        larger.push_back(pairs[i].first);
    }

    sortDeque(larger);

    std::deque<int> main_chain;
    std::deque<int> pend;
    std::deque<bool> used(pairs.size(), false);

    for (size_t i = 0; i < larger.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (!used[j] && pairs[j].first == larger[i]) {
                main_chain.push_back(pairs[j].first);
                pend.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }

    if (!pend.empty()) {
        main_chain.push_front(pend[0]);
    }

    std::deque<size_t> jacobOrder = generateJacobsthalSequenceDeque(pend.size());
    for (size_t i = 0; i < jacobOrder.size(); ++i) {
        size_t idx = jacobOrder[i];
        int valToInsert = pend[idx];

        std::deque<int>::iterator limit = std::find(main_chain.begin(), main_chain.end(), larger[idx]);
        std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), limit, valToInsert);
        main_chain.insert(pos, valToInsert);
    }

    if (hasStraggler) {
        std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
        main_chain.insert(pos, straggler);
    }

    arr = main_chain;
}

bool PmergeMe::run(int argc, char** argv) {
    std::vector<int> rawInput;

    // Validate and collect numbers
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        std::stringstream ss(arg);
        std::string token;
        while (ss >> token) {
            int value;
            if (!isValidPositiveInteger(token, value)) {
                std::cerr << "Error" << std::endl;
                return false;
            }
            rawInput.push_back(value);
        }
    }

    if (rawInput.empty()) {
        std::cerr << "Error" << std::endl;
        return false;
    }

    // Print Before
    std::cout << "Before:";
    for (size_t i = 0; i < rawInput.size(); ++i) {
        std::cout << " " << rawInput[i];
    }
    std::cout << std::endl;

    // Measure std::vector (data management + sorting)
    double startVec = getCurrentTimeInUs();
    _vec.clear();
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        std::stringstream ss(arg);
        std::string token;
        while (ss >> token) {
            int value;
            isValidPositiveInteger(token, value);
            _vec.push_back(value);
        }
    }
    sortVector(_vec);
    double endVec = getCurrentTimeInUs();
    double timeVec = endVec - startVec;

    // Measure std::deque (data management + sorting)
    double startDeq = getCurrentTimeInUs();
    _deq.clear();
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        std::stringstream ss(arg);
        std::string token;
        while (ss >> token) {
            int value;
            isValidPositiveInteger(token, value);
            _deq.push_back(value);
        }
    }
    sortDeque(_deq);
    double endDeq = getCurrentTimeInUs();
    double timeDeq = endDeq - startDeq;

    // Print After
    std::cout << "After:";
    for (size_t i = 0; i < _vec.size(); ++i) {
        std::cout << " " << _vec[i];
    }
    std::cout << std::endl;

    // Print Time statistics
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque : " << timeDeq << " us" << std::endl;

    return true;
}
