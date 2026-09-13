# شرح الكود سطراً بسطر (Line-by-line Code Explanation) - ex02 (PmergeMe)

هاد الملف كايشرح الكود كامل ديال تمرين **PmergeMe** بالتفصيل الممل وبالدارجة المغربية، باش تفهم كل سطر وتكون قادر تجاوب على أي سؤال كايطرحو المصحح (Peer Evaluator) وبدون تردد.

---

# الجزء 1: ملف الرأس `PmergeMe.hpp`

---

### 1. الـ Include Guards

```cpp
#ifndef PMERGEME_HPP
#define PMERGEME_HPP
```
- **شنو كيدير:** هادو Include Guards (حراس التضمين).
- **علاش درنا هاد الشي؟**
  باش نمنعو مشكل "Double Inclusion". إلا تضمن هاد الملف فكتر من بلاصة أثناء الـ Compilation، الكومبيلر مايعاودش يعرف الكلاس جوج مرات.
- **شنو غادي يوقع إلا حيدناه؟**
  الكومبيلر غادي يعطي خطأ تكرار التعريف: `redefinition of 'class PmergeMe'`.

---

### 2. استدعاء المكتبات الضرورية

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <utility>
#include <sys/time.h>
```
- **شنو كيدير:**
  - `<iostream>`: باش نطبعو `Before:`, `After:`, والإحصائيات بـ `std::cout`، والـ `Error` بـ `std::cerr`.
  - `<string>`: للتعامل مع النصوص والـ Arguments.
  - `<vector>`: الحاوية الأولى المعتمدة للترتيب (`std::vector`).
  - `<deque>`: الحاوية الثانية المعتمدة للترتيب (`std::deque`).
  - `<utility>`: باش نستعملو `std::pair` و `std::make_pair` فتقسيم الأعداد لأزواج.
  - `<sys/time.h>`: باش نستعملو دالة `gettimeofday` لحساب الوقت بدقة الـ Microseconds.
- **علاش درنا هاد الشي؟**
  هادو هما الأدوات الأساسية اللي كيحتاجها الكلاس ديالنا.
- **شنو غادي يوقع إلا حيدناه؟**
  الكومبيلر ماغايعرفش الأنواع وغايعطي أخطاء تجميع مباشرة.

---

### 3. تعريف الكلاس والقسم الخاص (Private)

```cpp
class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int>  _deq;
```
- **شنو كيدير:**
  - كانعرفو الكلاس `PmergeMe`.
  - كانصرحو على جوج ديال الخصائص الخاصة: `_vec` لتخزين وترتيب الأعداد باستعمال `std::vector`، و `_deq` لتخزين وترتيب الأعداد باستعمال `std::deque`.
- **علاش درنا هاد الشي؟**
  تطبيقاً لمبدأ الـ Encapsulation (التغليف). البيانات الداخلية خاصة بالكلاس وما يقدر حتى كود خارجي يعبث بها.
- **شنو غادي يوقع إلا حيدناه؟**
  الكلاس ماغاديش يكون عندها فين تخزن البيانات ديال كل حاوية.

---

### 4. الدوال المساعدة الخاصة بالـ Parsing والخوارزمية

```cpp
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
```
- **شنو كيدير:**
  - `isValidPositiveInteger`: كاتفحص واش النص كيمثل عدد صحيح موجب قطعا وماكيفوتش `INT_MAX`.
  - `sortVector`: الدالة الرئيسية اللي كاتطبق خوارزمية Ford-Johnson على الـ `std::vector`.
  - `generateJacobsthalSequence`: كاتولد ترتيب الإدخال لـ `pend` بالاعتماد على أرقام Jacobsthal.
  - `sortDeque` و `generateJacobsthalSequenceDeque`: نفس المنطق ولكن مخصص للحاوية `std::deque` (طبقاً لملاحظة السوجي بتجنب الدوال العامة).
  - `getCurrentTimeInUs`: دالة `static` مساعدة كترجع الوقت الحالي بالـ Microseconds باستعمال `gettimeofday`.
- **علاش درنا هاد الشي؟**
  تقسيم المهام وتطبيق خوارزمية Ford-Johnson بشكل نظيف ومستقل لكل حاوية.
- **شنو غادي يوقع إلا حيدناه؟**
  الكود غادي يكون مخلط وصعيب يتفهم وصعيب يتقرا أو يتشرح فالمقابلة.

---

### 5. القسم العام (Public) والصيغة القياسية (Orthodox Canonical Form)

```cpp
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    bool run(int argc, char** argv);
};

#endif
```
- **شنو كيدير:**
  - **Constructors / Destructor:** الصيغة القياسية الكانونية المطلوبة فكل كلاس فـ 42 (Default Constructor, Copy Constructor, Copy Assignment Operator, Destructor).
  - `run(int argc, char** argv)`: الدالة الرئيسية اللي كينادي عليها `main.cpp` لتشغيل الفحص والترتيب وطباعة النتائج.
- **علاش درنا هاد الشي؟**
  - ورقة التقييم (Evaluation Sheet) كاتقول صراحة: "If any non-interface class is not in orthodox canonical class form, do not grade this exercise".
  - دالة `run` كاتخلي `main.cpp` بسيط ومختصر جداً كما تنص القواعد.

---

# الجزء 2: ملف التنفيذ `PmergeMe.cpp`

---

### 1. الـ Constructors و الـ Destructor

```cpp
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
```
- **شنو كيدير:**
  - استدعاء المكتبات المساعدة: `<sstream>` لقراءة الأرقام من النصوص، `<algorithm>` لاستعمال `std::lower_bound` و `std::find`، `<iomanip>` لتنسيق طباعة الأرقام العشرية، `<climits>` لمعرفة قيمة `INT_MAX`.
  - تطبيق الـ Orthodox Canonical Form بنسخ وتفريغ الحاويات بكل أمان.
- **علاش درنا هاد الشي؟**
  لضمان احترام قواعد C++98 ومعايير مدرسة 42.

---

### 2. دالة حساب الوقت `getCurrentTimeInUs`

```cpp
double PmergeMe::getCurrentTimeInUs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (static_cast<double>(tv.tv_sec) * 1000000.0) + static_cast<double>(tv.tv_usec);
}
```
- **شنو كيدير:**
  - كيجيب الوقت الحالي ديال النظام باستعمال بنية `struct timeval` ودالة `gettimeofday`.
  - `tv.tv_sec`: الثواني (Seconds)، كنضربوها فـ `1000000.0` باش تولي Microseconds.
  - `tv.tv_usec`: الميكروثانية الإضافية (Microseconds).
  - كنجمعوهم ونرجعو القيمة كـ `double`.
- **علاش درنا هاد الشي؟**
  السوجي طلب قياس الوقت بدقة الـ `us` (Microseconds). دالة `gettimeofday` كتعطي دقة عالية كتناسب هاد الحساب تماماً.
- **شنو غادي يوقع إلا حيدناه؟**
  ما غاديش نقدرو نحسبو الوقت المستغرق بدقة الـ Microseconds ونبينو الفرق بين الحاويات.

---

### 3. دالة فحص المدخلات `isValidPositiveInteger`

```cpp
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
```
- **شنو كيدير:**
  1. كايتأكد أن النص ماشي خاوي.
  2. كيقبل علامة `+` اختيارية فالأول، ولكن إلا كان وراها والو كايرفض.
  3. كيتأكد أن كاع الحروف المتبقية هي أرقام فقط (`isdigit`). هاد الشي كيمنع الأعداد السالبة (حيت علامة `-` غاتترفض هنا).
  4. كايقرا الرقم باستعمال `long long` عبر `stringstream`.
  5. كيتأكد من 4 شروط حاسمة:
     - القراءة نجحات (`!ss.fail()`).
     - تقرا النص كامل بدون حروف شايطة (`ss.eof()`).
     - الرقم موجب قطعا (`num > 0`).
     - الرقم ماكيفوتش الحد الأقصى للأنتجر (`num <= INT_MAX`).
- **علاش درنا هاد الشي؟**
  باش نحميو البروجرام من أي إدخال خبيث أو خاطئ، ومن الـ Integer Overflow.
- **شنو غادي يوقع إلا حيدناه؟**
  البرنامج غايتعامل مع أعداد سالبة أو أعداد خيالية كبر من `INT_MAX` وغايوقع فيه Behavior غير محدد (Undefined Behavior).

---

### 4. توليد ترتيب أرقام Jacobsthal لـ `std::vector`

```cpp
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
```
- **شنو كيدير:**
  - إلا كان الحجم 1 أو 0، الترتيب كيكون خاوي حيت العنصر الأول كيدخل تلقائياً.
  - كانولدو متتالية Jacobsthal: $J_0 = 0, J_1 = 1$, وكل رقم جديد هو:
    `next = jacob[n-1] + 2 * jacob[n-2]`.
  - كنحبسو فاش كايوصل رقم Jacobsthal أو كيفوت `size`.
- **علاش درنا هاد الشي؟**
  هاد الأرقام هي المفتاح الرياضي لخوارزمية Ford-Johnson.

```cpp
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
```
- **شنو كيدير:**
  - كيبني مجموعات الإدخال (Insertion groups) تنازلياً من `limit` حتى لـ `lastIndex + 1`.
  - كيحولها لـ 0-based index (`idx - 1`) ويضيفها لـ `order`.
  - مثلاً، إلا كان `size = 5`: المجموعات كترجع `[2, 1, 4, 3]`. ومع العنصر 0 اللي دخل أولاً، كاع العناصر كيدخلو بالتسلسل المثالي لجاكوبستال!
- **علاش درنا هاد الشي؟**
  لأن الترتيب التنازلي داخل كل مجموعة جاكوبستال هو اللي كايضمن استغلال عدد المقارنات فالـ Binary Search بأفضل مردودية ممكنة.

---

### 5. خوارزمية Ford-Johnson لـ `std::vector` (`sortVector`)

```cpp
void PmergeMe::sortVector(std::vector<int>& arr) {
    if (arr.size() <= 1)
        return;
```
- **شنو كيدير:** الـ Base Case ديال التراجع (Recursion): إلا كان المصفوفة فيها عنصر واحد أو خاوية، فهي مرتبة بالفعل، كنرجعو مباشرة.

```cpp
    // 1. Check for straggler (odd element)
    bool hasStraggler = false;
    int straggler = 0;
    if (arr.size() % 2 != 0) {
        hasStraggler = true;
        straggler = arr.back();
        arr.pop_back();
    }
```
- **شنو كيدير:**
  - إلا كان عدد العناصر فردي، كانعزلو العنصر الأخير فمتغير `straggler` ونحيدوه من المصفوفة مؤقتاً.
- **علاش درنا هاد الشي؟**
  باش يبقى عدد العناصر زوجي ونقدرو نقسموهم لأزواج متساوية.
- **شنو غادي يوقع إلا حيدناه؟**
  العنصر الفردي الأخير غادي يضيع وماغايترتبش فالمصفوفة.

```cpp
    // 2. Pair up elements: pair.first = larger, pair.second = smaller
    std::vector<std::pair<int, int> > pairs;
    pairs.reserve(arr.size() / 2);
    for (size_t i = 0; i < arr.size(); i += 2) {
        if (arr[i] < arr[i + 1])
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
        else
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
    }
```
- **شنو كيدير:**
  - كنجمعو كل عنصرين متجاورين فـ `std::pair`.
  - كانقارنوهم: العنصر الكبير كنحطوه فـ `pair.first` والصغير فـ `pair.second`.
- **علاش درنا هاد الشي؟**
  هادي هي الخطوة الأولى فـ Ford-Johnson، باش نفصلو الكبار على الصغار مع الحفاظ على العلاقة بين كل كبير وشريكو الصغير.

```cpp
    // 3. Extract larger elements
    std::vector<int> larger;
    larger.reserve(pairs.size());
    for (size_t i = 0; i < pairs.size(); ++i) {
        larger.push_back(pairs[i].first);
    }

    // 4. Recursively sort the larger elements
    sortVector(larger);
```
- **شنو كيدير:**
  - كنجمعو كاع العناصر الكبيرة (`pair.first`) فـ vector سميتو `larger`.
  - كانعيطو لـ `sortVector(larger)` تراجعياً باش ترتب العناصر الكبيرة.
- **علاش درنا هاد الشي؟**
  هذا جوهر الـ Merge فـ Ford-Johnson: ترتيب النصف الأكبر تراجعياً أولاً.

```cpp
    // 5. Construct main_chain with sorted larger elements and re-order pend elements
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
```
- **شنو كيدير:**
  - من بعد ما ترتبات `larger`، خاصنا نرتبو الأزواج `pairs` بنفس الترتيب الجديد ديال العناصر الكبيرة!
  - كاندوزو على `larger` المرتبة، ونقلبو على الزوج المقابل ليها، وكنعمرو `main_chain` بالعنصر الكبير و `pend` بالعنصر الصغير الشريك ديالو.
  - الـ `used[j]` كايضمن أن حتى إلا كانو عناصر مكررة (Duplicates)، كل زوج كايتستعمل مرة وحدة بالضبط.
- **علاش درنا هاد الشي؟**
  باش نحافظو على الرابط بين كل $a_i$ وشريكو $b_i$ بدقة متناهية.

```cpp
    // 6. Insert first pend element into main_chain (unconditionally at begin)
    if (!pend.empty()) {
        main_chain.insert(main_chain.begin(), pend[0]);
    }
```
- **شنو كيدير:** كاندخلو العنصر الصغير الأول `pend[0]` مباشرة فبداية `main_chain`.
- **علاش درنا هاد الشي؟**
  لأن $b_1 \le a_1$، وبما أن $a_1$ هو أصغر عنصر كبير فالسلسلة المرتبة، إذن $b_1$ أصغر من كاع عناصر السلسلة بلا حتى شي شك! إذن كاندخلوه فالبداية **بلا ما نضيعو حتى مقارنة واحدة**!
- **شنو غادي يوقع إلا درنا مقارنة؟**
  غادي نضيعو مقارنة زايدة بدون أي فائدة وغانخالفو المبدأ الذهبي لخوارزمية Ford-Johnson.

```cpp
    // 7. Insert remaining pend elements using Jacobsthal order and binary search
    std::vector<size_t> jacobOrder = generateJacobsthalSequence(pend.size());
    for (size_t i = 0; i < jacobOrder.size(); ++i) {
        size_t idx = jacobOrder[i];
        int valToInsert = pend[idx];

        std::vector<int>::iterator limit = std::find(main_chain.begin(), main_chain.end(), larger[idx]);
        std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), limit, valToInsert);
        main_chain.insert(pos, valToInsert);
    }
```
- **شنو كيدير:**
  - كانجيبو ترتيب الإدخال حسب أرقام جاكوبستال.
  - لكل عنصر $b_i$: كانعرفو شريكو $a_i$ فين كاين فـ `main_chain` باستعمال `limit`.
  - كانديرو **Binary Search** باستعمال `std::lower_bound` فقط من البداية حتى لـ `limit`!
  - كاندخلو العنصر فالموضع الصحيح `pos`.
- **علاش حددنا المجال حتى لـ `limit`؟**
  حيت $b_i \le a_i$، فمن المستحيل يكون مكان $b_i$ مورا $a_i$. هاد التحديد كاينقص مجال البحث وكايقلص عدد المقارنات كما تقتضي الخوارزمية.

```cpp
    // 8. Insert straggler if it exists
    if (hasStraggler) {
        std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
        main_chain.insert(pos, straggler);
    }

    arr = main_chain;
}
```
- **شنو كيدير:**
  - إلا كان عندنا عنصر شايط، كاندخلوه فالمكان المناسب ديالو فالسلسلة باستعمال `std::lower_bound`.
  - كانعوضو المصفوفة الأصلية `arr` بالسلسلة المرتبة `main_chain`.

---

### 6. تنفيذ خوارزمية Ford-Johnson لـ `std::deque`

الدالتين `generateJacobsthalSequenceDeque` و `sortDeque` كيطبقو نفس الخوارزمية تماماً، مع نقطة قوة فريدة كتميز `std::deque`:
```cpp
    if (!pend.empty()) {
        main_chain.push_front(pend[0]);
    }
```
- فـ `std::vector` استعملنا `insert(begin(), ...)`.
- فـ `std::deque` استعملنا `push_front(...)`.
- **علاش؟** لأن `std::deque` كتدعم إضافة العناصر فالبداية فـ $O(1)$ بدون الحاجة لتحريك باقي العناصر كما فالمصفوفات المتصلة! هاد الملاحظة مهمة بزاف تشرحها للـ Evaluator.

---

### 7. دالة `run` الشاملة

```cpp
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
```
- **شنو كيدير:** كيدوز على كاع الـ Arguments وكايفرق الكلمات بفراغات (باش يخدم سواء تعطات الأرقام مفروقة فـ `argv` أو مجمعة فـ String واحدة بين علامتي تنصيص).
- إلا لقى أي خطأ كيطبع `Error` فالـ `std::cerr` ويحبس.

```cpp
    // Print Before
    std::cout << "Before:";
    for (size_t i = 0; i < rawInput.size(); ++i) {
        std::cout << " " << rawInput[i];
    }
    std::cout << std::endl;
```
- **شنو كيدير:** كايطبع السلسلة الأصلية قبل أي ترتيب طبقاً للمثال فالسوجي.

```cpp
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
```
- **شنو كيدير:**
  - كيبدا العداد الزمني.
  - كايقرا الأعداد ويعمر `_vec`.
  - كيطبق `sortVector`.
  - كايحبس العداد ويحسب الفارق الزمني.
- **علاش درنا هاد الشي؟**
  احتراماً لملاحظة السوجي رقم 320: قياس الوقت خاص يشمل مرحلة إدارة وتعبئة البيانات ومرحلة الترتيب معاً.

```cpp
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
```
- نفس العملية بالضبط لـ `std::deque`.

```cpp
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
```
- **شنو كيدير:**
  - كيطبع السلسلة بعد الترتيب `After:`.
  - كيطبع الوقت المستغرق لكل Container مع عدد العناصر وصيغة `us` بدقة 5 أرقام عشرية.

---

# الجزء 3: ملف نقطة البداية `main.cpp`

```cpp
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
```
- **شنو كيدير:**
  1. كيتأكد واش كاين على الأقل Argument واحد (`argc >= 2`). إلا ما كاين والو كيطبع `Error` ويرجع 1.
  2. كينشئ كائن `sorter` من نوع `PmergeMe`.
  3. كينادي على `sorter.run(argc, argv)`.
  4. كايرجع 0 عند النجاح أو 1 عند الفشل.
- **علاش الكود ديال `main.cpp` قصير هكذا؟**
  تطبيقاً لقواعد المشروع: `main.cpp` خاص يبقى بسيط ونظيف بزاف، وتقتصر مهمتو على فحص المعطيات واستدعاء الكائن والدالة المناسبة.
