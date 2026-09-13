# وثيقة الاختبارات والتصحيح الذاتي (Self-Test & Correction Documentation) - ex01 (RPN)

---

## 1. نتيجة الكومبيلاسيون النهائية (Final Compilation Result)

تم فحص الكومبيلاسيون بالأعلام الإلزامية الصارمة:
```bash
c++ -Wall -Wextra -Werror -std=c++98 main.cpp RPN.cpp -o RPN
```

- **النتيجة:** دازت بنجاح تام وبدون أي Warning وبدون أي Error:
  ```text
  c++ -Wall -Wextra -Werror -std=c++98 -c main.cpp -o main.o
  c++ -Wall -Wextra -Werror -std=c++98 -c RPN.cpp -o RPN.o
  c++ -Wall -Wextra -Werror -std=c++98 main.o RPN.o -o RPN
  ```
- **اختبار عدم إعادة الربط (No relink):**
  ```bash
  make
  make: Nothing to be done for 'all'.
  ```

---

## 2. جدول الاختبارات التفصيلي (Detailed Test Cases)

| # | نوع الاختبار | الأمر المستعمل (Command) | النتيجة المتوقعة (Expected) | النتيجة المحصلة (Actual) | الحالة (Status) |
|---|---|---|---|---|---|
| 1 | مثال السوجي 1 | `./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"` | `42` | `42` | ✅ ناجح |
| 2 | مثال السوجي 2 | `./RPN "7 7 * 7 -"` | `42` | `42` | ✅ ناجح |
| 3 | مثال السوجي 3 | `./RPN "1 2 * 2 / 2 * 2 4 - +"` | `0` | `0` | ✅ ناجح |
| 4 | مثال السوجي (أقواس مرفوضة) | `./RPN "(1 + 1)"` | `Error` | `Error` | ✅ ناجح |
| 5 | ورقة التقييم 1 | `./RPN "9 8 * 4 * 4 / 2 + 9 - 8 - 8 - 1 - 6 -"` | `42` | `42` | ✅ ناجح |
| 6 | ورقة التقييم 2 | `./RPN "1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 /"` | `15` | `15` | ✅ ناجح |
| 7 | قسمة على صفر (Division by zero) | `./RPN "5 0 /"` | `Error` | `Error` | ✅ ناجح |
| 8 | بدون أرقام كافية | `./RPN "+"` | `Error` | `Error` | ✅ ناجح |
| 9 | رقم واحد وعملية | `./RPN "5 +"` | `Error` | `Error` | ✅ ناجح |
| 10 | أرقام شايطة بلا عملية | `./RPN "5 6"` | `Error` | `Error` | ✅ ناجح |
| 11 | أرقام شايطة كتر من المطلوب | `./RPN "1 2 3 +"` | `Error` | `Error` | ✅ ناجح |
| 12 | حروف ورموز غير مدعومة | `./RPN "a b +"` | `Error` | `Error` | ✅ ناجح |
| 13 | سلسلة نصية خاوية | `./RPN ""` | `Error` | `Error` | ✅ ناجح |
| 14 | سلسلة كلها فراغات | `./RPN "   "` | `Error` | `Error` | ✅ ناجح |
| 15 | رقم فردي واحد فقط | `./RPN "5"` | `5` | `5` | ✅ ناجح |
| 16 | نتيجة سالبة صحيحة | `./RPN "3 5 -"` | `-2` | `-2` | ✅ ناجح |
| 17 | رقم كبر من 9 فالمعطيات | `./RPN "12 3 +"` | `Error` | `Error` | ✅ ناجح |
| 18 | عدد سالب فالمعطيات | `./RPN "-1 2 +"` | `Error` | `Error` | ✅ ناجح |
| 19 | بدون أي Argument | `./RPN` | `Error` | `Error` | ✅ ناجح |
| 20 | كتر من Argument واحد | `./RPN "1 2 +" "3 4 +"` | `Error` | `Error` | ✅ ناجح |

---

## 3. فحص تسريب الذاكرة (Memory Leaks Check - Valgrind)

تم تشغيل الأمر:
```bash
valgrind --leak-check=full ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

- **تقرير Valgrind:**
  ```text
  == HEAP SUMMARY:
  ==     in use at exit: 0 bytes in 0 blocks
  ==   total heap usage: 8 allocs, 8 frees, 75,956 bytes allocated
  == 
  == All heap blocks were freed -- no leaks are possible
  == 
  == ERROR SUMMARY: 0 errors from 0 contexts
  ```
- **الخلاصة:** زيرو تسريب (0 leaks) وزيرو أخطاء ذاكرة (0 errors).

---

## 4. الأخطاء المكتشفة وطريقة حلها (Discovered Errors & Fixes)

1. **التحقق من ترتيب المعاملات (Operand Order):**
   - **المشكلة:** فـ Stack، أول قيمة كاتخرج بـ `pop()` هي المعامل الثاني (Right operand) ماشي الأول.
   - **الحل:** تم تخزين القيمة الأولى فـ `b` والثانية فـ `a` وإجراء العملية كالتالي: `a - b` و `a / b`.
2. **القسمة على صفر:**
   - **المشكلة:** فحص القسمة على صفر خاصو يكون قبل إجراء أي عملية تفادياً لـ `Floating point exception / SIGFPE`.
   - **الحل:** تم وضع شرط صريح `if (b == 0) return false;` داخل `executeOperation`.
3. **تحديد مخرج الأخطاء:**
   - **المشكلة:** السوجي يطلب صراحة طباعة رسائل الخطأ على `std::cerr` وليس `std::cout`.
   - **الحل:** توجيه جميع رسائل `Error` لـ `std::cerr`.
