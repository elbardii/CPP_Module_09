# وثيقة الاختبارات والتصحيح الذاتي (Self-Test & Correction Documentation) - ex02 (PmergeMe)

---

## 1. نتيجة الكومبيلاسيون النهائية (Final Compilation Result)

تم فحص الكومبيلاسيون بالأعلام الإلزامية الصارمة:
```bash
c++ -Wall -Wextra -Werror -std=c++98 main.cpp PmergeMe.cpp -o PmergeMe
```

- **النتيجة:** دازت بنجاح تام وبدون أي Warning وبدون أي Error:
  ```text
  c++ -Wall -Wextra -Werror -std=c++98 -c main.cpp -o main.o
  c++ -Wall -Wextra -Werror -std=c++98 -c PmergeMe.cpp -o PmergeMe.o
  c++ -Wall -Wextra -Werror -std=c++98 main.o PmergeMe.o -o PmergeMe
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
| 1 | مثال السوجي الأساسي | `./PmergeMe 3 5 9 7 4` | مرتب: `3 4 5 7 9` مع توقيت الحاويتين | `After: 3 4 5 7 9` | ✅ ناجح |
| 2 | عدد سالب فالمعطيات | `./PmergeMe "-1" "2"` | `Error` | `Error` | ✅ ناجح |
| 3 | عدد سالب مدمج | `./PmergeMe "3 5 -9 7"` | `Error` | `Error` | ✅ ناجح |
| 4 | حرف مع رقم | `./PmergeMe "abc" "2"` | `Error` | `Error` | ✅ ناجح |
| 5 | رمز غير مدعوم | `./PmergeMe "12 34 abc"` | `Error` | `Error` | ✅ ناجح |
| 6 | نص فارغ | `./PmergeMe ""` | `Error` | `Error` | ✅ ناجح |
| 7 | بدون أي معطيات | `./PmergeMe` | `Error` | `Error` | ✅ ناجح |
| 8 | تجاوز الحد الأقصى (INT_MAX Overflow) | `./PmergeMe "2147483648"` | `Error` | `Error` | ✅ ناجح |
| 9 | الصفر كمدخل | `./PmergeMe "0"` | `Error` | `Error` | ✅ ناجح |
| 10 | أعداد مكررة (Duplicates) | `./PmergeMe 4 2 7 2 9 4 1 5` | `After: 1 2 2 4 4 5 7 9` | `After: 1 2 2 4 4 5 7 9` | ✅ ناجح |
| 11 | سلسلة مرتبة أصلاً | `./PmergeMe 1 2 3 4 5 6` | `After: 1 2 3 4 5 6` | `After: 1 2 3 4 5 6` | ✅ ناجح |
| 12 | سلسلة مرتبة عكسياً | `./PmergeMe 6 5 4 3 2 1` | `After: 1 2 3 4 5 6` | `After: 1 2 3 4 5 6` | ✅ ناجح |
| 13 | عنصر واحد فقط | `./PmergeMe 42` | `After: 42` | `After: 42` | ✅ ناجح |
| 14 | عنصرين فقط | `./PmergeMe 42 21` | `After: 21 42` | `After: 21 42` | ✅ ناجح |
| 15 | ثلاثة عناصر (فردي) | `./PmergeMe 10 30 20` | `After: 10 20 30` | `After: 10 20 30` | ✅ ناجح |
| 16 | اختبار 3000 رقم عشوائي متميز | `./PmergeMe $(shuf -i 1-100000 -n 3000 \| tr "\n" " ")` | سلسلة مرتبة 100% مطابقة لـ `sort -n` | `SORT_OK: Length: 3000` | ✅ ناجح |
| 17 | اختبار 3000 رقم مع تكرار | `./PmergeMe $(shuf -r -i 1-1000 -n 3000 \| tr "\n" " ")` | سلسلة مرتبة 100% مع التكرارات | `SORT_OK: Length: 3000` | ✅ ناجح |
| 18 | اختبار 5000 رقم عشوائي | `./PmergeMe $(shuf -i 1-100000 -n 5000 \| tr "\n" " ")` | سلسلة مرتبة 100% بسرعة فائقة | `SORT_OK: Length: 5000` | ✅ ناجح |

---

## 3. فحص تسريب الذاكرة (Memory Leaks Check - Valgrind)

### اختبار الحالة العادية:
```bash
valgrind --leak-check=full ./PmergeMe 3 5 9 7 4
```

- **تقرير Valgrind:**
```text
==11460== HEAP SUMMARY:
==11460==     in use at exit: 0 bytes in 0 blocks
==11460==   total heap usage: 54 allocs, 54 frees, 84,116 bytes allocated
==11460== 
==11460== All heap blocks were freed -- no leaks are possible
==11460== 
==11460== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### اختبار حالة الخطأ:
```bash
valgrind --leak-check=full ./PmergeMe "-1" "2"
```

- **تقرير Valgrind:**
```text
==11527== HEAP SUMMARY:
==11527==     in use at exit: 0 bytes in 0 blocks
==11527==   total heap usage: 3 allocs, 3 frees, 74,304 bytes allocated
==11527== 
==11527== All heap blocks were freed -- no leaks are possible
==11527== 
==11527== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

**الخلاصة:** البرنامج نظيف تماماً وخالي من أي تسريب للذاكرة (0 leaks).
