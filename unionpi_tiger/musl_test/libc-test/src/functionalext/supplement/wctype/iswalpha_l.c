/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <wctype.h>
#include <locale.h>
#include <stdlib.h>
#include "functionalext.h"

const int COUNT = 52;
const int SIZE = 128;
const int BPMF_SIZE = 43;
const int RET_TRUE = 1;
const int RET_FALSE = 0;

/**
 * @tc.name      : iswalpha_l_0100
 * @tc.desc      : Verify iswalpha_l process success when using the en_US.UTF-8 character set.
 *                 The parameter c is an English letter,
 *                 and it is judged that the input character is a letter.
 * @tc.level     : Level 0
 */

void iswalpha_l_0100(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "en_US.UTF-8", NULL);
    const char *str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != '\0') {
        ret = iswalpha_l(*p, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}



/**
 * @tc.name      : iswalpha_l_0200
 * @tc.desc      : Verify iswalpha_l process fail when using the en_US.UTF-8 character set.
 *                 The parameter c is an English number,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_0200(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "en_US.UTF-8", NULL);
    const char *str = "0123456789";
    const char *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != '\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_0300
 * @tc.desc      : Verify iswalpha_l process fail when using the en_US.UTF-8 character set.
 *                 The parameter c is an special character,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_0300(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "en_US.UTF-8", NULL);
    const char *str = "@#$%^&";
    const char *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != '\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_0400
 * @tc.desc      : Verify iswalpha_l process success when using the en_US.UTF-8 character set.
 *                 Determine the number of letters in the ascii code table.
 * @tc.level     : Level 1
 */
void iswalpha_l_0400(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "en_US.UTF-8", NULL);
    int total = 0;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    for (int i = 0; i < SIZE; i++) {
        ret = iswalpha_l(i, m_locale);
        if (ret) {
            total++;
        }
    }

    EXPECT_EQ(__FUNCTION__, total, COUNT);
    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_0500
 * @tc.desc      : Verify iswalpha_l process success when using the en_US.UTF-8 character set.
 *                 The parameter c is an wide English character,
 *                 and it is judged that the input wide character is a letter.
 * @tc.level     : Level 0
 */
void iswalpha_l_0500(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "en_US.UTF-8", NULL);
    const wchar_t *str = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_0600
 * @tc.desc      : Verify iswalpha_l process fail when using the en_US.UTF-8 character set.
 *                 The parameter c is an wide English character,
 *                 and it is judged that the input wide character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_0600(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "en_US.UTF-8", NULL);
    const wchar_t *str = L"0123456789";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_0700
 * @tc.desc      : Verify iswalpha_l process fail when using the en_US.UTF-8 character set.
 *                 The parameter c is an wide English character,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_0700(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "en_US.UTF-8", NULL);
    const wchar_t *str = L"@#$%^&";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_0800
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN character set.
 *                 The parameter c is an English letter,
 *                 and it is judged that the input character is a letter.
 * @tc.level     : Level 0
 */
void iswalpha_l_0800(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    const char *str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != '\0') {
        ret = iswalpha_l(*p, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_0900
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN character set.
 *                 The parameter c is an English number,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_0900(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    const char *str = "0123456789";
    const char *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != '\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_1000
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN character set.
 *                 The parameter c is an special character,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_1000(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    const char *str = "@#$%^&";
    const char *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != '\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_1100
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN character set.
 *                 Determine the number of letters in the ascii code table.
 * @tc.level     : Level 1
 */
void iswalpha_l_1100(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    int total = 0;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    for (int i = 0; i < SIZE; i++) {
        ret = iswalpha_l(i, m_locale);
        if (ret) {
            total++;
        }
    }

    EXPECT_EQ(__FUNCTION__, total, COUNT);
    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_1200
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN character set.
 *                 The parameter c is an wide English character,
 *                 and it is judged that the input wide character is a letter.
 * @tc.level     : Level 0
 */
void iswalpha_l_1200(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    const wchar_t *str = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_1300
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN character set.
 *                 The parameter c is an wide English character,
 *                 and it is judged that the input wide character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_1300(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    const wchar_t *str = L"0123456789";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_1400
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN character set.
 *                 The parameter c is an wide English character,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_1400(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    const wchar_t *str = L"@#$%^&";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_1500
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN character set.
 *                 The characters are not in the en_US.UTF-8 and zh_CN character sets,
 *                 and it is judged that the input character is a letter.
 * @tc.level     : Level 0
 */
void iswalpha_l_1500(void)
{
    int ret = RET_FALSE;
    int i = 0;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    //GREEK characters(U+03AC - U+03CE)
    //GREEK SMALL LETTER
    for (i = 0x03AC; i <= 0x03CE; i++) {
        ret = iswalpha_l(i, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing unicode %04x\n", __FUNCTION__, i);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
    }

    //ARMENIAN characters(U+0531 - U+0556)
    //ARMENIAN CAPITAL LETTER
    for (i = 0x0531; i <= 0x0556; i++) {
        ret = iswalpha_l(i, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing unicode %04x\n", __FUNCTION__, i);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_1600
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN character set.
 *                 The characters are not in the en_US.UTF-8 and zh_CN character sets,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_1600(void)
{
    int ret = RET_FALSE;
    int i = 0;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    //GREEK TONOS
    //GREEK DIALYTIKA TONOS
    for (i = 0x0384; i <= 0x0385; i++) {
        ret = iswalpha_l(i, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing unicode %04x\n", __FUNCTION__, i);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
    }

    //ARMENIAN APOSTROPHE
    //ARMENIAN EMPHASIS MARK
    //ARMENIAN EXCLAMATION MARK
    //ARMENIAN COMMA
    //ARMENIAN QUESTION MARK
    //ARMENIAN ABBREVIATION MARK
    for (i = 0x055A; i <= 0x055F; i++) {
        ret = iswalpha_l(i, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing unicode %04x\n", __FUNCTION__, i);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_1700
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN character set.
 *                 BOPOMOFO LETTER in the unicode is letter.
 * @tc.level     : Level 1
 */
void iswalpha_l_1700(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    int total = 0;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    //0x3105(BOPOMOFO LETTER B) ~ 0x312f(BOPOMOFO LETTER NN)
    for (int i = 0x3105; i <= 0x312f; i++) {
        ret = iswalpha_l(i, m_locale);
        if (ret) {
            total++;
        } else {
            t_printf("Test case %s failed i = 0x%x\n", __FUNCTION__, i);
        }
    }

    EXPECT_EQ(__FUNCTION__, total, BPMF_SIZE);
    freelocale(m_locale);
    m_locale = NULL;
}

/**
 * @tc.name      : iswalpha_l_1800
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN character set.
 *                 The parameter c is an wide CYRILLIC LETTER,
 *                 and it is judged that the input wide character is a are CYRILLIC LETTER.
 * @tc.level     : Level 0
 */
void iswalpha_l_1800(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    const wchar_t *str = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}

/**
 * @tc.name      : iswalpha_l_1900
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN character set.
 *                 The parameter c is an wide GREEK LETTER,
 *                 and it is judged that the input wide character is a are GREEK LETTER.
 * @tc.level     : Level 0
 */
void iswalpha_l_1900(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    const wchar_t *str = L"αβγδεζηθικλμνξοπρστυφχψωΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}

/**
 * @tc.name      : iswalpha_l_2000
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN character set.
 *                 The parameter c is an special character,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_2000(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN", NULL);
    const wchar_t *str = L"₽&$€£¥₩";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}

/**
 * @tc.name      : iswalpha_l_2100
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN.UTF-8 character set.
 *                 The parameter c is an English letter,
 *                 and it is judged that the input character is a letter.
 * @tc.level     : Level 0
 */
void iswalpha_l_2100(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    const char *str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != '\0') {
        ret = iswalpha_l(*p, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_2200
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN.UTF-8 character set.
 *                 The parameter c is an English number,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_2200(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    const char *str = "0123456789";
    const char *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != '\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_2300
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN.UTF-8 character set.
 *                 The parameter c is an special character,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_2300(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    const char *str = "@#$%^&";
    const char *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != '\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_2400
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN.UTF-8 character set.
 *                 Determine the number of letters in the ascii code table.
 * @tc.level     : Level 1
 */
void iswalpha_l_2400(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    int total = 0;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    for (int i = 0; i < SIZE; i++) {
        ret = iswalpha_l(i, m_locale);
        if (ret) {
            total++;
        }
    }

    EXPECT_EQ(__FUNCTION__, total, COUNT);
    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_2500
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN.UTF-8 character set.
 *                 The parameter c is an wide English character,
 *                 and it is judged that the input wide character is a letter.
 * @tc.level     : Level 0
 */
void iswalpha_l_2500(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    const wchar_t *str = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_2600
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN.UTF-8 character set.
 *                 The parameter c is an wide English character,
 *                 and it is judged that the input wide character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_2600(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    const wchar_t *str = L"0123456789";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_2700
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN.UTF-8 character set.
 *                 The parameter c is an wide English character,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_2700(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    const wchar_t *str = L"@#$%^&";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_2800
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN.UTF-8 character set.
 *                 The characters are not in the en_US.UTF-8 and zh_CN.UTF-8 character sets,
 *                 and it is judged that the input character is a letter.
 * @tc.level     : Level 0
 */
void iswalpha_l_2800(void)
{
    int ret = RET_FALSE;
    int i = 0;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    //GREEK characters(U+03AC - U+03CE)
    //GREEK SMALL LETTER
    for (i = 0x03AC; i <= 0x03CE; i++) {
        ret = iswalpha_l(i, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing unicode %04x\n", __FUNCTION__, i);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
    }

    //ARMENIAN characters(U+0531 - U+0556)
    //ARMENIAN CAPITAL LETTER
    for (i = 0x0531; i <= 0x0556; i++) {
        ret = iswalpha_l(i, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing unicode %04x\n", __FUNCTION__, i);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_2900
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN.UTF-8 character set.
 *                 The characters are not in the en_US.UTF-8 and zh_CN.UTF-8 character sets,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_2900(void)
{
    int ret = RET_FALSE;
    int i = 0;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    //GREEK TONOS
    //GREEK DIALYTIKA TONOS
    for (i = 0x0384; i <= 0x0385; i++) {
        ret = iswalpha_l(i, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing unicode %04x\n", __FUNCTION__, i);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
    }

    //ARMENIAN APOSTROPHE
    //ARMENIAN EMPHASIS MARK
    //ARMENIAN EXCLAMATION MARK
    //ARMENIAN COMMA
    //ARMENIAN QUESTION MARK
    //ARMENIAN ABBREVIATION MARK
    for (i = 0x055A; i <= 0x055F; i++) {
        ret = iswalpha_l(i, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing unicode %04x\n", __FUNCTION__, i);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
    }

    freelocale(m_locale);
    m_locale = NULL;
}


/**
 * @tc.name      : iswalpha_l_3000
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN.UTF-8 character set.
 *                 BOPOMOFO LETTER in the unicode is letter.
 * @tc.level     : Level 1
 */
void iswalpha_l_3000(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    int total = 0;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    //0x3105(BOPOMOFO LETTER B) ~ 0x312f(BOPOMOFO LETTER NN)
    for (int i = 0x3105; i <= 0x312f; i++) {
        ret = iswalpha_l(i, m_locale);
        if (ret) {
            total++;
        } else {
            t_printf("Test case %s failed i = 0x%x\n", __FUNCTION__, i);
        }
    }

    EXPECT_EQ(__FUNCTION__, total, BPMF_SIZE);
    freelocale(m_locale);
    m_locale = NULL;
}

/**
 * @tc.name      : iswalpha_l_3100
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN.UTF-8 character set.
 *                 The parameter c is an wide CYRILLIC LETTER,
 *                 and it is judged that the input wide character is a are CYRILLIC LETTER.
 * @tc.level     : Level 0
 */
void iswalpha_l_3100(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    const wchar_t *str = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}

/**
 * @tc.name      : iswalpha_l_3200
 * @tc.desc      : Verify iswalpha_l process success when using the zh_CN.UTF-8 character set.
 *                 The parameter c is an wide GREEK LETTER,
 *                 and it is judged that the input wide character is a are GREEK LETTER.
 * @tc.level     : Level 0
 */
void iswalpha_l_3200(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    const wchar_t *str = L"αβγδεζηθικλμνξοπρστυφχψωΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (!ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_TRUE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}

/**
 * @tc.name      : iswalpha_l_3300
 * @tc.desc      : Verify iswalpha_l process fail when using the zh_CN.UTF-8 character set.
 *                 The parameter c is an special character,
 *                 and it is judged that the input character is not a letter.
 * @tc.level     : Level 2
 */
void iswalpha_l_3300(void)
{
    int ret = RET_FALSE;
    locale_t m_locale = newlocale(LC_ALL_MASK, "zh_CN.UTF-8", NULL);
    const wchar_t *str = L"₽&$€£¥₩";
    const wchar_t *p = str;

    if (!m_locale) {
        t_printf("Test case %s failed to call function newlocale\n", __FUNCTION__);
        EXPECT_NE(__FUNCTION__, ret, RET_FALSE);
        return ;
    }

    while (p && *p != L'\0') {
        ret = iswalpha_l(*p, m_locale);
        if (ret) {
            t_printf("Test case %s failed while testing character %c\n", __FUNCTION__, *p);
        }
        EXPECT_EQ(__FUNCTION__, ret, RET_FALSE);
        p++;
    }

    freelocale(m_locale);
    m_locale = NULL;
}

int main(void)
{
    iswalpha_l_0100();
    iswalpha_l_0200();
    iswalpha_l_0300();
    iswalpha_l_0400();
    iswalpha_l_0500();
    iswalpha_l_0600();
    iswalpha_l_0700();
    iswalpha_l_0800();
    iswalpha_l_0900();
    iswalpha_l_1000();
    iswalpha_l_1100();
    iswalpha_l_1200();
    iswalpha_l_1300();
    iswalpha_l_1400();
    iswalpha_l_1500();
    iswalpha_l_1600();
    iswalpha_l_1700();
    iswalpha_l_1800();
    iswalpha_l_1900();
    iswalpha_l_2000();
    iswalpha_l_2100();
    iswalpha_l_2200();
    iswalpha_l_2300();
    iswalpha_l_2400();
    iswalpha_l_2500();
    iswalpha_l_2600();
    iswalpha_l_2700();
    iswalpha_l_2800();
    iswalpha_l_2900();
    iswalpha_l_3000();
    iswalpha_l_3100();
    iswalpha_l_3200();
    iswalpha_l_3300();
    return t_status;
}
