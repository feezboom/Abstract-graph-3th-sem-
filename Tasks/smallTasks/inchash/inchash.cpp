//
// Created by avk on 17.12.15.
//

#include "inchash.h"
#include <cmath>

// https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%A0%D0%B0%D0%B1%D0%B8%D0%BD%D0%B0_%E2%80%94_%D0%9A%D0%B0%D1%80%D0%BF%D0%B0
// Одна популярная и эффективная кольцевая хэш-функция
// интерпретирует каждую подстроку как число в некоторой системе счисления,
// основание которой является большим простым числом.

long hashFoo(string s) {
    long long hash = 0;
    static const int p = 101;
    for (int i = 0; i < s.length(); ++i)
        hash += ((int)s[i])*pow(p, i);
    return hash;
}