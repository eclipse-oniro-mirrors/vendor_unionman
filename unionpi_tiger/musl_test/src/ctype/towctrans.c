#include <wctype.h>
#ifndef __LITEOS__
#include <ctype.h>
#include <dlfcn.h>
#include <stddef.h>
#endif
#ifdef FEATURE_ICU_LOCALE_TMP
#include <locale.h>
#include "locale_impl.h"
#endif

static const unsigned char tab[];

static const unsigned char rulebases[512];
static const int rules[];

static const unsigned char exceptions[][2];

#include "casemap.h"

static int casemap(unsigned c, int dir)
{
	unsigned b, x, y, v, rt, xb, xn;
	int r, rd, c0 = c;

	if (c >= 0x20000) return c;

	b = c>>8;
	c &= 255;
	x = c/3;
	y = c%3;

	/* lookup entry in two-level base-6 table */
	v = tab[tab[b]*86+x];
	static const int mt[] = { 2048, 342, 57 };
	v = (v*mt[y]>>11)%6;

	/* use the bit vector out of the tables as an index into
	 * a block-specific set of rules and decode the rule into
	 * a type and a case-mapping delta. */
	r = rules[rulebases[b]+v];
	rt = r & 255;
	rd = r >> 8;

	/* rules 0/1 are simple lower/upper case with a delta.
	 * apply according to desired mapping direction. */
	if (rt < 2) return c0 + (rd & -(rt^dir));

	/* binary search. endpoints of the binary search for
	 * this block are stored in the rule delta field. */
	xn = rd & 0xff;
	xb = (unsigned)rd >> 8;
	while (xn) {
		unsigned try = exceptions[xb+xn/2][0];
		if (try == c) {
			r = rules[exceptions[xb+xn/2][1]];
			rt = r & 255;
			rd = r >> 8;
			if (rt < 2) return c0 + (rd & -(rt^dir));
			/* Hard-coded for the four exceptional titlecase */
			return c0 + (dir ? -1 : 1);
		} else if (try > c) {
			xn /= 2;
		} else {
			xb += xn/2;
			xn -= xn/2;
		}
	}
	return c0;
}

#ifndef __LITEOS__
static void* g_hmicu_handle = NULL;
static wint_t (*g_hm_ucase_toupper)(wint_t);

static void* find_hmicu_symbol(const char* symbol_name) {
  if (!g_hmicu_handle) {
	g_hmicu_handle = dlopen("libhmicuuc.z.so", RTLD_LOCAL);
  }
  return g_hmicu_handle ? dlsym(g_hmicu_handle, symbol_name) : NULL;
}
#endif

wint_t towlower(wint_t wc)
{
#ifndef __LITEOS__
	if (wc < 0x80) {
		if (wc >= 'A' && wc <= 'Z') return wc | 0x20;
		return wc;
	}
#endif
	return casemap(wc, 0);
}

wint_t towupper(wint_t wc)
{
#ifndef __LITEOS__
	if (wc < 0x80) {
		if (wc >= 'a' && wc <= 'z') return wc ^ 0x20;
		return wc;
	}
	if (!g_hm_ucase_toupper) {
		typedef wint_t (*f)(wint_t);
		g_hm_ucase_toupper = (f)find_hmicu_symbol("ucase_toupper_72");
	}
	return g_hm_ucase_toupper ? g_hm_ucase_toupper(wc) : casemap(wc, 1);
#else
	return casemap(wc, 1);
#endif
}

wint_t __towupper_l(wint_t c, locale_t l)
{
#ifdef FEATURE_ICU_LOCALE_TMP
	if (l && l->cat[LC_CTYPE] && l->cat[LC_CTYPE]->flag == ICU_VALID) {
		get_icu_symbol(ICU_I18N, &(g_icu_opt_func.u_toupper), ICU_UCHAR_TOUPPER_SYMBOL);
		if (g_icu_opt_func.u_toupper) {
			return g_icu_opt_func.u_toupper(c);
		}
	}
#endif
	return towupper(c);
}

wint_t __towlower_l(wint_t c, locale_t l)
{
#ifdef FEATURE_ICU_LOCALE_TMP
	if (l && l->cat[LC_CTYPE] && l->cat[LC_CTYPE]->flag == ICU_VALID) {		
		get_icu_symbol(ICU_I18N, &(g_icu_opt_func.u_tolower), ICU_UCHAR_TOLOWER_SYMBOL);
		if (g_icu_opt_func.u_tolower) {
			return g_icu_opt_func.u_tolower(c);
		}
	}
#endif
	return towlower(c);
}

weak_alias(__towupper_l, towupper_l);
weak_alias(__towlower_l, towlower_l);
