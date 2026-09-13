# شرح الكود سطر بسطر (Line-by-Line Code Explanation) بالدارجة المغربية

---

فهاد الدليل، غانمشيو مع الكود ديال `ex00` سطر بسطر، من أول سطر فـ `BitcoinExchange.hpp`، دوزاناً بـ `BitcoinExchange.cpp`، حتى لآخر سطر فـ `main.cpp`.
كل جزء كود غانشرحو:
1. شنو كيدير؟
2. **علاش درنا هاد الشي؟**
3. **شنو غادي يوقع إلا حيدناه؟**
4. المفاهيم البرمجية الأساسية.

---

# الجزء الأول: ملف الرأس `BitcoinExchange.hpp`

```cpp
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
```
- **شنو كيدير:** هادو كايتسماو **Include Guards**.
- **علاش درنا هاد الشي؟** باش نمنعو الكومبيلر يدخل نفس ملف الـ header جوج مرات فاش نديرو ليه `#include` فبزاف ديال البلايص.
- **شنو غادي يوقع إلا حيدناه؟** إلا درنا `#include` للهيدر فـ جوج ملفات (`main.cpp` و `BitcoinExchange.cpp`)، الكومبيلر غايعطي خطأ ديال `redefinition of class BitcoinExchange` وما غايتكومبيلاش البروجرام.

---

```cpp
#include <iostream>
#include <string>
#include <map>
```
- **شنو كيدير:** كانجيبو المكتبات القياسية اللي غانحتاجوها:
  - `<iostream>`: باش نطبعو الرسائل (`std::cout`, `std::cerr`).
  - `<string>`: باش نخدمو بالنصوص والتواريخ (`std::string`).
  - `<map>`: باش نستعملو حاوية الـ STL المطلوبة `std::map`.
- **علاش درنا هاد الشي؟** هاد المكتبات فيهم التعريفات ديال الأدوات اللي الكلاس ديالنا كايعتمد عليها.
- **شنو غادي يوقع إلا حيدناه؟** الكومبيلر ما غايعرفش شنو كايعني `std::string` ولا `std::map`.

---

```cpp
class BitcoinExchange {
private:
    std::map<std::string, double> _database;
```
- **شنو كيدير:** كانعلنو على الـ attribute الخاص بالكلاس: شجرة خريطة (`std::map`) اللي المفتاح (Key) ديالها هو التاريخ على شكل نص `std::string`، والقيمة (Value) ديالها هي سعر الصرف على شكل عدد حقيقي `double`.
- **علاش درنا هاد الشي؟** باش نخزنو قاعدة البيانات `data.csv` فالذاكرة، ونقدرو نوصلو لأي سعر تاريخ فسرعة $O(\log N)$. ودرناها فـ `private` احتراما لمبدأ الـ **Encapsulation** فـ OOP، بحيث حتى شي كود من برا الكلاس ما يقدر يغير البيانات مباشرة.
- **شنو غادي يوقع إلا حيدناه؟** ما غايكونش عندنا فين نحتفظو بأسعار البيتكوين اللي قريناها من الملف، والبروجرام ما غايعرفش فاش يضرب.

---

```cpp
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& str, double& value) const;
    std::string trim(const std::string& str) const;
```
- **شنو كيدير:** هادو دوال مساعدة خاصة (Private Helper Functions):
  - `isValidDate`: كاتقلب واش التاريخ صالح ومنطقي (العام، الشهر بين 1 و 12، النهار، والسنوات الكبيسة).
  - `isValidValue`: كاتتأكد واش القيمة عدد حقيقي ومحصورة بين 0 و 1000.
  - `trim`: كاتمسح الفراغات الزائدة فالبداية والنهاية ديال السطر.
- **علاش درنا هاد الشي؟** تنظيم الكود وتقسيم المسؤوليات (Single Responsibility Principle). باش كل دالة دير خدمة وحدة محددة ومتقونة.
- **شنو غادي يوقع إلا حيدناه؟** غايولي الكود مخبل فدالة وحدة كبيرة، صعيب تفهمو وصعيب تشرحو للمصحح.

---

```cpp
public:
    BitcoinExchange();
    BitcoinExchange(const std::string& dbPath);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();
```
- **شنو كيدير:** هادو هما الدوال الأربعة الإلزامية ديال **Orthodox Canonical Form**:
  - Default constructor: كايصاوب أوبجيكت خاوي ويشارجي `data.csv`.
  - Constructor with path: كاياخد مسار ملف قاعدة البيانات.
  - Copy constructor: كايصاوب نسخة جديدة من أوبجيكت قديم.
  - Assignment operator: كاينسخ محتوى أوبجيكت لأوبجيكت آخر موجود ديجا.
  - Destructor: كاينظف الذاكرة فاش كايموت الأوبجيكت.
- **علاش درنا هاد الشي؟** قاعدة إجبارية فـ C++ Modules من 42 (الفصل الثاني من السوجي). أي كلاس خاصها تكون Orthodox Canonical Form إلا إذا كان استثناء صريح.
- **شنو غادي يوقع إلا حيدناه؟** المصحح يقدر يحط ليك Flag ديال النورم أو الشكل القياسي للكلاس، وماتحصلش على النقطة.

---

```cpp
    void loadDatabase(const std::string& dbPath);
    void processInput(const std::string& inputPath) const;
};

#endif
```
- **شنو كيدير:** الدوال العامة (Public Methods):
  - `loadDatabase`: كاتقرا ملف `data.csv` وتعمّر الـ `_database`.
  - `processInput`: كاتقرا ملف `input.txt`، تفاليدي السطور، وتحسب وتطبع النتائج.
- **علاش درنا هاد الشي؟** باش الـ `main()` يقدر يعيط عليهم فقط.

---

# الجزء الثاني: ملف التطبيق `BitcoinExchange.cpp`

```cpp
#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
```
- **شنو كيدير:**
  - `<fstream>`: لقراءة الملفات بالـ `std::ifstream`.
  - `<sstream>`: للتعامل مع الـ String Streams.
  - `<cstdlib>`: للدوال بحال `std::strtod` و `std::atoi`.
  - `<cctype>`: للتحقق من الأرقام بالـ `std::isdigit`.

---

```cpp
BitcoinExchange::BitcoinExchange() {
    std::ifstream file("data.csv");
    if (file.is_open()) {
        file.close();
        loadDatabase("data.csv");
    } else {
        loadDatabase("ex00/data.csv");
    }
}
```
- **شنو كيدير:** الـ Default Constructor كايجرب يفتح `data.csv` فالمسار الحالي، وإلا مالقاهش كايجرب فـ `ex00/data.csv`.
- **علاش درنا هاد الشي؟** هادي ذكاء فالكود، باش إلا لونصيتي البروجرام من وسط `ex00/` يخدم، وإلا لونصيتيه من الـ root ديال البروجي يخدم حتى هو بلا مشاكل فالمسار.
- **شنو غادي يوقع إلا حيدناه؟** إلا كنتي فمسار مختلف ودرتي `./ex00/btc input.txt`، البروجرام ما غايعرفش يلقى `data.csv` وغايعطيك خطأ.

---

```cpp
BitcoinExchange::BitcoinExchange(const std::string& dbPath) {
    loadDatabase(dbPath);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        this->_database = other._database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {
}
```
- **شنو كيدير:** تطبيق الـ Orthodox Canonical Form.
  - فالـ Copy constructor والـ `operator=`، الـ `std::map` كايعرف يدير Deep Copy لمحتواه بوحدو بدون أدنى مشكل.
  - فالـ Destructor، الـ `std::map` راسو كايحرر الكاع الـ Nodes ديال الشجرة، فما كنحتاجو نديرو والو بيدينا.

---

```cpp
std::string BitcoinExchange::trim(const std::string& str) const {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}
```
- **شنو كيدير:** دالة كاتمسح الفراغات (spaces, tabs, return carriage) من أول النص ومن آخرو.
- **علاش درنا هاد الشي؟** السطور فالملفات النصية تقدر تجي فيها فراغات عشوائية قبل أو بعد الرموز (بحال `" 2011-01-03 "` أو سطر جاي من Windows فيه `\r\n`). هاد الدالة كاتنقي النص باش نقدر نفيريفوه مزيان.
- **شنو غادي يوقع إلا حيدناه؟** أي فراغ زايد يقدر يخسر الفاليديشن ديال التاريخ أو يخلي `strtod` ماتقراش الرقم مزيان.

---

```cpp
bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < 10; ++i) {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
```
- **شنو كيدير:** كايتأكد من شكل التاريخ (Format):
  - الطول خاصو يكون 10 أحرف بالضبط (`YYYY-MM-DD`).
  - الحرف رقم 4 خاصو يكون عارضة `-`.
  - الحرف رقم 7 خاصو يكون عارضة `-`.
  - باقي الحروف كاملين خاصهم يكونو أرقام إجبارياً من 0 لـ 9.
- **علاش درنا هاد الشي؟** باش نمنعو أي تاريخ معطوب بحال `2011/01/01` ولا `201-1-1` ولا `abcd-ef-gh`.
- **شنو غادي يوقع إلا حيدناه؟** إدخال نصوص عشوائية يقدر يدخل لقاعدة البيانات ويعطي نتائج غالطة أو يسبب Crash.

---

```cpp
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1)
        return false;
```
- **شنو كيدير:** كايقطع السلسلة و كايحول الأجزاء لأرقام صحيحة:
  - `year`: العام (أول 4 أرقام).
  - `month`: الشهر (رقمين).
  - `day`: النهار (رقمين).
  وكايتأكد باللي الشهر بين 1 و 12، والنهار موجب.
- **علاش درنا هاد الشي؟** فالسوجي كاين مثال `2001-42-42` حيث الشهر 42 والنهار 42، هاد الشرط كايفرشخ هاد النوع ديال الأخطاء.

---

```cpp
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == 2 && isLeap)
        daysInMonth[2] = 29;

    if (day > daysInMonth[month])
        return false;

    return true;
}
```
- **شنو كيدير:** كايتحقق من صحة أيام كل شهر مع حساب السنة الكبيسة (Leap Year):
  - الجدول `daysInMonth` كايحدد أقصى عدد أيام لكل شهر.
  - إلا كان العام كبيس (كايتقسم على 4 وماكايتقسمش على 100، أو كايتقسم على 400)، كايولي شهر 2 فيه 29 يوم بلاصة 28 يوم.
  - إلا كان النهار كبر من الماكس ديال داك الشهر، كايعتبر التاريخ غير صالح.
- **علاش درنا هاد الشي؟** باش نضمنو أن تواريخ وهمية بحال `2011-02-29` (سنة ماشي كبيسة) أو `2011-04-31` (أبريل فيه غير 30) يترفضو فوراً.
- **شنو غادي يوقع إلا حيدناه؟** فتقييم الـ Peer Evaluation، المصححين كايجربو `2011-02-29` باش يشوفو واش داير الحساب الفلكي، وإلا ما درتيهش كايسقطوك.

---

```cpp
void BitcoinExchange::loadDatabase(const std::string& dbPath) {
    std::ifstream file(dbPath.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open database file." << std::endl;
        return;
    }

    std::string line;
    if (std::getline(file, line)) {
        if (line.find("date") == std::string::npos) {
            size_t comma = line.find(',');
            if (comma != std::string::npos) {
                std::string date = trim(line.substr(0, comma));
                double rate = std::strtod(trim(line.substr(comma + 1)).c_str(), NULL);
                _database[date] = rate;
            }
        }
    }
```
- **شنو كيدير:** كايفتح ملف `data.csv`. كايقرا السطر الأول: إلا كان هو الهيدر (`date,exchange_rate`) كايتجاوزو، وإلا كان بيانات كايخزنها.

---

```cpp
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        size_t comma = line.find(',');
        if (comma == std::string::npos)
            continue;
        std::string date = trim(line.substr(0, comma));
        double rate = std::strtod(trim(line.substr(comma + 1)).c_str(), NULL);
        _database[date] = rate;
    }
    file.close();
}
```
- **شنو كيدير:** حلقة كتقرا جميع أسطر `data.csv`:
  - كتقلب على الفاصلة `,`.
  - كتقسم السطر لتاريخ وسعر.
  - كتحول السعر لـ `double` باستعمال `std::strtod`.
  - كتحط الزوج فالـ `std::map`: `_database[date] = rate;`.
- **علاش درنا هاد الشي؟** باش نحملو كل البيانات فالذاكرة بشكل منظم ومرتب تلقائياً.

---

```cpp
void BitcoinExchange::processInput(const std::string& inputPath) const {
    std::ifstream file(inputPath.c_str());
    if (!file.is_open()) {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }

    if (_database.empty()) {
        std::cout << "Error: database is empty." << std::endl;
        return;
    }
```
- **شنو كيدير:** كايفتح ملف `input.txt` ويتأكد باللي تحل، وباللي قاعدة البيانات عامرة.
- **علاش درنا هاد الشي؟** إلا كان المسار غالط كايطبع بالضبط الرسالة المطلوبة فالسوجي: `Error: could not open file.`.

---

```cpp
    std::string line;
    if (std::getline(file, line)) {
        std::string trimmedLine = trim(line);
        if (trimmedLine != "date | value") {
            file.seekg(0, std::ios::beg);
        }
    }
```
- **شنو كيدير:** كايقرا السطر الأول ديال ملف الإدخال: إلا كان هو الهيدر `date | value` كايتجاهلو، وإلا ماكانش كايعاود يرجع المؤشر لأول الملف باش يعالجو.

---

```cpp
    while (std::getline(file, line)) {
        std::string trimmedLine = trim(line);
        if (trimmedLine.empty())
            continue;

        size_t pipePos = trimmedLine.find('|');
        if (pipePos == std::string::npos) {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        std::string dateStr = trim(trimmedLine.substr(0, pipePos));
        std::string valStr = trim(trimmedLine.substr(pipePos + 1));
```
- **شنو كيدير:** كايقرا كل سطر:
  - كايقلب على الرمز `|`.
  - إلا مالقاهش (بحال السطر `2001-42-42` فالسوجي)، كايطبع `Error: bad input => [trimmedLine]` ويكمل للسطر التالي.
  - إلا لقاه، كايقطع التاريخ على اليسار والقيمة على اليمين وينقيهم بالفراغات.

---

```cpp
        if (!isValidDate(dateStr)) {
            std::cout << "Error: bad input => " << dateStr << std::endl;
            continue;
        }

        if (valStr.empty()) {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }
```
- **شنو كيدير:** كايتحقق من صلاحية التاريخ بالدالة `isValidDate`، وكايتأكد باللي كاينا قيمة مورا الـ `|`.

---

```cpp
        char* endPtr = NULL;
        double val = std::strtod(valStr.c_str(), &endPtr);
        if (endPtr == valStr.c_str() || *endPtr != '\0') {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }
```
- **شنو كيدير:** كايحول القيمة لـ `double` باستعمال `std::strtod` مع التحقق من الـ `endPtr`.
- **علاش درنا هاد الشي؟** دالة `strtod` فاش كاتسالي التحويل، كتحط مؤشر فـ `endPtr` على أول حرف ماقداتش تحولو. إلا كان `*endPtr != '\0'`، هادا كايعني باللي كاينين حروف مخربقين فالقيمة (مثلاً `12abc` أو `1.2.3`).
- **شنو غادي يوقع إلا حيدناه؟** قيم خاطئة غاتعتبر صحيحة وتخرج أرقام عشوائية.

---

```cpp
        if (val < 0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }

        if (val > 1000) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }
```
- **شنو كيدير:** التحقق من شروط السوجي:
  - إلا كانت القيمة سالبة (`val < 0`): كايطبع `Error: not a positive number.`.
  - إلا كانت القيمة كبر من 1000 (`val > 1000`): كايطبع `Error: too large a number.`.

---

```cpp
        // Find date in database: exact or closest lower date
        std::map<std::string, double>::const_iterator it = _database.upper_bound(dateStr);
        if (it == _database.begin()) {
            std::cout << "Error: bad input => " << dateStr << std::endl;
            continue;
        }

        --it;
        double rate = it->second;
        std::cout << dateStr << " => " << valStr << " = " << (val * rate) << std::endl;
    }
    file.close();
}
```
- **شنو كيدير:** هادا هو **قلب التمرين**:
  1. كايعيط على `_database.upper_bound(dateStr)`: هاد الفانكشن كترجع Iterator كايشير لأول تاريخ فالـ map اللي كبر قطعا من `dateStr`.
  2. إلا كان هاد الـ Iterator هو البداية نيت (`_database.begin()`)، كايعني أن التاريخ اللي دخلتي أصغر حتى من أول نهار فـ DB كاملة، إذن ماكاينش تاريخ سابق ليه، كايطبع `Error: bad input`.
  3. إلا ماكانش هو البداية، كانرجعو بخطوة وحدة بالـ `--it`. دابا هاد الـ `it` كايشير بالضبط لأقرب تاريخ مساوي أو أصغر من التاريخ المطلوب (closest lower date).
  4. كاياخد سعر الصرف `rate = it->second`، ويضربو فالقيمة `val * rate`، ويطبع السطر النهائي.
- **علاش درنا هاد الشي بهاد الطريقة؟**
  هادي هي الطريقة القياسية والأنقى فـ STL C++ باش تجيب Closest Lower Bound فسرعة $O(\log N)$.

---

# الجزء الثالث: ملف البداية `main.cpp`

```cpp
#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    btc.processInput(argv[1]);

    return 0;
}
```
- **شنو كيدير:**
  - كايتأكد من عدد الـ Arguments (`argc == 2`). إلا مادخلتي والو ولا دخلتي كتر من بارامتر، كايطبع `Error: could not open file.` ويرجع `1`.
  - كايصاوب كائن من الكلاس: `BitcoinExchange btc;`. الكونستركتور كايشارجي `data.csv`.
  - كايعيط على `btc.processInput(argv[1]);` باش يعالج الملف.
  - كايسالي البروجرام بنجاح (`return 0;`).
- **علاش `main.cpp` بسيط هكا؟**
  حيت القاعدة رقم 6 فالطلب كاتاكد أن `main.cpp` خاصو يبقى خفيف وظريف، واللوجيك كلو يكون مفرق داخل الكلاس.
