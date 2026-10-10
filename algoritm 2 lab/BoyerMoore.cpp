#include "BoyerMoore.h"

#include <algorithm>
#include <codecvt>
#include <locale>
#include <unordered_map>

static std::u32string toU32(const std::string& utf8)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.from_bytes(utf8);
}

// ---------- Таблица плохого символа ----------
static std::unordered_map<char32_t, int> buildBadCharTable(const std::u32string& pattern)
{
    std::unordered_map<char32_t, int> badChar;

    for (int i = 0; i < static_cast<int>(pattern.size()); ++i)
    {
        badChar[pattern[i]] = i;
    }

    return badChar;
}

static int getBadChar(const std::unordered_map<char32_t, int>& badChar, char32_t c)
{
    auto it = badChar.find(c);
    return (it == badChar.end()) ? -1 : it->second;
}

// ---------- Таблица хорошего суффикса ----------
static std::vector<int> buildGoodSuffixTable(const std::u32string& pattern)
{
    const int m = static_cast<int>(pattern.size());
    std::vector<int> goodSuffix(m + 1, 0);
    std::vector<int> borderPos(m + 1, 0);

    int i = m;
    int j = m + 1;
    borderPos[i] = j;

    while (i > 0)
    {
        while (j <= m && pattern[i - 1] != pattern[j - 1])
        {
            if (goodSuffix[j] == 0)
            {
                goodSuffix[j] = j - i;
            }
            j = borderPos[j];
        }
        --i;
        --j;
        borderPos[i] = j;
    }

    j = borderPos[0];
    for (i = 0; i <= m; ++i)
    {
        if (goodSuffix[i] == 0)
        {
            goodSuffix[i] = j;
        }
        if (i == j)
        {
            j = borderPos[j];
        }
    }

    return goodSuffix;
}

// ---------- Внутренний поиск ----------
static std::vector<int> search(const std::u32string& text,
    const std::u32string& pattern,
    int start,
    int stop)
{
    std::vector<int> result;

    const int n = static_cast<int>(text.size());
    const int m = static_cast<int>(pattern.size());

    if (m == 0 || n == 0 || start < 0 || stop >= n || start > stop)
    {
        return result;
    }

    const auto badChar = buildBadCharTable(pattern);
    const auto goodSuffix = buildGoodSuffixTable(pattern);

    const int lastStart = stop - m + 1;

    int shift = start;
    while (shift <= lastStart)
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j])
        {
            --j;
        }

        if (j < 0)
        {
            result.push_back(shift);
            shift += goodSuffix[0];
        }
        else
        {
            const int badCharShift = j - getBadChar(badChar, text[shift + j]);
            const int goodSuffixShift = goodSuffix[j + 1];

            shift += std::max(1, std::max(badCharShift, goodSuffixShift));
        }
    }

    return result;
}

// ---------- 1. Первое вхождение ----------
int findFirst(const std::string& text, const std::string& pattern)
{
    const std::u32string u32text = toU32(text);
    const std::u32string u32pattern = toU32(pattern);

    const std::vector<int> all =
        search(u32text, u32pattern, 0, static_cast<int>(u32text.size()) - 1);

    return all.empty() ? -1 : all.front();
}

// ---------- 2. Все вхождения ----------
std::vector<int> findAll(const std::string& text, const std::string& pattern)
{
    const std::u32string u32text = toU32(text);

    return search(u32text, toU32(pattern), 0,
        static_cast<int>(u32text.size()) - 1);
}

// ---------- 3. Все вхождения в диапазоне ----------
std::vector<int> findAll(const std::string& text,
    const std::string& pattern,
    int begin,
    int end)
{
    const std::u32string u32text = toU32(text);

    return search(u32text, toU32(pattern), begin, end);
}